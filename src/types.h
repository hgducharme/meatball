#pragma once

#include <cstdint>

using u64 = std::uint64_t;

namespace bitboard
{

constexpr u64 ONE = 1;
constexpr u64 EMPTY_BOARD = 0;
constexpr u64 UNIVERSE = 0xFFFFFFFFFFFFFFFF;
constexpr u64 MOST_SIGNIFICANT_BIT_SET = ONE << 63;

constexpr u64 DEFAULT_BLACK_PAWN_STRUCTURE =   0x00FF000000000000;
constexpr u64 DEFAULT_BLACK_KNIGHT_STRUCTURE = 0x4200000000000000;
constexpr u64 DEFAULT_BLACK_BISHOP_STRUCTURE = 0x2400000000000000;
constexpr u64 DEFAULT_BLACK_ROOK_STRUCTURE =   0x8100000000000000;
constexpr u64 DEFAULT_BLACK_QUEEN_STRUCTURE =  0x0800000000000000;
constexpr u64 DEFAULT_BLACK_KING_STRUCTURE =   0x1000000000000000;
constexpr u64 DEFAULT_BLACK_OCCUPIED =         0xFFFF000000000000;

constexpr u64 DEFAULT_WHITE_PAWN_STRUCTURE =   0x000000000000FF00;
constexpr u64 DEFAULT_WHITE_KNIGHT_STRUCTURE = 0x0000000000000042;
constexpr u64 DEFAULT_WHITE_BISHOP_STRUCTURE = 0x0000000000000024;
constexpr u64 DEFAULT_WHITE_ROOK_STRUCTURE =   0x0000000000000081;
constexpr u64 DEFAULT_WHITE_QUEEN_STRUCTURE =  0x0000000000000008;
constexpr u64 DEFAULT_WHITE_KING_STRUCTURE =   0x0000000000000010;
constexpr u64 DEFAULT_WHITE_OCCUPIED =         0x000000000000FFFF;

constexpr u64 DEFAULT_PAWN_STRUCTURE = DEFAULT_BLACK_PAWN_STRUCTURE | DEFAULT_WHITE_PAWN_STRUCTURE;
constexpr u64 DEFAULT_KNIGHT_STRUCTURE = DEFAULT_BLACK_KNIGHT_STRUCTURE | DEFAULT_WHITE_KNIGHT_STRUCTURE;
constexpr u64 DEFAULT_BISHOP_STRUCTURE = DEFAULT_BLACK_BISHOP_STRUCTURE | DEFAULT_WHITE_BISHOP_STRUCTURE;
constexpr u64 DEFAULT_ROOK_STRUCTURE = DEFAULT_BLACK_ROOK_STRUCTURE | DEFAULT_WHITE_ROOK_STRUCTURE;
constexpr u64 DEFAULT_QUEEN_STRUCTURE = DEFAULT_BLACK_QUEEN_STRUCTURE | DEFAULT_WHITE_QUEEN_STRUCTURE;
constexpr u64 DEFAULT_KING_STRUCTURE = DEFAULT_BLACK_KING_STRUCTURE | DEFAULT_WHITE_KING_STRUCTURE;

} // namespace bitboard

enum PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NUMBER_OF_PIECES = 6
};

// one move to the north west corresponds to the bit 7 positions larger than the current bit
// one move to the north      corresponds to the bit 8 positions larger than the current bit
// one move to the north east corresponds to the bit 9 positions larger than the current bit
enum Direction
{
    NORTH = 8,
    SOUTH = -8,
    NORTH_EAST = 9,
    SOUTH_WEST = -9,
    NORTH_WEST = 7,
    SOUTH_EAST = -7,
    EAST = 1,
    WEST = -1,
};

enum Square
{
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    NUMBER_OF_SQUARES = 64,
};

enum Color
{
    WHITE,
    BLACK,
    NUMBER_OF_COLORS = 2
};