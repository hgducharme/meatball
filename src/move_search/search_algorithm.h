#pragma once

#include "move.h"
#include "chessboard.h"
#include "move_search/position_evaluator.h"

enum class SearchAlgorithmImplementation { MonteCarloTreeSearch };

namespace interfaces
{
   class SearchAlgorithm
   {
      public:
         virtual ~SearchAlgorithm() {};
         virtual Move getBestMove(const Chessboard & gameState) = 0;

      protected:
         SearchAlgorithm(const interfaces::PositionEvaluator & evaluator, int searchDepth) : evaluator_(evaluator), searchDepth_(searchDepth) {};
         const PositionEvaluator & evaluator_;
         int searchDepth_ = 1;
   };
}

std::unique_ptr<interfaces::SearchAlgorithm> createSearchAlgorithm(SearchAlgorithmImplementation implementation, interfaces::PositionEvaluator & evaluator, int searchDepth);