#include "bitboard.h"

Bitboard::Bitboard(u64 boardState)
{
    this->setBoard(boardState);
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

int Bitboard::getBit(int n)
{
    // Move the bit of interest to the least significant bit and compare it to 1
    return ( (board_ >> n) & bitboard::ONE );
}