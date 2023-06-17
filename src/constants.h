#pragma once

#include "types.h"

namespace constants
{
   namespace attack_masks
   {
      constexpr u64 pawn_single_push = 0x7;
   }

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
   }
}

enum File
{
   FILE_A,
   FILE_B,
   FILE_C,
   FILE_D,
   FILE_E,
   FILE_F,
   FILE_G,
   FILE_H,
   NUMBER_OF_FILES = 8
};

enum Rank
{
   RANK_1,
   RANK_2,
   RANK_3,
   RANK_4,
   RANK_5,
   RANK_6,
   RANK_7,
   RANK_8,
   NUMBER_OF_RANKS = 8
};