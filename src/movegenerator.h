#pragma once

#include "chessboard.h"

#include <vector>

using MoveVector = std::vector<Move>;

// Move generation interface
class MoveGenerator
{
   public:
      virtual MoveVector generateLegalMoves(const Chessboard & gameState) = 0;
};

class LegalMoveGenerator : public MoveGenerator
{
    public:
        LegalMoveGenerator() = default;
        MoveVector generateLegalMoves(const Chessboard & gameState) override;
        MoveVector generatePsuedoLegalMoves(const Chessboard & gameState) const;
        MoveVector getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const;
        Bitboard filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves);
};