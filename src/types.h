#pragma once

#include <cstdint>
#include <bitset>

using u64 = std::uint64_t;

namespace bitboard {
constexpr u64 DEFAULT_BLACK_PAWN_STRUCTURE = 0xFF000000000000;
constexpr u64 ONE = 1;
constexpr u64 EMPTY_BOARD = 0;
constexpr u64 FULL_BOARD = 0xFFFFFFFFFFFFFFFF;
} // namespace bitboard

enum Pieces {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Directions {
    NORTH = 1,
    SOUTH = -1,
    EAST = 2,
    WEST = -2,
    NORTH_EAST = 3,
    SOUTH_WEST = -3,
    NORTH_WEST = 4,
    SOUTH_EAST = -4
};

enum Square {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
};
