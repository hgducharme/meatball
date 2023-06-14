#include "attacktables.h"

namespace attack_tables
{

Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
Bitboard knight[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];

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
        Bitboard legalWhitePawnMoves;
        Bitboard legalBlackPawnMoves;

        // From the side to move reference frame: a pawn will never be on rank 1,
        // and if a pawn is on the last rank that means it's a promotion
        if (Chessboard::squareToRank(square) == RANK_1 || Chessboard::squareToRank(square) == RANK_8)
        {
            attack_tables::pawn[Color::WHITE][square] = Bitboard();
            attack_tables::pawn[Color::BLACK][square] = Bitboard();
        }

        // Determine valid move directions based on file
        if (Chessboard::squareToFile(square) == FILE_A)
        {
            legalWhitePawnMoves = squareBitboard.getNeighbor(NORTH) | squareBitboard.getNeighbor(NORTH_EAST);
            legalBlackPawnMoves = squareBitboard.getNeighbor(SOUTH) | squareBitboard.getNeighbor(SOUTH_EAST);
        }
        else if (Chessboard::squareToFile(square) == FILE_H)
        {
            legalWhitePawnMoves = squareBitboard.getNeighbor(NORTH) | squareBitboard.getNeighbor(NORTH_WEST);
            legalBlackPawnMoves = squareBitboard.getNeighbor(SOUTH) | squareBitboard.getNeighbor(SOUTH_WEST);
        }
        else
        {
            legalWhitePawnMoves = squareBitboard.getNeighbor(NORTH) |
                                  squareBitboard.getNeighbor(NORTH_WEST) |
                                  squareBitboard.getNeighbor(NORTH_EAST);

            legalBlackPawnMoves = squareBitboard.getNeighbor(SOUTH) |
                                  squareBitboard.getNeighbor(SOUTH_WEST) |
                                  squareBitboard.getNeighbor(SOUTH_EAST);
        }

        // Store the moves in the pawn table
        attack_tables::pawn[Color::WHITE][square] = legalWhitePawnMoves;
        attack_tables::pawn[Color::BLACK][square] = legalBlackPawnMoves;
    }
}

void initializeKnightAttackTable()
{
    for (unsigned int s = 0; s < Square::NUMBER_OF_SQUARES; s++)
    {
        Square square = static_cast<Square>(s);
        Bitboard squareBitboard(square);
        Bitboard legalWhiteKnightMoves;
        Bitboard legalBlackKnightMoves;

        // A knight can move:
        // north 2 east 1 -- this corresponds to 17 bits ahead of current square
        // north 2 west 1 -- this corresponds to 15 bits ahead of current square
        // north 1 east 2 -- this corresponds to 10 bits ahead of current square
        // north 1 west 2 -- this corresponds to 6 bits ahead of current square
        // south 2 east 1 -- this corresponds to 15 bits behind current square
        // south 2 west 1 -- this corresponds to 17 bits behind current square
        // south 1 east 2 -- this corresponds to 6 bits behind current square
        // south 1 west 2 -- this corresponds to 10 bits behind current square
        // If we calculate the north moves we could just mirror the board vertically across the current square's rank
        // to get the squares for the moves to the south

        // What is an efficient way to trim off-board moves?

        /*
        legalWhiteKnightMoves = 
        */        

        attack_tables::knight[Color::WHITE][square] = legalWhiteKnightMoves;
    }
}

} // namespace attack_tables