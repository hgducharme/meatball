#include "utils.h"

namespace utils
{

Bitboard shiftPieceOnBitboard(const Bitboard & oldPosition, const int numberOfBits)
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

int calculateDistanceFromEdgeOfBoard(Square square, Direction direction)
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

    return std::min(horizontalDistanceFromEdge, verticalDistanceFromEdge);
}

u64 getRandom64BitInteger()
{
    // Generate random integers, cast them to a 64-bit integer, and only take the first 2 bytes (16 bits)
    u64 bytes1And2 = (u64)(random()) & 0xFFFF;
    u64 bytes3And4 = (u64)(random()) & 0xFFFF;
    u64 bytes5And6 = (u64)(random()) & 0xFFFF;
    u64 bytes7and8 = (u64)(random()) & 0xFFFF;

    // Create the random 64 bit integer by mix and matching the two-byte snippets or "words"
    return bytes1And2 | (bytes3And4 << constants::INDEX_OF_THIRD_BYTE) | (bytes5And6 << constants::INDEX_OF_FIFTH_BYTE) | (bytes7and8 << constants::INDEX_OF_SEVENTH_BYTE);
}

} // namespace utils