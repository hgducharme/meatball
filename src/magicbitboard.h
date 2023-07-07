#pragma once

#include "types.h"
#include "bitboard.h"
#include "utils.h"

namespace magic_bitboards
{

struct MagicBitboardEntry
{
    Square square;
    Bitboard blockerMask;
    u64 magicNumber;
    Bitboard blockerMaskAndMagicProduct;
    int numberOfBitsInProduct;
};

extern MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern Bitboard bishopAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square
extern Bitboard rookAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square

void init();

namespace
{

void instantiateMagicBitboardEntries();
void generateBlockerMasks();
Bitboard calculateBishopBlockerMask(const Bitboard &bitboard);
Bitboard calculateRookBlockerMask(const Bitboard &bitboard);
void generateMagicNumbers();
u64 calculateBishopMagicNumber(const Bitboard & blockerMask);
u64 calculateRookMagicNumber(const Bitboard & blockerMask);
void computeBlockerMaskAndMagicNumberProducts();
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &blockers);

} // anonymous namespace

} // namespace magic_bitboards