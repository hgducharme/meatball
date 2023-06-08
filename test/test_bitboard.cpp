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
   Bitboard bitboard(bitboard::UNIVERSE);

   bitboard.clearBit(g3);

   u64 EXPECTED_BITBOARD = 0xFFFFFFFFFFBFFFFF;
   ASSERT_EQ(bitboard.getBoard(), EXPECTED_BITBOARD);
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
   Bitboard bitboard(bitboard::UNIVERSE);
   bitboard.clearBit(g3);

   ASSERT_EQ(bitboard.getBit(g3), 0);
}

TEST_F(BitboardTest, reset_ResetsBoardState)
{
   Bitboard bitboard(bitboard::UNIVERSE);

   bitboard.reset();

   ASSERT_EQ(bitboard.getBoard(), bitboard::EMPTY_BOARD);
}

TEST_F(BitboardTest, setBoard_correctlySetsBitboard)
{
   Bitboard bitboard;

   bitboard.setBoard(bitboard::UNIVERSE);

   ASSERT_EQ(bitboard.getBoard(), bitboard::UNIVERSE);
}

TEST_F(BitboardTest, bitwiseOrOperator_returnsNewBitboard)
{
   Bitboard a(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   Bitboard b(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);

   Bitboard c = a | b;

   u64 EXPECTED = 0x00FF00000000FF00;
   ASSERT_EQ(c.getBoard(), EXPECTED);
}

TEST_F(BitboardTest, shorthandBitwiseOrOperator_correctlySetsNewBoardState)
{
   Bitboard a(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   Bitboard b(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);

   a |= b;

   u64 EXPECTED = 0x08FF000000000000;

   // bitboard a has an updated state
   ASSERT_EQ(a.getBoard(), EXPECTED);

   // bitboard b is unchanged
   ASSERT_EQ(b.getBoard(), bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
}

}  // namespace
}  // namespace meatball