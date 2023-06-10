#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"

namespace attack_tables
{
    extern Bitboard pawn[Square::NUMBER_OF_SQUARES];
    void init();
    void initializePawnAttackTable();
}