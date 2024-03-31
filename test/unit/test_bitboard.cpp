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

TEST_F(BitboardTest, defaultConstructor_shouldInitializeBoardWithStateOfZero)
{
   Bitboard bitboard;

   ASSERT_EQ(bitboard.toU64(), constants::EMPTY_BOARD);
}

TEST_F(BitboardTest, constructor_canInitializeBoardWithAState)
{
   Bitboard bitboard(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   ASSERT_EQ(bitboard.toU64(), constants::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, constructor_createBitboardFromSquare)
{
   Bitboard d5(Square::d5);

   u64 EXPECTED = 0x800000000;
   ASSERT_EQ(d5.toU64(), EXPECTED);
}

TEST_F(BitboardTest, constructor_createBitboardFromInt)
{
   int bit = 32;
   Bitboard a5(bit);

   u64 EXPECTED_A5 = 0x100000000;
   ASSERT_EQ(a5.toU64(), EXPECTED_A5);
}

TEST_F(BitboardTest, setBit)
{
   Bitboard bitboard;

   bitboard.setBit(g3);
   
   u64 EXPECTED_BITBOARD = 0x0000000000400000;
   ASSERT_EQ(bitboard.toU64(), EXPECTED_BITBOARD);
}

TEST_F(BitboardTest, setBit_throwsExceptionIfBitIsOutOfRange)
{
   Bitboard bitboard;

   int inRange = 0;
   EXPECT_NO_THROW(bitboard.setBit(inRange));
   inRange = 63;
   EXPECT_NO_THROW(bitboard.setBit(inRange));

   EXPECT_THROW({
   try
   {
      int outOfRange = 64;
      bitboard.setBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );

   EXPECT_THROW({
   try
   {
      int outOfRange = -1;
      bitboard.setBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );
}

TEST_F(BitboardTest, clearBit)
{
   Bitboard bitboard(constants::UNIVERSE);

   bitboard.clearBit(g3);

   u64 EXPECTED_BITBOARD = 0xFFFFFFFFFFBFFFFF;
   ASSERT_EQ(bitboard.toU64(), EXPECTED_BITBOARD);
}

TEST_F(BitboardTest, clearBit2)
{
   Bitboard bitboard;

   bitboard.setBit(g3);
   bitboard.clearBit(g3);

   ASSERT_EQ(bitboard.toU64(), constants::EMPTY_BOARD);
}

TEST_F(BitboardTest, clearBit_throwsExceptionIfBitIsOutOfRange)
{
   Bitboard bitboard;

   int inRange = 0;
   EXPECT_NO_THROW(bitboard.clearBit(inRange));
   inRange = 63;
   EXPECT_NO_THROW(bitboard.clearBit(inRange));

   EXPECT_THROW({
   try
   {
      int outOfRange = 64;
      bitboard.clearBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );

   EXPECT_THROW({
   try
   {
      int outOfRange = -1;
      bitboard.clearBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );
}

TEST_F(BitboardTest, getBit)
{
   Bitboard bitboard(constants::EMPTY_BOARD);
   bitboard.setBit(g3);

   ASSERT_EQ(bitboard.getBit(g3), 1);
}

TEST_F(BitboardTest, getBit2)
{
   Bitboard bitboard(constants::UNIVERSE);
   bitboard.clearBit(g3);

   ASSERT_EQ(bitboard.getBit(g3), 0);
}

TEST_F(BitboardTest, getBit_throwsExceptionIfBitIsOutOfRange)
{
   Bitboard bitboard;

   int inRange = 0;
   EXPECT_NO_THROW(bitboard.getBit(inRange));
   inRange = 63;
   EXPECT_NO_THROW(bitboard.getBit(inRange));

   EXPECT_THROW({
   try
   {
      int outOfRange = 64;
      bitboard.getBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );

   EXPECT_THROW({
   try
   {
      int outOfRange = -1;
      bitboard.getBit(outOfRange);
   }
   catch( const std::out_of_range & e )
   {
      throw;
   }
   }, std::out_of_range );
}

TEST_F(BitboardTest, reset_ResetsBoardState)
{
   Bitboard bitboard(constants::UNIVERSE);

   bitboard.reset();

   ASSERT_EQ(bitboard.toU64(), constants::EMPTY_BOARD);
}

TEST_F(BitboardTest, setBoard_correctlySetsBitboard)
{
   Bitboard bitboard;

   bitboard.setBoard(constants::UNIVERSE);

   ASSERT_EQ(bitboard.toU64(), constants::UNIVERSE);
}

TEST_F(BitboardTest, bitwiseOrOperator_returnsNewBitboard)
{
   Bitboard a(constants::DEFAULT_BLACK_PAWN_STRUCTURE);
   Bitboard b(constants::DEFAULT_WHITE_PAWN_STRUCTURE);

   Bitboard c = a | b;

   u64 EXPECTED = 0x00FF00000000FF00;
   ASSERT_EQ(c.toU64(), EXPECTED);
}

TEST_F(BitboardTest, shorthandBitwiseOrOperator_correctlySetsNewBoardState)
{
   Bitboard a(constants::DEFAULT_BLACK_PAWN_STRUCTURE);
   Bitboard b(constants::DEFAULT_BLACK_QUEEN_STRUCTURE);

   a |= b;

   u64 EXPECTED = 0x08FF000000000000;

   // bitboard a has an updated state
   ASSERT_EQ(a.toU64(), EXPECTED);

   // bitboard b is unchanged
   ASSERT_EQ(b.toU64(), constants::DEFAULT_BLACK_QUEEN_STRUCTURE);
}

TEST_F(BitboardTest, bitwiseAndOperator_returnsNewBitboardWithCorrectResult)
{
   Bitboard universe(constants::UNIVERSE);
   Bitboard whitePawns(constants::DEFAULT_WHITE_PAWN_STRUCTURE);

   Bitboard result = universe & whitePawns;

   ASSERT_EQ(result.toU64(), constants::DEFAULT_WHITE_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, shorthandBitwiseAndOperator_correctlySetsNewBoardState)
{
   Bitboard universe(constants::UNIVERSE);
   Bitboard pawns(constants::DEFAULT_PAWN_STRUCTURE);

   universe &= pawns;

   ASSERT_EQ(universe.toU64(), constants::DEFAULT_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInUniverseSet)
{
   Bitboard universe(constants::UNIVERSE);

   int numberOfSetBits = universe.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 64);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInEmptySet)
{
   Bitboard emptySet(constants::EMPTY_BOARD);

   int numberOfSetBits = emptySet.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 0);
}

TEST_F(BitboardTest, numberOfSetBits_countsNumberOfSetBitsInWhiteBishopStructure)
{
   Bitboard whiteBishops(constants::DEFAULT_WHITE_BISHOP_STRUCTURE);

   int numberOfSetBits = whiteBishops.numberOfSetBits();

   ASSERT_EQ(numberOfSetBits, 2);
}

TEST_F(BitboardTest, numberOfSetBits_doesNotModifyTheOriginalValue)
{
   Bitboard universe(constants::UNIVERSE);

   universe.numberOfSetBits();

   ASSERT_EQ(universe.toU64(), constants::UNIVERSE);
}

TEST_F(BitboardTest, findIndexLSB_findsIndexOfLeastSignificantBit)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfFirstBlackPawn = blackPawns.findIndexLSB();

   ASSERT_EQ(indexOfFirstBlackPawn, Square::a7);
}

TEST_F(BitboardTest, findIndexLSB_doesNotModifyTheOriginalValue)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   blackPawns.findIndexLSB();

   ASSERT_EQ(blackPawns.toU64(), constants::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, findIndexLSB_returnsNegativeOneIfNoBitIsSet)
{
   Bitboard emptyBoard(constants::EMPTY_BOARD);

   int indexOfLSB = emptyBoard.findIndexLSB();

   ASSERT_EQ(indexOfLSB, -1);
}

TEST_F(BitboardTest, findMSBIndex_findsIndexOfMostSignificantBit)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfLastBlackPawn = blackPawns.findIndexMSB();

   ASSERT_EQ(indexOfLastBlackPawn, Square::h7);
}

TEST_F(BitboardTest, findIndexMSB_doesNotModifyTheOriginalValue)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   blackPawns.findIndexMSB();

   ASSERT_EQ(blackPawns.toU64(), constants::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, findIndexMSB_returnsNegativeOneIfNoBitIsSet)
{
   Bitboard emptyBoard(constants::EMPTY_BOARD);

   int indexOfMSB = emptyBoard.findIndexMSB();

   ASSERT_EQ(indexOfMSB, -1);
}

TEST_F(BitboardTest, clearAndReturnLSB)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfLSB = blackPawns.clearAndReturnLSB();

   int squareA7 = 48;
   EXPECT_EQ(indexOfLSB, squareA7);
   EXPECT_EQ(blackPawns.getBit(indexOfLSB), 0);
}

TEST_F(BitboardTest, returnAndClearMSB)
{
   Bitboard blackPawns(constants::DEFAULT_BLACK_PAWN_STRUCTURE);

   int indexOfMSB = blackPawns.clearAndReturnMSB();

   int squareH7 = 55;
   EXPECT_EQ(indexOfMSB, squareH7);
   EXPECT_EQ(blackPawns.getBit(indexOfMSB), 0);
}

TEST_F(BitboardTest, getNeighbor)
{
   Bitboard d5(Square::d5);

   u64 d6_EXPECTED = 0x80000000000;
   u64 e5_EXPECTED = 0x1000000000;
   u64 d4_EXPECTED = 0x8000000;
   u64 c5_EXPECTED = 0x400000000;
   u64 c6_EXPECTED = 0x40000000000;
   u64 e6_EXPECTED = 0x100000000000;
   u64 c4_EXPECTED = 0x4000000;
   u64 e4_EXPECTED = 0x10000000;

   EXPECT_EQ(d5.getNeighbor(NORTH),      d6_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(EAST),       e5_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(SOUTH),      d4_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(WEST),       c5_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(NORTH_WEST), c6_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(NORTH_EAST), e6_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(SOUTH_WEST), c4_EXPECTED);
   EXPECT_EQ(d5.getNeighbor(SOUTH_EAST), e4_EXPECTED);
}

TEST_F(BitboardTest, bitboardCanBeMultipliedWith64BitIntegers)
{
   const u64 universe = 0xFFFFFFFFFFFFFFFF;
   const u64 one = 1;
   const Bitboard b(one);

   EXPECT_EQ(b * universe, universe);
   EXPECT_EQ(universe * b, universe);
}

}  // namespace
}  // namespace meatball