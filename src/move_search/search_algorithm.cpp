#include "search_algorithm.h"
#include "exceptions.h"
#include "move_search/mcts/mcts.h"

std::unique_ptr<interfaces::SearchAlgorithm> createSearchAlgorithm(SearchAlgorithmImplementation implementation, interfaces::PositionEvaluator & evaluator, int searchDepth)
{
   switch (implementation) {
      case SearchAlgorithmImplementation::MonteCarloTreeSearch:
      {
         return std::make_unique<MonteCarloTreeSearch>(evaluator, searchDepth);
      }
      default:
      {
         throw exceptions::InvalidEnumOption("Invalid SearchAlgorithmImplementation option");
      }
   }
}