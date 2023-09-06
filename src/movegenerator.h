#pragma once

#include "chessboard.h"

#include <vector>

class MoveGenerator
{
    public:
        MoveGenerator() = default;
        std::vector<Move> generatePsuedoLegalMoves(const Chessboard & chessboard) const;
        std::vector<Move> generatePawnMoves(const Chessboard & chessboard) const;
};