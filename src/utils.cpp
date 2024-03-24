#include "utils.h"

#include "constants.h"
#include "chessboard.h"

#include <cmath>     // std::abs
#include <algorithm> // std::math
#include <random>    // random number generation

namespace utils
{

Bitboard shiftCurrentSquareByDirection(const Bitboard & oldPosition, const int numberOfBits)
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

} // namespace utils