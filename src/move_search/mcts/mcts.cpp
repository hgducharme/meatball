#include "mcts.h"

Move MonteCarloTreeSearch::getBestMove(const Chessboard & gameState)
{
   Node root;
   root.currentPlayer = gameState.getActivePlayer();
   
   for (int i = 0; i < 2; i++)
   {
      Node leaf = selectChildNode(root);
      if (leaf.endsGame) { continue; }
      // expand(leaf);
      // (leaf_value, policy) = simulate(leaf); // lc0's "policy" is a list of moves and a probability for each move. see here: https://lczero.org/dev/wiki/technical-explanation-of-leela-chess-zero/
      // backpropgate(leaf, result);
   }

   // return bestMove(root);
}

Node MonteCarloTreeSearch::selectChildNode(const Node & root)
{
   for (const Node & child : root.children)
   {
      int i = 1;
      // int sumOfAllSiblingVisitCounts = sum(root.children, unless c == child);
      // int puct = child.currentPlayer * averageUtilityOf(child) + ( cpuct * policyOf(child) * (1 / (1 + child.visits)) * sqrt( sumOfAllSiblingVisitCounts ) );
   }
}