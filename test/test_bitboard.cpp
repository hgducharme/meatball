#include "../src/bitboard.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class BitboardTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  BitboardTest() {
     // You can do set-up work for each test here.
  }

  ~BitboardTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite.
};

TEST_F(BitboardTest, defaultBitboardStateShouldBeZero) {
   u64 DEFAULT_BOARD_STATE = 0;

   Bitboard bitboard;

   ASSERT_EQ(bitboard.getBoard(), DEFAULT_BOARD_STATE);
}

TEST_F(BitboardTest, constructorShouldBeAbleToInitializeBoardWithAState) {
   Bitboard bitboard(constants::DEFAULT_BLACK_PAWN_STRUCTURE);
   u64 board = bitboard.getBoard();

   ASSERT_EQ(board, constants::DEFAULT_BLACK_PAWN_STRUCTURE);
}

TEST_F(BitboardTest, setSquareSetsCorrectSquare) {
   Bitboard bitboard;

   bitboard.setBit(g3);
   
   u64 EXPECTED_BITBOARD = 0x0000000000400000;
   ASSERT_EQ(bitboard.getBoard(), EXPECTED_BITBOARD);
}

}  // namespace
}  // namespace meatball