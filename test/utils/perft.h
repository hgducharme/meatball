#pragma once

#include "../src/types.h"
#include "../src/chessboard.h"

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

PerftResults perft(Chessboard & gameState, const uint16_t depth);