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
MoveVector LegalMoveGenerator::getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const
{
    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerPieceType = gameState.getBitboard(activePlayer, pieceType);
    
    const int numberOfActivePlayerPieceType = activePlayerPieceType.numberOfSetBits();
    for (int i = 0; i < numberOfActivePlayerPieceType; i++)
    {
        const Square startingSquare = (Square)(activePlayerPieceType.clearAndReturnLSB());

        Bitboard psuedoLegalMoves = attack_tables::getAttacks(pieceType, startingSquare, gameState);

        // Remove any moves that attack our own pieces
        psuedoLegalMoves &= ~(activePlayerPieces & psuedoLegalMoves);

        // TODO: remove any moves that will result in the active player being in check, this is illegal

        int numberOfPsuedoLegalMoves = psuedoLegalMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalMoves; j++)
        {
            const Square targetSquare = (Square)(psuedoLegalMoves.clearAndReturnLSB());
            Move m(activePlayer, PAWN, startingSquare, targetSquare);
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
}