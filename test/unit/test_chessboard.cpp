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

   chessboard.applyMove(Move(WHITE, PAWN, e2, e4));

   u64 EXPECTED = 0x1000EF00;
   const Bitboard & bitboard = chessboard.getBitboard(WHITE, PAWN);
   ASSERT_EQ(bitboard.toU64(), EXPECTED);
}

TEST_F(ChessboardTest, movePiece_togglesActivePlayer)
{
   Chessboard chessboard;

   // Make sure after white's move it becomes black's move
   chessboard.applyMove(Move(WHITE, PAWN, e2, e4));
   Color activePlayer = chessboard.getActivePlayer();
   ASSERT_EQ(activePlayer, BLACK);

   // Once black moves it should be white's move again
   chessboard.applyMove(Move(BLACK, PAWN, d7, d5));
   activePlayer = chessboard.getActivePlayer();
   ASSERT_EQ(activePlayer, WHITE);
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

   chessboard.applyMove(Move(WHITE, PAWN, e2, e4));
   chessboard.applyMove(Move(BLACK, PAWN, e7, e5));
   chessboard.applyMove(Move(WHITE, PAWN, d2, d4));
   chessboard.applyMove(Move(BLACK, PAWN, d7, d5));

   u64 EXPECTED = 0xffe700181800e7ff;
   ASSERT_EQ(chessboard.getOccupiedSquares().toU64(), EXPECTED);
}

TEST_F(ChessboardTest, getLastMove_returnsEmptyOptional)
{
   Chessboard board;

   ASSERT_FALSE(board.getLastMove().has_value());
}

TEST_F(ChessboardTest, getLastMove_returnsLastMove)
{
   Chessboard board;
   Move move(WHITE, PAWN, e2, e4);
   
   board.applyMove(move);
   
   const std::optional<const Move> returnedMove = board.getLastMove();

   EXPECT_TRUE(returnedMove.has_value());
   EXPECT_EQ(returnedMove.value(), move);
}

TEST_F(ChessboardTest, castleRights_allCastleRightsAreTrueByDefault)
{
   Chessboard board;

   CastleRights whiteCastleRights = board.getCastleRights(WHITE);
   CastleRights blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::KING_AND_QUEEN_SIDE);
   EXPECT_EQ(blackCastleRights, CastleRights::KING_AND_QUEEN_SIDE);
}

TEST_F(ChessboardTest, castleRights_castleRightsAreTurnedOffIfKingMoves)
{
   Chessboard board;

   board.applyMove(Move(WHITE, PAWN, e2, e4));
   board.applyMove(Move(WHITE, KING, e1, e2));

   CastleRights whiteCastleRights = board.getCastleRights(WHITE);
   CastleRights blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::NONE);
   EXPECT_EQ(blackCastleRights, CastleRights::KING_AND_QUEEN_SIDE);

   board.applyMove(Move(BLACK, PAWN, e7, e5));
   board.applyMove(Move(BLACK, KING, e8, e7));

   whiteCastleRights = board.getCastleRights(WHITE);
   blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::NONE);
   EXPECT_EQ(blackCastleRights, CastleRights::NONE);
}

TEST_F(ChessboardTest, castleRights_kingSideCastleRightsAreTurnedOffIfKingSideRookMoves)
{
   Chessboard board;

   board.applyMove(Move(WHITE, PAWN, h2, h4));
   board.applyMove(Move(WHITE, ROOK, h1, h3));

   CastleRights whiteCastleRights = board.getCastleRights(WHITE);
   CastleRights blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::ONLY_QUEEN_SIDE);
   EXPECT_EQ(blackCastleRights, CastleRights::KING_AND_QUEEN_SIDE);

   board.applyMove(Move(BLACK, PAWN, h7, h5));
   board.applyMove(Move(BLACK, ROOK, h8, h7));

   whiteCastleRights = board.getCastleRights(WHITE);
   blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::ONLY_QUEEN_SIDE);
   EXPECT_EQ(blackCastleRights, CastleRights::ONLY_QUEEN_SIDE);
}

