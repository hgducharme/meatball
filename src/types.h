#pragma once

#include <cstdint>

using u64 = std::uint64_t;

namespace constants {

constexpr u64 DEFAULT_BLACK_PAWN_STRUCTURE = 0xFF00000000000000;

} // namespace constants

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
    a1 = 1, a2, a3, a4, a5, a6, a7, a8,
    b1, b2, b3, b4, b5, b6, b7, b8,
    c1, c2, c3, c4, c5, c6, c7, c8,
    d1, d2, d3, d4, d5, d6, d7, d8,
    e1, e2, e3, e4, e5, e6, e7, e8,
    f1, f2, f3, f4, f5, f6, f7, f8,
    g1, g2, g3, g4, g5, g6, g7, g8,
    h1, h2, h3, h4, h5, h6, h7, h8,
};
