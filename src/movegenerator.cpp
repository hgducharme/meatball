#include "movegenerator.h"

#include "move.h"
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

// TODO: This currently doesn't handle single push, double push, en pessant, castling, or pawn promotions
// TODO: This currently is calculating bishop moves wrong. It thinks the bishop can move but it can't because
// it's blocked by pawns.
// This is not calculating rook moves correctly. It thinks the rook on A1 can move but it can't because it's blocked by pawns.
// The moves for rook on H1 isn't being calculated.
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

        Bitboard psuedoLegalMoves = attack_tables::getAttacks(activePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        // Remove any moves that attack our own pieces
        psuedoLegalMoves &= ~(activePlayerPieces & psuedoLegalMoves);

        Bitboard attackedSquaresByNonActivePlayer = attack_tables::getAttacks(nonActivePlayer, pieceType, startingSquare, gameState.getOccupiedSquares());

        int numberOfPsuedoLegalMoves = psuedoLegalMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalMoves; j++)
        {
            // TODO: remove any moves that will result in the active player being in check, this is illegal
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