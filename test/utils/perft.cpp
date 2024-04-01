#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"


u64 perft(Chessboard & gameState, const uint16_t depth)
{
   LegalMoveGenerator moveGenerator;
   int numberOfMoves, i;
   u64 numberOfNodes = 1;

   if (depth == 0) { return numberOfNodes; }

   MoveVector moves = moveGenerator.generateLegalMoves(gameState);
   for (const Move & m : moves)
   {
      gameState.applyMove(m);
      numberOfNodes += perft(gameState, depth - 1);
      gameState.undoMove(m);      
   }

   return numberOfNodes;
}