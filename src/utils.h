#pragma once

#include "bitboard.h"

namespace utils
{

Bitboard shiftCurrentSquareByDirection(const Bitboard & oldPosition, const int numberOfBits);

int calculateDistanceToEdgeOfBoard(const Square square, const Direction direction, bool includeEdgeSquare = true);

u64 getRandom64BitInteger();

u64 getSparselyPopulatedRandom64BitInteger();

} // namespace utils