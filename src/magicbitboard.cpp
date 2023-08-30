#include "magicbitboard.h"

#include <iostream>

namespace magic_bitboards
{

MagicBitboardEntry BISHOP_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
MagicBitboardEntry ROOK_MAGIC_LOOKUP[Square::NUMBER_OF_SQUARES];
Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS];
Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];

void init()
{
    initializeAttackDatabases();
    initializeMagicBitboardEntries();
    generateBlockerMasks();
    generateBishopMagics();
    // generateRookMagics();
    // generateAttackBoard(PieceType::BISHOP);
    // generateAttackBoard(PieceType::ROOK);
}

namespace
{

u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

void initializeAttackDatabases()
{
    // Initialize every elementof BISHOP_ATTACKS and ROOK_ATTACKS to the universe bitboard
    std::fill(&BISHOP_ATTACKS[0][0],
              &BISHOP_ATTACKS[0][0] + sizeof(BISHOP_ATTACKS) / sizeof(BISHOP_ATTACKS[0][0]),
              Bitboard(constants::UNIVERSE));
    std::fill(&ROOK_ATTACKS[0][0],
              &ROOK_ATTACKS[0][0] + sizeof(ROOK_ATTACKS) / sizeof(ROOK_ATTACKS[0][0]),
              Bitboard(constants::UNIVERSE));
}

void initializeMagicBitboardEntries()
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

/*
 * This is commented out because instead of doing an inital magic number generation loop at the beginning,
 * i'm going to just fold this into the whole process of finding magic numbers for each piece.
*/
// void generateInitialMagicNumbers()
// {
//     for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
//     {
//         BISHOP_MAGIC_LOOKUP[square].magicNumber = utils::getRandom64BitInteger();
//         ROOK_MAGIC_LOOKUP[square].magicNumber = utils::getRandom64BitInteger();
//     }
// }

void generateBishopMagics()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        // Index the magic lookup table to get the magic entry for this square
        MagicBitboardEntry entry = BISHOP_MAGIC_LOOKUP[square];

        // Calculate the blocker variations for this blocker mask
        std::vector<Bitboard> allBlockerVariations = calculateAllBlockerVariations(entry.blockerMask);
        int numberOfBlockerVariations = allBlockerVariations.size();

        // Calculate the attack board for each blocker variation
        std::vector<Bitboard> attackBoards(numberOfBlockerVariations);
        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            attackBoards[i] = calculateBishopAttackBoard((Square)square, allBlockerVariations[i]);
        }

        std::cout << "(" << square << ") SEARCHING for magic number..." << std::endl;

        entry.magicNumber = searchForBishopMagicNumbers(square, allBlockerVariations, attackBoards);

        /*
         * CHESS PROGRAMMING WIKI STRUCTURE
        */

        // int hasFailed, nthVariation;
        // int numberOfRetries = 1000000;
        // // Attempt to search for a magic number
        // for (int retry = 0; retry < numberOfRetries; retry++)
        // {
        //     // Calculate a magic number for this square
        //     u64 magicNumber = utils::getSparselyPopulatedRandom64BitInteger();

        //     // Make sure the magic number efficiently maps bits from the blocker mask to the most significant bit positons
        //     // This aids in minimizing the size of the hashed index
        //     if (Bitboard( (entry.blockerMask * magicNumber) & 0xFF00000000000000ULL ).numberOfSetBits() < 6) continue;

        //     // Make sure the magic number works for all blocker variations, if not, restart with a new magic number
        //     for (nthVariation, hasFailed = 0; !hasFailed && nthVariation < numberOfBlockerVariations; nthVariation++)
        //     {
        //         // Hash the index and check if this causes a collission
        //         u64 hashedIndex = (allBlockerVariations[nthVariation] * magicNumber) >> (64 - entry.blockerMask.numberOfSetBits());
        //         if (BISHOP_ATTACKS[square][hashedIndex].getBoard() == constants::UNIVERSE)
        //         {
        //             BISHOP_ATTACKS[square][hashedIndex] = attackBoards[nthVariation];
        //         }

        //         // If we get a collision, then initiate the fail condition and start over with a new magic number
        //         else if (BISHOP_ATTACKS[square][hashedIndex].getBoard() != attackBoards[nthVariation].getBoard())
        //         {
        //             hasFailed = 1;
        //             if (retry == (numberOfRetries - 1))
        //             {
        //                 std::cout << "(" << square << ", " << nthVariation << ") ERROR: no magic number found" << std::endl;
        //             }
        //         }
        //     }
            
        //     // If we stored all the attack boards and a fail condition was never met, then we successfully found a magic number
        //     if (!hasFailed)
        //     {
        //         entry.magicNumber = magicNumber;
        //         break;
        //     }
        // }

        // if (!hasFailed)
        // {
        //     std::cout << "(" << square << ", " << nthVariation << ") FOUND magic number: " << entry.magicNumber << std::endl;
        // }
        // else 
        // {
        //     std::cout << "(" << square << ", " << nthVariation << ") ERROR: no magic number found" << std::endl;
        // }
    }

}

