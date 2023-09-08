#include "magicbitboard.h"

#include "attacktables.h"
#include "types.h"
#include "utils.h"
#include "constants.h"

#include <iostream>
#include <array>
#include <cmath>

namespace magic_bitboards
{

HashingParameters BISHOP_HASHING_PARAMETERS_LOOKUP[Square::NUMBER_OF_SQUARES];
HashingParameters ROOK_HASHING_PARAMETERS_LOOKUP[Square::NUMBER_OF_SQUARES];

void init()
{
    initializeHashingParameters();
    generateBlockerMasks();

    ArrayOfBitboardVectors bishopBlockerVariations = calculateBlockerVariations(BISHOP_HASHING_PARAMETERS_LOOKUP);
    ArrayOfBitboardVectors rookBlockerVariations = calculateBlockerVariations(ROOK_HASHING_PARAMETERS_LOOKUP);

    ArrayOfBitboardVectors bishopAttacks = calculateAttacks(constants::BISHOP_DIRECTIONS, bishopBlockerVariations);
    ArrayOfBitboardVectors rookAttacks = calculateAttacks(constants::ROOK_DIRECTIONS, rookBlockerVariations);

    std::cout << "Searching for bishop magics, this could take up to 30 seconds... " << std::endl;
    generateMagicNumbers(BISHOP_HASHING_PARAMETERS_LOOKUP, MINIMUM_NUMBER_OF_BITS_FOR_BISHOP_HASHING, bishopBlockerVariations, bishopAttacks);
    std::cout << "DONE." << std::endl;

    std::cout << "Searching for rook magic numbers, this could take up to 30 seconds... " << std::endl;
    generateMagicNumbers(ROOK_HASHING_PARAMETERS_LOOKUP, MINIMUM_NUMBER_OF_BITS_FOR_ROOK_HASHING, rookBlockerVariations, rookAttacks);
    std::cout << "DONE." << std::endl;

    populateAttackDatabase(attack_tables::BISHOP_ATTACKS, BISHOP_HASHING_PARAMETERS_LOOKUP, bishopBlockerVariations, bishopAttacks);
    populateAttackDatabase(attack_tables::ROOK_ATTACKS, ROOK_HASHING_PARAMETERS_LOOKUP, rookBlockerVariations, rookAttacks);
}

namespace
{

u64 BISHOP_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];
u64 ROOK_MAGIC_NUMBERS[Square::NUMBER_OF_SQUARES];

void initializeHashingParameters()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        HashingParameters bishopEntry;
        HashingParameters rookEntry;

        BISHOP_HASHING_PARAMETERS_LOOKUP[square] = bishopEntry;
        ROOK_HASHING_PARAMETERS_LOOKUP[square] = rookEntry;
    }
}

void generateBlockerMasks()
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        Bitboard squareBitboard(square);

        // Calculate the blocker mask for each piece on this square
        BISHOP_HASHING_PARAMETERS_LOOKUP[square].blockerMask = calculateBlockerMask(squareBitboard, constants::BISHOP_DIRECTIONS);
        ROOK_HASHING_PARAMETERS_LOOKUP[square].blockerMask = calculateBlockerMask(squareBitboard, constants::ROOK_DIRECTIONS);

        // Store the shift amount to be used in the hash function
        BISHOP_HASHING_PARAMETERS_LOOKUP[square].shiftAmount = BISHOP_HASHING_PARAMETERS_LOOKUP[square].blockerMask.numberOfSetBits();
        ROOK_HASHING_PARAMETERS_LOOKUP[square].shiftAmount = ROOK_HASHING_PARAMETERS_LOOKUP[square].blockerMask.numberOfSetBits();
    }
}

// TODO: verify this is correct
template <uint8_t size>
Bitboard calculateBlockerMask(const Bitboard & position, const Direction (&sliderPieceDirections)[size])
{
    Bitboard potentialBlockerSquares;
    Square currentSquare = static_cast<Square>(position.findIndexLSB());

    for (const Direction direction : sliderPieceDirections)
    {
        int distanceToEdge = utils::calculateDistanceToEdgeOfBoard(currentSquare, direction);

        for (int i = 1; i < distanceToEdge; i++)
        {
            potentialBlockerSquares |= utils::shiftCurrentSquareByDirection(position, i * direction);
        }
    }

    return potentialBlockerSquares;
}

ArrayOfBitboardVectors calculateBlockerVariations(HashingParameters const * hashingParametersLookup)
{
    ArrayOfBitboardVectors blockerVariations;
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        blockerVariations[square] = enumerateSubmasks(hashingParametersLookup[square].blockerMask);
    }

    return blockerVariations;
}

std::vector<Bitboard> enumerateSubmasks(Bitboard blockerMask)
{
    /*
     * This solved problem is also known as: enumerate all submasks of a bitmask.
     * Here is a link with some explanation: https://www.geeksforgeeks.org/print-all-submasks-of-a-given-mask/
     * One with better explanation: https://cp-algorithms.com/algebra/all-submasks.html
     */
    std::uint16_t numberOfBlockerVariations = std::pow(2, blockerMask.numberOfSetBits());
    std::vector<Bitboard> allBlockerVariations(numberOfBlockerVariations);

    std::uint16_t i = 0;
    for (u64 blockerVariation = blockerMask.getBoard(); blockerVariation; blockerVariation = (blockerVariation - 1) & blockerMask.getBoard())
    {
        allBlockerVariations[i] = blockerVariation;
        i++;
    }

    return allBlockerVariations;
}

