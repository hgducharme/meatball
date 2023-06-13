#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"
#include "chessboard.h"

namespace attack_tables
{
    extern Bitboard pawn[Square::NUMBER_OF_SQUARES];
    extern Bitboard knight[Square::NUMBER_OF_SQUARES];
    void init();
    void initializePawnAttackTable();
}