u64 searchForBishopMagicNumbers(const int square, const std::vector<Bitboard> & allBlockerVariations, const std::vector<Bitboard> & attackBoards)
{
    MagicBitboardEntry entry = BISHOP_MAGIC_LOOKUP[square];

    // TODO: Putting this into the parent function for some reason doesn't store the calculation in entry.shiftAmount
    entry.shiftAmount = entry.blockerMask.numberOfSetBits();
    
    const int numberOfBlockerVariations = allBlockerVariations.size();

    // TODO: This is stuck in an infinite loop
    // u64 magicNumberCandidate;
    bool foundMagicNumber = false;
    while (foundMagicNumber == false)
    {
        bool currentMagicNumberIsValid = true;

        // Calculate a magic number candidate for this square
        u64 magicNumberCandidate = utils::getSparselyPopulatedRandom64BitInteger();
        // std::cout << "(" << square << ") TRYING magic number: " << magicNumberCandidate << std::endl;

        // Verify that it effeciently maps bits from the blocker mask to the most significant bit positions of the productr
        if (Bitboard( (entry.blockerMask * magicNumberCandidate) & 0xFF00000000000000ULL ).numberOfSetBits() < 6) continue;

        // Hash each blocker variation and attempt to store the attack boards
        for (int i = 0; (i < numberOfBlockerVariations) && currentMagicNumberIsValid; i++)
        {
            u64 hashedIndex = hashBlockerVariation(allBlockerVariations[i], magicNumberCandidate, entry.shiftAmount);
  
            // When allocating space for the database, we made every bitboard entry equal to the universe set
            // If we find an entry that is equal to the universe set, then it hasn't been modified because
            // the universe set is not a legal attack set for any chess piece. This is how we can
            // find if the current entry is an already computed attack set or if its an entry that can be replaced.
            // Check if this hashed index already has an entry in the database
            // If it doesn't, then store the attack board for this hashed index
            // otherwise, regenerate the magic number for this square and recompute a hashed index
            if (BISHOP_ATTACKS[square][hashedIndex].getBoard() == constants::UNIVERSE)
            {
                BISHOP_ATTACKS[square][hashedIndex] = attackBoards[i];
            }

            // If the collision gives us the same attack board, then we're fine
            // If the collision gives us a different attack board, start over with a new magic number
            else if (BISHOP_ATTACKS[square][hashedIndex].getBoard() != attackBoards[i].getBoard())
            {
                currentMagicNumberIsValid = false;
            }
        }

        if (currentMagicNumberIsValid)
        {
            std::cout << "(" << square << ") FOUND magic number: " << magicNumberCandidate << std::endl;
            foundMagicNumber = true;
            return magicNumberCandidate;
        }
    }
    // return magicNumberCandidate;
}

u64 hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount)
{
    return (blockerVariation * magicNumber) >> (Square::NUMBER_OF_SQUARES - shiftAmount);
}

/*
 * This is commented out so that I can focus on improving the magic number generation functions.
 * This function has also gotten needlessly complex by trying to make it usable for both rooks and bishops
 * My adherence to the liskov substitution principle here I think is getting messy, and there is 
 * most likely a more efficient way to perform this algorithm on difference piece types.
 * The use of a switch statement to look up data depending on the piece type feels like
 * a bit of a code smell. This was an attempt to fold 
 * generateBishopAttackBoard() and generateRookAttackBoard() into one function so as not to duplicate
 * code.
*/
// void generateAttackBoard(PieceType pieceType)
// {
//     // A pointer to either BISHOP_MAGIC_LOOKUP or ROOK_MAGIC_LOOKUP
//     MagicBitboardEntry * MAGIC_LOOKUP_TABLE;

