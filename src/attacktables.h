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
    Bitboard calculateBishopAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateRookAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard);

}

namespace magic_bitboards
{
    extern Bitboard bishopOccupancies[Square::NUMBER_OF_SQUARES];
    extern Bitboard rookOccupancies[Square::NUMBER_OF_SQUARES];
    // extern Bitboard bishopAttacks[INSERT SIZE];
    // extern Bitboard rookAttacks[INSERT SIZE];

    Bitboard calculatePotentialBlockerSquaresForBishopMoves(const Bitboard & bitboard);
    Bitboard calculatePotentialBlockerSquaresForRookMoves(const Bitboard & bitboard);                           
}