TEST_F(ChessboardTest, castleRights_queenSideCastleRightsAreTurnedOffIfQueenSideRookMoves)
{
   Chessboard board;

   board.applyMove(Move(WHITE, PAWN, a2, a4));
   board.applyMove(Move(WHITE, ROOK, a1, a3));

   CastleRights whiteCastleRights = board.getCastleRights(WHITE);
   CastleRights blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::ONLY_KING_SIDE);
   EXPECT_EQ(blackCastleRights, CastleRights::KING_AND_QUEEN_SIDE);

   board.applyMove(Move(BLACK, PAWN, a7, a5));
   board.applyMove(Move(BLACK, ROOK, a8, a7));

   whiteCastleRights = board.getCastleRights(WHITE);
   blackCastleRights = board.getCastleRights(BLACK);

   EXPECT_EQ(whiteCastleRights, CastleRights::ONLY_KING_SIDE);
   EXPECT_EQ(blackCastleRights, CastleRights::ONLY_KING_SIDE);
}

TEST_F(ChessboardTest, squareIsOccupied)
{
   Chessboard game;

   EXPECT_TRUE(game.squareIsOccupied(Square::a1));
   EXPECT_TRUE(game.squareIsOccupied(Square::a8));
   EXPECT_FALSE(game.squareIsOccupied(Square::a3));
   EXPECT_FALSE(game.squareIsOccupied(Square::e3));
}

TEST_F(ChessboardTest, getPieceAt)
{
   Chessboard game;

   EXPECT_EQ(game.getPieceAt(Square::a2).value(), Piece(WHITE, PAWN));
   EXPECT_EQ(game.getPieceAt(Square::b1).value(), Piece(WHITE ,KNIGHT));
   EXPECT_EQ(game.getPieceAt(Square::c1).value(), Piece(WHITE ,BISHOP));
   EXPECT_EQ(game.getPieceAt(Square::a8).value(), Piece(BLACK ,ROOK));
   EXPECT_EQ(game.getPieceAt(Square::d8).value(), Piece(BLACK ,QUEEN));
   EXPECT_EQ(game.getPieceAt(Square::e8).value(), Piece(BLACK ,KING));
   EXPECT_FALSE(game.getPieceAt(Square::e4).has_value());
}

TEST_F(ChessboardTest, applyMove_promotionMoveGetsCorrectlyApplied)
{
   Chessboard game;
   Move promotionMove(WHITE, PAWN, g7, g8, Move::PROMOTION);
   promotionMove.setPromotionPiece(PieceType::QUEEN);

   game.applyMove(Move(WHITE, PAWN, f2, f4));
   game.applyMove(Move(BLACK, PAWN, g7, g5));
   Move captureG5(WHITE, PAWN, f4, g5, Move::CAPTURE);
   CapturedPiece pawnG5(BLACK, PAWN, g5);
   captureG5.setCapturedPiece(pawnG5);
   game.applyMove(captureG5);
   game.applyMove(Move(BLACK, KNIGHT, g8, h6));
   game.applyMove(Move(WHITE, PAWN, g5, g6));
   game.applyMove(Move(BLACK, PAWN, e7, e6));
   game.applyMove(Move(WHITE, PAWN, g6, g7));
   game.applyMove(Move(BLACK, PAWN, e6, e5));
   game.applyMove(promotionMove);

   ExpectedU64 EXPECTED_WHITE_PAWNS(0xdf00);
   ExpectedU64 EXPECTED_WHITE_QUEENS(0x4000000000000008);
   ExpectedU64 EXPECTED_WHITE_OCCUPANCY(0x400000000000dfff);
   ExpectedU64 EXPECTED_BLACK_OCCUPANCY(0xbfaf801000000000);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::QUEEN), EXPECTED_WHITE_QUEENS);
   EXPECT_EQ(game.getBitboard(Color::WHITE), EXPECTED_WHITE_OCCUPANCY);
   EXPECT_EQ(game.getBitboard(Color::BLACK), EXPECTED_BLACK_OCCUPANCY);
}

