#pragma once

#include "types.h"

namespace constants
{
   namespace attack_masks
   {
      constexpr u64 pawn_single_push = 0x7;
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