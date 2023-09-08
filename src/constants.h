#pragma once

#include "types.h"

namespace constants
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

constexpr int INDEX_OF_THIRD_BYTE = 16;
constexpr int INDEX_OF_FIFTH_BYTE = 32;
constexpr int INDEX_OF_SEVENTH_BYTE = 48;

constexpr Direction BISHOP_DIRECTIONS[4] = { Direction::NORTH_EAST, Direction::NORTH_WEST, Direction::SOUTH_WEST, Direction::SOUTH_EAST };
constexpr Direction ROOK_DIRECTIONS[4] = { Direction::NORTH, Direction::WEST, Direction::SOUTH, Direction::EAST };

namespace bit_masks
{

constexpr u64 FILE_A = 0x101010101010101;
constexpr u64 FILE_B = 0x202020202020202;
constexpr u64 FILE_C = 0x404040404040404;
constexpr u64 FILE_D = 0x808080808080808;
constexpr u64 FILE_E = 0x1010101010101010;
constexpr u64 FILE_F = 0x20202020202020;
constexpr u64 FILE_G = 0x4040404040404040;
constexpr u64 FILE_H = 0x8080808080808080;
constexpr u64 EXCLUDE_FILE_A = ~FILE_A;
constexpr u64 EXCLUDE_FILE_H = ~FILE_H;
constexpr u64 EXCLUDE_FILES_A_AND_B = ~FILE_A & ~FILE_B; 
constexpr u64 EXCLUDE_FILES_H_AND_G = ~FILE_H & ~FILE_G;
constexpr u64 LAST_EIGHT_BITS = 0xFF00000000000000;

} // namespace bit_masks
} //namespace constants