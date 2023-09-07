#pragma once

#include "chessboard.h"

#include <vector>

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
        std::vector<Move> generateLegalMoves(const Chessboard & chessboard) const;
        std::vector<Move> generatePsuedoLegalMoves(const Chessboard & chessboard) const;
        std::vector<Move> generatePawnMoves(const Chessboard & chessboard) const;
        Bitboard filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves);
};