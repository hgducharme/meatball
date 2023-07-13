#include "../src/constants.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class ConstantsTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ConstantsTest()
  {
     // You can do set-up work for each test here.
  }

  ~ConstantsTest() override
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
  }

  static void TearDownTestSuite()
  {
   // Code here will be called after the last test.
  }

  // Class members declared here can be used by all tests in the test suite.
  // To share resources between tests, declare them as static class members,
  // then add their definition just below the test fixture class.
};

TEST_F(ConstantsTest, defaultBlackPawnStructure)
{
   u64 EXPECTED = 0x00FF000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_PAWN_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackKnightStructure)
{
   u64 EXPECTED = 0x4200000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_KNIGHT_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackBishopStructure)
{
   u64 EXPECTED = 0x2400000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_BISHOP_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackRookStructure)
{
   u64 EXPECTED = 0x8100000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_ROOK_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackQueenStructure)
{
   u64 EXPECTED = 0x0800000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_QUEEN_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackKingStructure)
{
   u64 EXPECTED = 0x1000000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_KING_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultBlackStructure)
{
   u64 EXPECTED = 0xFFFF000000000000;
   ASSERT_EQ(constants::DEFAULT_BLACK_OCCUPIED, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhitePawnStructure)
{
   u64 EXPECTED = 0xFF00;
   ASSERT_EQ(constants::DEFAULT_WHITE_PAWN_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteKnightStructure)
{
   u64 EXPECTED = 0x42;
   ASSERT_EQ(constants::DEFAULT_WHITE_KNIGHT_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteBishopStructure)
{
   u64 EXPECTED = 0x24;
   ASSERT_EQ(constants::DEFAULT_WHITE_BISHOP_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteRookStructure)
{
   u64 EXPECTED = 0x81;
   ASSERT_EQ(constants::DEFAULT_WHITE_ROOK_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteQueenStructure)
{
   u64 EXPECTED = 0x8;
   ASSERT_EQ(constants::DEFAULT_WHITE_QUEEN_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteKingStructure)
{
   u64 EXPECTED = 0x10;
   ASSERT_EQ(constants::DEFAULT_WHITE_KING_STRUCTURE, EXPECTED);
}

TEST_F(ConstantsTest, defaultWhiteStructure)
{
   u64 EXPECTED = 0xFFFF;
   ASSERT_EQ(constants::DEFAULT_WHITE_OCCUPIED, EXPECTED);
}

TEST_F(ConstantsTest, mostSignificantBitSet)
{
   u64 EXPECTED = 0x8000000000000000;
   ASSERT_EQ(constants::MOST_SIGNIFICANT_BIT_SET, EXPECTED);
}

}  // namespace
}  // namespace meatball

