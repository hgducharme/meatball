#pragma once

#include "bitboard.h"

namespace utils
{

Bitboard shiftSquareByDirection(const Square square, const int numberOfBits);

Bitboard shiftSquareByDirection(const Bitboard & oldPosition, const int numberOfBits);

int calculateDistanceToEdgeOfBoard(const Square square, const Direction direction);

u64 getRandom64BitInteger();

u64 getSparselyPopulatedRandom64BitInteger();

} // namespace utils