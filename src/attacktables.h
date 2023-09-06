#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"
#include "chessboard.h"
#include "utils.h"
#include "magicbitboard.h"

namespace attack_tables
{
    extern Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
    extern Bitboard knight[Square::NUMBER_OF_SQUARES];
    extern Bitboard king[Square::NUMBER_OF_SQUARES];

    void init();
    Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard);
    Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateBishopAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateRookAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard);

namespace
{
    void initializeAttacksForLeaperPieces();
    void initializeAttacksForSliderPieces();
} // anonymous namespace
} // attack_tables namespace