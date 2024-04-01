#include "movegenerator.h"

#include "move.h"
#include "utils.h"
#include "attacktables.h"

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

// TODO: This currently doesn't handle en pessant, castling, or pawn promotions
MoveVector LegalMoveGenerator::getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const
{
    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Color nonActivePlayer = gameState.getNonActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerPieceType = gameState.getBitboard(activePlayer, pieceType);
    
    const int numberOfActivePlayerPieceType = activePlayerPieceType.numberOfSetBits();
    for (int i = 0; i < numberOfActivePlayerPieceType; i++)
    {
        const Square startingSquare = (Square)(activePlayerPieceType.clearAndReturnLSB());

        // Get the attacks for this piece.
        // The attack ray for a piece is the same as the possible moves for all pieces
        // except pawns.
        Bitboard psuedoLegalMoves = attack_tables::getAttacks(activePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        // Add single pushes for pawns to the list of psuedo legal moves
        if (pieceType == PieceType::PAWN)
        {
            // TODO: North only works for white
            Direction direction = NORTH;
            if (activePlayer == Color::BLACK)
            {
                direction = Direction::SOUTH;
            }
            Bitboard singlePush = utils::shiftCurrentSquareByDirection(startingSquare, direction);

            // TODO: Verify that this single push doens't put us off the board.
            // TODO: Check if this single push gives us a promotion.
            psuedoLegalMoves |= singlePush;

            // If this pawn exists on the default pawn structure, then it is psueo-ellegible for a double push push
            // TODO: Fix the if conditional to something a bit better and readable.
            Bitboard pawnExistsOnDefaultPawnStructure = Bitboard(startingSquare) & constants::DEFAULT_PAWN_STRUCTURE;
            if (pawnExistsOnDefaultPawnStructure.numberOfSetBits() == 1)
            {
                Bitboard doublePush = utils::shiftCurrentSquareByDirection(startingSquare, 2 * direction);
                psuedoLegalMoves |= doublePush;
            }
        }

        // Remove any moves that attack our own pieces
        psuedoLegalMoves &= ~(activePlayerPieces & psuedoLegalMoves);

        // TODO: I'm pretty sure this is incorrect. If white plays e2e4 and then
        // We get here by calculating psuedo legal moves for black bishops,
        // We should expect this to show the attack ray of the white F1 bishop,
        // but this says that the f1 bishop has 0 attack ray, which is untrue.
        Bitboard attackedSquaresByNonActivePlayer = attack_tables::getAttacks(nonActivePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        int numberOfPsuedoLegalMoves = psuedoLegalMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalMoves; j++)
        {
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
            Bitboard activePlayerKingPosition = gameState.getBitboard(activePlayer, PieceType::KING);
            activePlayerKingPosition &= attackedSquaresByNonActivePlayer;

            if (activePlayerKingPosition.numberOfSetBits() > 0)
            {
                // Don't add this move to the list since it either puts the king in check or leaves the king in check
                continue;
            }

            const Square targetSquare = (Square)(psuedoLegalMoves.clearAndReturnLSB());
            Move m(activePlayer, pieceType, startingSquare, targetSquare);
            moves.push_back(m);
        }
    }

    return moves;
}

Bitboard LegalMoveGenerator::filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves)
{}

MoveVector LegalMoveGenerator::generateLegalMoves(const Chessboard & gameState)
{
    MoveVector psuedoLegalMoves = generatePsuedoLegalMoves(gameState);
    
    // MoveList legalMoves = filterOutIllegalMoves(psuedoLegalMoves);
    // return legalMoves;

    return psuedoLegalMoves;
}