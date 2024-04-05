#include "../src/movegenerator.h"
#include "../src/attacktables.h"
#include "../src/types.h"
#include "../utils/perft.h"

#include "gtest/gtest.h"

namespace meatball
{
   namespace
   {

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

         static void SetUpTestSuite()
         {
            // Code here will be called before the first test and will not be called again.
            attack_tables::init();
         }

         static void TearDownTestSuite()
         {
            // Code here will be called after the last test.
         }

         // Class members declared here can be used by all tests in the test suite.
         // To share resources between tests, declare them as static class members,
         // then add their definition just below the test fixture class.
      };

      // TEST_F(MoveGeneratorTest, perft_initialPositionDepth1)
      // {
      //    Chessboard game;
      //    uint16_t depth = 1;
         
      //    u64 numberOfNodes = perft(game, depth);

      //    u64 EXPECTED = 20;
      //    ASSERT_EQ(numberOfNodes, EXPECTED);
      // }

      // TEST_F(MoveGeneratorTest, perft_initialPositionDepth3)
      // {
      //    Chessboard game;
      //    uint16_t depth = 3;

      //    u64 numberOfNodes = perft(game, depth);

      //    u64 EXPECTED = 8902;
      //    ASSERT_EQ(numberOfNodes, EXPECTED);
      // }


      TEST_F(MoveGeneratorTest, perft_enPassant)
      {
         Chessboard game;
         uint16_t depth = 1;

         game.applyMove(Move(WHITE, PAWN, e2, e4));
         game.applyMove(Move(BLACK, PAWN, e7, e5));

         u64 numberOfNodes = perft(game, depth);

         u64 EXPECTED = 8902;
         ASSERT_EQ(numberOfNodes, EXPECTED);
      }

   } // namespace
} // namespace meatball