#include "../src/move.h"

#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class MoveTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  MoveTest()
  {
     // You can do set-up work for each test here.
  }

  ~MoveTest() override
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

TEST_F(MoveTest, equalityOperatorOverload)
{
   Move move1(WHITE, PAWN, e2, e4);
   Move move2(WHITE, PAWN, e2, e4);
   Move move3(BLACK, PAWN, e7, e5);

   EXPECT_TRUE(move1 == move2);
   EXPECT_FALSE(move1 == move3);
}

TEST_F(MoveTest, getFlags)
{
   uint8_t flags = Move::PROMOTION | Move::CAPTURE | Move::PAWN_DOUBLE_PUSH | Move::EN_PASSANT | Move::KINGSIDE_CASTLE | Move::QUEENSIDE_CASTLE | Move::CHECK;
   Move m(WHITE, PAWN, e2, e4, flags);

   uint8_t EXPECTED = 0b1111111;
   ASSERT_EQ(m.getFlags(), EXPECTED);
}

TEST_F(MoveTest, moveFlag_promotion) {
   uint8_t flags = Move::PROMOTION;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isPromotion());
}

TEST_F(MoveTest, setPromotionPiece)
{
   Move m(WHITE, PAWN, e7, e8, Move::PROMOTION);

   ASSERT_FALSE(m.promotionPiece().has_value());

   m.setPromotionPiece(PieceType::QUEEN);

   ASSERT_TRUE(m.promotionPiece().has_value());
   ASSERT_EQ(m.promotionPiece().value(), PieceType::QUEEN);
}

TEST_F(MoveTest, moveFlag_pawnDoublePush)
{
   uint8_t flags = Move::PAWN_DOUBLE_PUSH;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isPawnDoublePush());
}

TEST_F(MoveTest, moveFlag_enPassant)
{
   uint8_t flags = Move::EN_PASSANT;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isEnPassant());
}

TEST_F(MoveTest, moveFlag_capture)
{
   uint8_t flags = Move::CAPTURE;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isCapture());
}

TEST_F(MoveTest, moveFlag_kingsideCastle)
{
   uint8_t flags = Move::KINGSIDE_CASTLE;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isKingsideCastle());
}

TEST_F(MoveTest, moveFlag_queensideCastle)
{
   uint8_t flags = Move::QUEENSIDE_CASTLE;
   Move m(WHITE, PAWN, e2, e4, flags);
   ASSERT_TRUE(m.isQueensideCastle());
}

TEST_F(MoveTest, isFlagSet)
{
   Move m1(WHITE, PAWN, e2, e4);
   ASSERT_FALSE(m1.isFlagSet(Move::PROMOTION));
   ASSERT_FALSE(m1.isFlagSet(Move::CAPTURE));
   ASSERT_FALSE(m1.isFlagSet(Move::PAWN_DOUBLE_PUSH));
   ASSERT_FALSE(m1.isFlagSet(Move::EN_PASSANT));
   ASSERT_FALSE(m1.isFlagSet(Move::KINGSIDE_CASTLE));
   ASSERT_FALSE(m1.isFlagSet(Move::QUEENSIDE_CASTLE));
   ASSERT_FALSE(m1.isFlagSet(Move::CHECK));

   uint8_t flags = Move::PROMOTION | Move::CAPTURE | Move::PAWN_DOUBLE_PUSH | Move::EN_PASSANT | Move::KINGSIDE_CASTLE | Move::QUEENSIDE_CASTLE | Move::CHECK;
   Move m2(WHITE, PAWN, e2, e4, flags);

   EXPECT_TRUE(m2.isFlagSet(Move::PROMOTION));
   EXPECT_TRUE(m2.isFlagSet(Move::CAPTURE));
   EXPECT_TRUE(m2.isFlagSet(Move::PAWN_DOUBLE_PUSH));
   EXPECT_TRUE(m2.isFlagSet(Move::EN_PASSANT));
   EXPECT_TRUE(m2.isFlagSet(Move::KINGSIDE_CASTLE));
   EXPECT_TRUE(m2.isFlagSet(Move::QUEENSIDE_CASTLE));
   EXPECT_TRUE(m2.isFlagSet(Move::CHECK));
}

TEST_F(MoveTest, setFlag)
{
   Move m(WHITE, PAWN, e2, e4);
   ASSERT_FALSE(m.isPawnDoublePush());
   m.setFlag(Move::PAWN_DOUBLE_PUSH);
   ASSERT_TRUE(m.isPawnDoublePush());
}

TEST_F(MoveTest, getEncoded)
{
   uint8_t flags = Move::PROMOTION | Move::CAPTURE | Move::PAWN_DOUBLE_PUSH | Move::EN_PASSANT | Move::KINGSIDE_CASTLE | Move::QUEENSIDE_CASTLE;
   Move m(WHITE, PAWN, e2, e4, flags);

   uint32_t EXPECTED = Color::WHITE << 0 | PieceType::PAWN << 1 | Square::e2 << 4 | Square::e4 << 10 | flags << 16;
   ASSERT_EQ(m.getEncoded(), EXPECTED);
}

TEST_F(MoveTest, color)
{
   Move m1(BLACK, PAWN, e2, e4);
   ASSERT_EQ(m1.color(), Color::BLACK);

   Move m2(WHITE, PAWN, e2, e4);
   ASSERT_EQ(m2.color(), Color::WHITE);
}

TEST_F(MoveTest, pieceType)
{
   Move m(WHITE, QUEEN, d1, d4);
   ASSERT_EQ(m.pieceType(), PieceType::QUEEN);
}

TEST_F(MoveTest, startSquare)
{
   Move m(WHITE, PAWN, e2, e4);
   ASSERT_EQ(m.startSquare(), Square::e2);
}

TEST_F(MoveTest, endSquare)
{
   Move m(WHITE, PAWN, e2, e4);
   ASSERT_EQ(m.endSquare(), Square::e4);
}

TEST_F(MoveTest, setCapturedPiece)
{
   Move m(WHITE, PAWN, e2, e4);
   CapturedPiece c(BLACK, PAWN, d5);

   ASSERT_FALSE(m.capturedPiece().has_value());

   m.setCapturedPiece(c);

   ASSERT_TRUE(m.capturedPiece().has_value());
   ASSERT_EQ(m.capturedPiece(), c);
}

TEST_F(MoveTest, castleSide_defaultsToNullOption)
{
   Move m(WHITE, PAWN, e2, e4);
   ASSERT_FALSE(m.castleSide().has_value());
}

TEST_F(MoveTest, castleSide_returnsQueenside)
{
   Move m(WHITE, PAWN, e2, e4, Move::QUEENSIDE_CASTLE);
   std::optional<CastleSide> castleSide = m.castleSide();
   ASSERT_TRUE(castleSide.has_value());
   ASSERT_EQ(castleSide.value(), CastleSide::QUEENSIDE);
}

TEST_F(MoveTest, castleSide_returnsKingside)
{
   Move m(WHITE, PAWN, e2, e4, Move::KINGSIDE_CASTLE);
   std::optional<CastleSide> castleSide = m.castleSide();
   ASSERT_TRUE(castleSide.has_value());
   ASSERT_EQ(castleSide.value(), CastleSide::KINGSIDE);
}

TEST_F(MoveTest, isCheck)
{
   Move m(WHITE, PAWN, e2, e4, Move::CHECK);
   ASSERT_TRUE(m.isCheck());
}

}  // namespace
}  // namespace meatball