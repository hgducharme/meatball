#pragma once

#include "bitboard.h"
#include <vector>

namespace magic_bitboards
{

struct HashingParameters
{
    Bitboard blockerMask;
    u64 magicNumber;
    int shiftAmount;
};

extern HashingParameters BISHOP_HASHING_PARAMETERS_LOOKUP[Square::NUMBER_OF_SQUARES];
extern HashingParameters ROOK_HASHING_PARAMETERS_LOOKUP[Square::NUMBER_OF_SQUARES];

// Bishops have between 32 and 512 unique possible blocker variations depending on the square
constexpr int LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS = 512;

// Rooks have between 1024 and 4096 unique possible blocker variations depending on the square
constexpr int LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS = 4096;

constexpr int MINIMUM_NUMBER_OF_BITS_FOR_BISHOP_HASHING = 3;
constexpr int MINIMUM_NUMBER_OF_BITS_FOR_ROOK_HASHING = 4;

void init();

namespace
{

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

using ArrayOfBitboardVectors = std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES>;

void initializeHashingParameters();

void generateBlockerMasks();

template <uint8_t size>
Bitboard calculateBlockerMask(const Bitboard & position, const Direction (&sliderPieceDirections)[size]);

ArrayOfBitboardVectors calculateBlockerVariations(HashingParameters const * hashingParametersLookup);

std::vector<Bitboard> enumerateSubmasks(Bitboard blockerMask);

template <uint8_t size>
ArrayOfBitboardVectors calculateAttacks(const Direction (&attackDirections)[size], const ArrayOfBitboardVectors & blockerVariations);

template <uint8_t size>
Bitboard calculateAttacksFromSquare(const Square & square, const Direction (&directionsToAttack)[size], const Bitboard & blockerVariation);

bool targetSquareIsBlocked(Bitboard targetSquare, Bitboard occupiedSquares);

void generateMagicNumbers(HashingParameters * hashingParametersLookup,
                          const int minimumBitsRequiredForHashing,
                          const ArrayOfBitboardVectors & blockerVariations,
                          const ArrayOfBitboardVectors & attackBoards);

u64 searchForMagicNumber(const HashingParameters & hashingParameters,
                         const int minimumAmountOfBitsInLastByte,
                         const std::vector<Bitboard> & allBlockerVariations,
                         const std::vector<Bitboard> & attackBoards);

int hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount);

void initializeMagicNumbers();

template <size_t rows, size_t columns>
void populateAttackDatabase(Bitboard (&attackDatabase)[rows][columns],
                            const HashingParameters * hashingParametersLookup,
                            const ArrayOfBitboardVectors & blockerVariations,
                            const ArrayOfBitboardVectors & attackBoards);

} // anonymous namespace

} // namespace magic_bitboards