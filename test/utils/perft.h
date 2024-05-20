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

namespace
{
// Override << to print various enums as text
std::ostream& operator<<(std::ostream& out, const Color value);
std::ostream& operator<<(std::ostream& out, const PieceType value);
std::ostream& operator<<(std::ostream& os, Square square);

std::string squareToString(Square square);
std::string moveToString(const Move & m);

// Perft with divide functionality
PerftResults __perft(Chessboard & gameState, const uint16_t depth, const uint16_t initialDepth, const bool showDivideOutput);
}

// Public interface to the perft function
PerftResults perft(Chessboard & gameState, const uint16_t depth, const bool showDivideOutput);