#include "attacktables.h"

namespace attack_tables
{

Bitboard pawn[Square::NUMBER_OF_SQUARES];

void init()
{
    initializePawnAttackTable();
    initializeKnightAttackTable();
}

void initializePawnAttackTable()
{
    for (unsigned int s = 0; s < Square::NUMBER_OF_SQUARES; s++)
    {
        Square square = static_cast<Square>(s);
        Bitboard squareBitboard(square);
        Bitboard legalMovesFromThisSquare;

        // From the side to move reference frame: a pawn will never be on rank 1,
        // and if a pawn is on the last rank that means it's a promotion
        if (Chessboard::squareToRank(square) == RANK_1 || Chessboard::squareToRank(square) == RANK_8)
        {
            attack_tables::pawn[square] = Bitboard();
        }

        // Determine valid move directions based on file
        if (Chessboard::squareToFile(square) == FILE_A)
        {
            legalMovesFromThisSquare = squareBitboard.getNeighbor(NORTH) | squareBitboard.getNeighbor(NORTH_EAST);
        }
        else if (Chessboard::squareToFile(square) == FILE_H)
        {
            legalMovesFromThisSquare = squareBitboard.getNeighbor(NORTH) | squareBitboard.getNeighbor(NORTH_WEST);
        }
        else
        {
            legalMovesFromThisSquare = squareBitboard.getNeighbor(NORTH_EAST) |
                                       squareBitboard.getNeighbor(NORTH)      |
                                       squareBitboard.getNeighbor(NORTH_WEST);
        }

        // Store the moves in the pawn table
        attack_tables::pawn[square] = legalMovesFromThisSquare;
    }
}

void initializeKnightAttackTable()
{
    for (unsigned int s = 0; s < Square::NUMBER_OF_SQUARES; s++)
    {
        Square square = static_cast<Square>(s);
        Bitboard squareBitboard(square);
        Bitboard legalMovesFromThisSquare;

        // From the perspective of whos side it is to move:
        

        attack_tables::knight[square] = legalMovesFromThisSquare;
    }
}

} // namespace attack_tables