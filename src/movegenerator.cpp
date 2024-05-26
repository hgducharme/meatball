#include "movegenerator.h"

#include "move.h"
#include "utils.h"
#include "attacktables.h"

#include <optional>
#include <cmath>

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

MoveVector LegalMoveGenerator::getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const
{
    /*
     * This function will return all of the possible moves for a piece without considering if it puts the king in check.
     */

    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Color nonActivePlayer = gameState.getNonActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerPieceType = gameState.getBitboard(activePlayer, pieceType);
    
    const int numberOfActivePieces = activePlayerPieceType.numberOfSetBits();
    for (int i = 0; i < numberOfActivePieces; i++)
    {
        Bitboard psuedoLegalMoves;
        const Square startingSquare = (Square)(activePlayerPieceType.clearAndReturnLSB());

        psuedoLegalMoves |= attack_tables::getAttacks(activePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());


        // TODO: We know at this moment if a pawn is a double push, or if a move is castling move. Maybe we pass in some sort of Flags struct
        // that gets modified to hold these flags, and then the struct gets passed into the Move() constructor where the constructor parses it?
        // Also computing flags will be so much faster if we do our computations doing bit arithmetic.
        if (pieceType == PieceType::PAWN)
        {
            const Bitboard occupiedSquares = gameState.getOccupiedSquares();
            psuedoLegalMoves |= getPawnPushes(activePlayer, startingSquare, occupiedSquares);
        }

        if (pieceType == KING)
        {
            psuedoLegalMoves |= getCastles(gameState);
        }

        // Remove any moves that attack our own pieces
        psuedoLegalMoves &= ~(activePlayerPieces & psuedoLegalMoves);

        const int numberOfMoves = psuedoLegalMoves.numberOfSetBits();
        for (int j = 0; j < numberOfMoves; j++)
        {
            const Square targetSquare = static_cast<Square>(psuedoLegalMoves.clearAndReturnLSB());
            Move move(activePlayer, pieceType, startingSquare, targetSquare);

            /*
             * START - set various flags about the type of move.
            */
           uint8_t moveFlags = 0;

            const Bitboard opponentOccupancySet = gameState.getBitboard(nonActivePlayer);
            if (pieceType == PieceType::PAWN)
            {
                if (pawnMoveIsAttackWithNoCaptures(move, opponentOccupancySet))
                {
                    continue;
                }

                const std::optional<const Move> opponentsPreviousMove = gameState.getLastMove();

                if (isPawnPromotion(targetSquare)) { moveFlags |= Move::PROMOTION; }
                if (isPawnDoublePush(startingSquare, targetSquare)) { moveFlags |= Move::PAWN_DOUBLE_PUSH; }
                if (isEnPassant(activePlayer, startingSquare, targetSquare, opponentsPreviousMove)) { moveFlags |= Move::EN_PASSANT; }
                const bool startingFileAndEndingFileAreDifferent = (Chessboard::squareToFile(startingSquare) != Chessboard::squareToFile(targetSquare));
                Bitboard targetSquareBitboard(static_cast<int>(targetSquare));
                Bitboard possibleCaptures = targetSquareBitboard & opponentOccupancySet;
                if (~(moveFlags & Move::EN_PASSANT) && ((startingFileAndEndingFileAreDifferent && (possibleCaptures.numberOfSetBits() == 1))))
                {
                    moveFlags |= (Move::CAPTURE);
                }
            }
            else
            {
                if ((opponentOccupancySet & Bitboard(targetSquare)).numberOfSetBits() == 1)
                {
                    moveFlags |= (Move::CAPTURE);
                }
            }

            if (moveFlags & Move::CAPTURE)
            {
                Piece p = gameState.getPieceAt(targetSquare).value();
                move.setCapturedPiece(CapturedPiece(p.color, p.type, targetSquare));
            }

            // TODO: The move is a castle if the king moves two squares
            const int twoSquares = 2;
            if ( (move.pieceType() == PieceType::KING) && (std::abs(targetSquare - startingSquare) == twoSquares) )
            {
                // TODO: distinguish if this is a kingside castle or a queenside castle.
                moveFlags |= (Move::KINGSIDE_CASTLE | Move::QUEENSIDE_CASTLE);
            }

            /*
             * END - set various flags about the type of move.
            */
            move.setFlags(moveFlags);
            moves.push_back(move);
        }
    }

    return moves;
}

