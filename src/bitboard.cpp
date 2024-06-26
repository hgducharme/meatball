#include "bitboard.h"

#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <iomanip>

Bitboard::Bitboard(u64 boardState) : board_(boardState)
{}

Bitboard::Bitboard(int bit)
{
    setBit(bit);
}

std::string Bitboard::toHex() const
{
    std::stringstream ss;
    ss << "0x" << std::hex << this->toU64();
    return ss.str();
}

std::string Bitboard::toBinary(bool includeSpaces) const
{
    std::stringstream ss;
    for (int i = 63; i >= 0; i--)
    {
        ss << ((board_ >> i) & 1);

        // Insert spaces every 8 bits for readability
        if (includeSpaces && (i % 8 == 0))
        {
            ss << ' ';
        }
    }

    return ss.str();
}

void Bitboard::setBit(int n)
{
    raiseExceptionIfBitIsOutOfRange(n);

    // Shift constants::ONE by n positions to the left and do a bitwise OR with board_
    board_ |= (constants::ONE << n);
}

void Bitboard::clearBit(int n)
{
    raiseExceptionIfBitIsOutOfRange(n);

    // Shift constants::ONE by n positions to the left, invert it, and do a bitwise AND with board_ 
    board_ &= ~(constants::ONE << n);
}

int Bitboard::getBit(int n) const
{
    raiseExceptionIfBitIsOutOfRange(n);

    // Move the bit of interest to the least significant bit and compare it to 1
    return ( (board_ >> n) & constants::ONE );
}

void Bitboard::raiseExceptionIfBitIsOutOfRange(int n) const
{
    if ( !((n >= 0) && (n < Square::NUMBER_OF_SQUARES)) )
    {
        throw std::out_of_range("Bitboard can only manipulate bits in the inclusive range [0, 63]. Received: " + std::to_string(n));
    }

}

void Bitboard::reset()
{
    setBoard(constants::EMPTY_BOARD);
}

int Bitboard::numberOfSetBits() const
{
    int count = 0;

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
    int currentPosition = 0;
    while (indexOfLSB < 0)
    {
        // Isolate the very first bit
        int valueOfLSB = (copyOfBoard & constants::ONE);

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
    int currentPosition = 63;
    u64 copyOfBoard = board_;
    while (indexOfMSB < 0)
    {
        // Isolate the very last bit
        u64 intersectionOfTheLastBit = (copyOfBoard & constants::MOST_SIGNIFICANT_BIT_SET);

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

Bitboard Bitboard::getNeighbor(Direction direction) const
{
    return (direction > 0) ? (toU64() << direction) : (toU64() >> std::abs(direction));
}

bool Bitboard::anyBitsSet() const
{
    return (numberOfSetBits() > 0);
}

bool Bitboard::noBitsSet() const
{
    return (numberOfSetBits() == 0);
}