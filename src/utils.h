#pragma once

#include "bitboard.h"
#include "constants.h"
#include "chessboard.h"

#include <cmath>

namespace utils
{

Bitboard shiftPieceOnBitboard(const Bitboard & oldPosition, const int numberOfBits);

// Shift a bitboard by a certain number of rank and files and return a new bitboard of the new position
Bitboard shiftToNewPosition(const Bitboard & oldPosition, const int numberOfRanksToMove, const int numberOfFilesToMove);

// Convert a difference in rank and files to the number of bits between squares
inline int convertRelativePositionVectorToNumberOfBits(const int numberOfRanksToMove, const int numberOfFilesToMove);

} // namespace utils