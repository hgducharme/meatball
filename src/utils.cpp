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

int calculateDistanceToEdgeOfBoard(Square square, Direction direction, bool includeEdgeSquare)
{
    Rank currentRank = Chessboard::squareToRank(square);
    File currentFile = Chessboard::squareToFile(square);

    int horizontalDistanceFromEdge, verticalDistanceFromEdge;
    switch (direction)
    {
        case NORTH_EAST:
            verticalDistanceFromEdge = Rank::RANK_8 - currentRank;
            horizontalDistanceFromEdge = File::FILE_H - Chessboard::squareToFile(square);
            break;
        case NORTH_WEST:
            verticalDistanceFromEdge = Rank::RANK_8 - currentRank;
            horizontalDistanceFromEdge = currentFile;
            break;
        case SOUTH_EAST:
            verticalDistanceFromEdge = currentRank;
            horizontalDistanceFromEdge = File::FILE_H - currentFile;
            break;
        case SOUTH_WEST:
            verticalDistanceFromEdge = currentRank;
            horizontalDistanceFromEdge = currentFile;
            break;
        case NORTH:
            return Rank::RANK_8 - currentRank;
        case SOUTH:
            return currentRank;
        case EAST:
            return File::FILE_H - currentFile;
        case WEST:
            return currentFile;
    }

    if (includeEdgeSquare == false)
    {
        constexpr int EDGE_SQUARE = 1;
        return std::min(horizontalDistanceFromEdge, verticalDistanceFromEdge) - EDGE_SQUARE;

    }

    return std::min(horizontalDistanceFromEdge, verticalDistanceFromEdge);
}

u64 getRandom64BitInteger()
{
    std::random_device randomSeed;
    std::mt19937_64 mersenneTwisterAlgorithm(randomSeed());
    std::uniform_int_distribution<u64> distribution(2, std::pow(2,64) - 1);

    return distribution(mersenneTwisterAlgorithm);
}

u64 getSparselyPopulatedRandom64BitInteger()
{
    return getRandom64BitInteger() & getRandom64BitInteger() & getRandom64BitInteger();
}

} // namespace utils