#include "../src/bitboard.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class BitboardTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  BitboardTest()
  {
     // You can do set-up work for each test here.
  }

  ~BitboardTest() override
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

TEST_F(BitboardTest, defaultConstructor_shouldInitializeBoardWithStateOfZero)
{
   Bitboard bitboard;

   ASSERT_EQ(bitboard.getBoard(), bitboard::EMPTY_BOARD);
}

TEST_F(BitboardTest, constructor_canInitializeBoardWithAState)
{
   Bitboard bitboard(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   ASSERT_EQ(bitboard.getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, setBit)
{
   Bitboard bitboard;

   bitboard.setBit(g3);
   
   u64 EXPECTED_BITBOARD = 0x0000000000400000;
   ASSERT_EQ(bitboard.getBoard(), EXPECTED_BITBOARD);
}

TEST_F(BitboardTest, clearBit)
{
   Bitboard bitboard(bitboard::FULL_BOARD);

   bitboard.clearBit(g3);

   u64 EXPECTED_BOARD = 0xFFFFFFFFFFBFFFFF;
   ASSERT_EQ(bitboard.getBoard(), EXPECTED_BOARD);
}

TEST_F(BitboardTest, clearBit2)
{
   Bitboard bitboard;

   bitboard.setBit(g3);
   bitboard.clearBit(g3);

   ASSERT_EQ(bitboard.getBoard(), bitboard::EMPTY_BOARD);
}

TEST_F(BitboardTest, getBit)
{
   Bitboard bitboard(bitboard::EMPTY_BOARD);
   bitboard.setBit(g3);

   ASSERT_EQ(bitboard.getBit(g3), 1);
}

TEST_F(BitboardTest, getBit2)
{
   Bitboard bitboard(bitboard::FULL_BOARD);
   bitboard.clearBit(g3);

   ASSERT_EQ(bitboard.getBit(g3), 0);
}

TEST_F(BitboardTest, reset_ResetsBoardState)
{
   Bitboard bitboard(bitboard::FULL_BOARD);

   bitboard.reset();

   ASSERT_EQ(bitboard.getBoard(), bitboard::EMPTY_BOARD);
}

}  // namespace
}  // namespace meatball