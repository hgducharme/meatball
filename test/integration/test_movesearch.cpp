#include "../src/chessboard.h"
#include "../src/move.h"
#include "../src/move_search/search_algorithm.h"
#include "../src/move_search/position_evaluator.h"

#include "gtest/gtest.h"

namespace meatball
{
   namespace
   {

      // The fixture for testing the class.
      class TestMoveSearch : public ::testing::Test
      {
      protected:
         // You can remove any or all of the following functions if their bodies would
         // be empty.

         TestMoveSearch()
         {
            // You can do set-up work for each test here.
         }

         ~TestMoveSearch() override
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

      TEST_F(TestMoveSearch, test1)
      {
         Chessboard game;
         const int searchDepth = 1;
         std::unique_ptr<interfaces::PositionEvaluator> neuralNetwork = createPositionEvaluator(PositionEvaluatorImplementation::NeuralNetwork);
         std::unique_ptr<interfaces::SearchAlgorithm> monteCarloTreeSearch = createSearchAlgorithm(SearchAlgorithmImplementation::MonteCarloTreeSearch, (*neuralNetwork), searchDepth);

         Move bestMove = monteCarloTreeSearch->getBestMove(game);

         ASSERT_FALSE(true);
      }

   } // namespace
} // namespace appname