//     // A pointer to either BISHOP_ATTACKS or ROOK_ATTACKS
//     Bitboard * ATTACK_TABLE;
//     // const int (&selectedArray)[BISHOP_SIZE][BISHOP_SIZE] = (piece == "bishop") ? bishopArray : rookArray;

//     // A pointer to a function that either calculates rook attacks or bishop attacks
//     Bitboard (*calculateSliderPieceAttackBoard)(const Square &, const Bitboard &);

//     // Depending on the piece type, determine which lookup table and which function to use
//     switch (pieceType)
//     {
//         case BISHOP:
//             MAGIC_LOOKUP_TABLE = BISHOP_MAGIC_LOOKUP;
//             calculateSliderPieceAttackBoard = calculateBishopAttackBoard;
//             break;
//         case ROOK:
//             MAGIC_LOOKUP_TABLE = ROOK_MAGIC_LOOKUP;
//             calculateSliderPieceAttackBoard = calculateRookAttackBoard;
//             break;
//         default:
//             throw std::invalid_argument("generateAttackBoard() is only defined for the arguments: 'BISHOP' and 'ROOK'.");
//     }

//     for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
//     {
//         // Index the magic lookup table to get the magic entry for this square
//         MagicBitboardEntry entry = *(MAGIC_LOOKUP_TABLE + square);

//         // Calculate the blocker variations for this blocker mask
//         std::vector<Bitboard> allBlockerVariations = calculateAllBlockerVariations(entry.blockerMask);
//         int numberOfBlockerVariations = allBlockerVariations.size();

//         // Calculate the attack board for each blocker variation
//         std::vector<Bitboard> attackBoards(numberOfBlockerVariations);
//         for (int i = 0; i < numberOfBlockerVariations; i++)
//         {
//             // TODO: Maybe we don't need to make this a pointer and we can generalize this function?
//             // calculateSliderPieceAttackBoard<ROOK>(square, blockerVariation)
//             // calculateSliderPieceAttackBoard<BISHOP>(square, blockerVariation)
//             attackBoards[i] = calculateSliderPieceAttackBoard((Square)square, allBlockerVariations[i]);
//         }

//         // Calculate the blocker variation and magic number products and right shift by number of set bits in product
//         for (int i = 0; i < numberOfBlockerVariations; i++)
//         {
//             entry.blockerVariationAndMagicProduct = allBlockerVariations[i] * entry.magicNumber;
//             entry.shiftAmount = entry.blockerVariationAndMagicProduct.numberOfSetBits();
//             u64 hashedIndex = entry.blockerVariationAndMagicProduct.getBoard() >> entry.shiftAmount;

//             // attempt to store the attack board using the index just computed
//             // if the index already has an entry we need to create a new magic number
//         }
//     }
// }

std::vector<Bitboard> calculateAllBlockerVariations(Bitboard blockerMask)
{
    /*
     * This solved problem is also known as: enumerate all submasks of a bitmask.
     * Here is a link with some explanation: https://www.geeksforgeeks.org/print-all-submasks-of-a-given-mask/
     * One with better explanation: https://cp-algorithms.com/algebra/all-submasks.html
     */
    std::uint16_t numberOfBlockerVariations = pow(2, blockerMask.numberOfSetBits());
    std::vector<Bitboard> allBlockerVariations(numberOfBlockerVariations);

    std::uint16_t i = 0;
    for (u64 blockerVariation = blockerMask.getBoard(); blockerVariation; blockerVariation = (blockerVariation - 1) & blockerMask.getBoard())
    {
        allBlockerVariations[i] = blockerVariation;
        i++;
    }

    return allBlockerVariations;
}

