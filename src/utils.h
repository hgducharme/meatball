#pragma once

#include "bitboard.h"
#include "constants.h"
#include "chessboard.h"

#include <cmath>     // std::abs
#include <algorithm> // std::math
#include <random>

namespace utils
{

Bitboard shiftCurrentSquareByDirection(const Bitboard & oldPosition, const int numberOfBits);

int calculateDistanceFromEdgeOfBoard(Square square, Direction direction);

u64 getRandom64BitInteger();

u64 getRandom64BitInteger_2();

} // namespace utils