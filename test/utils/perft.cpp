#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"

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

std::string squareToString(Square square)
{
   switch (square)
   {
   case a1:
      return "a1";
   case b1:
      return "b1";
   case c1:
      return "c1";
   case d1:
      return "d1";
   case e1:
      return "e1";
   case f1:
      return "f1";
   case g1:
      return "g1";
   case h1:
      return "h1";
   case a2:
      return "a2";
   case b2:
      return "b2";
   case c2:
      return "c2";
   case d2:
      return "d2";
   case e2:
      return "e2";
   case f2:
      return "f2";
   case g2:
      return "g2";
   case h2:
      return "h2";
   case a3:
      return "a3";
   case b3:
      return "b3";
   case c3:
      return "c3";
   case d3:
      return "d3";
   case e3:
      return "e3";
   case f3:
      return "f3";
   case g3:
      return "g3";
   case h3:
      return "h3";
   case a4:
      return "a4";
   case b4:
      return "b4";
   case c4:
      return "c4";
   case d4:
      return "d4";
   case e4:
      return "e4";
   case f4:
      return "f4";
   case g4:
      return "g4";
   case h4:
      return "h4";
   case a5:
      return "a5";
   case b5:
      return "b5";
   case c5:
      return "c5";
   case d5:
      return "d5";
   case e5:
      return "e5";
   case f5:
      return "f5";
   case g5:
      return "g5";
   case h5:
      return "h5";
   case a6:
      return "a6";
   case b6:
      return "b6";
   case c6:
      return "c6";
   case d6:
      return "d6";
   case e6:
      return "e6";
   case f6:
      return "f6";
   case g6:
      return "g6";
   case h6:
      return "h6";
   case a7:
      return "a7";
   case b7:
      return "b7";
   case c7:
      return "c7";
   case d7:
      return "d7";
   case e7:
      return "e7";
   case f7:
      return "f7";
   case g7:
      return "g7";
   case h7:
      return "h7";
   case a8:
      return "a8";
   case b8:
      return "b8";
   case c8:
      return "c8";
   case d8:
      return "d8";
   case e8:
      return "e8";
   case f8:
      return "f8";
   case g8:
      return "g8";
   case h8:
      return "h8";
   default:
      return "UNKNOWN";
   }
}

// Override << to print Square enum as text
std::ostream &operator<<(std::ostream &os, Square square)
{
   return os << squareToString(square);
}

std::string moveToString(const Move &m)
{
   return squareToString(m.startSquare) + squareToString(m.endSquare);
}

// This perft takes an initialDepth parameter so that we can implement perft divide functionality
// Perft divide means that we can spit how many child nodes are located under each top level node
// TODO: make sure en passant also gets restored after unmaking a move.
// TODO: I'm not sure why it's still broken. We removed pushes to occupied squares. Double check why.
// TODO: place the following conditional breakpoint right inside the for loop:
// (depth == 1) && (move.startSquare == a4) && (move.endSquare == a5)
// The move history goes: a2a4, a7a5, and then the move generator says we can make the move a4a5 but we can't
// because there is a piece there. And then when we unmake the move a4a5 we clear the a5 bit which deletes
// the black pawn that was occupying that square.
// https://www.reddit.com/r/chessprogramming/comments/152monz/how_to_use_perft_results_when_debugging_and/
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
      results.captures += static_cast<int>(move.isCapture);

      PerftResults childResults = __perft(gameState, depth - 1, initialDepth, showDivideOutput);
      results += childResults;

      if (depth == initialDepth)
      {
         std::string topLevelNode = moveToString(move);

         results.topLevelNodes.push_back(std::make_tuple(topLevelNode, childResults.numberOfNodes));

         if (showDivideOutput)
         {
            std::cout << move.color << " " << move.piece << " : " << move.startSquare << move.endSquare << " - " << childResults.numberOfNodes << std::endl;
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