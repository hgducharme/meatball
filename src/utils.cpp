#include "utils.h"

#include "constants.h"
#include "chessboard.h"

#include <cmath>     // std::abs
#include <algorithm> // std::math
#include <random>    // random number generation

namespace utils
{

Bitboard shiftSquareByDirection(const Square square, const int numberOfBits)
{
   Bitboard squareAsBitboard(square);
   return shiftSquareByDirection(squareAsBitboard, numberOfBits);
}

Bitboard shiftSquareByDirection(const Bitboard & oldPosition, const int numberOfBits)
{
   Bitboard newPosition;

   if (numberOfBits > 0)
   {
      newPosition = oldPosition << numberOfBits;
   }
   else
   {
      newPosition = oldPosition >> std::abs(numberOfBits);
   }

   return newPosition;
}

int calculateDistanceToEdgeOfBoard(Square square, Direction direction)
{
    Rank currentRank = Chessboard::squareToRank(square);
    File currentFile = Chessboard::squareToFile(square);
    
    int distance;
    int horizontalDistanceToEdge;
    int verticalDistanceToEdge;
    
    switch (direction)
    {
        case NORTH_EAST:
            verticalDistanceToEdge = Rank::RANK_8 - currentRank;
            horizontalDistanceToEdge = File::FILE_H - Chessboard::squareToFile(square);
            distance = std::min(horizontalDistanceToEdge, verticalDistanceToEdge);
            break;
        case NORTH_WEST:
            verticalDistanceToEdge = Rank::RANK_8 - currentRank;
            horizontalDistanceToEdge = currentFile;
            distance = std::min(horizontalDistanceToEdge, verticalDistanceToEdge);
            break;
        case SOUTH_EAST:
            verticalDistanceToEdge = currentRank;
            horizontalDistanceToEdge = File::FILE_H - currentFile;
            distance = std::min(horizontalDistanceToEdge, verticalDistanceToEdge);
            break;
        case SOUTH_WEST:
            verticalDistanceToEdge = currentRank;
            horizontalDistanceToEdge = currentFile;
            distance = std::min(horizontalDistanceToEdge, verticalDistanceToEdge);
            break;
        case NORTH:
            distance = Rank::RANK_8 - currentRank;
            break;
        case SOUTH:
            distance = currentRank;
            break;
        case EAST:
            distance = File::FILE_H - currentFile;
            break;
        case WEST:
            distance = currentFile;
            break;
    }

    return distance;
}

u64 getRandom64BitInteger()
{
    std::random_device randomSeed;
    std::mt19937_64 mersenneTwisterAlgorithm(randomSeed());
    std::uniform_int_distribution<u64> distribution(2, UINT64_MAX);

    return distribution(mersenneTwisterAlgorithm);
}

u64 getSparselyPopulatedRandom64BitInteger()
{
    return getRandom64BitInteger() & getRandom64BitInteger() & getRandom64BitInteger();
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

} // namespace utils