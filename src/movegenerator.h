#pragma once

#include "chessboard.h"

#include <vector>

using MoveVector = std::vector<Move>;

// Move generation interface
class MoveGenerator
{
   public:
      virtual MoveVector generateLegalMoves(const Chessboard & chessboard) = 0;
};

class LegalMoveGenerator : public MoveGenerator
{
    public:
        LegalMoveGenerator() = default;
        MoveVector generateLegalMoves(const Chessboard & chessboard) override;
        MoveVector generatePsuedoLegalMoves(const Chessboard & chessboard) const;
        MoveVector getMovesByPiece(const PieceType pieceType, const Chessboard & gameState) const;
        Bitboard filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves);
};