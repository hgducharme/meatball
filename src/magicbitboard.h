#pragma once

#include "types.h"
#include "bitboard.h"
#include "utils.h"
#include "constants.h"

#include <vector>

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
extern Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][4096];
extern Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][4096];

void init();

namespace
{

extern u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

void instantiateMagicBitboardEntries();
void generateBlockerMasks();
Bitboard calculateBishopBlockerMask(const Bitboard &bitboard);
Bitboard calculateRookBlockerMask(const Bitboard &bitboard);
void generateMagicNumbers();
u64 getRandom64BitInteger();
void generateAttackBoard(PieceType pieceType);
std::vector<Bitboard> calculateAllBlockerVariations(Bitboard blockerMask);
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &blockers);

} // anonymous namespace

} // namespace magic_bitboards