#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"

PerftResults perft(Chessboard & gameState, const uint16_t depth)
{
   LegalMoveGenerator moveGenerator;
   PerftResults results;

   if (depth == 0)
   {
      results.numberOfNodes = 1;
      return results;
   }

   MoveVector moves = moveGenerator.generateLegalMoves(gameState);
   for (const Move & m : moves)
   {
      gameState.applyMove(m);
      results += perft(gameState, depth - 1);
      gameState.undoMove(m);      
   }

   return results;
}