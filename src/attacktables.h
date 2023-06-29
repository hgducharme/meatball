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
    /* This can be cleaned up. Instead of having this many arrays, we can have two arrays called
     * bishopMagicBitboard and rookMagicBitboard that contain MagicEntrys.
     * struct MagicEntry
     * {
     *    Bitboard occupancyMask,
     *    u64 MagicNumber,
     *    int numberOfBits,
     *    Square square,
     * }
     */
    extern Bitboard bishopOccupancies[Square::NUMBER_OF_SQUARES];
    extern Bitboard rookOccupancies[Square::NUMBER_OF_SQUARES];
    extern u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
    extern u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
    extern u64 BISHOP_NUMBER_OF_BITS[Square::NUMBER_OF_SQUARES];
    extern u64 ROOK_NUMBER_OF_BITS[Square::NUMBER_OF_SQUARES];
    // extern Bitboard bishopAttacks[Square::NUMBER_OF_SQUARES][Number of blocker configurations for this square];
    // extern Bitboard rookAttacks[Square::NUMBER_OF_SQUARES][Number of blocker configurations for this square];

    Bitboard calculatePotentialBlockerSquaresForBishopMoves(const Bitboard & bitboard);
    Bitboard calculatePotentialBlockerSquaresForRookMoves(const Bitboard & bitboard);
    u64 bitboardToHashedIndex(const Square square, const Bitboard & blockers);
    Bitboard getPotentialBishopAttacks(const int square, const Bitboard & blockers);
}