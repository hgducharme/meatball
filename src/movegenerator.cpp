#include "movegenerator.h"

#include "move.h"
#include "utils.h"
#include "attacktables.h"
#include "exceptions.h"

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

            const Bitboard opponentOccupancySet = gameState.getBitboard(nonActivePlayer);
            if (pieceType == PieceType::PAWN)
            {
                if (pawnMoveIsAttackWithNoCaptures(move, opponentOccupancySet))
                {
                    continue;
                }

                const std::optional<const Move> opponentsPreviousMove = gameState.getLastMove();

                // Set flags: promotion, double push, en passant
                if (isPawnPromotion(targetSquare)) { 
                    move.setFlag(Move::PROMOTION);
                }
                if (isPawnDoublePush(startingSquare, targetSquare)) { move.setFlag(Move::PAWN_DOUBLE_PUSH); }
                if (isEnPassant(activePlayer, startingSquare, targetSquare, opponentsPreviousMove)) { move.setFlag(Move::EN_PASSANT); }

                // Set pawn capture flag
                const bool startingFileAndEndingFileAreDifferent = (Chessboard::squareToFile(startingSquare) != Chessboard::squareToFile(targetSquare));
                Bitboard targetSquareBitboard(static_cast<int>(targetSquare));
                Bitboard possibleCaptures = targetSquareBitboard & opponentOccupancySet;

                // Set the capture flag for this pawn move if it is NOT en passant, if the starting file and end file are different
                // and if the target square has an opponent's piece
                if (!move.isEnPassant() && ((startingFileAndEndingFileAreDifferent && (possibleCaptures.numberOfSetBits() == 1))))
                {
                    move.setFlag(Move::CAPTURE);
                }
            }
            else
            {
                // Set capture flag for pieces that aren't pawns
                if ((opponentOccupancySet & Bitboard(targetSquare)).numberOfSetBits() == 1) { move.setFlag(Move::CAPTURE); }
            }

            // Set captured piece information
            if (move.isCapture())
            {
                Piece p = gameState.getPieceAt(targetSquare).value();
                move.setCapturedPiece(CapturedPiece(p.color, p.type, targetSquare));
            }

            // Set castle flag
            // TODO: The move is a castle if the king moves two squares
            const int twoSquares = 2;
            if ( (move.pieceType() == PieceType::KING) && (std::abs(targetSquare - startingSquare) == twoSquares) )
            {
                if (Chessboard::squareToFile(targetSquare) == FILE_C)
                {
                    move.setFlag(Move::QUEENSIDE_CASTLE);
                }
                else
                {
                    move.setFlag(Move::KINGSIDE_CASTLE);
                }
            }

            /* TODO: This must happen after all the flags have been set EXCEPT for the check flag. Each one of these pieces must
             * be checked individually if they are a check move. This is ultimately because of bad design. We need to refactor this function, it's
             * gotten too out of control.
             */
            /* TODO: We need to replace the promotion move with four different moves: one for each promotion piece. */
            /* If the move is pawn d7c8, then this needs to become d7c8b, d7c8n, d7c8r, d7c8q */
            if (move.isPromotion())
            {
                for (const PieceType promotionPiece : { PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN })
                {
                    Move promotionMove = move;
                    promotionMove.setPromotionPiece(promotionPiece);
                    if (isCheck(gameState, promotionMove, activePlayer, nonActivePlayer)) { promotionMove.setFlag(Move::CHECK); }
                    moves.push_back(promotionMove);
                }
            }
            // Promotion moves already get their check flag set, no need to do it twice
            else
            {
                // Set check flag
                if (isCheck(gameState, move, activePlayer, nonActivePlayer)) { move.setFlag(Move::CHECK); }
                moves.push_back(move);
            }

            /*
             * END - set various flags about the type of move.
            */

        }
    }

    return moves;
}

bool LegalMoveGenerator::isCheck(const Chessboard &gameState, const Move &move, const Color activePlayer, const Color nonActivePlayer) const
{
    Move moveCopy = move;
    Chessboard gameCopy = gameState;
    gameCopy.applyMove(moveCopy);

    /* If there are shared bits between the active player's attacked square and the
     * non-active player's king bitboard, then this move puts the king into check.
     */
    if (attack_tables::getAttacks(gameCopy, activePlayer) & gameCopy.getBitboard(nonActivePlayer, PieceType::KING))
    {
        return true;
    }

    return false;
}

Bitboard LegalMoveGenerator::getPawnPushes(const Color activePlayer, const Square startingSquare, const Bitboard occupiedSquares) const
{
    Bitboard pawnPushes;

    Direction direction = NORTH;
    if (activePlayer == Color::BLACK)
    {
        direction = Direction::SOUTH;
    }

    pawnPushes |= getPawnSinglePush(activePlayer, startingSquare, direction, occupiedSquares);
    pawnPushes |= getPawnDoublePush(activePlayer, startingSquare, direction, occupiedSquares);

    return pawnPushes;
}

Bitboard LegalMoveGenerator::getPawnSinglePush(const Color activePlayer, const Square startingSquare, Direction direction, const Bitboard occupiedSquares) const
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

    // Remove pushes to occupied squares
    singlePush &= (~occupiedSquares);

    return singlePush;
}

Bitboard LegalMoveGenerator::getPawnDoublePush(const Color activePlayer, const Square startingSquare, Direction direction, const Bitboard occupiedSquares) const
{
    Bitboard doublePush;

    const Bitboard oneSquareForward = utils::shiftSquareByDirection(startingSquare, 1 * direction);
    const Bitboard twoSquaresForward = utils::shiftSquareByDirection(startingSquare, 2 * direction);
    const bool squareInFrontIsNotOccupied = (oneSquareForward & occupiedSquares).noBitsSet();
    const bool twoSquaresInFrontIsNotOccupied = (twoSquaresForward & occupiedSquares).noBitsSet();
    const bool squaresInFrontAreNotOccupied = (squareInFrontIsNotOccupied && twoSquaresInFrontIsNotOccupied);
    if (squaresInFrontAreNotOccupied && pawnHasNotMoved(activePlayer, startingSquare))
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

        case CastleRights::ONLY_KINGSIDE:
        {
            auto [kingTargetSquare, squaresInBetweenKingAndRook] = getKingSideCastleSquares(activePlayer);
            return computeCastleBitboard(gameState, squaresInBetweenKingAndRook, kingTargetSquare);
        }

        case CastleRights::ONLY_QUEENSIDE:
        {
            auto [kingTargetSquare, squaresInBetweenKingAndRook] = getQueenSideCastleSquares(activePlayer);
            return computeCastleBitboard(gameState, squaresInBetweenKingAndRook, kingTargetSquare);
        }

        case CastleRights::KING_AND_QUEENSIDE:
        {
            auto [kingSideTargetSquare, squaresInBetweenKingAndRookKingSide] = getKingSideCastleSquares(activePlayer);
            Bitboard kingSideCastle = computeCastleBitboard(gameState, squaresInBetweenKingAndRookKingSide, kingSideTargetSquare);

            auto [queenSideTargetSquare, squaresInBetweenKingAndRookQueenSide] = getQueenSideCastleSquares(activePlayer);
            Bitboard queenSideCastle = computeCastleBitboard(gameState, squaresInBetweenKingAndRookQueenSide, queenSideTargetSquare);

            return kingSideCastle | queenSideCastle;
        }
        case CastleRights::NUMBER_OF_CASTLE_STATES:
        {
            throw exceptions::move_generation::InvalidSwitchCase("Not a valid switch case. Received 'NUMBER_OF_CASTLE_STATES'.");
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