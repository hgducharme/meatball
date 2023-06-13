#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"
#include "chessboard.h"

namespace attack_tables
{
    // The legal pawn moves for each square on the chessboard
    extern Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];

    // The legal knight moves for each square on the chessboard
    extern Bitboard knight[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];

    void init();
    void initializePawnAttackTable();
    void initializeKnightAttackTable();
}