TEST_F(ChessboardTest, applyMove_captureIntoPromotionGetsCorrectlyApplied)
{
   Chessboard game;
   CapturedPiece blackRookH8(Color::BLACK, PieceType::ROOK, Square::h8);
   Move promotionMove(WHITE, PAWN, g7, h8, Move::PROMOTION | Move::CAPTURE);
   promotionMove.setPromotionPiece(PieceType::QUEEN);
   promotionMove.setCapturedPiece(blackRookH8);

   game.applyMove(Move(WHITE, PAWN, f2, f4));
   game.applyMove(Move(BLACK, PAWN, g7, g5));
   Move captureG5(WHITE, PAWN, f4, g5, Move::CAPTURE);
   CapturedPiece pawnG5(BLACK, PAWN, g5);
   captureG5.setCapturedPiece(pawnG5);
   game.applyMove(captureG5);
   game.applyMove(Move(BLACK, KNIGHT, g8, h6));
   game.applyMove(Move(WHITE, PAWN, g5, g6));
   game.applyMove(Move(BLACK, PAWN, e7, e6));
   game.applyMove(Move(WHITE, PAWN, g6, g7));
   game.applyMove(Move(BLACK, PAWN, e6, e5));
   game.applyMove(promotionMove);

   ExpectedU64 EXPECTED_WHITE_PAWNS(0xdf00);
   ExpectedU64 EXPECTED_WHITE_QUEENS(0x8000000000000008);
   ExpectedU64 EXPECTED_WHITE_OCCUPANCY(0x800000000000dfff);
   ExpectedU64 EXPECTED_BLACK_ROOKS(0x100000000000000);
   ExpectedU64 EXPECTED_BLACK_OCCUPANCY(0x3faf801000000000);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::QUEEN), EXPECTED_WHITE_QUEENS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::ROOK), EXPECTED_BLACK_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::WHITE), EXPECTED_WHITE_OCCUPANCY);
   EXPECT_EQ(game.getBitboard(Color::BLACK), EXPECTED_BLACK_OCCUPANCY);
}

TEST_F(ChessboardTest, undoMove_captureIntoPromotionGetsCorrectlyUndone)
{
   Chessboard game;
   CapturedPiece blackRookH8(Color::BLACK, PieceType::ROOK, Square::h8);
   Move captureIntoPromotion(WHITE, PAWN, g7, h8, Move::CAPTURE | Move::PROMOTION);
   captureIntoPromotion.setPromotionPiece(PieceType::QUEEN);
   captureIntoPromotion.setCapturedPiece(blackRookH8);

   game.applyMove(Move(WHITE, PAWN, f2, f4));
   game.applyMove(Move(BLACK, PAWN, g7, g5));
   Move captureG5(WHITE, PAWN, f4, g5, Move::CAPTURE);
   CapturedPiece pawnG5(BLACK, PAWN, g5);
   captureG5.setCapturedPiece(pawnG5);
   game.applyMove(captureG5);
   game.applyMove(Move(BLACK, KNIGHT, g8, h6));
   game.applyMove(Move(WHITE, PAWN, g5, g6));
   game.applyMove(Move(BLACK, PAWN, e7, e6));
   game.applyMove(Move(WHITE, PAWN, g6, g7));
   game.applyMove(Move(BLACK, PAWN, e6, e5));
   game.applyMove(captureIntoPromotion);
   game.undoMove(captureIntoPromotion);

   ExpectedU64 EXPECTED_WHITE_PAWNS(0x4000000000df00);
   ExpectedU64 EXPECTED_WHITE_KNIGHTS(0x42);
   ExpectedU64 EXPECTED_WHITE_BISHOPS(0x24);
   ExpectedU64 EXPECTED_WHITE_ROOKS(0x81);
   ExpectedU64 EXPECTED_WHITE_QUEEN(0x8);
   ExpectedU64 EXPECTED_WHITE_KING(0x10);

   ExpectedU64 EXPECTED_BLACK_PAWNS(0xaf001000000000);
   ExpectedU64 EXPECTED_BLACK_KNIGHTS(0x200800000000000);
   ExpectedU64 EXPECTED_BLACK_BISHOPS(0x2400000000000000);
   ExpectedU64 EXPECTED_BLACK_ROOKS(0x8100000000000000);
   ExpectedU64 EXPECTED_BLACK_QUEEN(0x800000000000000);
   ExpectedU64 EXPECTED_BLACK_KING(0x1000000000000000);

   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::KNIGHT), EXPECTED_WHITE_KNIGHTS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::BISHOP), EXPECTED_WHITE_BISHOPS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::ROOK), EXPECTED_WHITE_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::QUEEN), EXPECTED_WHITE_QUEEN);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::KING), EXPECTED_WHITE_KING);

   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::PAWN), EXPECTED_BLACK_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::KNIGHT), EXPECTED_BLACK_KNIGHTS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::BISHOP), EXPECTED_BLACK_BISHOPS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::ROOK), EXPECTED_BLACK_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::QUEEN), EXPECTED_BLACK_QUEEN);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::KING), EXPECTED_BLACK_KING);
}

