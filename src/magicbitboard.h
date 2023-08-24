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
    int shiftAmount;
};

extern MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];

// Bishops have between 32 and 512 unique possible blocker variations depending on the square
// Rooks have between 1024 and 4096 unique possible blocker variations depending on the square
constexpr int LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS = 512;
constexpr int LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS = 4096;

extern Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS];
extern Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];

void init();

namespace
{

extern u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
extern u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

// The number of set bits in the bishop blocker mask for each square
constexpr int NUMBER_OF_SET_BITS_IN_BISHOP_BLOCKER_MASK[Square::NUMBER_OF_SQUARES] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6,
};

// The number of set bits in the rook blocker mask for each square
constexpr int NUMBER_OF_SET_BITS_IN_ROOK_BLOCKER_MASK[Square::NUMBER_OF_SQUARES] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12,
};

void initializeAttackDatabases();
void initializeMagicBitboardEntries();
void generateBlockerMasks();
Bitboard calculateBishopBlockerMask(const Bitboard &bitboard);
Bitboard calculateRookBlockerMask(const Bitboard &bitboard);
void generateInitialMagicNumbers();
void generateBishopMagics();
void generateAttackBoard(PieceType pieceType);
std::vector<Bitboard> calculateAllBlockerVariations(Bitboard blockerMask);
Bitboard calculateBishopAttackBoard(const Square & square, const Bitboard & blockerVariation);
Bitboard calculateRookAttackBoard(const Square & square, const Bitboard & blockerVariation);
bool targetSquareIsBlocked(Bitboard targetSquare, Bitboard occupiedSquares);
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &blockers);

} // anonymous namespace

} // namespace magic_bitboards