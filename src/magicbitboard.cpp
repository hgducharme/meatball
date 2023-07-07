#include "magicbitboard.h"

namespace magic_bitboards
{

MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
Bitboard bishopAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square
Bitboard rookAttacks[Square::NUMBER_OF_SQUARES][4096]; // TOOD: 4096 is just a place holder for the number of potential blocker configurations for each square

void init()
{
    instantiateMagicBitboardEntries();
    generateBlockerMasks();
    generateMagicNumbers();
    computeBlockerMaskAndMagicNumberProducts();
}

namespace
{

void instantiateMagicBitboardEntries()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        MagicBitboardEntry bishopEntry;
        MagicBitboardEntry rookEntry;

        BISHOP_MAGIC_LOOKUP[square] = bishopEntry;
        ROOK_MAGIC_LOOKUP[square] = rookEntry;
    }
}

void generateBlockerMasks()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        Bitboard squareBitboard(square);

        BISHOP_MAGIC_LOOKUP[square].blockerMask = calculateBishopBlockerMask(squareBitboard);
        ROOK_MAGIC_LOOKUP[square].blockerMask = calculateRookBlockerMask(squareBitboard);
    }
}

void generateMagicNumbers()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        BISHOP_MAGIC_LOOKUP[square].magicNumber = calculateBishopMagicNumber(BISHOP_MAGIC_LOOKUP[square].blockerMask);
        ROOK_MAGIC_LOOKUP[square].magicNumber = calculateRookMagicNumber(ROOK_MAGIC_LOOKUP[square].blockerMask);
    }
}

u64 calculateBishopMagicNumber(const Bitboard & blockerMask)
{

}

u64 calculateRookMagicNumber(const Bitboard & blockerMask)
{

}

void computeBlockerMaskAndMagicNumberProducts()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        MagicBitboardEntry bishopEntry = BISHOP_MAGIC_LOOKUP[square];
        MagicBitboardEntry rookEntry = ROOK_MAGIC_LOOKUP[square];

        // Calculate and store the product between then blocker mask and the magic number
        bishopEntry.blockerMaskAndMagicProduct = bishopEntry.blockerMask * bishopEntry.magicNumber;
        rookEntry.blockerMaskAndMagicProduct = rookEntry.blockerMask * rookEntry.magicNumber;

        // Calculate and store how many bits are set in the product
        bishopEntry.numberOfBitsInProduct = bishopEntry.blockerMaskAndMagicProduct.numberOfSetBits();
        rookEntry.numberOfBitsInProduct = rookEntry.blockerMaskAndMagicProduct.numberOfSetBits();
    }
}

Bitboard calculateBishopBlockerMask(const Bitboard &bitboard)
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

Bitboard calculateRookBlockerMask(const Bitboard &bitboard)
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

    Bitboard blockersToBishop = boardState & bishopEntry.blockerMask;
    u64 hashedBlockerConfiguration = bishopEntry.blockerMaskAndMagicProduct.getBoard() >> (Square::NUMBER_OF_SQUARES - bishopEntry.numberOfBitsInProduct);
    return bishopAttacks[square][hashedBlockerConfiguration];
}

} // anonymous namespace

} // namespace magic_bitboards