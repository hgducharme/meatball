#pragma once

#include "types.h"
#include "bitboard.h"

namespace attack_tables
{
    Bitboard pawn[64];
    void init();
    void initializePawnAttackTable();
}