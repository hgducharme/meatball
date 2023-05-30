#include "bitboard.h"

#include <iostream>

Bitboard::Bitboard(u64 boardState)
{
    this->setBoard(boardState);
}

void Bitboard::setBit(Square s)
{
    board_ |= (1ULL << s);
}