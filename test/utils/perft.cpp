#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"
#include "../src/utils.h"

#include <iostream>

PerftResults perft(Chessboard &gameState, const uint16_t depth, const bool showDivideOutput)
{
   return __perft(gameState, depth, depth, showDivideOutput);
}

void PerftResults::printTopLevelNodes() const {
    for (const auto& [move, childNodes] : topLevelNodes) {
        std::cout << move << ": " << childNodes << std::endl;
    }

    std::cout << "==========" << std::endl;
    std::cout << "Nodes searched: " << numberOfNodes << std::endl;
}

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

      PerftResults childResults = __perft(gameState, depth - 1, initialDepth, showDivideOutput);
      results += childResults;

      trackMetaData(results, move, depth, initialDepth, childResults);
      gameState.undoMove(move);
      raiseExceptionIfGameStateNotProperlyRestored(gameState, originalState, move, depth, initialDepth);
   }

   if (depth == initialDepth && showDivideOutput)
   {
      printDivideOutput(results);
   }

   return results;
}

void trackMetaData(PerftResults &results, const Move &move, const uint16_t depth, const uint16_t initialDepth, PerftResults &childResults)
{
   tallyMoveType(results, move);
   tallyTopLevelNodes(depth, initialDepth, move, results, childResults);
}

void tallyMoveType(PerftResults &results, const Move &move)
{
   results.captures += static_cast<int>(move.isCapture());
   results.enPassants += static_cast<int>(move.isEnPassant());
   results.castles += static_cast<int>(move.isCastle());
   results.promotions += static_cast<int>(move.isPromotion());

   /*
   // TODO: add the rest of the move types to the results.
   results.checks += static_cast<int>(move.isCheck());
   results.discoveryChecks += static_cast<int>(move.isDiscoveryCheck());
   results.doubleChecks += static_cast<int>(move.isDoubleCheck());
   results.checkmates += static_cast<int>(move.isCheckmate());
   */
}

void tallyTopLevelNodes(const uint16_t depth, const uint16_t initialDepth, const Move &move, PerftResults &results, PerftResults &childResults)
{
   if (depth == initialDepth)
   {
      std::string topLevelNode = moveToString(move);
      results.topLevelNodes.push_back(std::make_tuple(topLevelNode, childResults.numberOfNodes));
   }
}

void raiseExceptionIfGameStateNotProperlyRestored(Chessboard &gameState, Chessboard &originalState, const Move &move, const uint16_t depth, const uint16_t initialDepth)
{
   // Verify the game state got restored correctly after undoing the move
   if (!(gameState == originalState))
   {
      // TODO: print move history.
      throw std::runtime_error("The state of the board was not correctly restored after making the move: " + moveToString(move) + ". Current depth: " + std::to_string(depth) + ". Initial depth: " + std::to_string(initialDepth));
   }
}

void printDivideOutput(const PerftResults &results)
{
   results.printTopLevelNodes();
}

} // end anonymous namespace