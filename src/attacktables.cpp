#include "attacktables.h"

namespace attack_tables
{

Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
Bitboard knight[Square::NUMBER_OF_SQUARES];
Bitboard bishop[Square::NUMBER_OF_SQUARES];
Bitboard rook[Square::NUMBER_OF_SQUARES];
Bitboard queen[Square::NUMBER_OF_SQUARES];
Bitboard king[Square::NUMBER_OF_SQUARES];

void init()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        Bitboard squareBitboard(square);

        pawn[Color::WHITE][square] = calculatePawnAttacksFromSquare(Color::WHITE, squareBitboard);
        pawn[Color::BLACK][square] = calculatePawnAttacksFromSquare(Color::BLACK, squareBitboard);
        knight[square] = calculateKnightAttacksFromSquare(squareBitboard);
        bishop[square] = calculateBishopAttacksFromSquare(squareBitboard);
        rook[square] = calculateRookAttacksFromSquare(squareBitboard);
        queen[square] |= bishop[square] | rook[square];
        king[square] = calculateKingAttacksFromSquare(squareBitboard);
    }
}

Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard)
{
    Bitboard legalPawnAttacks;
    Rank rank = Chessboard::squareToRank(bitboard.findIndexLSB());

    // A pawn only has valid moves between ranks 2 and 7
    if (rank == RANK_1 || rank == RANK_8)
    {
        return legalPawnAttacks;
    }

    // White pawns can only move north and black pawns can only move south
    Direction eastDirection = NORTH_EAST;
    Direction westDirection = NORTH_WEST;
    if (color == BLACK)
    {
        eastDirection = SOUTH_EAST;
        westDirection = SOUTH_WEST;
    }

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    legalPawnAttacks |= utils::shiftPieceOnBitboard(bitboard, eastDirection) & constants::bit_masks::EXCLUDE_FILE_A;
    legalPawnAttacks |= utils::shiftPieceOnBitboard(bitboard, westDirection) & constants::bit_masks::EXCLUDE_FILE_H;

    return legalPawnAttacks;
}

Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalKnightAttacks;

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * NORTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;    
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * SOUTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * NORTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * SOUTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;
    legalKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;

    return legalKnightAttacks;
}

Bitboard calculateBishopAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalBishopAttacks;

    Rank currentRank = Chessboard::squareToRank(bitboard.findIndexLSB());
    File currentFile = Chessboard::squareToFile(bitboard.findIndexLSB());

    // Magic bitboard process:
    // Bitboard maskedOccupancySquares = move_generation::magic_bitboard::calculateOccupancyMask();
    // Calculate magic numbers? move_generation::magic_bitboard::generateMagicNumbers();
    // Hash them? move_generation::magic_bitboard::hash(magicNumbers, maskedOccupancySquares);

    // find number of squares till edge of board north east
    // int numberOfSquaresTillNorthEastEdge = sqrt( (squares till east edge)**2 + (squares till the rank that the current ray intersects)**2 )
    // find number of squares till edge of board north west
    // find number of squares till edge of board south east
    // find number of squares till edge of board south west

    // for (int i = 0; i < squaresTillNorthEastEdgeOfBoard - 1; i++)
    // {
    //     legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST);
    // }

        // for (int i = 0; i < squaresTillNorthWestEdgeOfBoard; i++)
    // {
    //     legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST);
    // }

    /*
        THIS IS THE MOST UPDATED CODE & MOST LIKELY TO WORK
    // This function calculates the ray distance of a bishop to the edge of the board in a given direction,
    // and will return the number of squares the bishop can move to reach the end of the board
    // DOES NOT ACCOUNT FOR OCCUPIED SQUARES
    // For magic bitboards we subtract 1 because we don't want to actually reach the edge of the boards
    // int numberOfMovesNorthEast = calculateBishopDistanceFromEdgeOfBoard(NORTHEAST) - 1;
    // int numberOfMovesNorthWest = calculateBishopDistanceFromEdgeOfBoard(NORTHEAST) - 1;
    // int numberOfMovesSouthEast = calculateBishopDistanceFromEdgeOfBoard(NORTHEAST) - 1;
    // int numberOfMovesSouthWest = calculateBishopDistanceFromEdgeOfBoard(NORTHEAST) - 1;
    // for (int i = 1; i <= numberOfMovesNorthEast; i++) { legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST); }
    // for (int i = 1; i <= numberOfMovesNorthWest; i++) { legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_WEST); }
    // for (int i = 1; i <= numberOfMovesSouthEast; i++) { legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_EAST); }
    // for (int i = 1; i <= numberOfMovesSouthWest; i++) { legalBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_WEST); }
    */

    return legalBishopAttacks;
}

Bitboard calculateRookAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalRookAttacks;

    Rank currentRank = Chessboard::squareToRank(bitboard.findIndexLSB());
    File currentFile = Chessboard::squareToFile(bitboard.findIndexLSB());

    int distanceFrom8thRank = NUMBER_OF_RANKS - currentRank;
    int distanceFromFileH = NUMBER_OF_FILES - currentFile;

    return legalRookAttacks;
}

Bitboard calculateQueenAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalQueenAttacks;

    return legalQueenAttacks;
}

Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalKingAttacks;

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH);
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH);
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    legalKingAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;

    return legalKingAttacks;
}

} // namespace attack_tables