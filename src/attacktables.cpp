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
        bishop[square] = calculateBishopAttacksFromSquareClassical(squareBitboard);
        rook[square] = calculateRookAttacksFromSquareClassical(squareBitboard);
        queen[square] |= bishop[square] | rook[square];
        king[square] = calculateKingAttacksFromSquare(squareBitboard);
    }

    // Initialize attack tables for slider pieces
    magic_bitboards::init();
}

Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard)
{
    Bitboard potentialPawnAttacks;
    Rank rank = Chessboard::squareToRank(bitboard.findIndexLSB());

    // A pawn only has valid moves between ranks 2 and 7
    if (rank == RANK_1 || rank == RANK_8)
    {
        return potentialPawnAttacks;
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
    potentialPawnAttacks |= utils::shiftCurrentSquareByDirection(bitboard, eastDirection) & constants::bit_masks::EXCLUDE_FILE_A;
    potentialPawnAttacks |= utils::shiftCurrentSquareByDirection(bitboard, westDirection) & constants::bit_masks::EXCLUDE_FILE_H;

    return potentialPawnAttacks;
}

Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard potentialKnightAttacks;

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, 2 * NORTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;    
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, 2 * SOUTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, 2 * NORTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, 2 * SOUTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, NORTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, SOUTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, NORTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;
    potentialKnightAttacks |= utils::shiftCurrentSquareByDirection(bitboard, SOUTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;

    return potentialKnightAttacks;
}

Bitboard calculateBishopAttacksFromSquareClassical(const Bitboard & bitboard)
{
    Bitboard potentialBishopAttacks;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    int numberOfMovesNorthEast = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_EAST);
    int numberOfMovesNorthWest = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_WEST);
    int numberOfMovesSouthEast = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_EAST);
    int numberOfMovesSouthWest = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_WEST);

    for (int i = 1; i <= numberOfMovesNorthEast; i++) { potentialBishopAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH_EAST); }
    for (int i = 1; i <= numberOfMovesNorthWest; i++) { potentialBishopAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH_WEST); }
    for (int i = 1; i <= numberOfMovesSouthEast; i++) { potentialBishopAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH_EAST); }
    for (int i = 1; i <= numberOfMovesSouthWest; i++) { potentialBishopAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH_WEST); }

    return potentialBishopAttacks;
}

Bitboard calculateRookAttacksFromSquareClassical(const Bitboard & bitboard)
{
    Bitboard potentialRookAttacks;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    int numberOfMovesNorth = utils::calculateDistanceFromEdgeOfBoard(square, NORTH);
    int numberOfMovesSouth = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH);
    int numberOfMovesEast = utils::calculateDistanceFromEdgeOfBoard(square, EAST);
    int numberOfMovesWest = utils::calculateDistanceFromEdgeOfBoard(square, WEST);

    for (int i = 1; i <= numberOfMovesNorth; i++) { potentialRookAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH); }
    for (int i = 1; i <= numberOfMovesSouth; i++) { potentialRookAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH); }
    for (int i = 1; i <= numberOfMovesEast; i++)  { potentialRookAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * EAST); }
    for (int i = 1; i <= numberOfMovesWest; i++)  { potentialRookAttacks |= utils::shiftCurrentSquareByDirection(bitboard, i * WEST); }

    return potentialRookAttacks;
}

Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard legalKingAttacks;

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, NORTH);
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, SOUTH);
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, NORTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, SOUTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, NORTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    legalKingAttacks |= utils::shiftCurrentSquareByDirection(bitboard, SOUTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;

    return legalKingAttacks;
}

} // namespace attack_tables