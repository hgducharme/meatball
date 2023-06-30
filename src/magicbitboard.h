#pragma once

#include "types.h"
#include "bitboard.h"
#include "utils.h"

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

struct MagicBitboardEntry
{
    Square square;
    Bitboard occupancyMask;
    u64 magicNumber;
    Bitboard occupancyMaskAndMagicProduct;
    int numberOfBitsInProduct;
};

extern MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern Bitboard bishopAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square
extern Bitboard rookAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square

void init();
Bitboard calculateBishopOccupancyMask(const Bitboard &bitboard);
Bitboard calculateRookOccupancyMask(const Bitboard &bitboard);
u64 bitboardToHashedIndex(const Square square, const Bitboard &blockers);
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &blockers);

} // namespace magic_bitboards