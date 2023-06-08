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

   ASSERT_EQ(chessboard.getBitboard(PAWN).getBoard(), bitboard::DEFAULT_PAWN_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(KNIGHT).getBoard(), bitboard::DEFAULT_KNIGHT_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(BISHOP).getBoard(), bitboard::DEFAULT_BISHOP_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(ROOK).getBoard(), bitboard::DEFAULT_ROOK_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(QUEEN).getBoard(), bitboard::DEFAULT_QUEEN_STRUCTURE);
   ASSERT_EQ(chessboard.getBitboard(KING).getBoard(), bitboard::DEFAULT_KING_STRUCTURE);
}

TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesWhiteAndBlackBitboards)
{
   Chessboard chessboard;

   ASSERT_EQ(chessboard.getBitboard(WHITE).getBoard(), bitboard::DEFAULT_WHITE_OCCUPIED);
   ASSERT_EQ(chessboard.getBitboard(BLACK).getBoard(), bitboard::DEFAULT_BLACK_OCCUPIED);
}

// TODO: Fix this to represent the new design
// TEST_F(ChessboardTest, defaultConstructor_correctlyInitializesOccupiedSquares)
// {
//    Chessboard chessboard;

//    u64 EXPECTED = bitboard::DEFAULT_WHITE_OCCUPIED | bitboard::DEFAULT_BLACK_OCCUPIED;

//    ASSERT_EQ(chessboard.getOccupiedSquares().getBoard(), EXPECTED);
// }

TEST_F(ChessboardTest, getBitboard_returnsBitboardByColor)
{
   Chessboard chessboard;

   Bitboard whiteBitboard = chessboard.getBitboard(WHITE);

   ASSERT_EQ(whiteBitboard.getBoard(), bitboard::DEFAULT_WHITE_OCCUPIED);
}

TEST_F(ChessboardTest, getBitboard_returnsBitboardByPiece)
{
   Chessboard chessboard;

   Bitboard pawnBitboard = chessboard.getBitboard(PAWN);
   Bitboard knightBitboard = chessboard.getBitboard(KNIGHT);
   Bitboard bishopBitboard = chessboard.getBitboard(BISHOP);
   Bitboard rookBitboard = chessboard.getBitboard(ROOK);
   Bitboard queenBitboard = chessboard.getBitboard(QUEEN);
   Bitboard kingBitboard = chessboard.getBitboard(KING);

   ASSERT_EQ(pawnBitboard.getBoard(), bitboard::DEFAULT_PAWN_STRUCTURE);
   ASSERT_EQ(knightBitboard.getBoard(), bitboard::DEFAULT_KNIGHT_STRUCTURE);
   ASSERT_EQ(bishopBitboard.getBoard(), bitboard::DEFAULT_BISHOP_STRUCTURE);
   ASSERT_EQ(rookBitboard.getBoard(), bitboard::DEFAULT_ROOK_STRUCTURE);
   ASSERT_EQ(queenBitboard.getBoard(), bitboard::DEFAULT_QUEEN_STRUCTURE);
   ASSERT_EQ(kingBitboard.getBoard(), bitboard::DEFAULT_KING_STRUCTURE);
}

TEST_F(ChessboardTest, getBitboard_returnsBitboardByColorAndPiece)
{
   Chessboard chessboard;

   Bitboard blackBishopBitboard = chessboard.getBitboard(BLACK, BISHOP);

   ASSERT_EQ(blackBishopBitboard.getBoard(), bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
}

TEST_F(ChessboardTest, movePiece_ShouldMoveWhitePawnToE4)
{
   // TODO: This test isn't working because of the 'const' in the getBitboard function.
   // The clearBit() and setBit() functions aren't actually modifying the desired bitboard
   Chessboard chessboard;

   chessboard.movePiece(WHITE, PAWN, e2, e4);

   u64 EXPECTED = 0x1000EF00;
   Bitboard bitboard = chessboard.getBitboard(WHITE, PAWN);

   std::cout << "Exp: " << std::bitset<64>(EXPECTED) << std::endl;
   std::cout << "Got: " << std::bitset<64>(bitboard.getBoard()) << std::endl;

   ASSERT_EQ(bitboard.getBoard(), EXPECTED);
}

TEST_F(ChessboardTest, generateMoves1)
{
   Chessboard chessboard;

   chessboard.generateMoves();
}

}  // namespace
}  // namespace meatball