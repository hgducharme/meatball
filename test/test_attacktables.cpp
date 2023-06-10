#include "../src/movegenerator.h"
#include "../src/types.h"

#include "gtest/gtest.h"

namespace meatball {
namespace {

// The fixture for testing the class.
class AttackTablesTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  AttackTablesTest()
  {
     // You can do set-up work for each test here.
  }

  ~AttackTablesTest() override
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

TEST_F(AttackTablesTest, pawnAttackTable)
{
   int lengthOfPawnTable = sizeof(attack_tables::pawn)/sizeof(attack_tables::pawn[0]);
   for (int square = 0; square < lengthOfPawnTable; square++)
   {
      EXPECT_EQ(attack_tables::pawn[square], constants::attack_masks::pawn_single_push);
   }
}

}  // namespace
}  // namespace meatball