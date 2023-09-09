#pragma once

#include "chessboard.h"

#include <vector>

using MoveVector = std::vector<Move>;

// Move generation interface
class MoveGenerator
{
   public:
      virtual std::vector<Move> generateLegalMoves(const Chessboard & chessboard) = 0;
};

class LegalMoveGenerator : public MoveGenerator
{
    public:
        LegalMoveGenerator() = default;
        MoveVector generateLegalMoves(const Chessboard & chessboard) override;
        MoveVector generatePsuedoLegalMoves(const Chessboard & chessboard) const;
        MoveVector generatePawnMoves(const Chessboard & chessboard) const;
        MoveVector generateKnightMoves(const Chessboard & chessboard) const;
        MoveVector generateBishopMoves(const Chessboard & gameState) const;
        Bitboard filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves);
};