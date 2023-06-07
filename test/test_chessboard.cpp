#include "../src/chessboard.h"
#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class ChessboardTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ChessboardTest()
  {
     // You can do set-up work for each test here.
  }

  ~ChessboardTest() override
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

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesAllPieceBitboards)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, PAWN).getBoard(), bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, KNIGHT).getBoard(), bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, BISHOP).getBoard(), bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, ROOK).getBoard(), bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, QUEEN).getBoard(), bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, KING).getBoard(), bitboard::DEFAULT_WHITE_KING_STRUCTURE);
   
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, PAWN).getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, KNIGHT).getBoard(), bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, BISHOP).getBoard(), bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, ROOK).getBoard(), bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, QUEEN).getBoard(), bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, KING).getBoard(), bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesWhiteAndBlackBitboards)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getColorBitboard(WHITE).getBoard(), bitboard::DEFAULT_WHITE_STRUCTURE);
   ASSERT_EQ(chessboard.getColorBitboard(BLACK).getBoard(), bitboard::DEFAULT_BLACK_STRUCTURE);
}

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesOccupiedSquares)
{
   Chessboard chessboard;

   u64 EXPECTED = bitboard::DEFAULT_WHITE_STRUCTURE & bitboard::DEFAULT_BLACK_STRUCTURE;
   ASSERT_EQ(chessboard.getOccupiedSquares().getBoard(), EXPECTED);
}

TEST_F(ChessboardTest, getPieceBitboard_returnsCorrectBitboard)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, PAWN).getBoard(), bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, KNIGHT).getBoard(), bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, BISHOP).getBoard(), bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, ROOK).getBoard(), bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, QUEEN).getBoard(), bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(WHITE, KING).getBoard(), bitboard::DEFAULT_WHITE_KING_STRUCTURE);
   
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, PAWN).getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, KNIGHT).getBoard(), bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, BISHOP).getBoard(), bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, ROOK).getBoard(), bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, QUEEN).getBoard(), bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getPieceBitboard(BLACK, KING).getBoard(), bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

TEST_F(ChessboardTest, movePiece_ShouldMoveWhitePawnToE4)
{
   Chessboard chessboard;

   chessboard.movePiece(WHITE, PAWN, e2, e4);

   u64 EXPECTED = 0x1000EF00;
   Bitboard bitboard = chessboard.getPieceBitboard(WHITE, PAWN);
   ASSERT_EQ(bitboard.getBoard(), EXPECTED);
}

TEST_F(ChessboardTest, generateMoves1)
{
   Chessboard chessboard;

   chessboard.generateMoves();
}

}  // namespace
}  // namespace meatball