template <uint8_t size>
ArrayOfBitboardVectors calculateAttacks(const Direction (&attackDirections)[size], const ArrayOfBitboardVectors & blockerVariations)
{
    ArrayOfBitboardVectors attacks;

    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        int numberOfBlockerVariations = blockerVariations[square].size();
        std::vector<Bitboard> attackBoards(numberOfBlockerVariations);
        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            attackBoards[i] = calculateAttacksFromSquare((Square)square, attackDirections, blockerVariations[square][i]);
        }

        attacks[square] = attackBoards;
    }
    
    return attacks;
}

template <uint8_t size>
Bitboard calculateAttacksFromSquare(const Square & square, const Direction (&attackDirections)[size], const Bitboard & blockerVariation)
{
    Bitboard attackBoard;
    Bitboard squareBitboard(square);

    for (Direction direction : attackDirections)
    {
        int distanceToEdge = utils::calculateDistanceToEdgeOfBoard(square, direction);

        for (int i = 1; i < distanceToEdge; i++)
        {
            Bitboard targetSquare = utils::shiftCurrentSquareByDirection(squareBitboard, i * direction);
            if (targetSquareIsBlocked(targetSquare, blockerVariation))
            {
                break;
            }
            else
            {
                attackBoard |= targetSquare;
            }
        }
    }

    return attackBoard;
}

bool targetSquareIsBlocked(Bitboard targetSquare, Bitboard occupiedSquares)
{
    return ( (targetSquare & occupiedSquares).numberOfSetBits() == 1 );
}

void generateMagicNumbers(HashingParameters * hashingParametersLookup,
                          const int minimumBitsRequiredForHashing,
                          const ArrayOfBitboardVectors & blockerVariations,
                          const ArrayOfBitboardVectors & attackBoards)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        hashingParametersLookup[square].magicNumber = searchForMagicNumber(hashingParametersLookup[square], minimumBitsRequiredForHashing, blockerVariations[square], attackBoards[square]);

        // #if DEBUG
        std::cout << "(Square " << square << ") Found magic number: " << hashingParametersLookup[square].magicNumber << std::endl;
        // #endif
    }
}

// TODO: magic number search for rooks is extremely slow.
u64 searchForMagicNumber(const HashingParameters & hashingParameters, const int minimumAmountOfBitsInLastByte, const std::vector<Bitboard> & allBlockerVariations, const std::vector<Bitboard> & attackBoards)
{
    Bitboard tempAttackDatabase[LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];
    const int numberOfBlockerVariations = allBlockerVariations.size();
    u64 magicNumberCandidate;
    bool foundMagicNumber = false;

    while (foundMagicNumber == false)
    {
        bool currentMagicNumberIsValid = true;

        // Reset the attack database
        std::fill(std::begin(tempAttackDatabase), std::end(tempAttackDatabase), Bitboard(constants::UNIVERSE));
        
        magicNumberCandidate = utils::getSparselyPopulatedRandom64BitInteger();

        // Verify the magic number effeciently maps bits from the blocker mask to the most significant bit positions of the product
        Bitboard lastByteOfMagicProduct = Bitboard( (hashingParameters.blockerMask * magicNumberCandidate) & constants::bit_masks::LAST_EIGHT_BITS );
        if (lastByteOfMagicProduct.numberOfSetBits() < minimumAmountOfBitsInLastByte)
        {
            continue;
        }

        // Hash each blocker variation and attempt to store the attack boards
        for (int i = 0; (i < numberOfBlockerVariations) && currentMagicNumberIsValid; i++)
        {
            int hashedIndex = hashBlockerVariation(allBlockerVariations[i], magicNumberCandidate, hashingParameters.shiftAmount);

            // Check if this spot in the database is empty
            if (tempAttackDatabase[hashedIndex].getBoard() == constants::UNIVERSE)
            {
                tempAttackDatabase[hashedIndex] = attackBoards[i];
            }

            // If the collision gives us the same attack board, then we're fine
            // If the collision gives us a different attack board, search for a new magic number 
            else if (tempAttackDatabase[hashedIndex].getBoard() != attackBoards[i].getBoard())
            {
                currentMagicNumberIsValid = false;
            }
        }

        // If we made it through the previous for loop with no collisions then we found a magic number
        if (currentMagicNumberIsValid)
        {
            foundMagicNumber = true;
        }
    }

    return magicNumberCandidate;
}

int hashBlockerVariation(const Bitboard & blockerVariation, const u64 magicNumber, const int shiftAmount)
{
    return (blockerVariation * magicNumber) >> (Square::NUMBER_OF_SQUARES - shiftAmount);
}

template <size_t rows, size_t columns>
void populateAttackDatabase(Bitboard (&attackDatabase)[rows][columns],
                            const HashingParameters * hashingParametersLookup,
                            const ArrayOfBitboardVectors & blockerVariations,
                            const ArrayOfBitboardVectors & attackBoards)
{
    for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
    {
        const HashingParameters & hashingParameters = hashingParametersLookup[square];
        int numberOfBlockerVariations = blockerVariations[square].size();

        for (int i = 0; i < numberOfBlockerVariations; i++)
        {
            int hashedIndex = hashBlockerVariation(blockerVariations[square][i], hashingParameters.magicNumber, hashingParameters.shiftAmount);
            attackDatabase[square][hashedIndex] = attackBoards[square][i];
        }
    }
}

} // anonymous namespace
} // namespace magic_bitboards