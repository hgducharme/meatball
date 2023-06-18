#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"
#include "chessboard.h"
#include "utils.h"

namespace attack_tables
{
    extern Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
    extern Bitboard knight[Square::NUMBER_OF_SQUARES];
    extern Bitboard bishop[Square::NUMBER_OF_SQUARES];
    extern Bitboard rook[Square::NUMBER_OF_SQUARES];
    extern Bitboard queen[Square::NUMBER_OF_SQUARES];
    extern Bitboard king[Square::NUMBER_OF_SQUARES];

    void init();
    Bitboard calculatePawnAttacksFromSquare(Color color, const Bitboard & bitboard);
    Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateBishopAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateRookAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateQueenAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard);
}