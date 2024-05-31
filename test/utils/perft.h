#pragma once

#include "../src/types.h"
#include "../src/chessboard.h"

#include <vector>
#include <string>
#include <tuple>

struct PerftResults
{
   u64 numberOfNodes = 0;
   int captures = 0;
   int enPassants = 0;
   int castles = 0;
   int promotions = 0;
   int checks = 0;
   int discoveryChecks = 0;
   int doubleChecks = 0;
   int checkmates = 0;

   std::vector<std::tuple<std::string, int>> topLevelNodes;
   void printTopLevelNodes() const;

   PerftResults & operator += (const PerftResults & other)
   {
      numberOfNodes += other.numberOfNodes;
      captures += other.captures;
      enPassants += other.enPassants;
      castles += other.castles;
      promotions += other.promotions;
      checks += other.checks;
      discoveryChecks += other.discoveryChecks;
      doubleChecks += other.doubleChecks;
      checkmates += other.checkmates;

      return *this;
   }
};

/* This perft is just a nice wrapper to the actual __perft method.
 * Set showDivideOutput to 'true' to have the divide results printed to the terminal
*/
PerftResults perft(Chessboard &gameState, const uint16_t depth, const bool showDivideOutput, MoveVector & moveHistory);

namespace
{

// Override << to print various enums as text
std::ostream& operator<<(std::ostream& out, const Color value);
std::ostream& operator<<(std::ostream& out, const PieceType value);
std::ostream& operator<<(std::ostream& os, Square square);

std::string moveToString(const Move & m);

/* This perft takes an initialDepth parameter so that we can implement perft divide functionality.
 * Perft divide means that we can show how many child nodes are located under each top level node.
 */
PerftResults __perft(Chessboard gameState, const uint16_t depth, const uint16_t initialDepth, const bool showDivideOutput, MoveVector & moveHistory);
void trackMetaData(PerftResults &results, const Move &move, const uint16_t depth, const uint16_t initialDepth, PerftResults &childResults);
void tallyTopLevelNodes(const uint16_t depth, const uint16_t initialDepth, const Move &move, PerftResults &results, PerftResults &childResults);
void tallyMoveType(PerftResults &results, const Move &move);
void raiseExceptionIfGameStateNotProperlyRestored(Chessboard &gameState, Chessboard &originalState, const Move &move, const uint16_t depth, const uint16_t initialDepth, const MoveVector & moveHistory);
void printDivideOutput(const PerftResults &results);
void printMoveHistory(const MoveVector & moveHistory);

} // end anonymous namespace