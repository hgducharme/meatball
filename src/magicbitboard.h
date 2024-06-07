#pragma once

#include "bitboard.h"
#include <vector>
#include <array>

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

int hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount);

} // namespace magic_bitboards