TEST_F(ChessboardTest, applyMove_enPassantMoveGetsCorrectlyApplied)
{
   Chessboard game;
   CapturedPiece blackPawn(BLACK, PAWN, f5);
   Move enPassantCapture(WHITE, PAWN, e5, f6, Move::EN_PASSANT);
   enPassantCapture.setCapturedPiece(blackPawn);

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d5));
   game.applyMove(Move(WHITE, PAWN, e4, e5));
   game.applyMove(Move(BLACK, PAWN, f7, f5));

   ExpectedU64 EXPECTED_WHITE_PAWNS(0x100000ef00);
   ExpectedU64 EXPECTED_BLACK_PAWNS(0xd7002800000000);
   ASSERT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   ASSERT_EQ(game.getBitboard(Color::BLACK, PieceType::PAWN), EXPECTED_BLACK_PAWNS);

   game.applyMove(enPassantCapture);

   EXPECTED_WHITE_PAWNS.value = 0x20000000ef00;
   EXPECTED_BLACK_PAWNS.value = 0xd7000800000000;
   ASSERT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   ASSERT_EQ(game.getBitboard(Color::BLACK, PieceType::PAWN), EXPECTED_BLACK_PAWNS);
}

TEST_F(ChessboardTest, undoMove_enPassantGetsCorrectlyUndone)
{
   Chessboard game;
   CapturedPiece blackPawn(BLACK, PAWN, f5);
   Move enPassantCapture(WHITE, PAWN, e5, f6, Move::EN_PASSANT);
   enPassantCapture.setCapturedPiece(blackPawn);

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d5));
   game.applyMove(Move(WHITE, PAWN, e4, e5));
   game.applyMove(Move(BLACK, PAWN, f7, f5));
   game.applyMove(enPassantCapture);
   game.undoMove(enPassantCapture);

   const ExpectedU64 EXPECTED(0xffd700380000efff);
   ASSERT_EQ(game.getOccupiedSquares(), EXPECTED);
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

TEST_F(ChessboardTest, undoMove_castleRightsGetRestoredAfterUndoingAMove)
{
   Chessboard game;

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(WHITE, KING, e1, e2));
   
   EXPECT_EQ(game.getCastleRights(WHITE), CastleRights::NONE);

   game.undoMove(Move(WHITE, KING, e1, e2));

   EXPECT_EQ(game.getCastleRights(WHITE), CastleRights::KING_AND_QUEEN_SIDE);
}

TEST_F(ChessboardTest, undoMove_capturedPieceGetsRestoredAfterUndoingMove)
{
   Chessboard game;
   CapturedPiece blackPawn(BLACK, PAWN, d5);
   Move e4CapturesD5(WHITE, PAWN, e4, d5, Move::CAPTURE);
   e4CapturesD5.setCapturedPiece(blackPawn);

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d5));
   game.applyMove(e4CapturesD5);
   game.undoMove(e4CapturesD5);

   const ExpectedU64 EXPECTED(0xfff700081000efff);
   ASSERT_EQ(game.getOccupiedSquares(), EXPECTED);
}

TEST_F(ChessboardTest, applyMove_castleMoveGetsCorrectlyApplied)
{
   Chessboard game;
   const Move castlingMove(WHITE, KING, e1, g1, Move::KINGSIDE_CASTLE);

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d6));
   game.applyMove(Move(WHITE, BISHOP, f1, d3));
   game.applyMove(Move(BLACK, PAWN, a7, a6));
   game.applyMove(Move(WHITE, KNIGHT, g1, f3));
   game.applyMove(castlingMove);

   ExpectedU64 EXPECTED_WHITE_ROOKS(0x21);
   ExpectedU64 EXPECTED_WHITE_KING(0x40);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::ROOK), EXPECTED_WHITE_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::KING), EXPECTED_WHITE_KING);
}

