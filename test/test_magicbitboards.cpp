#include "../src/magicbitboard.h"
#include "../src/types.h"
#include "../src/bitboard.h"

#include "gtest/gtest.h"

#include <iostream>

namespace meatball {
namespace {

// The fixture for testing the class.
class MagicBitboardsTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  MagicBitboardsTest()
  {
     // You can do set-up work for each test here.
  }

  ~MagicBitboardsTest() override
  {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override
  {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override
  {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  static void SetUpTestSuite()
  {
   	// Code here will be called before the first test and will not be called again.
      magic_bitboards::init();

      /* Expected bishop attack table */
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[0] = 0x40201008040200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[1] = 0x402010080400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[2] = 0x4020100a00;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[3] = 0x40221400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[4] = 0x2442800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[5] = 0x204085000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[6] = 0x20408102000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[7] = 0x2040810204000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[8] = 0x20100804020000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[9] = 0x40201008040000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[10] = 0x4020100a0000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[11] = 0x4022140000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[12] = 0x244280000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[13] = 0x20408500000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[14] = 0x2040810200000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[15] = 0x4081020400000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[16] = 0x10080402000200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[17] = 0x20100804000400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[18] = 0x4020100a000a00;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[19] = 0x402214001400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[20] = 0x24428002800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[21] = 0x2040850005000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[22] = 0x4081020002000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[23] = 0x8102040004000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[24] = 0x8040200020400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[25] = 0x10080400040800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[26] = 0x20100a000a1000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[27] = 0x40221400142200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[28] = 0x2442800284400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[29] = 0x4085000500800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[30] = 0x8102000201000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[31] = 0x10204000402000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[32] = 0x4020002040800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[33] = 0x8040004081000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[34] = 0x100a000a102000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[35] = 0x22140014224000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[36] = 0x44280028440200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[37] = 0x8500050080400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[38] = 0x10200020100800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[39] = 0x20400040201000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[40] = 0x2000204081000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[41] = 0x4000408102000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[42] = 0xa000a10204000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[43] = 0x14001422400000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[44] = 0x28002844020000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[45] = 0x50005008040200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[46] = 0x20002010080400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[47] = 0x40004020100800;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[48] = 0x20408102000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[49] = 0x40810204000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[50] = 0xa1020400000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[51] = 0x142240000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[52] = 0x284402000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[53] = 0x500804020000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[54] = 0x201008040200;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[55] = 0x402010080400;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[56] = 0x2040810204000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[57] = 0x4081020400000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[58] = 0xa102040000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[59] = 0x14224000000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[60] = 0x28440200000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[61] = 0x50080402000000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[62] = 0x20100804020000;
      MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[63] = 0x40201008040200;

      /* Expected rook attack table */
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[0] = 0x101010101017e;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[1] = 0x202020202027c;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[2] = 0x404040404047a;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[3] = 0x8080808080876;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[4] = 0x1010101010106e;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[5] = 0x2020202020205e;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[6] = 0x4040404040403e;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[7] = 0x8080808080807e;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[8] = 0x1010101017e00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[9] = 0x2020202027c00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[10] = 0x4040404047a00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[11] = 0x8080808087600;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[12] = 0x10101010106e00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[13] = 0x20202020205e00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[14] = 0x40404040403e00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[15] = 0x80808080807e00;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[16] = 0x10101017e0100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[17] = 0x20202027c0200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[18] = 0x40404047a0400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[19] = 0x8080808760800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[20] = 0x101010106e1000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[21] = 0x202020205e2000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[22] = 0x404040403e4000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[23] = 0x808080807e8000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[24] = 0x101017e010100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[25] = 0x202027c020200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[26] = 0x404047a040400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[27] = 0x8080876080800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[28] = 0x1010106e101000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[29] = 0x2020205e202000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[30] = 0x4040403e404000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[31] = 0x8080807e808000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[32] = 0x1017e01010100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[33] = 0x2027c02020200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[34] = 0x4047a04040400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[35] = 0x8087608080800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[36] = 0x10106e10101000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[37] = 0x20205e20202000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[38] = 0x40403e40404000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[39] = 0x80807e80808000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[40] = 0x17e0101010100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[41] = 0x27c0202020200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[42] = 0x47a0404040400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[43] = 0x8760808080800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[44] = 0x106e1010101000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[45] = 0x205e2020202000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[46] = 0x403e4040404000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[47] = 0x807e8080808000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[48] = 0x7e010101010100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[49] = 0x7c020202020200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[50] = 0x7a040404040400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[51] = 0x76080808080800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[52] = 0x6e101010101000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[53] = 0x5e202020202000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[54] = 0x3e404040404000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[55] = 0x7e808080808000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[56] = 0x7e01010101010100;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[57] = 0x7c02020202020200;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[58] = 0x7a04040404040400;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[59] = 0x7608080808080800;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[60] = 0x6e10101010101000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[61] = 0x5e20202020202000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[62] = 0x3e40404040404000;
      MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[63] = 0x7e80808080808000;

      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[0] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[0] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[0];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[1] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[1] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[1];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[2] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[2] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[2];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[3] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[3] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[3];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[4] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[4] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[4];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[5] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[5] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[5];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[6] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[6] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[6];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[7] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[7] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[7];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[8] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[8] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[8];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[9] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[9] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[9];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[10] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[10] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[10];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[11] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[11] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[11];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[12] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[12] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[12];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[13] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[13] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[13];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[14] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[14] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[14];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[15] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[15] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[15];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[16] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[16] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[16];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[17] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[17] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[17];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[18] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[18] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[18];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[19] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[19] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[19];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[20] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[20] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[20];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[21] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[21] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[21];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[22] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[22] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[22];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[23] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[23] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[23];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[24] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[24] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[24];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[25] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[25] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[25];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[26] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[26] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[26];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[27] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[27] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[27];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[28] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[28] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[28];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[29] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[29] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[29];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[30] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[30] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[30];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[31] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[31] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[31];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[32] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[32] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[32];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[33] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[33] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[33];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[34] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[34] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[34];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[35] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[35] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[35];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[36] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[36] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[36];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[37] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[37] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[37];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[38] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[38] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[38];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[39] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[39] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[39];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[40] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[40] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[40];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[41] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[41] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[41];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[42] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[42] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[42];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[43] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[43] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[43];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[44] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[44] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[44];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[45] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[45] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[45];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[46] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[46] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[46];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[47] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[47] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[47];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[48] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[48] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[48];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[49] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[49] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[49];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[50] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[50] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[50];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[51] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[51] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[51];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[52] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[52] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[52];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[53] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[53] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[53];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[54] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[54] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[54];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[55] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[55] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[55];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[56] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[56] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[56];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[57] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[57] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[57];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[58] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[58] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[58];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[59] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[59] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[59];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[60] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[60] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[60];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[61] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[61] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[61];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[62] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[62] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[62];
      MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[63] = MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[63] | MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[63];
   }

  static void TearDownTestSuite()
  {
		// Code here will be called after the last test.
  }

   // Class members declared here can be used by all tests in the test suite.
   // To share resources between tests, declare them as static class members,
   // then add their definition just below the test fixture class.
   static u64 EXPECTED_BISHOP_MAGIC_LOOKUP[64];
   static u64 EXPECTED_ROOK_MAGIC_LOOKUP[64];
   static u64 EXPECTED_QUEEN_MAGIC_LOOKUP[64];
};

u64 MagicBitboardsTest::EXPECTED_BISHOP_MAGIC_LOOKUP[64];
u64 MagicBitboardsTest::EXPECTED_ROOK_MAGIC_LOOKUP[64];
u64 MagicBitboardsTest::EXPECTED_QUEEN_MAGIC_LOOKUP[64];

TEST_F(MagicBitboardsTest, bishopMagicLookup)
{
   for (int square = 0; square < 64; square++)
   {
      EXPECT_EQ(magic_bitboards::BISHOP_MAGIC_LOOKUP[square].blockerMask.getBoard(), EXPECTED_BISHOP_MAGIC_LOOKUP[square]);
   }
}

TEST_F(MagicBitboardsTest, rookMagicLookup)
{
   for (int square = 0; square < 64; square++)
   {
      EXPECT_EQ(magic_bitboards::ROOK_MAGIC_LOOKUP[square].blockerMask.getBoard(), EXPECTED_ROOK_MAGIC_LOOKUP[square]);
   }
}

}  // namespace
}  // namespace meatball