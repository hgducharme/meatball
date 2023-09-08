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

    #ifdef GENERATE
    std::cout << "Searching for bishop magics, this could take up to 30 seconds... " << std::endl;
    generateMagicNumbers(BISHOP_HASHING_PARAMETERS_LOOKUP, MINIMUM_NUMBER_OF_BITS_FOR_BISHOP_HASHING, bishopBlockerVariations, bishopAttacks);
    std::cout << "DONE." << std::endl;

    std::cout << "Searching for rook magic numbers, this could take up to 30 seconds... " << std::endl;
    generateMagicNumbers(ROOK_HASHING_PARAMETERS_LOOKUP, MINIMUM_NUMBER_OF_BITS_FOR_ROOK_HASHING, rookBlockerVariations, rookAttacks);
    std::cout << "DONE." << std::endl;
    #else
    initializeMagicNumbers();
    #endif

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

    // 1 << n is equavalent to 2^n
    std::uint16_t numberOfBlockerVariations = 1 << blockerMask.numberOfSetBits();
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

        #if DEBUG
        std::cout << "(Square " << square << ") Using magic number: " << hashingParametersLookup[square].magicNumber << std::endl;
        #endif
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

void initializeMagicNumbers()
{
    // TODO: finish this. Use the std::cout statement in generateMagicNumbers() to make this easier.
    BISHOP_HASHING_PARAMETERS_LOOKUP[0].magicNumber = 9873895970016936192;
    BISHOP_HASHING_PARAMETERS_LOOKUP[1].magicNumber = 883277444818175001;
    BISHOP_HASHING_PARAMETERS_LOOKUP[2].magicNumber = 6764749619462208;
    BISHOP_HASHING_PARAMETERS_LOOKUP[3].magicNumber = 10146329811681344;
    BISHOP_HASHING_PARAMETERS_LOOKUP[4].magicNumber = 4684308830723506440;
    BISHOP_HASHING_PARAMETERS_LOOKUP[5].magicNumber = 4620992594149673008;
    BISHOP_HASHING_PARAMETERS_LOOKUP[6].magicNumber = 2305992560010592260;
    BISHOP_HASHING_PARAMETERS_LOOKUP[7].magicNumber = 585487751625967654;
    BISHOP_HASHING_PARAMETERS_LOOKUP[8].magicNumber = 22624676803117696;
    BISHOP_HASHING_PARAMETERS_LOOKUP[9].magicNumber = 2260802132279460;
    BISHOP_HASHING_PARAMETERS_LOOKUP[10].magicNumber = 18594944977480384;
    BISHOP_HASHING_PARAMETERS_LOOKUP[11].magicNumber = 144119775109611776;
    BISHOP_HASHING_PARAMETERS_LOOKUP[12].magicNumber = 6605928411136;
    BISHOP_HASHING_PARAMETERS_LOOKUP[13].magicNumber = 9007817799237640;
    BISHOP_HASHING_PARAMETERS_LOOKUP[14].magicNumber = 167768298959159392;
    BISHOP_HASHING_PARAMETERS_LOOKUP[15].magicNumber = 577588855571124240;
    BISHOP_HASHING_PARAMETERS_LOOKUP[16].magicNumber = 580965488219132032;
    BISHOP_HASHING_PARAMETERS_LOOKUP[17].magicNumber = 9538661428542767632;
    BISHOP_HASHING_PARAMETERS_LOOKUP[18].magicNumber = 2308094877772030028;
    BISHOP_HASHING_PARAMETERS_LOOKUP[19].magicNumber = 1153487341323554850;
    BISHOP_HASHING_PARAMETERS_LOOKUP[20].magicNumber = 36310306892809218;
    BISHOP_HASHING_PARAMETERS_LOOKUP[21].magicNumber = 4611756464486220818;
    BISHOP_HASHING_PARAMETERS_LOOKUP[22].magicNumber = 1171077706964799489;
    BISHOP_HASHING_PARAMETERS_LOOKUP[23].magicNumber = 2323913210153140768;
    BISHOP_HASHING_PARAMETERS_LOOKUP[24].magicNumber = 22535591397298816;
    BISHOP_HASHING_PARAMETERS_LOOKUP[25].magicNumber = 37165709759349568;
    BISHOP_HASHING_PARAMETERS_LOOKUP[26].magicNumber = 72110387809747008;
    BISHOP_HASHING_PARAMETERS_LOOKUP[27].magicNumber = 9300219103547752576;
    BISHOP_HASHING_PARAMETERS_LOOKUP[28].magicNumber = 162270461546332224;
    BISHOP_HASHING_PARAMETERS_LOOKUP[29].magicNumber = 5838919115930092064;
    BISHOP_HASHING_PARAMETERS_LOOKUP[30].magicNumber = 147494124755879684;
    BISHOP_HASHING_PARAMETERS_LOOKUP[31].magicNumber = 468692120207770884;
    BISHOP_HASHING_PARAMETERS_LOOKUP[32].magicNumber = 1130583704994304;
    BISHOP_HASHING_PARAMETERS_LOOKUP[33].magicNumber = 9235761351092085024;
    BISHOP_HASHING_PARAMETERS_LOOKUP[34].magicNumber = 37159099267417600;
    BISHOP_HASHING_PARAMETERS_LOOKUP[35].magicNumber = 36099475009208832;
    BISHOP_HASHING_PARAMETERS_LOOKUP[36].magicNumber = 1459187174283939904;
    BISHOP_HASHING_PARAMETERS_LOOKUP[37].magicNumber = 5198288679474430088;
    BISHOP_HASHING_PARAMETERS_LOOKUP[38].magicNumber = 600341938726913;
    BISHOP_HASHING_PARAMETERS_LOOKUP[39].magicNumber = 144401063249191440;
    BISHOP_HASHING_PARAMETERS_LOOKUP[40].magicNumber = 2325845361320828994;
    BISHOP_HASHING_PARAMETERS_LOOKUP[41].magicNumber = 2455025850812211204;
    BISHOP_HASHING_PARAMETERS_LOOKUP[42].magicNumber = 2269958952194048;
    BISHOP_HASHING_PARAMETERS_LOOKUP[43].magicNumber = 1152961224749619209;
    BISHOP_HASHING_PARAMETERS_LOOKUP[44].magicNumber = 74344596750017536;
    BISHOP_HASHING_PARAMETERS_LOOKUP[45].magicNumber = 9241404182439678018;
    BISHOP_HASHING_PARAMETERS_LOOKUP[46].magicNumber = 153702934335521024;
    BISHOP_HASHING_PARAMETERS_LOOKUP[47].magicNumber = 13880376707665400336;
    BISHOP_HASHING_PARAMETERS_LOOKUP[48].magicNumber = 1128271299750144;
    BISHOP_HASHING_PARAMETERS_LOOKUP[49].magicNumber = 146930367510094352;
    BISHOP_HASHING_PARAMETERS_LOOKUP[50].magicNumber = 70523466285056;
    BISHOP_HASHING_PARAMETERS_LOOKUP[51].magicNumber = 37299976543666176;
    BISHOP_HASHING_PARAMETERS_LOOKUP[52].magicNumber = 297255442606850562;
    BISHOP_HASHING_PARAMETERS_LOOKUP[53].magicNumber = 5773685434999671808;
    BISHOP_HASHING_PARAMETERS_LOOKUP[54].magicNumber = 81100166660112416;
    BISHOP_HASHING_PARAMETERS_LOOKUP[55].magicNumber = 3542793624830509066;
    BISHOP_HASHING_PARAMETERS_LOOKUP[56].magicNumber = 4917966127921381408;
    BISHOP_HASHING_PARAMETERS_LOOKUP[57].magicNumber = 4613738540645490720;
    BISHOP_HASHING_PARAMETERS_LOOKUP[58].magicNumber = 81135168484018202;
    BISHOP_HASHING_PARAMETERS_LOOKUP[59].magicNumber = 4629700967942852872;
    BISHOP_HASHING_PARAMETERS_LOOKUP[60].magicNumber = 2341871978878730762;
    BISHOP_HASHING_PARAMETERS_LOOKUP[61].magicNumber = 72620578905000996;
    BISHOP_HASHING_PARAMETERS_LOOKUP[62].magicNumber = 9024811439260672;
    BISHOP_HASHING_PARAMETERS_LOOKUP[63].magicNumber = 577059466752426048;

    ROOK_HASHING_PARAMETERS_LOOKUP[0].magicNumber = 2377918472463122464;
    ROOK_HASHING_PARAMETERS_LOOKUP[1].magicNumber = 1369112020783218689;
    ROOK_HASHING_PARAMETERS_LOOKUP[2].magicNumber = 72067495079452672;
    ROOK_HASHING_PARAMETERS_LOOKUP[3].magicNumber = 72066458853319424;
    ROOK_HASHING_PARAMETERS_LOOKUP[4].magicNumber = 7638140719467610624;
    ROOK_HASHING_PARAMETERS_LOOKUP[5].magicNumber = 36033195099029888;
    ROOK_HASHING_PARAMETERS_LOOKUP[6].magicNumber = 36029346791555584;
    ROOK_HASHING_PARAMETERS_LOOKUP[7].magicNumber = 144119594721002533;
    ROOK_HASHING_PARAMETERS_LOOKUP[8].magicNumber = 2392537847316488;
    ROOK_HASHING_PARAMETERS_LOOKUP[9].magicNumber = 581808987318517889;
    ROOK_HASHING_PARAMETERS_LOOKUP[10].magicNumber = 1266774859419648;
    ROOK_HASHING_PARAMETERS_LOOKUP[11].magicNumber = 4614078590097559552;
    ROOK_HASHING_PARAMETERS_LOOKUP[12].magicNumber = 9234771790599833600;
    ROOK_HASHING_PARAMETERS_LOOKUP[13].magicNumber = 802203872873955841;
    ROOK_HASHING_PARAMETERS_LOOKUP[14].magicNumber = 171981219360735236;
    ROOK_HASHING_PARAMETERS_LOOKUP[15].magicNumber = 9147938890600704;
    ROOK_HASHING_PARAMETERS_LOOKUP[16].magicNumber = 3463413798783696896;
    ROOK_HASHING_PARAMETERS_LOOKUP[17].magicNumber = 9227877011408601089;
    ROOK_HASHING_PARAMETERS_LOOKUP[18].magicNumber = 22518685334242305;
    ROOK_HASHING_PARAMETERS_LOOKUP[19].magicNumber = 10423581887447437312;
    ROOK_HASHING_PARAMETERS_LOOKUP[20].magicNumber = 54184482839726082;
    ROOK_HASHING_PARAMETERS_LOOKUP[21].magicNumber = 9691887685379064832;
    ROOK_HASHING_PARAMETERS_LOOKUP[22].magicNumber = 2668809389745934338;
    ROOK_HASHING_PARAMETERS_LOOKUP[23].magicNumber = 1162388299726454913;
    ROOK_HASHING_PARAMETERS_LOOKUP[24].magicNumber = 360358341081862176;
    ROOK_HASHING_PARAMETERS_LOOKUP[25].magicNumber = 9077570148499584;
    ROOK_HASHING_PARAMETERS_LOOKUP[26].magicNumber = 148636382038852488;
    ROOK_HASHING_PARAMETERS_LOOKUP[27].magicNumber = 845666176729352;
    ROOK_HASHING_PARAMETERS_LOOKUP[28].magicNumber = 288511872603783184;
    ROOK_HASHING_PARAMETERS_LOOKUP[29].magicNumber = 1127000496407040;
    ROOK_HASHING_PARAMETERS_LOOKUP[30].magicNumber = 9223654272040960512;
    ROOK_HASHING_PARAMETERS_LOOKUP[31].magicNumber = 54197152926302417;
    ROOK_HASHING_PARAMETERS_LOOKUP[32].magicNumber = 5188182230257631360;
    ROOK_HASHING_PARAMETERS_LOOKUP[33].magicNumber = 4504287262540096;
    ROOK_HASHING_PARAMETERS_LOOKUP[34].magicNumber = 612595104628084740;
    ROOK_HASHING_PARAMETERS_LOOKUP[35].magicNumber = 2954396578598621188;
    ROOK_HASHING_PARAMETERS_LOOKUP[36].magicNumber = 853223179027456;
    ROOK_HASHING_PARAMETERS_LOOKUP[37].magicNumber = 3467776113277665792;
    ROOK_HASHING_PARAMETERS_LOOKUP[38].magicNumber = 2814784160402244;
    ROOK_HASHING_PARAMETERS_LOOKUP[39].magicNumber = 148623222827384897;
    ROOK_HASHING_PARAMETERS_LOOKUP[40].magicNumber = 4614470256755310592;
    ROOK_HASHING_PARAMETERS_LOOKUP[41].magicNumber = 4503737070796802;
    ROOK_HASHING_PARAMETERS_LOOKUP[42].magicNumber = 297237718298198035;
    ROOK_HASHING_PARAMETERS_LOOKUP[43].magicNumber = 290554538754080;
    ROOK_HASHING_PARAMETERS_LOOKUP[44].magicNumber = 39973844873674880;
    ROOK_HASHING_PARAMETERS_LOOKUP[45].magicNumber = 4630264708063166480;
    ROOK_HASHING_PARAMETERS_LOOKUP[46].magicNumber = 144678155343495169;
    ROOK_HASHING_PARAMETERS_LOOKUP[47].magicNumber = 2534397928669204;
    ROOK_HASHING_PARAMETERS_LOOKUP[48].magicNumber = 11583821759039881728;
    ROOK_HASHING_PARAMETERS_LOOKUP[49].magicNumber = 4648005637364646400;
    ROOK_HASHING_PARAMETERS_LOOKUP[50].magicNumber = 396457573418535040;
    ROOK_HASHING_PARAMETERS_LOOKUP[51].magicNumber = 5768021274991395328;
    ROOK_HASHING_PARAMETERS_LOOKUP[52].magicNumber = 1517717472604618880;
    ROOK_HASHING_PARAMETERS_LOOKUP[53].magicNumber = 2254001051566208;
    ROOK_HASHING_PARAMETERS_LOOKUP[54].magicNumber = 1407933229564160;
    ROOK_HASHING_PARAMETERS_LOOKUP[55].magicNumber = 72058848176783872;
    ROOK_HASHING_PARAMETERS_LOOKUP[56].magicNumber = 297257093885395109;
    ROOK_HASHING_PARAMETERS_LOOKUP[57].magicNumber = 2378323116414738514;
    ROOK_HASHING_PARAMETERS_LOOKUP[58].magicNumber = 13836263201634787329;
    ROOK_HASHING_PARAMETERS_LOOKUP[59].magicNumber = 576466249997946881;
    ROOK_HASHING_PARAMETERS_LOOKUP[60].magicNumber = 577305185895317521;
    ROOK_HASHING_PARAMETERS_LOOKUP[61].magicNumber = 72620831891522562;
    ROOK_HASHING_PARAMETERS_LOOKUP[62].magicNumber = 182958739702682626;
    ROOK_HASHING_PARAMETERS_LOOKUP[63].magicNumber = 289638867728876930;
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