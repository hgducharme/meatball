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
    initializeMagicBitboardEntries();
    generateBlockerMasks();

    // TODO: Go through each function and find out what the variables are that need to become function parameters.
    // Then work on making one function instead of having two that are doing the exact same thing

    // Bishop magic bitboard generation
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> bishopBlockerVariations = calculateBlockerVariations(BISHOP_MAGIC_LOOKUP);
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> bishopAttacks = calculateAttacks(calculateBishopAttackBoard, bishopBlockerVariations);
    std::cout << "Searching for bishop magics, this could take up to 30 seconds... " << std::endl;
    generateBishopMagicNumbers(bishopBlockerVariations, bishopAttacks);
    std::cout << "DONE." << std::endl;
    populateBishopAttackDatabase(bishopBlockerVariations, bishopAttacks);

    // Rook magic bitboard generation
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> rookBlockerVariations = calculateBlockerVariations(ROOK_MAGIC_LOOKUP);
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> rookAttacks = calculateAttacks(calculateRookAttackBoard, rookBlockerVariations);
    std::cout << "Searching for rook magic numbers, this could take up to 30 seconds... " << std::endl;
    generateRookMagicNumbers(rookBlockerVariations, rookAttacks);
    std::cout << "DONE." << std::endl;
    populateRookAttackDatabase(rookBlockerVariations, rookAttacks);
}

namespace
{

u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

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

        // Calculate the blocker mask for each piece on this square
        BISHOP_MAGIC_LOOKUP[square].blockerMask = calculateBishopBlockerMask(squareBitboard);
        ROOK_MAGIC_LOOKUP[square].blockerMask = calculateRookBlockerMask(squareBitboard);

        // Store the shift amount to be used in the hash function
        BISHOP_MAGIC_LOOKUP[square].shiftAmount = BISHOP_MAGIC_LOOKUP[square].blockerMask.numberOfSetBits();
        ROOK_MAGIC_LOOKUP[square].shiftAmount = ROOK_MAGIC_LOOKUP[square].blockerMask.numberOfSetBits();
    }
}

std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> calculateBlockerVariations(MagicBitboardEntry const * MAGIC_LOOKUP_TABLE)
{
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> blockerVariations;
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        blockerVariations[square] = enumerateSubmasks(MAGIC_LOOKUP_TABLE[square].blockerMask);
    }

    return blockerVariations;
}

std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> calculateAttacks(calculateAttackBoardFunction calculateAttackBoard, const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations)
{
    std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> attacks;

    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        int numberOfBlockerVariations = blockerVariations[square].size();
        std::vector<Bitboard> attackBoards(numberOfBlockerVariations);
        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            attackBoards[i] = calculateAttackBoard((Square)square, blockerVariations[square][i]);
        }

        attacks[square] = attackBoards;
    }
    
    return attacks;
}

void generateBishopMagicNumbers(const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                                const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards)
{
    // Variables: BISHOP_MAGIC_LOOKUP, (i'm going to exclude searchForBishopMagicNumber since that is easily turned into one function)

    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        BISHOP_MAGIC_LOOKUP[square].magicNumber = searchForBishopMagicNumber((Square)square, blockerVariations[square], attackBoards[square]);
    }
}

void generateRookMagicNumbers(const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                              const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        ROOK_MAGIC_LOOKUP[square].magicNumber = searchForRookMagicNumber((Square)square, blockerVariations[square], attackBoards[square]);
    }
}

u64 searchForBishopMagicNumber(const Square square, const std::vector<Bitboard> & allBlockerVariations, const std::vector<Bitboard> & attackBoards)
{
    // Variables: BISHOP_MAGIC_LOOKUP, LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS, < 3 number

    MagicBitboardEntry entry = BISHOP_MAGIC_LOOKUP[square];
    Bitboard tempAttackDatabase[LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS];
    const int numberOfBlockerVariations = allBlockerVariations.size();
    u64 magicNumberCandidate;

    bool foundMagicNumber = false;
    while (foundMagicNumber == false)
    {
        bool currentMagicNumberIsValid = true;

        // Reset the attack database to all empty boards
        std::fill(std::begin(tempAttackDatabase), std::end(tempAttackDatabase), Bitboard(constants::UNIVERSE));
        
        // Calculate a magic number candidate for this square
        magicNumberCandidate = utils::getSparselyPopulatedRandom64BitInteger();

        // Verify the magic number effeciently maps bits from the blocker mask to the most significant bit positions of the product
        if (Bitboard( (entry.blockerMask * magicNumberCandidate) & 0xFF00000000000000ULL ).numberOfSetBits() < 3) { continue; }

        // Hash each blocker variation and attempt to store the attack boards
        for (int i = 0; (i < numberOfBlockerVariations) && currentMagicNumberIsValid; i++)
        {
            int hashedIndex = hashBlockerVariation(allBlockerVariations[i], magicNumberCandidate, entry.shiftAmount);

            // Check if this spot in the database is empty
            if (tempAttackDatabase[hashedIndex].getBoard() == constants::UNIVERSE) { tempAttackDatabase[hashedIndex] = attackBoards[i]; }

            // If the collision gives us the same attack board, then we're fine
            // If the collision gives us a different attack board, search for a new magic number 
            else if (tempAttackDatabase[hashedIndex].getBoard() != attackBoards[i].getBoard()) { currentMagicNumberIsValid = false; }
        }

        // If we made it through the previous for loop with no collisions then we found a magic number
        if (currentMagicNumberIsValid) { foundMagicNumber = true; }
    }

    #if DEBUG
    if (foundMagicNumber)
    {
        std::cout << "(Square " << square << ") FOUND magic number: " << magicNumberCandidate << std::endl;
    }
    else
    {
        std::cout << "(Square " << square << ") ERROR, no magic number found" << magicNumberCandidate << std::endl;
    }
    #endif

    return magicNumberCandidate;
}

int hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount)
{
    return (blockerVariation * magicNumber) >> (Square::NUMBER_OF_SQUARES - shiftAmount);
}

void populateBishopAttackDatabase(const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                                  const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        const MagicBitboardEntry & hashInfo = BISHOP_MAGIC_LOOKUP[square];
        int numberOfBlockerVariations = blockerVariations[square].size();

        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            int hashedIndex = hashBlockerVariation(blockerVariations[square][i], hashInfo.magicNumber, hashInfo.shiftAmount);
            BISHOP_ATTACKS[square][hashedIndex] = attackBoards[square][i];
        }
    }
}

u64 searchForRookMagicNumber(const Square square, const std::vector<Bitboard> & allBlockerVariations, const std::vector<Bitboard> & attackBoards)
{
    MagicBitboardEntry entry = ROOK_MAGIC_LOOKUP[square];
    Bitboard tempAttackDatabase[LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];
    const int numberOfBlockerVariations = allBlockerVariations.size();
    u64 magicNumberCandidate;

    bool foundMagicNumber = false;
    while (foundMagicNumber == false)
    {
        bool currentMagicNumberIsValid = true;

        // Reset the attack database to all empty boards
        std::fill(std::begin(tempAttackDatabase), std::end(tempAttackDatabase), Bitboard(constants::UNIVERSE));
        
        // Calculate a magic number candidate for this square
        magicNumberCandidate = utils::getSparselyPopulatedRandom64BitInteger();

        // Verify the magic number effeciently maps bits from the blocker mask to the most significant bit positions of the product
        if (Bitboard( (entry.blockerMask * magicNumberCandidate) & 0xFF00000000000000ULL ).numberOfSetBits() < 6) { continue; }

        // Hash each blocker variation and attempt to store the attack boards
        for (int i = 0; (i < numberOfBlockerVariations) && currentMagicNumberIsValid; i++)
        {
            int hashedIndex = hashBlockerVariation(allBlockerVariations[i], magicNumberCandidate, entry.shiftAmount);

            // Check if this spot in the database is empty
            if (tempAttackDatabase[hashedIndex].getBoard() == constants::UNIVERSE) { tempAttackDatabase[hashedIndex] = attackBoards[i]; }

            // If the collision gives us the same attack board, then we're fine
            // If the collision gives us a different attack board, search for a new magic number 
            else if (tempAttackDatabase[hashedIndex].getBoard() != attackBoards[i].getBoard()) { currentMagicNumberIsValid = false; }
        }

        // If we made it through the previous for loop with no collisions then we found a magic number
        if (currentMagicNumberIsValid) { foundMagicNumber = true; }
    }

    #if DEBUG
    if (foundMagicNumber)
    {
        std::cout << "(Square " << square << ") FOUND magic number: " << magicNumberCandidate << std::endl;
    }
    else
    {
        std::cout << "(Square " << square << ") ERROR, no magic number found" << magicNumberCandidate << std::endl;
    }
    #endif

    return magicNumberCandidate;
}

void populateRookAttackDatabase(const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & blockerVariations,
                                const std::array<std::vector<Bitboard>, Square::NUMBER_OF_SQUARES> & attackBoards)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        const MagicBitboardEntry & hashInfo = ROOK_MAGIC_LOOKUP[square];
        int numberOfBlockerVariations = blockerVariations[square].size();

        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            int hashedIndex = hashBlockerVariation(blockerVariations[square][i], hashInfo.magicNumber, hashInfo.shiftAmount);
            ROOK_ATTACKS[square][hashedIndex] = attackBoards[square][i];
        }
    }
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
//         std::vector<Bitboard> allBlockerVariations = enumerateSubmasks(entry.blockerMask);
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

std::vector<Bitboard> enumerateSubmasks(Bitboard blockerMask)
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

} // anonymous namespace

} // namespace magic_bitboards