#pragma once

#include "bitboard.h"
#include "constants.h"

namespace utils
{

// Return all legal knight attacks from a given square on the chessboard
Bitboard getKnightAttacks(const Bitboard & bitboard);

}