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
   }

  static void TearDownTestSuite()
  {
		// Code here will be called after the last test.
  }

  // Class members declared here can be used by all tests in the test suite.
  // To share resources between tests, declare them as static class members,
  // then add their definition just below the test fixture class.
  static u64 EXPECTED_PAWN[2][64];
};

u64 AttackTablesTest::EXPECTED_PAWN[2][64];

TEST_F(AttackTablesTest, whitePawnAttackTable)
{
   for (unsigned int square = 0; square < 64; square++)
   {
      EXPECT_EQ(attack_tables::pawn[0][square], EXPECTED_PAWN[0][square]);
   }
}

TEST_F(AttackTablesTest, blackPawnAttackTable)
{
   for (unsigned int square = 0; square < 64; square++)
   {
      ASSERT_EQ(attack_tables::pawn[1][square], EXPECTED_PAWN[1][square]);
   }
}

}  // namespace
}  // namespace meatball