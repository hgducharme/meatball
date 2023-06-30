#include "magicbitboard.h"

namespace magic_bitboards
{

MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];

void init()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        Bitboard squareBitboard(square);

        // Initialize the magic bitboard entries
        MagicBitboardEntry bishopEntry;
        MagicBitboardEntry rookEntry;

        // Calculate the occupancy masks
        bishopEntry.occupancyMask = calculateBishopOccupancyMask(squareBitboard);
        rookEntry.occupancyMask = calculateRookOccupancyMask(squareBitboard);

        // Attach the magic number to this magic bitboard entry
        bishopEntry.magicNumber = BISHOP_MAGIC_NUMBERS[square];
        rookEntry.magicNumber = ROOK_MAGIC_NUMBERS[square];

        // Store the product between the occupancy mask and the magic number
        // TODO: override * operator for bitboard and u64 object
        // bishopEntry.occupancyMaskAndMagicProduct = bishopEntry.occupancyMask * bishopEntry.magicNumber;
        // rookEntry.occupancyMaskAndMagicProduct = rookEntry.occupancyMask * rookEntry.magicNumber;

        // Store the number of bits in the product of the occupancy mask and the magic number
        bishopEntry.numberOfBitsInProduct = bishopEntry.occupancyMaskAndMagicProduct.numberOfSetBits();
        rookEntry.numberOfBitsInProduct = rookEntry.occupancyMaskAndMagicProduct.numberOfSetBits();
    }
}

Bitboard calculateBishopOccupancyMask(const Bitboard &bitboard)
{
    Bitboard potentialBlockersToTheBishop;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    // This is for magic bitboards, subtract 1 since the edge of the board isn't considered a blocking square
    int numberOfMovesNorthEast = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_EAST) - 1;
    int numberOfMovesNorthWest = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_WEST) - 1;
    int numberOfMovesSouthEast = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_EAST) - 1;
    int numberOfMovesSouthWest = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_WEST) - 1;

    for (int i = 1; i <= numberOfMovesNorthEast; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_EAST);
    }
    for (int i = 1; i <= numberOfMovesNorthWest; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * NORTH_WEST);
    }
    for (int i = 1; i <= numberOfMovesSouthEast; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_EAST);
    }
    for (int i = 1; i <= numberOfMovesSouthWest; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH_WEST);
    }

    return potentialBlockersToTheBishop;
}

Bitboard calculateRookOccupancyMask(const Bitboard &bitboard)
{
    Bitboard potentialBlockersToTheRook;
    Square square = static_cast<Square>(bitboard.findIndexLSB());

    // This is for magic bitboards, subtract 1 since the edge of the board isn't considered a blocking square
    int numberOfMovesNorth = utils::calculateDistanceFromEdgeOfBoard(square, NORTH) - 1;
    int numberOfMovesSouth = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH) - 1;
    int numberOfMovesEast = utils::calculateDistanceFromEdgeOfBoard(square, EAST) - 1;
    int numberOfMovesWest = utils::calculateDistanceFromEdgeOfBoard(square, WEST) - 1;

    for (int i = 1; i <= numberOfMovesNorth; i++)
    {
        potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * NORTH);
    }
    for (int i = 1; i <= numberOfMovesSouth; i++)
    {
        potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * SOUTH);
    }
    for (int i = 1; i <= numberOfMovesEast; i++)
    {
        potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * EAST);
    }
    for (int i = 1; i <= numberOfMovesWest; i++)
    {
        potentialBlockersToTheRook |= utils::shiftPieceOnBitboard(bitboard, i * WEST);
    }

    return potentialBlockersToTheRook;
}

Bitboard getPotentialBishopAttacks(const int square, const Bitboard &boardState)
{
    MagicBitboardEntry bishopEntry = BISHOP_MAGIC_LOOKUP[square];

    Bitboard blockersToBishop = boardState & bishopEntry.occupancyMask;
    // TODO: Allow for bitboard converstion to u64
    // u64 hashedBlockerConfiguration = bishopEntry.occupancyMaskAndMagicProduct >> (Square::NUMBER_OF_SQUARES - bishopEntry.numberOfBitsInProduct);
    // return bishopAttacks[square][hashedBlockerConfiguration];
}

} // namespace magic_bitboards