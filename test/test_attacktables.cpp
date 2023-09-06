#include "../src/attacktables.h"
#include "../src/types.h"
#include "../src/bitboard.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class AttackTablesTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  AttackTablesTest()
  {
     // You can do set-up work for each test here.
  }

  ~AttackTablesTest() override
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
      attack_tables::init();

      /* Expected white pawn attack table */
      AttackTablesTest::EXPECTED_PAWN[0][0] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][1] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][2] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][3] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][4] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][5] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][6] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][7] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][8] = 0x20000;
      AttackTablesTest::EXPECTED_PAWN[0][9] = 0x50000;
      AttackTablesTest::EXPECTED_PAWN[0][10] = 0xa0000;
      AttackTablesTest::EXPECTED_PAWN[0][11] = 0x140000;
      AttackTablesTest::EXPECTED_PAWN[0][12] = 0x280000;
      AttackTablesTest::EXPECTED_PAWN[0][13] = 0x500000;
      AttackTablesTest::EXPECTED_PAWN[0][14] = 0xa00000;
      AttackTablesTest::EXPECTED_PAWN[0][15] = 0x400000;
      AttackTablesTest::EXPECTED_PAWN[0][16] = 0x2000000;
      AttackTablesTest::EXPECTED_PAWN[0][17] = 0x5000000;
      AttackTablesTest::EXPECTED_PAWN[0][18] = 0xa000000;
      AttackTablesTest::EXPECTED_PAWN[0][19] = 0x14000000;
      AttackTablesTest::EXPECTED_PAWN[0][20] = 0x28000000;
      AttackTablesTest::EXPECTED_PAWN[0][21] = 0x50000000;
      AttackTablesTest::EXPECTED_PAWN[0][22] = 0xa0000000;
      AttackTablesTest::EXPECTED_PAWN[0][23] = 0x40000000;
      AttackTablesTest::EXPECTED_PAWN[0][24] = 0x200000000;
      AttackTablesTest::EXPECTED_PAWN[0][25] = 0x500000000;
      AttackTablesTest::EXPECTED_PAWN[0][26] = 0xa00000000;
      AttackTablesTest::EXPECTED_PAWN[0][27] = 0x1400000000;
      AttackTablesTest::EXPECTED_PAWN[0][28] = 0x2800000000;
      AttackTablesTest::EXPECTED_PAWN[0][29] = 0x5000000000;
      AttackTablesTest::EXPECTED_PAWN[0][30] = 0xa000000000;
      AttackTablesTest::EXPECTED_PAWN[0][31] = 0x4000000000;
      AttackTablesTest::EXPECTED_PAWN[0][32] = 0x20000000000;
      AttackTablesTest::EXPECTED_PAWN[0][33] = 0x50000000000;
      AttackTablesTest::EXPECTED_PAWN[0][34] = 0xa0000000000;
      AttackTablesTest::EXPECTED_PAWN[0][35] = 0x140000000000;
      AttackTablesTest::EXPECTED_PAWN[0][36] = 0x280000000000;
      AttackTablesTest::EXPECTED_PAWN[0][37] = 0x500000000000;
      AttackTablesTest::EXPECTED_PAWN[0][38] = 0xa00000000000;
      AttackTablesTest::EXPECTED_PAWN[0][39] = 0x400000000000;
      AttackTablesTest::EXPECTED_PAWN[0][40] = 0x2000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][41] = 0x5000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][42] = 0xa000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][43] = 0x14000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][44] = 0x28000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][45] = 0x50000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][46] = 0xa0000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][47] = 0x40000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][48] = 0x200000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][49] = 0x500000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][50] = 0xa00000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][51] = 0x1400000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][52] = 0x2800000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][53] = 0x5000000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][54] = 0xa000000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][55] = 0x4000000000000000;
      AttackTablesTest::EXPECTED_PAWN[0][56] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][57] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][58] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][59] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][60] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][61] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][62] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[0][63] = 0x0;

      /* Expected black pawn attack table */
      AttackTablesTest::EXPECTED_PAWN[1][0] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][1] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][2] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][3] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][4] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][5] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][6] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][7] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][8] = 0x2;
      AttackTablesTest::EXPECTED_PAWN[1][9] = 0x5;
      AttackTablesTest::EXPECTED_PAWN[1][10] = 0xa;
      AttackTablesTest::EXPECTED_PAWN[1][11] = 0x14;
      AttackTablesTest::EXPECTED_PAWN[1][12] = 0x28;
      AttackTablesTest::EXPECTED_PAWN[1][13] = 0x50;
      AttackTablesTest::EXPECTED_PAWN[1][14] = 0xa0;
      AttackTablesTest::EXPECTED_PAWN[1][15] = 0x40;
      AttackTablesTest::EXPECTED_PAWN[1][16] = 0x200;
      AttackTablesTest::EXPECTED_PAWN[1][17] = 0x500;
      AttackTablesTest::EXPECTED_PAWN[1][18] = 0xa00;
      AttackTablesTest::EXPECTED_PAWN[1][19] = 0x1400;
      AttackTablesTest::EXPECTED_PAWN[1][20] = 0x2800;
      AttackTablesTest::EXPECTED_PAWN[1][21] = 0x5000;
      AttackTablesTest::EXPECTED_PAWN[1][22] = 0xa000;
      AttackTablesTest::EXPECTED_PAWN[1][23] = 0x4000;
      AttackTablesTest::EXPECTED_PAWN[1][24] = 0x20000;
      AttackTablesTest::EXPECTED_PAWN[1][25] = 0x50000;
      AttackTablesTest::EXPECTED_PAWN[1][26] = 0xa0000;
      AttackTablesTest::EXPECTED_PAWN[1][27] = 0x140000;
      AttackTablesTest::EXPECTED_PAWN[1][28] = 0x280000;
      AttackTablesTest::EXPECTED_PAWN[1][29] = 0x500000;
      AttackTablesTest::EXPECTED_PAWN[1][30] = 0xa00000;
      AttackTablesTest::EXPECTED_PAWN[1][31] = 0x400000;
      AttackTablesTest::EXPECTED_PAWN[1][32] = 0x2000000;
      AttackTablesTest::EXPECTED_PAWN[1][33] = 0x5000000;
      AttackTablesTest::EXPECTED_PAWN[1][34] = 0xa000000;
      AttackTablesTest::EXPECTED_PAWN[1][35] = 0x14000000;
      AttackTablesTest::EXPECTED_PAWN[1][36] = 0x28000000;
      AttackTablesTest::EXPECTED_PAWN[1][37] = 0x50000000;
      AttackTablesTest::EXPECTED_PAWN[1][38] = 0xa0000000;
      AttackTablesTest::EXPECTED_PAWN[1][39] = 0x40000000;
      AttackTablesTest::EXPECTED_PAWN[1][40] = 0x200000000;
      AttackTablesTest::EXPECTED_PAWN[1][41] = 0x500000000;
      AttackTablesTest::EXPECTED_PAWN[1][42] = 0xa00000000;
      AttackTablesTest::EXPECTED_PAWN[1][43] = 0x1400000000;
      AttackTablesTest::EXPECTED_PAWN[1][44] = 0x2800000000;
      AttackTablesTest::EXPECTED_PAWN[1][45] = 0x5000000000;
      AttackTablesTest::EXPECTED_PAWN[1][46] = 0xa000000000;
      AttackTablesTest::EXPECTED_PAWN[1][47] = 0x4000000000;
      AttackTablesTest::EXPECTED_PAWN[1][48] = 0x20000000000;
      AttackTablesTest::EXPECTED_PAWN[1][49] = 0x50000000000;
      AttackTablesTest::EXPECTED_PAWN[1][50] = 0xa0000000000;
      AttackTablesTest::EXPECTED_PAWN[1][51] = 0x140000000000;
      AttackTablesTest::EXPECTED_PAWN[1][52] = 0x280000000000;
      AttackTablesTest::EXPECTED_PAWN[1][53] = 0x500000000000;
      AttackTablesTest::EXPECTED_PAWN[1][54] = 0xa00000000000;
      AttackTablesTest::EXPECTED_PAWN[1][55] = 0x400000000000;
      AttackTablesTest::EXPECTED_PAWN[1][56] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][57] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][58] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][59] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][60] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][61] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][62] = 0x0;
      AttackTablesTest::EXPECTED_PAWN[1][63] = 0x0;

      /* Expected knight attack table */
      AttackTablesTest::EXPECTED_KNIGHT[0] = 0x20400;
      AttackTablesTest::EXPECTED_KNIGHT[1] = 0x50800;
      AttackTablesTest::EXPECTED_KNIGHT[2] = 0xa1100;
      AttackTablesTest::EXPECTED_KNIGHT[3] = 0x142200;
      AttackTablesTest::EXPECTED_KNIGHT[4] = 0x284400;
      AttackTablesTest::EXPECTED_KNIGHT[5] = 0x508800;
      AttackTablesTest::EXPECTED_KNIGHT[6] = 0xa01000;
      AttackTablesTest::EXPECTED_KNIGHT[7] = 0x402000;
      AttackTablesTest::EXPECTED_KNIGHT[8] = 0x2040004;
      AttackTablesTest::EXPECTED_KNIGHT[9] = 0x5080008;
      AttackTablesTest::EXPECTED_KNIGHT[10] = 0xa110011;
      AttackTablesTest::EXPECTED_KNIGHT[11] = 0x14220022;
      AttackTablesTest::EXPECTED_KNIGHT[12] = 0x28440044;
      AttackTablesTest::EXPECTED_KNIGHT[13] = 0x50880088;
      AttackTablesTest::EXPECTED_KNIGHT[14] = 0xa0100010;
      AttackTablesTest::EXPECTED_KNIGHT[15] = 0x40200020;
      AttackTablesTest::EXPECTED_KNIGHT[16] = 0x204000402;
      AttackTablesTest::EXPECTED_KNIGHT[17] = 0x508000805;
      AttackTablesTest::EXPECTED_KNIGHT[18] = 0xa1100110a;
      AttackTablesTest::EXPECTED_KNIGHT[19] = 0x1422002214;
      AttackTablesTest::EXPECTED_KNIGHT[20] = 0x2844004428;
      AttackTablesTest::EXPECTED_KNIGHT[21] = 0x5088008850;
      AttackTablesTest::EXPECTED_KNIGHT[22] = 0xa0100010a0;
      AttackTablesTest::EXPECTED_KNIGHT[23] = 0x4020002040;
      AttackTablesTest::EXPECTED_KNIGHT[24] = 0x20400040200;
      AttackTablesTest::EXPECTED_KNIGHT[25] = 0x50800080500;
      AttackTablesTest::EXPECTED_KNIGHT[26] = 0xa1100110a00;
      AttackTablesTest::EXPECTED_KNIGHT[27] = 0x142200221400;
      AttackTablesTest::EXPECTED_KNIGHT[28] = 0x284400442800;
      AttackTablesTest::EXPECTED_KNIGHT[29] = 0x508800885000;
      AttackTablesTest::EXPECTED_KNIGHT[30] = 0xa0100010a000;
      AttackTablesTest::EXPECTED_KNIGHT[31] = 0x402000204000;
      AttackTablesTest::EXPECTED_KNIGHT[32] = 0x2040004020000;
      AttackTablesTest::EXPECTED_KNIGHT[33] = 0x5080008050000;
      AttackTablesTest::EXPECTED_KNIGHT[34] = 0xa1100110a0000;
      AttackTablesTest::EXPECTED_KNIGHT[35] = 0x14220022140000;
      AttackTablesTest::EXPECTED_KNIGHT[36] = 0x28440044280000;
      AttackTablesTest::EXPECTED_KNIGHT[37] = 0x50880088500000;
      AttackTablesTest::EXPECTED_KNIGHT[38] = 0xa0100010a00000;
      AttackTablesTest::EXPECTED_KNIGHT[39] = 0x40200020400000;
      AttackTablesTest::EXPECTED_KNIGHT[40] = 0x204000402000000;
      AttackTablesTest::EXPECTED_KNIGHT[41] = 0x508000805000000;
      AttackTablesTest::EXPECTED_KNIGHT[42] = 0xa1100110a000000;
      AttackTablesTest::EXPECTED_KNIGHT[43] = 0x1422002214000000;
      AttackTablesTest::EXPECTED_KNIGHT[44] = 0x2844004428000000;
      AttackTablesTest::EXPECTED_KNIGHT[45] = 0x5088008850000000;
      AttackTablesTest::EXPECTED_KNIGHT[46] = 0xa0100010a0000000;
      AttackTablesTest::EXPECTED_KNIGHT[47] = 0x4020002040000000;
      AttackTablesTest::EXPECTED_KNIGHT[48] = 0x400040200000000;
      AttackTablesTest::EXPECTED_KNIGHT[49] = 0x800080500000000;
      AttackTablesTest::EXPECTED_KNIGHT[50] = 0x1100110a00000000;
      AttackTablesTest::EXPECTED_KNIGHT[51] = 0x2200221400000000;
      AttackTablesTest::EXPECTED_KNIGHT[52] = 0x4400442800000000;
      AttackTablesTest::EXPECTED_KNIGHT[53] = 0x8800885000000000;
      AttackTablesTest::EXPECTED_KNIGHT[54] = 0x100010a000000000;
      AttackTablesTest::EXPECTED_KNIGHT[55] = 0x2000204000000000;
      AttackTablesTest::EXPECTED_KNIGHT[56] = 0x4020000000000;
      AttackTablesTest::EXPECTED_KNIGHT[57] = 0x8050000000000;
      AttackTablesTest::EXPECTED_KNIGHT[58] = 0x110a0000000000;
      AttackTablesTest::EXPECTED_KNIGHT[59] = 0x22140000000000;
      AttackTablesTest::EXPECTED_KNIGHT[60] = 0x44280000000000;
      AttackTablesTest::EXPECTED_KNIGHT[61] = 0x88500000000000;
      AttackTablesTest::EXPECTED_KNIGHT[62] = 0x10a00000000000;
      AttackTablesTest::EXPECTED_KNIGHT[63] = 0x20400000000000;

      /* Expected bishop attack table */
      AttackTablesTest::EXPECTED_BISHOP[0] = 0x8040201008040200;
      AttackTablesTest::EXPECTED_BISHOP[1] = 0x80402010080500;
      AttackTablesTest::EXPECTED_BISHOP[2] = 0x804020110a00;
      AttackTablesTest::EXPECTED_BISHOP[3] = 0x8041221400;
      AttackTablesTest::EXPECTED_BISHOP[4] = 0x182442800;
      AttackTablesTest::EXPECTED_BISHOP[5] = 0x10204885000;
      AttackTablesTest::EXPECTED_BISHOP[6] = 0x102040810a000;
      AttackTablesTest::EXPECTED_BISHOP[7] = 0x102040810204000;
      AttackTablesTest::EXPECTED_BISHOP[8] = 0x4020100804020002;
      AttackTablesTest::EXPECTED_BISHOP[9] = 0x8040201008050005;
      AttackTablesTest::EXPECTED_BISHOP[10] = 0x804020110a000a;
      AttackTablesTest::EXPECTED_BISHOP[11] = 0x804122140014;
      AttackTablesTest::EXPECTED_BISHOP[12] = 0x18244280028;
      AttackTablesTest::EXPECTED_BISHOP[13] = 0x1020488500050;
      AttackTablesTest::EXPECTED_BISHOP[14] = 0x102040810a000a0;
      AttackTablesTest::EXPECTED_BISHOP[15] = 0x204081020400040;
      AttackTablesTest::EXPECTED_BISHOP[16] = 0x2010080402000204;
      AttackTablesTest::EXPECTED_BISHOP[17] = 0x4020100805000508;
      AttackTablesTest::EXPECTED_BISHOP[18] = 0x804020110a000a11;
      AttackTablesTest::EXPECTED_BISHOP[19] = 0x80412214001422;
      AttackTablesTest::EXPECTED_BISHOP[20] = 0x1824428002844;
      AttackTablesTest::EXPECTED_BISHOP[21] = 0x102048850005088;
      AttackTablesTest::EXPECTED_BISHOP[22] = 0x2040810a000a010;
      AttackTablesTest::EXPECTED_BISHOP[23] = 0x408102040004020;
      AttackTablesTest::EXPECTED_BISHOP[24] = 0x1008040200020408;
      AttackTablesTest::EXPECTED_BISHOP[25] = 0x2010080500050810;
      AttackTablesTest::EXPECTED_BISHOP[26] = 0x4020110a000a1120;
      AttackTablesTest::EXPECTED_BISHOP[27] = 0x8041221400142241;
      AttackTablesTest::EXPECTED_BISHOP[28] = 0x182442800284482;
      AttackTablesTest::EXPECTED_BISHOP[29] = 0x204885000508804;
      AttackTablesTest::EXPECTED_BISHOP[30] = 0x40810a000a01008;
      AttackTablesTest::EXPECTED_BISHOP[31] = 0x810204000402010;
      AttackTablesTest::EXPECTED_BISHOP[32] = 0x804020002040810;
      AttackTablesTest::EXPECTED_BISHOP[33] = 0x1008050005081020;
      AttackTablesTest::EXPECTED_BISHOP[34] = 0x20110a000a112040;
      AttackTablesTest::EXPECTED_BISHOP[35] = 0x4122140014224180;
      AttackTablesTest::EXPECTED_BISHOP[36] = 0x8244280028448201;
      AttackTablesTest::EXPECTED_BISHOP[37] = 0x488500050880402;
      AttackTablesTest::EXPECTED_BISHOP[38] = 0x810a000a0100804;
      AttackTablesTest::EXPECTED_BISHOP[39] = 0x1020400040201008;
      AttackTablesTest::EXPECTED_BISHOP[40] = 0x402000204081020;
      AttackTablesTest::EXPECTED_BISHOP[41] = 0x805000508102040;
      AttackTablesTest::EXPECTED_BISHOP[42] = 0x110a000a11204080;
      AttackTablesTest::EXPECTED_BISHOP[43] = 0x2214001422418000;
      AttackTablesTest::EXPECTED_BISHOP[44] = 0x4428002844820100;
      AttackTablesTest::EXPECTED_BISHOP[45] = 0x8850005088040201;
      AttackTablesTest::EXPECTED_BISHOP[46] = 0x10a000a010080402;
      AttackTablesTest::EXPECTED_BISHOP[47] = 0x2040004020100804;
      AttackTablesTest::EXPECTED_BISHOP[48] = 0x200020408102040;
      AttackTablesTest::EXPECTED_BISHOP[49] = 0x500050810204080;
      AttackTablesTest::EXPECTED_BISHOP[50] = 0xa000a1120408000;
      AttackTablesTest::EXPECTED_BISHOP[51] = 0x1400142241800000;
      AttackTablesTest::EXPECTED_BISHOP[52] = 0x2800284482010000;
      AttackTablesTest::EXPECTED_BISHOP[53] = 0x5000508804020100;
      AttackTablesTest::EXPECTED_BISHOP[54] = 0xa000a01008040201;
      AttackTablesTest::EXPECTED_BISHOP[55] = 0x4000402010080402;
      AttackTablesTest::EXPECTED_BISHOP[56] = 0x2040810204080;
      AttackTablesTest::EXPECTED_BISHOP[57] = 0x5081020408000;
      AttackTablesTest::EXPECTED_BISHOP[58] = 0xa112040800000;
      AttackTablesTest::EXPECTED_BISHOP[59] = 0x14224180000000;
      AttackTablesTest::EXPECTED_BISHOP[60] = 0x28448201000000;
      AttackTablesTest::EXPECTED_BISHOP[61] = 0x50880402010000;
      AttackTablesTest::EXPECTED_BISHOP[62] = 0xa0100804020100;
      AttackTablesTest::EXPECTED_BISHOP[63] = 0x40201008040201;

      /* Expected rook attack table */
      AttackTablesTest::EXPECTED_ROOK[0] = 0x1010101010101fe;
      AttackTablesTest::EXPECTED_ROOK[1] = 0x2020202020202fd;
      AttackTablesTest::EXPECTED_ROOK[2] = 0x4040404040404fb;
      AttackTablesTest::EXPECTED_ROOK[3] = 0x8080808080808f7;
      AttackTablesTest::EXPECTED_ROOK[4] = 0x10101010101010ef;
      AttackTablesTest::EXPECTED_ROOK[5] = 0x20202020202020df;
      AttackTablesTest::EXPECTED_ROOK[6] = 0x40404040404040bf;
      AttackTablesTest::EXPECTED_ROOK[7] = 0x808080808080807f;
      AttackTablesTest::EXPECTED_ROOK[8] = 0x10101010101fe01;
      AttackTablesTest::EXPECTED_ROOK[9] = 0x20202020202fd02;
      AttackTablesTest::EXPECTED_ROOK[10] = 0x40404040404fb04;
      AttackTablesTest::EXPECTED_ROOK[11] = 0x80808080808f708;
      AttackTablesTest::EXPECTED_ROOK[12] = 0x101010101010ef10;
      AttackTablesTest::EXPECTED_ROOK[13] = 0x202020202020df20;
      AttackTablesTest::EXPECTED_ROOK[14] = 0x404040404040bf40;
      AttackTablesTest::EXPECTED_ROOK[15] = 0x8080808080807f80;
      AttackTablesTest::EXPECTED_ROOK[16] = 0x101010101fe0101;
      AttackTablesTest::EXPECTED_ROOK[17] = 0x202020202fd0202;
      AttackTablesTest::EXPECTED_ROOK[18] = 0x404040404fb0404;
      AttackTablesTest::EXPECTED_ROOK[19] = 0x808080808f70808;
      AttackTablesTest::EXPECTED_ROOK[20] = 0x1010101010ef1010;
      AttackTablesTest::EXPECTED_ROOK[21] = 0x2020202020df2020;
      AttackTablesTest::EXPECTED_ROOK[22] = 0x4040404040bf4040;
      AttackTablesTest::EXPECTED_ROOK[23] = 0x80808080807f8080;
      AttackTablesTest::EXPECTED_ROOK[24] = 0x1010101fe010101;
      AttackTablesTest::EXPECTED_ROOK[25] = 0x2020202fd020202;
      AttackTablesTest::EXPECTED_ROOK[26] = 0x4040404fb040404;
      AttackTablesTest::EXPECTED_ROOK[27] = 0x8080808f7080808;
      AttackTablesTest::EXPECTED_ROOK[28] = 0x10101010ef101010;
      AttackTablesTest::EXPECTED_ROOK[29] = 0x20202020df202020;
      AttackTablesTest::EXPECTED_ROOK[30] = 0x40404040bf404040;
      AttackTablesTest::EXPECTED_ROOK[31] = 0x808080807f808080;
      AttackTablesTest::EXPECTED_ROOK[32] = 0x10101fe01010101;
      AttackTablesTest::EXPECTED_ROOK[33] = 0x20202fd02020202;
      AttackTablesTest::EXPECTED_ROOK[34] = 0x40404fb04040404;
      AttackTablesTest::EXPECTED_ROOK[35] = 0x80808f708080808;
      AttackTablesTest::EXPECTED_ROOK[36] = 0x101010ef10101010;
      AttackTablesTest::EXPECTED_ROOK[37] = 0x202020df20202020;
      AttackTablesTest::EXPECTED_ROOK[38] = 0x404040bf40404040;
      AttackTablesTest::EXPECTED_ROOK[39] = 0x8080807f80808080;
      AttackTablesTest::EXPECTED_ROOK[40] = 0x101fe0101010101;
      AttackTablesTest::EXPECTED_ROOK[41] = 0x202fd0202020202;
      AttackTablesTest::EXPECTED_ROOK[42] = 0x404fb0404040404;
      AttackTablesTest::EXPECTED_ROOK[43] = 0x808f70808080808;
      AttackTablesTest::EXPECTED_ROOK[44] = 0x1010ef1010101010;
      AttackTablesTest::EXPECTED_ROOK[45] = 0x2020df2020202020;
      AttackTablesTest::EXPECTED_ROOK[46] = 0x4040bf4040404040;
      AttackTablesTest::EXPECTED_ROOK[47] = 0x80807f8080808080;
      AttackTablesTest::EXPECTED_ROOK[48] = 0x1fe010101010101;
      AttackTablesTest::EXPECTED_ROOK[49] = 0x2fd020202020202;
      AttackTablesTest::EXPECTED_ROOK[50] = 0x4fb040404040404;
      AttackTablesTest::EXPECTED_ROOK[51] = 0x8f7080808080808;
      AttackTablesTest::EXPECTED_ROOK[52] = 0x10ef101010101010;
      AttackTablesTest::EXPECTED_ROOK[53] = 0x20df202020202020;
      AttackTablesTest::EXPECTED_ROOK[54] = 0x40bf404040404040;
      AttackTablesTest::EXPECTED_ROOK[55] = 0x807f808080808080;
      AttackTablesTest::EXPECTED_ROOK[56] = 0xfe01010101010101;
      AttackTablesTest::EXPECTED_ROOK[57] = 0xfd02020202020202;
      AttackTablesTest::EXPECTED_ROOK[58] = 0xfb04040404040404;
      AttackTablesTest::EXPECTED_ROOK[59] = 0xf708080808080808;
      AttackTablesTest::EXPECTED_ROOK[60] = 0xef10101010101010;
      AttackTablesTest::EXPECTED_ROOK[61] = 0xdf20202020202020;
      AttackTablesTest::EXPECTED_ROOK[62] = 0xbf40404040404040;
      AttackTablesTest::EXPECTED_ROOK[63] = 0x7f80808080808080;

      AttackTablesTest::EXPECTED_QUEEN[0] = AttackTablesTest::EXPECTED_BISHOP[0] | AttackTablesTest::EXPECTED_ROOK[0];
      AttackTablesTest::EXPECTED_QUEEN[1] = AttackTablesTest::EXPECTED_BISHOP[1] | AttackTablesTest::EXPECTED_ROOK[1];
      AttackTablesTest::EXPECTED_QUEEN[2] = AttackTablesTest::EXPECTED_BISHOP[2] | AttackTablesTest::EXPECTED_ROOK[2];
      AttackTablesTest::EXPECTED_QUEEN[3] = AttackTablesTest::EXPECTED_BISHOP[3] | AttackTablesTest::EXPECTED_ROOK[3];
      AttackTablesTest::EXPECTED_QUEEN[4] = AttackTablesTest::EXPECTED_BISHOP[4] | AttackTablesTest::EXPECTED_ROOK[4];
      AttackTablesTest::EXPECTED_QUEEN[5] = AttackTablesTest::EXPECTED_BISHOP[5] | AttackTablesTest::EXPECTED_ROOK[5];
      AttackTablesTest::EXPECTED_QUEEN[6] = AttackTablesTest::EXPECTED_BISHOP[6] | AttackTablesTest::EXPECTED_ROOK[6];
      AttackTablesTest::EXPECTED_QUEEN[7] = AttackTablesTest::EXPECTED_BISHOP[7] | AttackTablesTest::EXPECTED_ROOK[7];
      AttackTablesTest::EXPECTED_QUEEN[8] = AttackTablesTest::EXPECTED_BISHOP[8] | AttackTablesTest::EXPECTED_ROOK[8];
      AttackTablesTest::EXPECTED_QUEEN[9] = AttackTablesTest::EXPECTED_BISHOP[9] | AttackTablesTest::EXPECTED_ROOK[9];
      AttackTablesTest::EXPECTED_QUEEN[10] = AttackTablesTest::EXPECTED_BISHOP[10] | AttackTablesTest::EXPECTED_ROOK[10];
      AttackTablesTest::EXPECTED_QUEEN[11] = AttackTablesTest::EXPECTED_BISHOP[11] | AttackTablesTest::EXPECTED_ROOK[11];
      AttackTablesTest::EXPECTED_QUEEN[12] = AttackTablesTest::EXPECTED_BISHOP[12] | AttackTablesTest::EXPECTED_ROOK[12];
      AttackTablesTest::EXPECTED_QUEEN[13] = AttackTablesTest::EXPECTED_BISHOP[13] | AttackTablesTest::EXPECTED_ROOK[13];
      AttackTablesTest::EXPECTED_QUEEN[14] = AttackTablesTest::EXPECTED_BISHOP[14] | AttackTablesTest::EXPECTED_ROOK[14];
      AttackTablesTest::EXPECTED_QUEEN[15] = AttackTablesTest::EXPECTED_BISHOP[15] | AttackTablesTest::EXPECTED_ROOK[15];
      AttackTablesTest::EXPECTED_QUEEN[16] = AttackTablesTest::EXPECTED_BISHOP[16] | AttackTablesTest::EXPECTED_ROOK[16];
      AttackTablesTest::EXPECTED_QUEEN[17] = AttackTablesTest::EXPECTED_BISHOP[17] | AttackTablesTest::EXPECTED_ROOK[17];
      AttackTablesTest::EXPECTED_QUEEN[18] = AttackTablesTest::EXPECTED_BISHOP[18] | AttackTablesTest::EXPECTED_ROOK[18];
      AttackTablesTest::EXPECTED_QUEEN[19] = AttackTablesTest::EXPECTED_BISHOP[19] | AttackTablesTest::EXPECTED_ROOK[19];
      AttackTablesTest::EXPECTED_QUEEN[20] = AttackTablesTest::EXPECTED_BISHOP[20] | AttackTablesTest::EXPECTED_ROOK[20];
      AttackTablesTest::EXPECTED_QUEEN[21] = AttackTablesTest::EXPECTED_BISHOP[21] | AttackTablesTest::EXPECTED_ROOK[21];
      AttackTablesTest::EXPECTED_QUEEN[22] = AttackTablesTest::EXPECTED_BISHOP[22] | AttackTablesTest::EXPECTED_ROOK[22];
      AttackTablesTest::EXPECTED_QUEEN[23] = AttackTablesTest::EXPECTED_BISHOP[23] | AttackTablesTest::EXPECTED_ROOK[23];
      AttackTablesTest::EXPECTED_QUEEN[24] = AttackTablesTest::EXPECTED_BISHOP[24] | AttackTablesTest::EXPECTED_ROOK[24];
      AttackTablesTest::EXPECTED_QUEEN[25] = AttackTablesTest::EXPECTED_BISHOP[25] | AttackTablesTest::EXPECTED_ROOK[25];
      AttackTablesTest::EXPECTED_QUEEN[26] = AttackTablesTest::EXPECTED_BISHOP[26] | AttackTablesTest::EXPECTED_ROOK[26];
      AttackTablesTest::EXPECTED_QUEEN[27] = AttackTablesTest::EXPECTED_BISHOP[27] | AttackTablesTest::EXPECTED_ROOK[27];
      AttackTablesTest::EXPECTED_QUEEN[28] = AttackTablesTest::EXPECTED_BISHOP[28] | AttackTablesTest::EXPECTED_ROOK[28];
      AttackTablesTest::EXPECTED_QUEEN[29] = AttackTablesTest::EXPECTED_BISHOP[29] | AttackTablesTest::EXPECTED_ROOK[29];
      AttackTablesTest::EXPECTED_QUEEN[30] = AttackTablesTest::EXPECTED_BISHOP[30] | AttackTablesTest::EXPECTED_ROOK[30];
      AttackTablesTest::EXPECTED_QUEEN[31] = AttackTablesTest::EXPECTED_BISHOP[31] | AttackTablesTest::EXPECTED_ROOK[31];
      AttackTablesTest::EXPECTED_QUEEN[32] = AttackTablesTest::EXPECTED_BISHOP[32] | AttackTablesTest::EXPECTED_ROOK[32];
      AttackTablesTest::EXPECTED_QUEEN[33] = AttackTablesTest::EXPECTED_BISHOP[33] | AttackTablesTest::EXPECTED_ROOK[33];
      AttackTablesTest::EXPECTED_QUEEN[34] = AttackTablesTest::EXPECTED_BISHOP[34] | AttackTablesTest::EXPECTED_ROOK[34];
      AttackTablesTest::EXPECTED_QUEEN[35] = AttackTablesTest::EXPECTED_BISHOP[35] | AttackTablesTest::EXPECTED_ROOK[35];
      AttackTablesTest::EXPECTED_QUEEN[36] = AttackTablesTest::EXPECTED_BISHOP[36] | AttackTablesTest::EXPECTED_ROOK[36];
      AttackTablesTest::EXPECTED_QUEEN[37] = AttackTablesTest::EXPECTED_BISHOP[37] | AttackTablesTest::EXPECTED_ROOK[37];
      AttackTablesTest::EXPECTED_QUEEN[38] = AttackTablesTest::EXPECTED_BISHOP[38] | AttackTablesTest::EXPECTED_ROOK[38];
      AttackTablesTest::EXPECTED_QUEEN[39] = AttackTablesTest::EXPECTED_BISHOP[39] | AttackTablesTest::EXPECTED_ROOK[39];
      AttackTablesTest::EXPECTED_QUEEN[40] = AttackTablesTest::EXPECTED_BISHOP[40] | AttackTablesTest::EXPECTED_ROOK[40];
      AttackTablesTest::EXPECTED_QUEEN[41] = AttackTablesTest::EXPECTED_BISHOP[41] | AttackTablesTest::EXPECTED_ROOK[41];
      AttackTablesTest::EXPECTED_QUEEN[42] = AttackTablesTest::EXPECTED_BISHOP[42] | AttackTablesTest::EXPECTED_ROOK[42];
      AttackTablesTest::EXPECTED_QUEEN[43] = AttackTablesTest::EXPECTED_BISHOP[43] | AttackTablesTest::EXPECTED_ROOK[43];
      AttackTablesTest::EXPECTED_QUEEN[44] = AttackTablesTest::EXPECTED_BISHOP[44] | AttackTablesTest::EXPECTED_ROOK[44];
      AttackTablesTest::EXPECTED_QUEEN[45] = AttackTablesTest::EXPECTED_BISHOP[45] | AttackTablesTest::EXPECTED_ROOK[45];
      AttackTablesTest::EXPECTED_QUEEN[46] = AttackTablesTest::EXPECTED_BISHOP[46] | AttackTablesTest::EXPECTED_ROOK[46];
      AttackTablesTest::EXPECTED_QUEEN[47] = AttackTablesTest::EXPECTED_BISHOP[47] | AttackTablesTest::EXPECTED_ROOK[47];
      AttackTablesTest::EXPECTED_QUEEN[48] = AttackTablesTest::EXPECTED_BISHOP[48] | AttackTablesTest::EXPECTED_ROOK[48];
      AttackTablesTest::EXPECTED_QUEEN[49] = AttackTablesTest::EXPECTED_BISHOP[49] | AttackTablesTest::EXPECTED_ROOK[49];
      AttackTablesTest::EXPECTED_QUEEN[50] = AttackTablesTest::EXPECTED_BISHOP[50] | AttackTablesTest::EXPECTED_ROOK[50];
      AttackTablesTest::EXPECTED_QUEEN[51] = AttackTablesTest::EXPECTED_BISHOP[51] | AttackTablesTest::EXPECTED_ROOK[51];
      AttackTablesTest::EXPECTED_QUEEN[52] = AttackTablesTest::EXPECTED_BISHOP[52] | AttackTablesTest::EXPECTED_ROOK[52];
      AttackTablesTest::EXPECTED_QUEEN[53] = AttackTablesTest::EXPECTED_BISHOP[53] | AttackTablesTest::EXPECTED_ROOK[53];
      AttackTablesTest::EXPECTED_QUEEN[54] = AttackTablesTest::EXPECTED_BISHOP[54] | AttackTablesTest::EXPECTED_ROOK[54];
      AttackTablesTest::EXPECTED_QUEEN[55] = AttackTablesTest::EXPECTED_BISHOP[55] | AttackTablesTest::EXPECTED_ROOK[55];
      AttackTablesTest::EXPECTED_QUEEN[56] = AttackTablesTest::EXPECTED_BISHOP[56] | AttackTablesTest::EXPECTED_ROOK[56];
      AttackTablesTest::EXPECTED_QUEEN[57] = AttackTablesTest::EXPECTED_BISHOP[57] | AttackTablesTest::EXPECTED_ROOK[57];
      AttackTablesTest::EXPECTED_QUEEN[58] = AttackTablesTest::EXPECTED_BISHOP[58] | AttackTablesTest::EXPECTED_ROOK[58];
      AttackTablesTest::EXPECTED_QUEEN[59] = AttackTablesTest::EXPECTED_BISHOP[59] | AttackTablesTest::EXPECTED_ROOK[59];
      AttackTablesTest::EXPECTED_QUEEN[60] = AttackTablesTest::EXPECTED_BISHOP[60] | AttackTablesTest::EXPECTED_ROOK[60];
      AttackTablesTest::EXPECTED_QUEEN[61] = AttackTablesTest::EXPECTED_BISHOP[61] | AttackTablesTest::EXPECTED_ROOK[61];
      AttackTablesTest::EXPECTED_QUEEN[62] = AttackTablesTest::EXPECTED_BISHOP[62] | AttackTablesTest::EXPECTED_ROOK[62];
      AttackTablesTest::EXPECTED_QUEEN[63] = AttackTablesTest::EXPECTED_BISHOP[63] | AttackTablesTest::EXPECTED_ROOK[63];

      /* Expected king attack table */
      AttackTablesTest::EXPECTED_KING[0] = 0x302;
      AttackTablesTest::EXPECTED_KING[1] = 0x705;
      AttackTablesTest::EXPECTED_KING[2] = 0xe0a;
      AttackTablesTest::EXPECTED_KING[3] = 0x1c14;
      AttackTablesTest::EXPECTED_KING[4] = 0x3828;
      AttackTablesTest::EXPECTED_KING[5] = 0x7050;
      AttackTablesTest::EXPECTED_KING[6] = 0xe0a0;
      AttackTablesTest::EXPECTED_KING[7] = 0xc040;
      AttackTablesTest::EXPECTED_KING[8] = 0x30203;
      AttackTablesTest::EXPECTED_KING[9] = 0x70507;
      AttackTablesTest::EXPECTED_KING[10] = 0xe0a0e;
      AttackTablesTest::EXPECTED_KING[11] = 0x1c141c;
      AttackTablesTest::EXPECTED_KING[12] = 0x382838;
      AttackTablesTest::EXPECTED_KING[13] = 0x705070;
      AttackTablesTest::EXPECTED_KING[14] = 0xe0a0e0;
      AttackTablesTest::EXPECTED_KING[15] = 0xc040c0;
      AttackTablesTest::EXPECTED_KING[16] = 0x3020300;
      AttackTablesTest::EXPECTED_KING[17] = 0x7050700;
      AttackTablesTest::EXPECTED_KING[18] = 0xe0a0e00;
      AttackTablesTest::EXPECTED_KING[19] = 0x1c141c00;
      AttackTablesTest::EXPECTED_KING[20] = 0x38283800;
      AttackTablesTest::EXPECTED_KING[21] = 0x70507000;
      AttackTablesTest::EXPECTED_KING[22] = 0xe0a0e000;
      AttackTablesTest::EXPECTED_KING[23] = 0xc040c000;
      AttackTablesTest::EXPECTED_KING[24] = 0x302030000;
      AttackTablesTest::EXPECTED_KING[25] = 0x705070000;
      AttackTablesTest::EXPECTED_KING[26] = 0xe0a0e0000;
      AttackTablesTest::EXPECTED_KING[27] = 0x1c141c0000;
      AttackTablesTest::EXPECTED_KING[28] = 0x3828380000;
      AttackTablesTest::EXPECTED_KING[29] = 0x7050700000;
      AttackTablesTest::EXPECTED_KING[30] = 0xe0a0e00000;
      AttackTablesTest::EXPECTED_KING[31] = 0xc040c00000;
      AttackTablesTest::EXPECTED_KING[32] = 0x30203000000;
      AttackTablesTest::EXPECTED_KING[33] = 0x70507000000;
      AttackTablesTest::EXPECTED_KING[34] = 0xe0a0e000000;
      AttackTablesTest::EXPECTED_KING[35] = 0x1c141c000000;
      AttackTablesTest::EXPECTED_KING[36] = 0x382838000000;
      AttackTablesTest::EXPECTED_KING[37] = 0x705070000000;
      AttackTablesTest::EXPECTED_KING[38] = 0xe0a0e0000000;
      AttackTablesTest::EXPECTED_KING[39] = 0xc040c0000000;
      AttackTablesTest::EXPECTED_KING[40] = 0x3020300000000;
      AttackTablesTest::EXPECTED_KING[41] = 0x7050700000000;
      AttackTablesTest::EXPECTED_KING[42] = 0xe0a0e00000000;
      AttackTablesTest::EXPECTED_KING[43] = 0x1c141c00000000;
      AttackTablesTest::EXPECTED_KING[44] = 0x38283800000000;
      AttackTablesTest::EXPECTED_KING[45] = 0x70507000000000;
      AttackTablesTest::EXPECTED_KING[46] = 0xe0a0e000000000;
      AttackTablesTest::EXPECTED_KING[47] = 0xc040c000000000;
      AttackTablesTest::EXPECTED_KING[48] = 0x302030000000000;
      AttackTablesTest::EXPECTED_KING[49] = 0x705070000000000;
      AttackTablesTest::EXPECTED_KING[50] = 0xe0a0e0000000000;
      AttackTablesTest::EXPECTED_KING[51] = 0x1c141c0000000000;
      AttackTablesTest::EXPECTED_KING[52] = 0x3828380000000000;
      AttackTablesTest::EXPECTED_KING[53] = 0x7050700000000000;
      AttackTablesTest::EXPECTED_KING[54] = 0xe0a0e00000000000;
      AttackTablesTest::EXPECTED_KING[55] = 0xc040c00000000000;
      AttackTablesTest::EXPECTED_KING[56] = 0x203000000000000;
      AttackTablesTest::EXPECTED_KING[57] = 0x507000000000000;
      AttackTablesTest::EXPECTED_KING[58] = 0xa0e000000000000;
      AttackTablesTest::EXPECTED_KING[59] = 0x141c000000000000;
      AttackTablesTest::EXPECTED_KING[60] = 0x2838000000000000;
      AttackTablesTest::EXPECTED_KING[61] = 0x5070000000000000;
      AttackTablesTest::EXPECTED_KING[62] = 0xa0e0000000000000;
      AttackTablesTest::EXPECTED_KING[63] = 0x40c0000000000000;
   }

  static void TearDownTestSuite()
  {
		// Code here will be called after the last test.
  }

   // Class members declared here can be used by all tests in the test suite.
   // To share resources between tests, declare them as static class members,
   // then add their definition just below the test fixture class.
   static u64 EXPECTED_PAWN[2][64];
   static u64 EXPECTED_KNIGHT[64];
   static u64 EXPECTED_BISHOP[64];
   static u64 EXPECTED_ROOK[64];
   static u64 EXPECTED_QUEEN[64];
   static u64 EXPECTED_KING[64];
};

