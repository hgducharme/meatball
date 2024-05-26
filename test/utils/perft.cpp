#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"
#include "../src/utils.h"

#include <iostream>

namespace
{

// Override << to print PieceType enum as text
std::ostream &operator<<(std::ostream &out, const PieceType value)
{
   auto str = [value]()
   {
      switch (value)
      {
      case PAWN:
         return "PAWN";
      case KNIGHT:
         return "KNIGHT";
      case BISHOP:
         return "BISHOP";
      case ROOK:
         return "ROOK";
      case QUEEN:
         return "QUEEN";
      case KING:
         return "KING";
      default:
         return "UNKNOWN";
      }
   }();
   return out << str;
}

// Override << to print Color enum as text
std::ostream &operator<<(std::ostream &out, const Color value)
{
   auto str = [value]()
   {
      switch (value)
      {
      case WHITE:
         return "WHITE";
      case BLACK:
         return "BLACK";
      default:
         return "UNKNOWN";
      }
   }();
   return out << str;
}

// Override << to print Square enum as text
std::ostream &operator<<(std::ostream &os, Square square)
{
   return os << utils::squareToString(square);
}

std::string moveToString(const Move &m)
{
   return utils::squareToString(m.startSquare()) + utils::squareToString(m.endSquare());
}

// This perft takes an initialDepth parameter so that we can implement perft divide functionality
// Perft divide means that we can spit how many child nodes are located under each top level node
PerftResults __perft(Chessboard &gameState, const uint16_t depth, const uint16_t initialDepth, const bool showDivideOutput)
{
   LegalMoveGenerator moveGenerator;
   PerftResults results;

   if (depth == 0)
   {
      results.numberOfNodes = 1;
      return results;
   }

   MoveVector moves = moveGenerator.generateLegalMoves(gameState);
   for (const Move & move : moves)
   {
      Chessboard originalState = gameState;
      gameState.applyMove(move);
      results.captures += static_cast<int>(move.isCapture());

      PerftResults childResults = __perft(gameState, depth - 1, initialDepth, showDivideOutput);
      results += childResults;

      if (depth == initialDepth)
      {
         std::string topLevelNode = moveToString(move);

         results.topLevelNodes.push_back(std::make_tuple(topLevelNode, childResults.numberOfNodes));

         if (showDivideOutput)
         {
            std::cout << move.color() << " " << move.pieceType() << " : " << move.startSquare() << move.endSquare() << " - " << childResults.numberOfNodes << std::endl;
         }
      }

      gameState.undoMove(move);
      if (!(gameState == originalState))
      {
         throw std::runtime_error("The state of the board was not correctly restored after making the move: " + moveToString(move) + ". Current depth: " + std::to_string(depth) + ". Initial depth: " + std::to_string(initialDepth));
      }
   }

   return results;
}

} // end anonymous namespace

// This perft is just a nice interface wrapper
// Set showDivideOutput to 'true' to have the divide results printed to the terminal
PerftResults perft(Chessboard &gameState, const uint16_t depth, const bool showDivideOutput)
{
   return __perft(gameState, depth, depth, showDivideOutput);
}