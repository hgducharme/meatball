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

}  // namespace
}  // namespace meatball