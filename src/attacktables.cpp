#include "attacktables.h"

#include <iostream>
#include <iomanip>

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

        // TODO: This is redundant. Both white and black knights have the exact same possible moves from each square.
        knight[square] = calculateKnightAttacksFromSquare(Color::WHITE, squareBitboard);
        knight[square] = calculateKnightAttacksFromSquare(Color::BLACK, squareBitboard);

        king[square] = calculateKingAttacksFromSquare(squareBitboard);
    }
}

Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard)
{
    Square currentSquare = static_cast<Square>(bitboard.findIndexLSB());
    Rank rank = Chessboard::squareToRank(currentSquare);

    // A pawn only has valid moves between ranks 2 and 7
    if (rank == RANK_1 || rank == RANK_8)
    {
        return constants::EMPTY_BOARD;
    }

    // white directions in white reference frame
    int forward = 1;
    int east = 1;
    int west = -1;

    // black directions in white reference frame to d
    if (color == Color::BLACK)
    {
        forward = -1;
    }

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    Bitboard captureEast = utils::shiftToNewPosition(bitboard, forward, east) & constants::bit_masks::EXCLUDE_FILE_A;
    Bitboard captureWest = utils::shiftToNewPosition(bitboard, forward, west) & constants::bit_masks::EXCLUDE_FILE_H;

    Bitboard pawnAttacks_whiteRefFrame = captureEast | captureWest;
    return pawnAttacks_whiteRefFrame;
}

Bitboard calculateKnightAttacksFromSquare(const Color color, const Bitboard & bitboard)
{
    // white directions in white reference frame
    int north = 1;
    int east = 1;
    int south = -1;
    int west = -1;

    // black directions in white reference frame to d
    if (color == Color::BLACK)
    {
        north = -1;
        east = 1;
        south = 1;
        west = -1;
    }

    Bitboard north2East1_whiteRefFrame = utils::shiftToNewPosition(bitboard, 2 * north, 1 * east) & constants::bit_masks::EXCLUDE_FILE_A;
    Bitboard south2East1_whiteRefFrame = utils::shiftToNewPosition(bitboard, 2 * south, 1 * east) & constants::bit_masks::EXCLUDE_FILE_A;
    Bitboard north2West1_whiteRefFrame = utils::shiftToNewPosition(bitboard, 2 * north, 1 * west) & constants::bit_masks::EXCLUDE_FILE_H;
    Bitboard south2West1_whiteRefFrame = utils::shiftToNewPosition(bitboard, 2 * south, 1 * west) & constants::bit_masks::EXCLUDE_FILE_H;
    Bitboard north1East2_whiteRefFrame = utils::shiftToNewPosition(bitboard, 1 * north, 2 * east) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    Bitboard south1East2_whiteRefFrame = utils::shiftToNewPosition(bitboard, 1 * south, 2 * east) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    Bitboard north1West2_whiteRefFrame = utils::shiftToNewPosition(bitboard, 1 * north, 2 * west) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;
    Bitboard south1West2_whiteRefFrame = utils::shiftToNewPosition(bitboard, 1 * south, 2 * west) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;

    Bitboard knightAttacks_whiteRefFrame = north2East1_whiteRefFrame | north2West1_whiteRefFrame | north1East2_whiteRefFrame | north1West2_whiteRefFrame |
                                           south2East1_whiteRefFrame | south2West1_whiteRefFrame | south1East2_whiteRefFrame | south1West2_whiteRefFrame;

    return knightAttacks_whiteRefFrame;
}

Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard)
{
    int north = 1;
    int south = -1;
    int east = 1;
    int west = -1;

    // utils::shiftPieceOnBitboardByDirection(bitboard, NORTH)
    Bitboard captureNorth = utils::shiftToNewPosition(bitboard, north, 0);
    Bitboard captureSouth = utils::shiftToNewPosition(bitboard, south, 0);
    Bitboard captureEast = utils::shiftToNewPosition(bitboard, 0, east) & constants::bit_masks::EXCLUDE_FILE_A;
    Bitboard captureWest = utils::shiftToNewPosition(bitboard, 0, west) & constants::bit_masks::EXCLUDE_FILE_H;
    Bitboard captureNorthWest = utils::shiftToNewPosition(bitboard, north, west) & constants::bit_masks::EXCLUDE_FILE_H;
    Bitboard captureNorthEast = utils::shiftToNewPosition(bitboard, north, east) & constants::bit_masks::EXCLUDE_FILE_A;
    Bitboard captureSouthWest = utils::shiftToNewPosition(bitboard, south, west) & constants::bit_masks::EXCLUDE_FILE_H;
    Bitboard captureSouthEast = utils::shiftToNewPosition(bitboard, south, east) & constants::bit_masks::EXCLUDE_FILE_A;

    Bitboard legalKingMoves = captureNorth     | captureSouth     | captureEast      | captureWest |
                              captureNorthWest | captureNorthEast | captureSouthWest | captureSouthEast;

    return legalKingMoves;
}

} // namespace attack_tables