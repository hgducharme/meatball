#include "perft.h"

#include "../src/types.h"
#include "../src/constants.h"
#include "../src/movegenerator.h"
#include "../src/utils.h"

#include <iostream>

PerftResults perft(Chessboard &gameState, const uint16_t depth, const bool showDivideOutput, MoveVector & moveHistory)
{
   return __perft(gameState, depth, depth, showDivideOutput, moveHistory);
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

PerftResults __perft(Chessboard gameState, const uint16_t depth, const uint16_t initialDepth, const bool showDivideOutput, MoveVector & moveHistory)
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
      moveHistory.push_back(move);

      try
      {
         gameState.applyMove(move);
      }
      catch (std::runtime_error e)
      {
         std::cerr << "Exception occured when trying to apply move: " << e.what() << std::endl;
         printMoveHistory(moveHistory);
      }
      PerftResults childResults = __perft(gameState, depth - 1, initialDepth, showDivideOutput, moveHistory);
      results += childResults;

      trackMetaData(results, move, depth, initialDepth, childResults);

      try
      {
         gameState.undoMove(move);
      }
      catch (std::runtime_error e)
      {
         std::cerr << "Exception occured when trying to undo move: " << e.what() << std::endl;
         printMoveHistory(moveHistory);
      }
      raiseExceptionIfGameStateNotProperlyRestored(gameState, originalState, move, depth, initialDepth, moveHistory);

      moveHistory.pop_back();
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
   results.checks += static_cast<int>(move.isCheck());

   /*
   // TODO: add the rest of the move types to the results.
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

void raiseExceptionIfGameStateNotProperlyRestored(Chessboard &gameState, Chessboard &originalState, const Move &move, const uint16_t depth, const uint16_t initialDepth, const MoveVector & moveHistory)
{
   // Verify the game state got restored correctly after undoing the move
   if (!(gameState == originalState))
   {
      printMoveHistory(moveHistory);

      throw std::runtime_error("The state of the board was not correctly restored after making the move: " + moveToString(move) + ". Current depth: " + std::to_string(depth) + ". Initial depth: " + std::to_string(initialDepth));
   }
}

void printDivideOutput(const PerftResults &results)
{
   results.printTopLevelNodes();
}

void printMoveHistory(const MoveVector & moveHistory)
{
   std::cout << "Move history:" << std::endl;
   for (const Move & m : moveHistory)
   {
      std::cout << moveToString(m) << std::endl;
   }
}

} // end anonymous namespace