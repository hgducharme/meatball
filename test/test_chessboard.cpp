#include "../src/chessboard.h"
#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class ChessBoardTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ChessBoardTest()
  {
     // You can do set-up work for each test here.
  }

  ~ChessBoardTest() override
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

TEST_F(ChessBoardTest, defaultConstructor_correctlyPlacesAllPiecesOnTheBoard)
{
   ChessBoard board;

   ASSERT_EQ(board.getPieceBitboard(WHITE, PAWN).getBoard(), bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, KNIGHT).getBoard(), bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, BISHOP).getBoard(), bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, ROOK).getBoard(), bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, QUEEN).getBoard(), bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, KING).getBoard(), bitboard::DEFAULT_WHITE_KING_STRUCTURE);
   
   ASSERT_EQ(board.getPieceBitboard(BLACK, PAWN).getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, KNIGHT).getBoard(), bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, BISHOP).getBoard(), bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, ROOK).getBoard(), bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, QUEEN).getBoard(), bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, KING).getBoard(), bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

TEST_F(ChessBoardTest, getPieceBitboard_returnsCorrectBitboard)
{
   ChessBoard board;

   ASSERT_EQ(board.getPieceBitboard(WHITE, PAWN).getBoard(), bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, KNIGHT).getBoard(), bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, BISHOP).getBoard(), bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, ROOK).getBoard(), bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, QUEEN).getBoard(), bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(WHITE, KING).getBoard(), bitboard::DEFAULT_WHITE_KING_STRUCTURE);
   
   ASSERT_EQ(board.getPieceBitboard(BLACK, PAWN).getBoard(), bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, KNIGHT).getBoard(), bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, BISHOP).getBoard(), bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, ROOK).getBoard(), bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, QUEEN).getBoard(), bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
   ASSERT_EQ(board.getPieceBitboard(BLACK, KING).getBoard(), bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

}  // namespace
}  // namespace meatball