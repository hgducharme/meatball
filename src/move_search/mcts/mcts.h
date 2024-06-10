#pragma once

#include "move.h"
#include "chessboard.h"
#include "move_search/mcts/node.h"
#include "move_search/search_algorithm.h"

class MonteCarloTreeSearch : public interfaces::SearchAlgorithm
{
   public:
      MonteCarloTreeSearch(const interfaces::PositionEvaluator & evaluator, int searchDepth) : SearchAlgorithm(evaluator, searchDepth) {};
      ~MonteCarloTreeSearch() override {};
      Move getBestMove(const Chessboard & gameState) override;
   private:
      Node selectChildNode(const Node & root);
};