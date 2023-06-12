#include "bitboard.h"
Bitboard::Bitboard(u64 boardState) : board_(boardState)
{}

Bitboard::Bitboard(Square s)
{
    setBit(s);
}

void Bitboard::setBit(int n)
{
    // Shift bitboard::ONE by n positions to the left and do a bitwise OR with board_
    board_ |= (bitboard::ONE << n);
}

void Bitboard::clearBit(int n)
{
    // Shift bitboard::ONE by n positions to the left, invert it, and do a bitwise AND with board_ 
    board_ &= ~(bitboard::ONE << n);
}

int Bitboard::getBit(int n) const
{
    // Move the bit of interest to the least significant bit and compare it to 1
    return ( (board_ >> n) & bitboard::ONE );
}

void Bitboard::reset()
{
    setBoard(bitboard::EMPTY_BOARD);
}

int Bitboard::numberOfSetBits() const
{
    unsigned int count = 0;

    if (board_ == 0) { return count; }

    u64 copyOfBoard = board_;
    while (copyOfBoard)
    {
        // Check if the least significant bit is 0 or 1 and add it to the count
        count += (copyOfBoard & 1);

        // Shift all values to the right one
        copyOfBoard >>= 1;
    }

    return count;
}

int Bitboard::findIndexLSB() const
{
    int indexOfLSB = -1;
    
    if (board_ == 0) { return indexOfLSB; }

    u64 copyOfBoard = board_;
    unsigned int currentPosition = 0;
    while (indexOfLSB < 0)
    {
        // Isolate the very first bit
        int valueOfLSB = (copyOfBoard & bitboard::ONE);

        // Check if we found the least significant bit
        if (valueOfLSB == 1) { indexOfLSB = currentPosition; }

        // Shift all the bits to the right one
        copyOfBoard >>= 1;

        // Increase the position one bit to the left
        currentPosition++;
    }

    return indexOfLSB;
}

int Bitboard::findIndexMSB() const
{
    int indexOfMSB = -1;

    if (board_ == 0) { return indexOfMSB; }
    
    // This loop starts searching from the most significant bit
    unsigned int currentPosition = 63;
    u64 copyOfBoard = board_;
    while (indexOfMSB < 0)
    {
        // Isolate the very last bit
        u64 intersectionOfTheLastBit = (copyOfBoard & bitboard::MOST_SIGNIFICANT_BIT_SET);

        // Shift the last bit to the very first bit
        int valueOfMSB = (intersectionOfTheLastBit >> 63);
        
        // Check if we found the most significant bit
        if (valueOfMSB == 1) { indexOfMSB = currentPosition; }

        // Shift all the bits to the left one
        copyOfBoard <<= 1;

        // Decrease the position one bit to the right
        currentPosition--;
    }

    return indexOfMSB;
}

int Bitboard::clearAndReturnLSB()
{
    int indexOfLSB = findIndexLSB();
    clearBit(indexOfLSB);
    return indexOfLSB;
}

int Bitboard::clearAndReturnMSB()
{
    int indexOfMSB = findIndexMSB();
    clearBit(indexOfMSB);
    return indexOfMSB;
}