TEST_F(ChessboardTest, undoMove_castleGetsCorrectlyUndone)
{
   Chessboard game;
   const Move castlingMove(WHITE, KING, e1, g1, Move::KINGSIDE_CASTLE);

   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d6));
   game.applyMove(Move(WHITE, BISHOP, f1, d3));
   game.applyMove(Move(BLACK, PAWN, a7, a6));
   game.applyMove(Move(WHITE, KNIGHT, g1, f3));
   game.applyMove(castlingMove);
   game.undoMove(castlingMove);

   const ExpectedU64 EXPECTED(0xfff609001028ef9f);
   ASSERT_EQ(game.getOccupiedSquares(), EXPECTED);
}

TEST_F(ChessboardTest, applyMove_raisesExceptionIfPieceDoesNotExistOnRequestedSquare)
{
   Chessboard game;
   ASSERT_THROW(game.applyMove(Move(WHITE, KNIGHT, e4, g5)), std::runtime_error);
}

TEST_F(ChessboardTest, applyMove_raisesExceptionIfCaptureInfoIsntSet)
{
   Chessboard game;
   game.applyMove(Move(WHITE, PAWN, e2, e4));
   game.applyMove(Move(BLACK, PAWN, d7, d5));
   Move capture(WHITE, PAWN, e4, d5, Move::CAPTURE);

   ASSERT_THROW(game.applyMove(capture), std::runtime_error);
}

TEST_F(ChessboardTest, applyMove_raisesExceptionIfPromotionInfoIsntSet)
{
   Chessboard game;

   /* This should throw an exception not because the pawn isn't moving to the last rank,
    * but because the move's promotion piece hasn't been set.
    */
   ASSERT_THROW(game.applyMove(Move(WHITE, PAWN, e2, e4, Move::PROMOTION)), std::runtime_error);
}

TEST_F(ChessboardTest, constructor_parsesFEN)
{
   std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   Chessboard game(startingPosition);

   ExpectedU64 EXPECTED_WHITE_PAWNS(0xff00);
   ExpectedU64 EXPECTED_WHITE_KNIGHTS(0x42);
   ExpectedU64 EXPECTED_WHITE_BISHOPS(0x24);
   ExpectedU64 EXPECTED_WHITE_ROOKS(0x81);
   ExpectedU64 EXPECTED_WHITE_QUEEN(0x8);
   ExpectedU64 EXPECTED_WHITE_KING(0x10);

   ExpectedU64 EXPECTED_BLACK_PAWNS(0xff000000000000);
   ExpectedU64 EXPECTED_BLACK_KNIGHTS(0x4200000000000000);
   ExpectedU64 EXPECTED_BLACK_BISHOPS(0x2400000000000000);
   ExpectedU64 EXPECTED_BLACK_ROOKS(0x8100000000000000);
   ExpectedU64 EXPECTED_BLACK_QUEEN(0x800000000000000);
   ExpectedU64 EXPECTED_BLACK_KING(0x1000000000000000);

   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::PAWN), EXPECTED_WHITE_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::KNIGHT), EXPECTED_WHITE_KNIGHTS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::BISHOP), EXPECTED_WHITE_BISHOPS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::ROOK), EXPECTED_WHITE_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::QUEEN), EXPECTED_WHITE_QUEEN);
   EXPECT_EQ(game.getBitboard(Color::WHITE, PieceType::KING), EXPECTED_WHITE_KING);

   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::PAWN), EXPECTED_BLACK_PAWNS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::KNIGHT), EXPECTED_BLACK_KNIGHTS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::BISHOP), EXPECTED_BLACK_BISHOPS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::ROOK), EXPECTED_BLACK_ROOKS);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::QUEEN), EXPECTED_BLACK_QUEEN);
   EXPECT_EQ(game.getBitboard(Color::BLACK, PieceType::KING), EXPECTED_BLACK_KING);

   EXPECT_EQ(game.getActivePlayer(), Color::WHITE);
   EXPECT_EQ(game.getNonActivePlayer(), Color::BLACK);
   EXPECT_EQ(game.getCastleRights(Color::WHITE), CastleRights::KING_AND_QUEEN_SIDE);
   EXPECT_EQ(game.getCastleRights(Color::BLACK), CastleRights::KING_AND_QUEEN_SIDE);
}

}  // namespace
}  // namespace meatball