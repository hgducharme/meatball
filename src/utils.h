#pragma once

#include "bitboard.h"
#include "constants.h"
#include "chessboard.h"

#include <cmath>

namespace utils
{

// Shift a bitboard by a certain number of rank and files and return a new bitboard of the new position
Bitboard shiftToNewPosition(const Bitboard & oldPosition, int numberOfRanksToMove, int numberOfFilesToMove);

// Convert a difference in rank and files to the number of bits between squares
inline int convertRelativePositionVectorToNumberOfBits(int numberOfRanksToMove, int numberOfFilesToMove);

} // namespace utils