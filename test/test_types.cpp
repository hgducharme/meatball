#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class TypesTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TypesTest()
  {
     // You can do set-up work for each test here.
  }

  ~TypesTest() override
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

  // Class members declared here can be used by all tests in the test suite.
};

TEST_F(TypesTest, defaultBlackPawnStructure)
{
   u64 EXPECTED = 0x00FF000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultBlackKnightStructure)
{
   u64 EXPECTED = 0x4200000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultBlackBishopStructure)
{
   u64 EXPECTED = 0x2400000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultBlackRookStructure)
{
   u64 EXPECTED = 0x8100000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_ROOK_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultBlackQueenStructure)
{
   u64 EXPECTED = 0x0800000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultBlackKingStructure)
{
   u64 EXPECTED = 0x1000000000000000;
   ASSERT_EQ(bitboard::DEFAULT_BLACK_KING_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhitePawnStructure)
{
   u64 EXPECTED = 0xFF00;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhiteKnightStructure)
{
   u64 EXPECTED = 0x42;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhiteBishopStructure)
{
   u64 EXPECTED = 0x24;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhiteRookStructure)
{
   u64 EXPECTED = 0x81;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_ROOK_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhiteQueenStructure)
{
   u64 EXPECTED = 0x8;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE, EXPECTED);
}

TEST_F(TypesTest, defaultWhiteKingStructure)
{
   u64 EXPECTED = 0x10;
   ASSERT_EQ(bitboard::DEFAULT_WHITE_KING_STRUCTURE, EXPECTED);
}

}  // namespace
}  // namespace meatball

