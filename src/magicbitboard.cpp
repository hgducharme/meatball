#include "magicbitboard.h"

namespace magic_bitboards
{

MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][4096];
Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][4096];

void init()
{
    instantiateMagicBitboardEntries();
    generateBlockerMasks();
    generateMagicNumbers();
    generateAttackBoard(PieceType::BISHOP);
    generateAttackBoard(PieceType::ROOK);
}

namespace
{

u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

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
        BISHOP_MAGIC_LOOKUP[square].magicNumber = getRandom64BitInteger();
        ROOK_MAGIC_LOOKUP[square].magicNumber = getRandom64BitInteger();
    }
}

u64 getRandom64BitInteger()
{
    u64 bytes1And2, bytes3And4, bytes5And6, bytes7and8;

    // Generate random integers, cast them to a 64-bit integer, and only take the first 2 bytes (16 bits)
    bytes1And2 = (u64)(random()) & 0xFFFF;
    bytes3And4 = (u64)(random()) & 0xFFFF;
    bytes5And6 = (u64)(random()) & 0xFFFF;
    bytes7and8 = (u64)(random()) & 0xFFFF;

    // Create the random 64 bit integer by mix and matching the two-byte snippets or "words"
    return bytes1And2 | (bytes3And4 << constants::INDEX_OF_THIRD_BYTE) | (bytes5And6 << constants::INDEX_OF_FIFTH_BYTE) | (bytes7and8 << constants::INDEX_OF_SEVENTH_BYTE);
}

void generateAttackBoard(PieceType pieceType)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        MagicBitboardEntry entry;

        switch (pieceType)
        {
            case BISHOP:
                entry = BISHOP_MAGIC_LOOKUP[square];
            case ROOK:
                entry = ROOK_MAGIC_LOOKUP[square];
            default:
                throw std::invalid_argument("generateAttackBoard is only defined for BISHOP and ROOK.");
        }

        std::vector<Bitboard> allBlockerVariations = calculateAllBlockerVariations(entry.blockerMask);

        // for each blocker variation, generate the attack board
        // take the blocker variation and multiply it by the magic number and right shift by number of set bits in product
        // attempt to store the attack board using the index just computed
        // if the index already has an entry we need to create a new magic number

        // entry.blockerMaskAndMagicProduct = entry.blockerMask * entry.magicNumber;
        // entry.numberOfBitsInProduct = entry.blockerMaskAndMagicProduct.numberOfSetBits();
    }
}

std::vector<Bitboard> calculateAllBlockerVariations(Bitboard blockerMask)
{
    std::vector<Bitboard> blockerVariations;

    


    return blockerVariations;
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
    return BISHOP_ATTACKS[square][hashedBlockerConfiguration];
}

} // anonymous namespace

} // namespace magic_bitboards