u64 AttackTablesTest::EXPECTED_PAWN[2][64];
u64 AttackTablesTest::EXPECTED_KNIGHT[64];
u64 AttackTablesTest::EXPECTED_BISHOP[64];
u64 AttackTablesTest::EXPECTED_ROOK[64];
u64 AttackTablesTest::EXPECTED_QUEEN[64];
u64 AttackTablesTest::EXPECTED_KING[64];

TEST_F(AttackTablesTest, whitePawnAttackTable)
{
   for (int square = 0; square < 64; square++)
   {
      EXPECT_EQ(attack_tables::PAWN_ATTACKS[0][square], EXPECTED_PAWN[0][square]);
   }
}

TEST_F(AttackTablesTest, blackPawnAttackTable)
{
   for (int square = 0; square < 64; square++)
   {
      ASSERT_EQ(attack_tables::PAWN_ATTACKS[1][square], EXPECTED_PAWN[1][square]);
   }
}

TEST_F(AttackTablesTest, knightAttackTable)
{
   for (int square = 0; square < 64; square++)
   {
      EXPECT_EQ(attack_tables::KNIGHT_ATTACKS[square], EXPECTED_KNIGHT[square]);
   }
}

// TODO: Should we add magic bitboard tests here?
// TEST_F(AttackTablesTest, bishopAttackTable)
// {
//    for (int square = 0; square < 64; square++)
//    {
//       EXPECT_EQ(attack_tables::bishop[square], EXPECTED_BISHOP[square]);
//    }
// }

// TEST_F(AttackTablesTest, rookAttackTable)
// {
//    for (int square = 0; square < 64; square++)
//    {
//       EXPECT_EQ(attack_tables::rook[square], EXPECTED_ROOK[square]);
//    }
// }

// TEST_F(AttackTablesTest, queenAttackTable)
// {
//    for (int square = 0; square < 64; square++)
//    {
//       EXPECT_EQ(attack_tables::queen[square], EXPECTED_QUEEN[square]);
//    }
// }

TEST_F(AttackTablesTest, kingAttackTable)
{
   for (int square = 0; square < 64; square++)
   {
      EXPECT_EQ(attack_tables::KING_ATTACKS[square], EXPECTED_KING[square]);
   }
}

}  // namespace
}  // namespace meatball