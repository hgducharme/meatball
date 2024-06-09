#include "../src/move_generation.h"
#include "../src/attacktables.h"
#include "../src/types.h"
#include "../utils/perft.h"

#include "gtest/gtest.h"

namespace meatball
{
   namespace
   {

      // The fixture for testing the class.
      class MoveGenerationTest : public ::testing::Test
      {
      protected:
         // You can remove any or all of the following functions if their bodies would
         // be empty.

         MoveGenerationTest()
         {
            // You can do set-up work for each test here.
         }

         ~MoveGenerationTest() override
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

      TEST_F(MoveGenerationTest, perft_initialPositionDepth1)
      {
         Chessboard game;
         uint16_t depth = 1;
         MoveVector moveHistory;
         
         PerftResults results = perft(game, depth, false, moveHistory);

         u64 EXPECTED_NODES = 20;
         int EXPECTED_CAPTURES = 0;
         int EXPECTED_ENPASSANTS = 0;
         int EXPECTED_CASTLES = 0;
         int EXPECTED_PROMOTIONS = 0;
         int EXPECTED_CHECKS = 0;
         int EXPECTED_DISCOVERYCHECKS = 0;
         int EXPECTED_DOUBLECHECKS = 0;
         int EXPECTED_CHECKMATES = 0;

         EXPECT_EQ(results.numberOfNodes, EXPECTED_NODES);
         EXPECT_EQ(results.captures, EXPECTED_CAPTURES);
         EXPECT_EQ(results.enPassants, EXPECTED_ENPASSANTS);
         EXPECT_EQ(results.castles, EXPECTED_CASTLES);
         EXPECT_EQ(results.promotions, EXPECTED_PROMOTIONS);
         EXPECT_EQ(results.checks, EXPECTED_CHECKS);
         EXPECT_EQ(results.discoveryChecks, EXPECTED_DISCOVERYCHECKS);
         EXPECT_EQ(results.doubleChecks, EXPECTED_DOUBLECHECKS);
         EXPECT_EQ(results.checkmates, EXPECTED_CHECKMATES);
      }

      TEST_F(MoveGenerationTest, perft_initialPositionDepth3)
      {
         Chessboard game;
         uint16_t depth = 3;
         MoveVector moveHistory;

         PerftResults results = perft(game, depth, false, moveHistory);

         u64 EXPECTED_NODES = 8902;
         int EXPECTED_CAPTURES = 34;
         int EXPECTED_ENPASSANTS = 0;
         int EXPECTED_CASTLES = 0;
         int EXPECTED_PROMOTIONS = 0;
         int EXPECTED_CHECKS = 12;
         int EXPECTED_DISCOVERYCHECKS = 0;
         int EXPECTED_DOUBLECHECKS = 0;
         int EXPECTED_CHECKMATES = 0;

         EXPECT_EQ(results.numberOfNodes, EXPECTED_NODES);
         EXPECT_EQ(results.captures, EXPECTED_CAPTURES);
         EXPECT_EQ(results.enPassants, EXPECTED_ENPASSANTS);
         EXPECT_EQ(results.castles, EXPECTED_CASTLES);
         EXPECT_EQ(results.promotions, EXPECTED_PROMOTIONS);
         EXPECT_EQ(results.checks, EXPECTED_CHECKS);
         EXPECT_EQ(results.discoveryChecks, EXPECTED_DISCOVERYCHECKS);
         EXPECT_EQ(results.doubleChecks, EXPECTED_DOUBLECHECKS);
         EXPECT_EQ(results.checkmates, EXPECTED_CHECKMATES);
      }

      TEST_F(MoveGenerationTest, perft_testPosition1)
      {
         Chessboard game("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
         uint16_t depth = 3;
         MoveVector moveHistory;

         PerftResults results = perft(game, depth, false, moveHistory);

         u64 EXPECTED_NODES = 62379;
         EXPECT_EQ(results.numberOfNodes, EXPECTED_NODES);
      }
   } // namespace
} // namespace meatball