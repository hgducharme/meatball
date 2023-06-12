#include "attacktables.h"

namespace attack_tables
{

Bitboard pawn[Square::NUMBER_OF_SQUARES];

constexpr void init()
{
    initializePawnAttackTable();
}

constexpr void initializePawnAttackTable()
{
    for (unsigned int s = 0; s < Square::NUMBER_OF_SQUARES; s++)
    {
        Square square = static_cast<Square>(s);

        // From the side to move reference frame: a pawn will never be on rank 1,
        // and if a pawn is on the last rank that means it's a promotion
        if (Chessboard::squareToRank(square) == RANK_1 || Chessboard::squareToRank(square) == RANK_8)
        {
            attack_tables::pawn[square] = 0;
        }

        // one move to the north west corresponds to the bit 7 positions larger than the current bit
        // one move to the north      corresponds to the bit 8 positions larger than the current bit
        // one move to the north east corresponds to the bit 9 positions larger than the current bit
        u64 legalMovesFromThisSquare = 0;
        if (Chessboard::squareToFile(square) == FILE_A)
        {
            u64 disabledNorthWestMoves = constants::attack_masks::pawn_single_push & 0x3;
            legalMovesFromThisSquare = disabledNorthWestMoves << (square + 8);
            // Possible ways to improve this:
            // legalMovesFromThisSquare = square.moveNorth(1)    | square.moveNorthEast(1);
            // legalMovesFromThisSquare = square.move(North, 1)  | square.move(NorthEast, 1);
            // legalMovesFromThisSquare = moveNorth(1, square)   | moveNorthEast(1, square);
            // legalMovesFromThisSquare = getBitboardForMoveNorth(1, currentSquare)
        }
        else if (Chessboard::squareToFile(square) == FILE_H)
        {
            u64 disabledNorthEastMoves = constants::attack_masks::pawn_single_push & 0x6;
            legalMovesFromThisSquare = disabledNorthEastMoves << (square + 6);
        }
        else
        {
            legalMovesFromThisSquare = constants::attack_masks::pawn_single_push << (square + 7);
        }

        attack_tables::pawn[square] = legalMovesFromThisSquare;
    }
}

}