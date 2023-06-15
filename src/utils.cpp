#include "utils.h"

namespace utils
{

Bitboard getKnightAttacks(const Bitboard & bitboard)
{

    // TODO: exclusion of off-board moves needs to happen on a color basis
    // Right now this is all assuming the move is being done by white
    // If color == white, do everything below:
    // else, if color == black, reverse the directions of the bit shift

    // north 2 east 1 -- this corresponds to 17 bits ahead of current square
    // If we perform this move and we end up on the A file, we need to exclude this
    Bitboard north2East1 = (bitboard << 17) & constants::bit_masks::NOT_FILE_A;

    // north 2 west 1 -- this corresponds to 15 bits ahead of current square
    // If we perform this move and we end up on the H file, we need to exclude this
    Bitboard north2West1 = (bitboard << 15) & constants::bit_masks::NOT_FILE_H;

    // north 1 east 2 -- this corresponds to 10 bits ahead of current square
    // If we perform this move and end up on the A or B file, we need to exclude that move
    Bitboard north1East2 = (bitboard << 10) & constants::bit_masks::NEITHER_FILE_A_NOR_B;

    // north 1 west 2 -- this corresponds to 6 bits ahead of current square
    // If we perform this move and end up on the H or G file, we need to exclude that move
    Bitboard north1West2 = (bitboard << 6) & constants::bit_masks::NEITHER_FILE_H_NOR_G;

    // south 2 east 1 -- this corresponds to 15 bits behind current square
    // If we perform this move and end up on the A file, we need to exclude that move
    Bitboard south2East1 = (bitboard >> 15) & constants::bit_masks::NOT_FILE_A;
    
    // south 2 west 1 -- this corresponds to 17 bits behind current square
    // If we perform this move and end up on the H file, we need to exclude that move
    Bitboard south2West1 = (bitboard >> 17) & constants::bit_masks::NOT_FILE_H;

    // south 1 east 2 -- this corresponds to 6 bits behind current square
    // If we perform this move and end up on the A or B file, we need to exclude that move
    Bitboard south1East2 = (bitboard >> 6) & constants::bit_masks::NEITHER_FILE_A_NOR_B;

    // south 1 west 2 -- this corresponds to 10 bits behind current square
    // If we perform this move and end up on the H or G file, we need to exclude that move
    Bitboard south1West2 = (bitboard >> 8) & constants::bit_masks::NEITHER_FILE_H_NOR_G;

    Bitboard knightAttacks = north2East1 | north2West1 | north1East2 | north1West2 |
                             south2East1 | south2West1 | south1East2 | south1West2;

    return knightAttacks;
}

}