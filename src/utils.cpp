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

Bitboard shiftToNewPosition(const Bitboard & oldPosition, const int numberOfRanksToMove, const int numberOfFilesToMove)
{
    /*
     * NOTE: This function produces the desired results by implicitly relying on the rules
     * for left shift and right shift operators in C++11. Left and right shifts are non-circular,
     * and bits that are shifted outside the width of the container will zero-fill that particular bit.
    */

    int numberOfBitsToMove = convertRelativePositionVectorToNumberOfBits(numberOfRanksToMove, numberOfFilesToMove);
    Bitboard newPosition;

    // If number of bits is positive, do a left shift, otherwise do a right shift
    if (numberOfBitsToMove > 0)
    {
        newPosition = oldPosition << numberOfBitsToMove;
    }
    else
    {
        newPosition = oldPosition >> std::abs(numberOfBitsToMove);
    }

    return newPosition;
}

int convertRelativePositionVectorToNumberOfBits(const int numberOfRanksToMove, const int numberOfFilesToMove)
{
    /* numberOfBits = numberOfFilesInARank * deltaRanks + deltaFiles */
    return File::NUMBER_OF_FILES * numberOfRanksToMove + numberOfFilesToMove;
}

} // namespace utils