Bitboard LegalMoveGenerator::getPawnPushes(const Color activePlayer, const Square startingSquare, const Bitboard occupiedSquares) const
{
    Bitboard pawnPushes;

    Direction direction = NORTH;
    if (activePlayer == Color::BLACK)
    {
        direction = Direction::SOUTH;
    }

    pawnPushes |= getPawnSinglePush(activePlayer, startingSquare, direction);
    pawnPushes |= getPawnDoublePush(activePlayer, startingSquare, direction);

    // Remove pushes to squares that are already occupied
    pawnPushes &= (~occupiedSquares);

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

bool LegalMoveGenerator::isPawnDoublePush(const Square startingSquare, const Square targetSquare) const
{
    // This move is a pawn double push if the start square and target square are 16 bits away from each other.
    const int sixteenBits = 16;
    bool isPawnDoublePush = ( std::abs(static_cast<int>(startingSquare - targetSquare)) == sixteenBits );
    return isPawnDoublePush;
}

bool LegalMoveGenerator::isEnPassant(const Color activePlayer, const Square startingSquare, const Square targetSquare, const std::optional<const Move> opponentsPreviousMove) const
{
    bool isEnPassant = false;

    // Make sure the capturing pawn is in the right position for en passant to be valid
    const Rank startingSquareRank = Chessboard::squareToRank(startingSquare);
    const bool currentPawnIsWhiteAndNotOn5thRank = ( (activePlayer == WHITE) && (startingSquareRank != RANK_5) );
    const bool currentPawnIsBlackAndNotOn4thRank = ( (activePlayer == BLACK) && (startingSquareRank != RANK_4) );
    if (currentPawnIsWhiteAndNotOn5thRank || currentPawnIsBlackAndNotOn4thRank)
    {
        return isEnPassant;
    }

    if (opponentsPreviousMove.has_value() && opponentsPreviousMove->isPawnDoublePush())
    {
        // TODO:
        // To verify that the last pawn's double push is able to be captured en passant, you can:
        // 1. check that the current pawns square is one bit away from the opponent's pawn square,
        //    but this will require the need to check for board wrapping
        // 2. An alternative is to check if the ranks are the same and the files are neighbors
        // 3. If we are constantly checking for board wrapping, we can make a static method
        //    Chessboard::areSquaresTouching(square1, square2, RANK) where the last parameter
        //    can be RANK, FILE, or DIAGONAL which is the direction to check for if the squares are touching.
        // isEnPassant = Chessboard::areSquaresTouching(square1, square2, EAST) || Chessboard::areSquaresTouching(square1, square2, WEST)
        // As of right now this works perfectly fine, but maybe we can improve readability with the above considerations.
        // NOTE: you must also check that the active pawn's target square is on the same file as the previous pawn move
        // To do this, you can check the files or check if the target square is 8 bits north/south of the current position
        // of the opponent's pawn.

        const File startingSquareFile = Chessboard::squareToFile(startingSquare);
        const File targetSquareFile = Chessboard::squareToFile(targetSquare);
        const File opponentPawnFile = Chessboard::squareToFile(opponentsPreviousMove->endSquare());
        const bool ranksAreSame = startingSquareRank == Chessboard::squareToRank(opponentsPreviousMove->endSquare());
        const bool filesAreNeighbors = std::abs(static_cast<int>(startingSquareFile - opponentPawnFile)) == 1;
        const bool targetSquareFileIsSameAsTargetPawnFile = (targetSquareFile == opponentPawnFile);

        isEnPassant = ranksAreSame && filesAreNeighbors && targetSquareFileIsSameAsTargetPawnFile;
    }

    return isEnPassant;
}

bool LegalMoveGenerator::pawnMoveIsAttackWithNoCaptures(const Move & m, const Bitboard & opponentOccupancySet) const
{
    if (m.isEnPassant() == false)
    {
        const bool startingFileAndEndingFileAreDifferent = (Chessboard::squareToFile(m.startSquare()) != Chessboard::squareToFile(m.endSquare()));

        Bitboard targetSquareBitboard(static_cast<int>(m.endSquare()));
        Bitboard possibleCaptures = targetSquareBitboard & opponentOccupancySet;
        if (startingFileAndEndingFileAreDifferent && possibleCaptures.numberOfSetBits() == 0)
        {
            return true;
        }
    }

    return false;
}

Bitboard LegalMoveGenerator::getCastles(const Chessboard & gameState) const
{
    const Color activePlayer = gameState.getActivePlayer();
    const CastleRights castleRights = gameState.getCastleRights(activePlayer);

    switch (castleRights)
    {
        case CastleRights::NONE:
        {
            return Bitboard();
        }

        case CastleRights::ONLY_KING_SIDE:
        {
            auto [kingTargetSquare, squaresInBetweenKingAndRook] = getKingSideCastleSquares(activePlayer);
            return computeCastleBitboard(gameState, squaresInBetweenKingAndRook, kingTargetSquare);
        }

        case CastleRights::ONLY_QUEEN_SIDE:
        {
            auto [kingTargetSquare, squaresInBetweenKingAndRook] = getQueenSideCastleSquares(activePlayer);
            return computeCastleBitboard(gameState, squaresInBetweenKingAndRook, kingTargetSquare);
        }

        case CastleRights::KING_AND_QUEEN_SIDE:
        {
            auto [kingSideTargetSquare, squaresInBetweenKingAndRookKingSide] = getKingSideCastleSquares(activePlayer);
            Bitboard kingSideCastle = computeCastleBitboard(gameState, squaresInBetweenKingAndRookKingSide, kingSideTargetSquare);

            auto [queenSideTargetSquare, squaresInBetweenKingAndRookQueenSide] = getQueenSideCastleSquares(activePlayer);
            Bitboard queenSideCastle = computeCastleBitboard(gameState, squaresInBetweenKingAndRookQueenSide, queenSideTargetSquare);

            return kingSideCastle | queenSideCastle;
        }
    }
}

const std::pair<Square, u64> LegalMoveGenerator::getKingSideCastleSquares(const Color activePlayer) const
{
    Square kingTargetSquare = constants::WHITE_KINGSIDE_CASTLE_SQUARE;
    u64 squaresInBetweenKingAndRook = constants::bit_masks::SQUARES_BETWEEN_WHITE_KING_AND_KINGSIDE_ROOK;

    if (activePlayer == Color::BLACK) {
        kingTargetSquare = constants::BLACK_KINGSIDE_CASTLE_SQUARE;
        squaresInBetweenKingAndRook = constants::bit_masks::SQUARES_BETWEEN_BLACK_KING_AND_KINGSIDE_ROOK;
    }

    return {kingTargetSquare, squaresInBetweenKingAndRook};
}

const std::pair<Square, u64> LegalMoveGenerator::getQueenSideCastleSquares(const Color activePlayer) const
{
    Square kingTargetSquare = constants::WHITE_QUEENSIDE_CASTLE_SQUARE;
    u64 squaresInBetweenKingAndRook = constants::bit_masks::SQUARES_BETWEEN_WHITE_KING_AND_QUEENSIDE_ROOK;

    if (activePlayer == Color::BLACK)
    {
        kingTargetSquare = constants::BLACK_QUEENSIDE_CASTLE_SQUARE;
        squaresInBetweenKingAndRook = constants::bit_masks::SQUARES_BETWEEN_BLACK_KING_AND_QUEENSIDE_ROOK;
    }

    return {kingTargetSquare, squaresInBetweenKingAndRook};
}

const Bitboard LegalMoveGenerator::computeCastleBitboard(const Chessboard & gameState, const u64 squaresInBetweenKingAndRook, const Square kingTargetSquare) const
{
    const Color nonActivePlayer = gameState.getNonActivePlayer();
    const Bitboard occupiedSquares = gameState.getOccupiedSquares();
    const Bitboard squaresAttackedByOpponent = attack_tables::getAttacks(gameState, nonActivePlayer);

    const bool noPiecesAreInTheWay = Bitboard(squaresInBetweenKingAndRook & occupiedSquares).noBitsSet();
    const bool noSquaresAreBeingAttacked = Bitboard(squaresInBetweenKingAndRook & squaresAttackedByOpponent).noBitsSet();
    if (noPiecesAreInTheWay && noSquaresAreBeingAttacked)
    {
        // This is a valid castle move, return the square the king would move to.
        return Bitboard(kingTargetSquare);
    }

    return Bitboard();
}

bool LegalMoveGenerator::isPawnPromotion(const Square targetSquare) const
{
    return (Chessboard::squareToRank(targetSquare) == RANK_8);
}

void LegalMoveGenerator::filterOutIllegalMoves(MoveVector & psuedoLegalMoves, const Chessboard & gameState) const
{

    // TODO: if the king is in check after this move, then we either moved the King into check, or we moved a piece that was pinned. Everything below this relates to checking if the king is in check.

    // TODO: This will be hard to check for castling. After castling we may no longer be in check. Also
    // we need to check attacked squares I think to determine if a castling move is moving through check.
    // For castling we can't just check the before and end state. We must check the intermediate step.

    const Color activePlayer = gameState.getActivePlayer();
    const Color nonActivePlayer = gameState.getNonActivePlayer();

    auto movePutsOrLeavesKingInCheck = [&](const Move & move) -> bool
    {
        Chessboard simulatedGameState = gameState;
        simulatedGameState.applyMove(move);
        Bitboard activePlayerKingPosition = simulatedGameState.getBitboard(activePlayer, PieceType::KING);
        Bitboard attackedSquaresByNonActivePlayer = attack_tables::getAttacks(gameState, nonActivePlayer);
        bool isKingUnderAttack = (attackedSquaresByNonActivePlayer & activePlayerKingPosition).numberOfSetBits() != 0;
        return isKingUnderAttack;
    };

    // Remove moves from the move vector that make the lambda function true
    psuedoLegalMoves.erase(std::remove_if(psuedoLegalMoves.begin(), psuedoLegalMoves.end(), movePutsOrLeavesKingInCheck), psuedoLegalMoves.end());
}

MoveVector LegalMoveGenerator::generateLegalMoves(const Chessboard & gameState)
{
    MoveVector moves = generatePsuedoLegalMoves(gameState);
    filterOutIllegalMoves(moves, gameState);

    return moves;
}