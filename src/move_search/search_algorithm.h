#pragma once

#include "move.h"
#include "chessboard.h"
#include "move_search/position_evaluator.h"

namespace interfaces
{
   class SearchAlgorithm
   {
      public:
         virtual ~SearchAlgorithm() {};
         virtual Move getBestMove(const Chessboard & gameState) = 0;

      protected:
         SearchAlgorithm(const interfaces::PositionEvaluator & evaluator, int searchDepth) : _evaluator(evaluator), _searchDepth(searchDepth) {};
         const PositionEvaluator & _evaluator;
         int _searchDepth = 1;
   };
}

enum class SearchAlgorithmImplementation { MonteCarloTreeSearch };

class MonteCarloTreeSearch : public interfaces::SearchAlgorithm
{
   public:
      MonteCarloTreeSearch(const interfaces::PositionEvaluator & evaluator, int searchDepth) : SearchAlgorithm(evaluator, searchDepth) {};
      ~MonteCarloTreeSearch() override {};
      Move getBestMove(const Chessboard & gameState) override;
};


std::unique_ptr<interfaces::SearchAlgorithm> createSearchAlgorithm(SearchAlgorithmImplementation implementation, interfaces::PositionEvaluator & evaluator, int searchDepth);