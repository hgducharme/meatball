#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"


u64 perft(Chessboard & gameState, const uint16_t depth)
{
   LegalMoveGenerator moveGenerator;

   if (depth == 0) { return 1; }

   u64 numberOfNodes = 0;
   MoveVector moves = moveGenerator.generateLegalMoves(gameState);
   for (const Move & m : moves)
   {
      gameState.applyMove(m);
      numberOfNodes += perft(gameState, depth - 1);
      gameState.undoMove(m);      
   }

   return numberOfNodes;
}