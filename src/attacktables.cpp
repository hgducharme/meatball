#include "attacktables.h"

namespace attack_tables
{

Bitboard pawn[Square::NUMBER_OF_SQUARES];

void init()
{
    initializePawnAttackTable();
}

void initializePawnAttackTable()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        // From the side to move reference frame:
        // No pawns will ever be on the first or last rank
        // Pawns get initialized on the second rank
        // and if a pawn is on the last rank that means it's a promotion
        if (square < Square::a2 || square > Square::h7)
        {
            /*
            From the perspective of the side who is moving, no pawn will ever be on the first rank
            NOTE: I need to be careful with this implementation. Right now I'm using absolute positions
            (square a1, a2, ..., etc.), but am messing with reference frames.
            For example, I am setting all squares A1 to H1 as having no valid moves for a pawn
            (from the perspective of whoever's side it is to move). However, when flipping reference frames,
            black pawns don't change their absolute position in the intertial reference frame (squares a1, a2, etc.).
            But this following implementation is saying the black pieces are moving their position in the interial frame
            to white's squares.
            */
            attack_tables::pawn[square] = bitboard::EMPTY_BOARD;
        }

        // Create a bitboard representing the position of the current square
        Bitboard b;
        b.setBit(square);

        // The valid positions from the current square is one move to either the north west, north, or north east
        // This corresponds to 7, 8, or 9 bits closer to the 64th (last) bit, respectively.
        // AKA:
        // one move to the north west corresponds to the bit 7 positions larger than the current bit
        // one move to the north      corresponds to the bit 8 positions larger than the current bit
        // one move to the north east corresponds to the bit 9 positions larger than the current bit
        // So shift the attack mask such that the LSB in the mask is 7 positions ahead of the current square
        // That will set the 7th, 8th, and 9th bit in "front" of the current square to 1
        attack_tables::pawn[square] = (constants::attack_masks::pawn_single_push << (square + 7));
    }
}

}