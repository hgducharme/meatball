#pragma once

#include "types.h"
#include "bitboard.h"
#include "utils.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <array>

namespace magic_bitboards
{

struct MagicBitboardEntry
{
    Bitboard blockerMask;
    u64 magicNumber;
    int shiftAmount;
};

extern MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
extern MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];

// Bishops have between 32 and 512 unique possible blocker variations depending on the square
constexpr int LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS = 512;

// Rooks have between 1024 and 4096 unique possible blocker variations depending on the square
constexpr int LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS = 4096;

constexpr int MINIMUM_NUMBER_OF_BITS_FOR_BISHOP_HASHING = 3;
constexpr int MINIMUM_NUMBER_OF_BITS_FOR_ROOK_HASHING = 6;

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

// Define an alias for passing calculate[Piece]AttackBoard() as a parameter to another function
using calculateAttackBoardFunction = Bitboard (*)(const Square & square, const Bitboard & blockerVariation);

void initializeMagicBitboardEntries();
void generateBlockerMasks();
Bitboard calculateBishopBlockerMask(const Bitboard &bitboard);
Bitboard calculateRookBlockerMask(const Bitboard &bitboard);

std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> calculateBlockerVariations(MagicBitboardEntry const * MAGIC_LOOKUP_TABLE);
std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> calculateAttacks(calculateAttackBoardFunction calculateAttackBoard, const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations);

void generateMagicNumbers(const PieceType pieceType,
                          const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                          const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards);

u64 searchForMagicNumber(PieceType pieceType, const Square square, const std::vector<Bitboard> & allBlockerVariations, const std::vector<Bitboard> & attackBoards);

void populateAttackDatabase(const PieceType pieceType,
                            const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                            const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards);

int hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount);
void generateAttackBoard(PieceType pieceType);
std::vector<Bitboard> enumerateSubmasks(Bitboard blockerMask);
Bitboard calculateBishopAttackBoard(const Square & square, const Bitboard & blockerVariation);
Bitboard calculateRookAttackBoard(const Square & square, const Bitboard & blockerVariation);
bool targetSquareIsBlocked(Bitboard targetSquare, Bitboard occupiedSquares);
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &blockers);

} // anonymous namespace

} // namespace magic_bitboards