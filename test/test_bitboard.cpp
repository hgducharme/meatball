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

TEST_F(BitboardTest, constructor_createBitboardFromSquare)
{
   Bitboard d5(Square::d5);

   u64 EXPECTED = 0x800000000;
   ASSERT_EQ(d5.getBoard(), EXPECTED);
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

TEST_F(BitboardTest, bitwiseAndOperator_returnsNewBitboardWithCorrectResult)
{
   Bitboard universe(bitboard::UNIVERSE);
   Bitboard whitePawns(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);

   Bitboard result = universe & whitePawns;

   ASSERT_EQ(result.getBoard(), bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, shorthandBitwiseAndOperator_correctlySetsNewBoardState)
{
   Bitboard universe(bitboard::UNIVERSE);
   Bitboard pawns(bitboard::DEFAULT_PAWN_STRUCTURE);

   universe &= pawns;

   ASSERT_EQ(universe.getBoard(), bitboard::DEFAULT_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInUniverseSet)
{
   Bitboard universe(bitboard::UNIVERSE);

   int numberOfSetBits = universe.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 64);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInEmptySet)
{
   Bitboard emptySet(bitboard::EMPTY_BOARD);

   int numberOfSetBits = emptySet.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 0);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInWhiteBishopStructure)
{
   Bitboard whiteBishops(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);

   int numberOfSetBits = whiteBishops.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 2);
}

TEST_F(BitboardTest, numberOfSetBits_doesNotModifyTheOriginalValue)
{
   Bitboard universe(bitboard::UNIVERSE);

   universe.numberOfSetBits();

   ASSERT_EQ(universe.getBoard(), bitboard::UNIVERSE);
}

TEST_F(BitboardTest, findIndexLSB_findsIndexOfLeastSignificantBit)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfFirstBlackPawn = blackPawns.findIndexLSB();

   ASSERT_EQ(indexOfFirstBlackPawn, Square::a7);
}

TEST_F(BitboardTest, findIndexLSB_doesNotModifyTheOriginalValue)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   blackPawns.findIndexLSB();

   ASSERT_EQ(blackPawns.getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, findIndexLSB_returnsNegativeOneIfNoBitIsSet)
{
   Bitboard emptyBoard(bitboard::EMPTY_BOARD);

   int indexOfLSB = emptyBoard.findIndexLSB();

   ASSERT_EQ(indexOfLSB, -1);
}

TEST_F(BitboardTest, findMSBIndex_findsIndexOfMostSignificantBit)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfLastBlackPawn = blackPawns.findIndexMSB();

   ASSERT_EQ(indexOfLastBlackPawn, Square::h7);
}

TEST_F(BitboardTest, findIndexMSB_doesNotModifyTheOriginalValue)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   blackPawns.findIndexMSB();

   ASSERT_EQ(blackPawns.getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, findIndexMSB_returnsNegativeOneIfNoBitIsSet)
{
   Bitboard emptyBoard(bitboard::EMPTY_BOARD);

   int indexOfMSB = emptyBoard.findIndexMSB();

   ASSERT_EQ(indexOfMSB, -1);
}

TEST_F(BitboardTest, clearAndReturnLSB)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfLSB = blackPawns.clearAndReturnLSB();

   int squareA7 = 48;
   EXPECT_EQ(indexOfLSB, squareA7);
   EXPECT_EQ(blackPawns.getBit(indexOfLSB), 0);
}

TEST_F(BitboardTest, returnAndClearMSB)
{
   Bitboard blackPawns(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfMSB = blackPawns.clearAndReturnMSB();

   int squareH7 = 55;
   EXPECT_EQ(indexOfMSB, squareH7);
   EXPECT_EQ(blackPawns.getBit(indexOfMSB), 0);
}

TEST_F(BitboardTest, getNeighbor)
{
   Bitboard d5(Square::d5);

   Bitboard d6 = d5.getNeighbor(NORTH);
   Bitboard e5 = d5.getNeighbor(EAST);
   Bitboard d4 = d5.getNeighbor(SOUTH);
   Bitboard c5 = d5.getNeighbor(WEST);
   Bitboard c6 = d5.getNeighbor(NORTH_WEST);
   Bitboard e6 = d5.getNeighbor(NORTH_EAST);
   Bitboard c4 = d5.getNeighbor(SOUTH_WEST);
   Bitboard e4 = d5.getNeighbor(SOUTH_EAST);

   u64 d6_EXPECTED = 0x80000000000;
   u64 e5_EXPECTED = 0x1000000000;
   u64 d4_EXPECTED = 0x8000000;
   u64 c5_EXPECTED = 0x400000000;
   u64 c6_EXPECTED = 0x40000000000;
   u64 e6_EXPECTED = 0x100000000000;
   u64 c4_EXPECTED = 0x4000000;
   u64 e4_EXPECTED = 0x10000000;

   EXPECT_EQ(d6.getBoard(), d6_EXPECTED);
   EXPECT_EQ(e5.getBoard(), e5_EXPECTED);
   EXPECT_EQ(d4.getBoard(), d4_EXPECTED);
   EXPECT_EQ(c5.getBoard(), c5_EXPECTED);
   EXPECT_EQ(c6.getBoard(), c6_EXPECTED);
   EXPECT_EQ(e6.getBoard(), e6_EXPECTED);
   EXPECT_EQ(c4.getBoard(), c4_EXPECTED);
   EXPECT_EQ(e4.getBoard(), e4_EXPECTED);
}

TEST_F(BitboardTest, implictConversionFromU64)
{

}

TEST_F(BitboardTest, implicitConversionToU64)
{
   Bitboard b;
   u64 zero = 0;
   ASSERT_EQ(b, zero);
}


}  // namespace
}  // namespace meatball