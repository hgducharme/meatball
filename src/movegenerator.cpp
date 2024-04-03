#include "movegenerator.h"

#include "move.h"
#include "utils.h"
#include "attacktables.h"

#include <optional>

MoveVector LegalMoveGenerator::generatePsuedoLegalMoves(const Chessboard & gameState) const
{
    MoveVector pawnMoves = getMovesByPiece(PieceType::PAWN, gameState);
    MoveVector knightMoves = getMovesByPiece(PieceType::KNIGHT, gameState);
    MoveVector bishopMoves = getMovesByPiece(PieceType::BISHOP, gameState);
    MoveVector rookMoves = getMovesByPiece(PieceType::ROOK, gameState);
    MoveVector queenMoves = getMovesByPiece(PieceType::QUEEN, gameState);
    MoveVector kingMoves = getMovesByPiece(PieceType::KING, gameState);

    // Concatenate all move vectors into one
    MoveVector psuedoLegalMoves;
    for (auto v : { &pawnMoves, &knightMoves, &bishopMoves, &rookMoves, &queenMoves, &kingMoves })
    {
        psuedoLegalMoves.insert(psuedoLegalMoves.end(), (*v).begin(), (*v).end());
    }

    return psuedoLegalMoves;
}

// TODO: This currently doesn't handle en pessant, castling.
MoveVector LegalMoveGenerator::getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const
{
    /*
     * This function will return all of the possible moves for a piece without considering if it puts the king in check
     * and for pawns will return their attack moves even if there's nothing to attack.
    */

    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Color nonActivePlayer = gameState.getNonActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerPieceType = gameState.getBitboard(activePlayer, pieceType);

    /* Potential refactor. The piece should know how itself moves.
    pieceType.getMoves();

    Pawn.getMoves
    {
        getPushes();
        getCaptures();
        isEnPessant();
        getPromotions();
    }
    */
    
    const int numberOfActivePieces = activePlayerPieceType.numberOfSetBits();
    for (int i = 0; i < numberOfActivePieces; i++)
    {
        Bitboard psuedoLegalMoves;
        const Square startingSquare = (Square)(activePlayerPieceType.clearAndReturnLSB());

        psuedoLegalMoves |= attack_tables::getAttacks(activePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        if (pieceType == PieceType::PAWN)
        {
            psuedoLegalMoves |= getPawnPushes(activePlayer, startingSquare);
        }

        if (pieceType == KING)
        {
            // We could check for castling moves for either the rooks or the king, I believe it's arbitrary.
            // I choose to only check for castling when generating moves for the king that way it only happens once (and not on both rooks)
            // and since the idea of castling is to protect the king, it makes sense in my mind to make this a king move.
            psuedoLegalMoves |= getCastles(activePlayer, startingSquare);
        }

        // Remove any moves that attack our own pieces
        psuedoLegalMoves &= ~(activePlayerPieces & psuedoLegalMoves);

        int numberOfMoves = psuedoLegalMoves.numberOfSetBits();
        for (int j = 0; j < numberOfMoves; j++)
        {
            // TODO: Remove empty pawn attacks HERE, not in the filterOutIllegalMoves().
            // All we have to do is AND the pawn attacks with the opponent's occupancy set.

            // TODO: Set the isPawnDoublePush flag

            const Square targetSquare = (Square)(psuedoLegalMoves.clearAndReturnLSB());
            const bool pawnPromotion = isPawnPromotion(pieceType, targetSquare);
            const bool enPessant = isEnPessant(activePlayer, startingSquare, gameState);
            const bool doublePush = isPawnDoublePush();
            const Move m(activePlayer, pieceType, startingSquare, targetSquare, pawnPromotion, doublePush, enPessant);
            moves.push_back(m);
        }
    }

    return moves;
}

Bitboard LegalMoveGenerator::getPawnPushes(const Color activePlayer, const Square startingSquare) const
{
    Bitboard pawnPushes;

    Direction direction = NORTH;
    if (activePlayer == Color::BLACK)
    {
        direction = Direction::SOUTH;
    }

    pawnPushes |= getPawnSinglePush(activePlayer, startingSquare, direction);
    pawnPushes |= getPawnDoublePush(activePlayer, startingSquare, direction);

    return pawnPushes;
}

Bitboard LegalMoveGenerator::getPawnSinglePush(const Color activePlayer, const Square startingSquare, Direction direction) const
{
    Bitboard singlePush;

    singlePush |= utils::shiftSquareByDirection(startingSquare, direction);

    // For a white pawn, make sure it's not pushing from rank 8 back to rank 1
    // For a black pawn, make sure it's not pushing from rank 1 to rank 8
    u64 excludeOverflowRank = constants::bit_masks::EXCLUDE_RANK_1;
    if (activePlayer == BLACK)
    {
        excludeOverflowRank = constants::bit_masks::EXCLUDE_RANK_8;
    }

    singlePush &= excludeOverflowRank;

    return singlePush;
}

Bitboard LegalMoveGenerator::getPawnDoublePush(const Color activePlayer, const Square startingSquare, Direction direction) const
{
    Bitboard doublePush;

    if (pawnHasNotMoved(activePlayer, startingSquare))
    {
        doublePush |= utils::shiftSquareByDirection(startingSquare, 2 * direction);
    }

    return doublePush;
}

bool LegalMoveGenerator::pawnHasNotMoved(const Color activePlayer, const Square pawnLocation) const
{
    return !pawnHasMoved(activePlayer, pawnLocation);
}

bool LegalMoveGenerator::pawnHasMoved(const Color activePlayer, const Square pawnLocation) const
{
    // The pawn has moved if it does not exist on it's own color's default pawn structure.
    u64 defaultPawnStructure = constants::DEFAULT_WHITE_PAWN_STRUCTURE;
    if (activePlayer == BLACK)
    {
        defaultPawnStructure = constants::DEFAULT_BLACK_PAWN_STRUCTURE;
    }

    Bitboard pawnRelationToInitialPosition = Bitboard(pawnLocation) & defaultPawnStructure;
    bool pawnIsAwayFromInitialPosition = (pawnRelationToInitialPosition.numberOfSetBits() == 0);
    return pawnIsAwayFromInitialPosition;
}

bool LegalMoveGenerator::isEnPessant(const Color activePlayer, const Square startingSquare, const Chessboard & gameState) const
{
    // TODO: Following algo can be cleaned up. The steps that are taking place are:
    // 1. Get the last move
    // 2. If it was a pawn double push and the pawn ended up on a square that is one integer away from
    //    the current pawn's square, then the last pawn double pushed to the same rank and an adjacent file,
    //    and therefore this is an en pessant move.
    //
    // We can check if the square's distances
    // by checking if (abs(squareA - squareB) == 1) or XORing the bitboard representations of both squares.
    // XORing the bitboard representations of both squares will give us the bit distance from squareA to squareB.
    // Doesn't matter what we do, they will give us the same answer. However, when checking distance like this 
    // it won't account for the wrapping of the board. The H file is technically one bit or one unit of distance
    // away from the A file.
    //
    // This does seem grossly inefficient to check every single pawn against the previous double push.
    // Ways that we can potentially improve the effeciency:
    // - If this white pawn (black pawn) is not on the 5th rank (4th rank), we don't need to check for en pessant.

    bool isEnPessant = false;

    const std::optional<const Move> optionalMove = gameState.getLastMove();
    const bool lastMoveWasPawnDoublePush = (optionalMove.has_value() && optionalMove.value().isPawnDoublePush);
    if (lastMoveWasPawnDoublePush)
    {
        const Move & lastMove = optionalMove.value();
        if ((startingSquare ^ lastMove.endSquare) == 1)
        {
            isEnPessant = true;
        }
    }

    return isEnPessant;
}

bool LegalMoveGenerator::isPawnDoublePush() const
{
    // TODO: this move is a pawn double push if the start square and end square are 16 bits away from each other.
    bool isPawnDoublePush = false;
    

    return isPawnDoublePush;
}

Bitboard LegalMoveGenerator::getCastles(const Color activePlayer, const Square startingSquare) const
{
    // TODO:
    // The chessboard should keep track of castling rights. Both players get a queenside and kingside castling right by default at the start of the game. After every applied move to the game, the chessboard should update each side's castling rights. If one side has already castled, then we don't need to bother with updating their rights anymore, it will always remain false from here on out. The chessboard shouldn't consider attack rays I don't think. It will only keep track of whether or not a side is psuedo-ellegible to castle. That is, it will look at the applied move and if a side has moved their king then their rights to castle get set to false, if they move a rook, then the right to castle to that side is set to false. If a right is ever set to false, we no longer need to update it regardless of what happens. Once it gets set to false it's always false.

    // We also need to consider if there are our own pieces in the way of our castling efforts.

    return Bitboard();
}

bool LegalMoveGenerator::isPawnPromotion(const PieceType pieceType, const Square targetSquare) const
{
    bool isPawnPromotion = false;

    if (pieceType == PAWN)
    {
        isPawnPromotion = (Chessboard::squareToRank(targetSquare) == RANK_8);
    }

    return isPawnPromotion;
}

void LegalMoveGenerator::filterOutIllegalMoves(MoveVector & psuedoLegalMoves) const
{
    // TODO: ./src/movegenerator.cpp:223:23: warning: comparison of integers of different signs: 'int' and 'std::vector<Move>::size_type' (aka 'unsigned long') [-Wsign-compare]
    for (int j = 0; j < psuedoLegalMoves.size(); j++)
    {
        // filterOutMovesThatLeaveKingInCheck();
        // filterOutEmptyPawnAttacks();

        // TODO: For pawns, remove attacks that don't capture anything. For all other pieces an attack and a move is the same thing. We can not wait until here to filter out pawn captures that don't capture anything. We won't know if the move is an attack or a push. I suppose we could check if the targetSquare is in a straight direction North or South from the start square.

        // TODO: if the king is in check after this move, then we either moved the King into check, or we moved a piece that was pinned. Everything below this relates to checking if the king is in check.

        // TODO: I'm pretty sure this is incorrect. If white plays e2e4 and then
        // We get here by calculating psuedo legal moves for black bishops,
        // We should expect this to show the attack ray of the white F1 bishop,
        // but this says that the f1 bishop has 0 attack ray, which is untrue.
        // Bitboard attackedSquaresByNonActivePlayer = attack_tables::getAttacks(nonActivePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        // Maybe this entire block should be saved for the filter out illegal moves thing method?
        // This block is checking for a move puts our king in check or not.
        // TODO: remove any moves that will result in the active player being in check, this is illegal
        // Technically this should be done in the filerOutIlliegalMoves().
        // Will ignore this issue for now and work on generating pawn pushes and double pushes.
        // If after this move the king is in check, then either we were in check to begin with or
        // this move puts the king in check, so don't add this move to the list
        // Brute force method: for every single black piece on the board, calculate the attack vector to the king,
        // is it blocked?
        // Maybe more efficient method: get the attack boards for all of the black pieces. Do a bitwise and with the king's position,
        // Do we get left with a set bit? If so, the king is under attack.
        // We need to pass in the color of the nonActivePlayer
        // Bitboard activePlayerKingPosition = gameState.getBitboard(activePlayer, PieceType::KING);
        // activePlayerKingPosition &= attackedSquaresByNonActivePlayer;

        // if (activePlayerKingPosition.numberOfSetBits() > 0)
        // {
        //     // Don't add this move to the list since it either puts the king in check or leaves the king in check
        //     continue;
        // }
    }
}

MoveVector LegalMoveGenerator::generateLegalMoves(const Chessboard & gameState)
{
    MoveVector moves = generatePsuedoLegalMoves(gameState);
    filterOutIllegalMoves(moves);

    return moves;
}