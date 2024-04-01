#pragma once

#include "chessboard.h"

#include <vector>

using MoveVector = std::vector<Move>;

class MoveGenerator
{
   public:
      virtual MoveVector generateLegalMoves(const Chessboard & gameState) = 0;
};

class LegalMoveGenerator : public MoveGenerator
{
    public:
        LegalMoveGenerator() = default;
        MoveVector getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const;
        MoveVector generateLegalMoves(const Chessboard & gameState) override;
        MoveVector generatePsuedoLegalMoves(const Chessboard & gameState) const;
        Bitboard filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves);
};