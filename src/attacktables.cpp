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

        magic_bitboards::bishopOccupancies[square] = magic_bitboards::calculatePotentialBlockerSquaresForBishopMoves(squareBitboard);
        magic_bitboards::rookOccupancies[square] = magic_bitboards::calculatePotentialBlockerSquaresForRookMoves(squareBitboard);

        u64 bishopHashedIndex = magic_bitboards::bitboardToHashedIndex(static_cast<Square>(square), magic_bitboards::bishopOccupancies[square]);
        u64 rookHashedIndex = magic_bitboards::bitboardToHashedIndex(static_cast<Square>(square), magic_bitboards::rookOccupancies[square]);
    }
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
    potentialPawnAttacks |= utils::shiftPieceOnBitboard(bitboard, eastDirection) & constants::bit_masks::EXCLUDE_FILE_A;
    potentialPawnAttacks |= utils::shiftPieceOnBitboard(bitboard, westDirection) & constants::bit_masks::EXCLUDE_FILE_H;

    return potentialPawnAttacks;
}

Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard)
{
    Bitboard potentialKnightAttacks;

    // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * NORTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;    
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * SOUTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * NORTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, 2 * SOUTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, NORTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;
    potentialKnightAttacks |= utils::shiftPieceOnBitboard(bitboard, SOUTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;

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

    for (int i = 1; i <= numberOfMovesNorthEast; i++) { potentialBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST); }
    for (int i = 1; i <= numberOfMovesNorthWest; i++) { potentialBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_WEST); }
    for (int i = 1; i <= numberOfMovesSouthEast; i++) { potentialBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_EAST); }
    for (int i = 1; i <= numberOfMovesSouthWest; i++) { potentialBishopAttacks |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_WEST); }

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

    for (int i = 1; i <= numberOfMovesNorth; i++) { potentialRookAttacks |= utils::shiftPieceOnBitboard(bitboard, i * NORTH); }
    for (int i = 1; i <= numberOfMovesSouth; i++) { potentialRookAttacks |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH); }
    for (int i = 1; i <= numberOfMovesEast; i++)  { potentialRookAttacks |= utils::shiftPieceOnBitboard(bitboard, i * EAST); }
    for (int i = 1; i <= numberOfMovesWest; i++)  { potentialRookAttacks |= utils::shiftPieceOnBitboard(bitboard, i * WEST); }

    return potentialRookAttacks;
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

namespace magic_bitboards
{

Bitboard bishopOccupancies[Square::NUMBER_OF_SQUARES];
Bitboard rookOccupancies[Square::NUMBER_OF_SQUARES];

Bitboard calculatePotentialBlockerSquaresForBishopMoves(const Bitboard & bitboard)
{
    Bitboard potentialBlockersToTheBishop;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    // This is for magic bitboards, subtract 1 since the edge of the board isn't considered a blocking square
    int numberOfMovesNorthEast = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_EAST) - 1;
    int numberOfMovesNorthWest = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_WEST) - 1;
    int numberOfMovesSouthEast = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_EAST) - 1;
    int numberOfMovesSouthWest = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_WEST) - 1;

    for (int i = 1; i <= numberOfMovesNorthEast; i++) { potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST); }
    for (int i = 1; i <= numberOfMovesNorthWest; i++) { potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_WEST); }
    for (int i = 1; i <= numberOfMovesSouthEast; i++) { potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_EAST); }
    for (int i = 1; i <= numberOfMovesSouthWest; i++) { potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_WEST); }

    return potentialBlockersToTheBishop;
}

Bitboard calculatePotentialBlockerSquaresForRookMoves(const Bitboard & bitboard)
{
    Bitboard potentialBlockersToTheRook;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    // This is for magic bitboards, subtract 1 since the edge of the board isn't considered a blocking square
    int numberOfMovesNorth = utils::calculateDistanceFromEdgeOfBoard(square, NORTH) - 1;
    int numberOfMovesSouth = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH) - 1;
    int numberOfMovesEast = utils::calculateDistanceFromEdgeOfBoard(square, EAST) - 1;
    int numberOfMovesWest = utils::calculateDistanceFromEdgeOfBoard(square, WEST) - 1;

    for (int i = 1; i <= numberOfMovesNorth; i++) { potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * NORTH); }
    for (int i = 1; i <= numberOfMovesSouth; i++) { potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH); }
    for (int i = 1; i <= numberOfMovesEast; i++)  { potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * EAST); }
    for (int i = 1; i <= numberOfMovesWest; i++)  { potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * WEST); }

    return potentialBlockersToTheRook;
}

u64 bitboardToHashedIndex(const Square square, const Bitboard & blockers)
{
    // return (blockers * magicNumbers[square]) >> (Square::NUMBER_OF_SQUARES - numberOfBits);
}

Bitboard getPotentialBishopAttacks(const int square, const Bitboard & boardState)
{
    Bitboard blockersToBishop = boardState & bishopOccupancies[square];
    u64 hashedBlockerConfiguration = (boardState * bishopMagicNumbers[square]) >> (Square::NUMBER_OF_SQUARES - bishopNumberOfBits[square]);
    return bishopAttacks[square][hashedBlockerConfiguration];
}

} // namespace magic_bitboards