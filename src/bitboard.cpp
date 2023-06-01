#include "bitboard.h"

Bitboard::Bitboard(u64 boardState)
{
    this->setBoard(boardState);
}

void Bitboard::setBit(int n)
{
    // Shift constants::ONE by n positions to the left and do a bitwise OR with board_
    board_ |= (constants::ONE << n);
}