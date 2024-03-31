#include "../src/chessboard.h"
#include "../src/exceptions.h"
#include "../src/types.h"
#include "../src/move.h"
#include "../utils/expected_uint64t.h"

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

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesAllPieceBitboards)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getBitboard(PAWN).toU64(), constants::DEFAULT_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(KNIGHT).toU64(), constants::DEFAULT_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(BISHOP).toU64(), constants::DEFAULT_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(ROOK).toU64(), constants::DEFAULT_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(QUEEN).toU64(), constants::DEFAULT_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(KING).toU64(), constants::DEFAULT_KING_STRUCTURE);
}

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesWhiteAndBlackBitboards)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getBitboard(WHITE).toU64(), constants::DEFAULT_WHITE_OCCUPIED);
   ASSERT_EQ(chessboard.getBitboard(BLACK).toU64(), constants::DEFAULT_BLACK_OCCUPIED);
}

TEST_F(ChessboardTest, getBitboard_returnsBitboardByColor)
{
   Chessboard chessboard;

   const Bitboard & whiteBitboard = chessboard.getBitboard(WHITE);

   ASSERT_EQ(whiteBitboard.toU64(), constants::DEFAULT_WHITE_OCCUPIED);
}

TEST_F(ChessboardTest, getBitboard_returnsBitboardByPiece)
{
   Chessboard chessboard;

   const Bitboard & pawnBitboard = chessboard.getBitboard(PAWN);
   const Bitboard & knightBitboard = chessboard.getBitboard(KNIGHT);
   const Bitboard & bishopBitboard = chessboard.getBitboard(BISHOP);
   const Bitboard & rookBitboard = chessboard.getBitboard(ROOK);
   const Bitboard & queenBitboard = chessboard.getBitboard(QUEEN);
   const Bitboard & kingBitboard = chessboard.getBitboard(KING);

   ASSERT_EQ(pawnBitboard.toU64(), constants::DEFAULT_PAWN_STRUCTURE);
   ASSERT_EQ(knightBitboard.toU64(), constants::DEFAULT_KNIGHT_STRUCTURE);
   ASSERT_EQ(bishopBitboard.toU64(), constants::DEFAULT_BISHOP_STRUCTURE);
   ASSERT_EQ(rookBitboard.toU64(), constants::DEFAULT_ROOK_STRUCTURE);
   ASSERT_EQ(queenBitboard.toU64(), constants::DEFAULT_QUEEN_STRUCTURE);
   ASSERT_EQ(kingBitboard.toU64(), constants::DEFAULT_KING_STRUCTURE);
}

TEST_F(ChessboardTest, getBitboard_returnsBitboardByColorAndPiece)
{
   Chessboard chessboard;

   const Bitboard & blackBishopBitboard = chessboard.getBitboard(BLACK, BISHOP);

   ASSERT_EQ(blackBishopBitboard.toU64(), constants::DEFAULT_BLACK_BISHOP_STRUCTURE);
}

TEST_F(ChessboardTest, movePiece_shouldMoveWhitePawnFromE2ToE4)
{
   Chessboard chessboard;

   chessboard.applyMove(WHITE, PAWN, e2, e4);

   u64 EXPECTED = 0x1000EF00;
   const Bitboard & bitboard = chessboard.getBitboard(WHITE, PAWN);
   ASSERT_EQ(bitboard.toU64(), EXPECTED);
}

TEST_F(ChessboardTest, movePiece_togglesActivePlayer)
{
   Chessboard chessboard;

   // Make sure after white's move it becomes black's move
   chessboard.applyMove(WHITE, PAWN, e2, e4);
   Color activePlayer = chessboard.getActivePlayer();
   ASSERT_EQ(activePlayer, BLACK);

   // Once black moves it should be white's move again
   chessboard.applyMove(BLACK, PAWN, d7, d5);
   activePlayer = chessboard.getActivePlayer();
   ASSERT_EQ(activePlayer, WHITE);
}

TEST_F(ChessboardTest, movePiece_doesNothingIfWrongSideTriesToMakeMove)
{
   Chessboard chessboard;

   // It's white's turn by default
   chessboard.applyMove(BLACK, PAWN, e2, e4);

   ASSERT_EQ(chessboard.getBitboard(PAWN).toU64(), constants::DEFAULT_PAWN_STRUCTURE);
}

