#pragma once

#include "bitboard.h"
#include "constants.h"
#include "chessboard.h"

#include <cmath>     // std::abs
#include <algorithm> // std::math

namespace utils
{

Bitboard shiftPieceOnBitboard(const Bitboard & oldPosition, const int numberOfBits);

int calculateDistanceFromEdgeOfBoard(Square square, Direction direction);

} // namespace utils