Bitboard calculateBishopAttackBoard(const Square & square, const Bitboard & blockerVariation)
{
    Bitboard attackBoard;
    Bitboard squareBitboard(square);

    int numberOfMovesNorthEast = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_EAST);
    int numberOfMovesNorthWest = utils::calculateDistanceFromEdgeOfBoard(square, NORTH_WEST);
    int numberOfMovesSouthEast = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_EAST);
    int numberOfMovesSouthWest = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH_WEST);

    // TODO: maybe we can implement a function like the following?
    // attackBoard |= calculateAttacksInDirection(NORTH_EAST, numberOfMovesNorthEast, squareBitboard, blockerVariation);

    // Attacks to the north east
    for (int i = 1; i < numberOfMovesNorthEast; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * NORTH_EAST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the north west
    for (int i = 1; i < numberOfMovesNorthWest; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * NORTH_WEST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the south east
    for (int i = 1; i < numberOfMovesSouthEast; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * SOUTH_EAST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the south west
    for (int i = 1; i < numberOfMovesSouthWest; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * SOUTH_WEST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    return attackBoard;
}

Bitboard calculateRookAttackBoard(const Square & square, const Bitboard & blockerVariation)
{
    Bitboard attackBoard;
    Bitboard squareBitboard(square);

    int numberOfMovesNorth = utils::calculateDistanceFromEdgeOfBoard(square, NORTH);
    int numberOfMovesSouth = utils::calculateDistanceFromEdgeOfBoard(square, SOUTH);
    int numberOfMovesEast = utils::calculateDistanceFromEdgeOfBoard(square, EAST);
    int numberOfMovesWest = utils::calculateDistanceFromEdgeOfBoard(square, WEST);

    // TODO: maybe we can implement a function like the following?
    // attackBoard |= calculateAttacksInDirection(NORTH_EAST, numberOfMovesNorthEast, squareBitboard, blockerVariation);

    // Attacks to the north
    for (int i = 1; i < numberOfMovesNorth; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * NORTH);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the south
    for (int i = 1; i < numberOfMovesSouth; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * SOUTH);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the east
    for (int i = 1; i < numberOfMovesEast; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * EAST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }

    // Attacks to the west
    for (int i = 1; i < numberOfMovesWest; i++)
    {
        Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * WEST);
        if (targetSquareIsBlocked(targetSquare, blockerVariation)) { break; }
        else { attackBoard |= targetSquare; }
    }
}

bool targetSquareIsBlocked(Bitboard targetSquare, Bitboard occupiedSquares)
{
    return ( (targetSquare & occupiedSquares).numberOfSetBits() == 1 );
}

Bitboard calculateBishopBlockerMask(const Bitboard & bitboard)
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
        potentialBlockersToTheBishop |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH_EAST);
    }
    for (int i = 1; i <= numberOfMovesNorthWest; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH_WEST);
    }
    for (int i = 1; i <= numberOfMovesSouthEast; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH_EAST);
    }
    for (int i = 1; i <= numberOfMovesSouthWest; i++)
    {
        potentialBlockersToTheBishop |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH_WEST);
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
        potentialBlockersToTheRook |= utils::shiftCurrentSquareByDirection(bitboard, i * NORTH);
    }
    for (int i = 1; i <= numberOfMovesSouth; i++)
    {
        potentialBlockersToTheRook |= utils::shiftCurrentSquareByDirection(bitboard, i * SOUTH);
    }
    for (int i = 1; i <= numberOfMovesEast; i++)
    {
        potentialBlockersToTheRook |= utils::shiftCurrentSquareByDirection(bitboard, i * EAST);
    }
    for (int i = 1; i <= numberOfMovesWest; i++)
    {
        potentialBlockersToTheRook |= utils::shiftCurrentSquareByDirection(bitboard, i * WEST);
    }

    return potentialBlockersToTheRook;
}

// This is an example of a function that would be used in movegen.cpp
// And how we would use the magic bitboards as an end user
Bitboard getPotentialBishopAttacks(const int square, const Bitboard &boardState)
{
    MagicBitboardEntry bishopEntry = BISHOP_MAGIC_LOOKUP[square];

    Bitboard blockersToBishop = boardState & bishopEntry.blockerMask;
    u64 hashedBlockerConfiguration = bishopEntry.blockerVariationAndMagicProduct.getBoard() >> (Square::NUMBER_OF_SQUARES - bishopEntry.shiftAmount);
    return BISHOP_ATTACKS[square][hashedBlockerConfiguration];
}

} // anonymous namespace

} // namespace magic_bitboards