TEST_F(ChessboardTest, applyMove_shouldMoveWhitePawnFromE2ToE4)
{
   Chessboard chessboard;

   chessboard.applyMove(Move(WHITE, PAWN, e2, e4));

   u64 EXPECTED = 0x1000EF00;
   const Bitboard & whitePawnBitboard = chessboard.getBitboard(WHITE, PAWN);
   ASSERT_EQ(whitePawnBitboard.toU64(), EXPECTED);

   ExpectedU64 WHITE_PAWN_E2_E4(0xffff00001000efff);
   const Bitboard occupiedSquares = chessboard.getOccupiedSquares();
   ASSERT_EQ(occupiedSquares, WHITE_PAWN_E2_E4);
}

TEST_F(ChessboardTest, getActivePlayer_returnsWhiteByDefault)
{
   Chessboard chessboard;

   Color activePlayer = chessboard.getActivePlayer();

   ASSERT_EQ(activePlayer, WHITE);
}

TEST_F(ChessboardTest, squareToFile)
{
   for (int i = Square::a1; i <= Square::h8; i++)
   {
      Square square = static_cast<Square>(i);
      File file = Chessboard::squareToFile(square);

      // Using this method for verifying file calculation:
      // https://www.chessprogramming.org/Squares#Square_by_Rank_and_File
      File EXPECTED = static_cast<File>(static_cast<u64>(i) & static_cast<u64>(7));
      EXPECT_EQ(file, EXPECTED);
   }
}

TEST_F(ChessboardTest, squareToRank)
{
   for (int i = Square::a1; i <= Square::h8; i++)
   {
      Square square = static_cast<Square>(i);
      Rank rank = Chessboard::squareToRank(square);

      // Using this method for verifying rank calculation:
      // https://www.chessprogramming.org/Squares#Square_by_Rank_and_File
      Rank EXPECTED = static_cast<Rank>(static_cast<u64>(i) >> static_cast<u64>(3));
      EXPECT_EQ(rank, EXPECTED);
   }
}

TEST_F(ChessboardTest, toggleActivePlayer)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getActivePlayer(), Color::WHITE);
   ASSERT_EQ(chessboard.getNonActivePlayer(), Color::BLACK);

   chessboard.toggleActivePlayer();

   ASSERT_EQ(chessboard.getActivePlayer(), Color::BLACK);
   ASSERT_EQ(chessboard.getNonActivePlayer(), Color::WHITE);
}

TEST_F(ChessboardTest, getOccupiedSquares)
{
   Chessboard chessboard;

   chessboard.applyMove(WHITE, PAWN, e2, e4);
   chessboard.applyMove(BLACK, PAWN, e7, e5);
   chessboard.applyMove(WHITE, PAWN, d2, d4);
   chessboard.applyMove(BLACK, PAWN, d7, d5);

   u64 EXPECTED = 0xffe700181800e7ff;
   ASSERT_EQ(chessboard.getOccupiedSquares().toU64(), EXPECTED);
}

TEST_F(ChessboardTest, undoMove_throwsExceptionIfThereIsNoMoveHistory)
{
   Chessboard board;
   Move m(WHITE, PAWN, e2, e4);
   ASSERT_THROW(board.undoMove(m), std::runtime_error);
}

TEST_F(ChessboardTest, undoMove_throwsExceptionIfMoveIsNotLastMove)
{
   Chessboard board;
   Move move1(WHITE, PAWN, e2, e4);
   Move move2(BLACK, PAWN, e7, e5);

   board.applyMove(move1);
   board.applyMove(move2);

   ASSERT_THROW(board.undoMove(move1), std::runtime_error);
}

TEST_F(ChessboardTest, undoMove)
{
   Chessboard board;
   Move move(WHITE, PAWN, e2, e4);

   board.applyMove(move);

   ASSERT_NO_THROW(board.undoMove(move));

   ExpectedU64 DEFAULT_INITAL_BOARD(0xFFFF00000000FFFF);
   ASSERT_EQ(board.getOccupiedSquares(), DEFAULT_INITAL_BOARD);
}

}  // namespace
}  // namespace meatball