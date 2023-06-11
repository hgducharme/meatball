#include "../src/movegenerator.h"
#include "../src/attacktables.h"
#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class MoveGeneratorTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  MoveGeneratorTest()
  {
     // You can do set-up work for each test here.
  }

  ~MoveGeneratorTest() override
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

TEST_F(MoveGeneratorTest, generatePsuedoLegalMoves)
{
   Chessboard chessboard;
   MoveGenerator moveGenerator;
   attack_tables::init();
   
   std::vector<Move> moveList = moveGenerator.generatePsuedoLegalMoves(chessboard);
}

}  // namespace
}  // namespace meatball