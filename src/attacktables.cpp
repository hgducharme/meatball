#include "attacktables.h"

#include "types.h"
#include "utils.h"

namespace attack_tables
{

namespace
{

    Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard)
    {
        // A pawn only has valid attacks if it exists on ranks 2 through 7
        Rank rank = Chessboard::squareToRank(bitboard.findIndexLSB());
        if (rank == RANK_1 || rank == RANK_8)
        {
            return constants::EMPTY_BOARD;
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
        Bitboard potentialPawnAttacks;
        potentialPawnAttacks |= utils::shiftSquareByDirection(bitboard, eastDirection) & constants::bit_masks::EXCLUDE_FILE_A;
        potentialPawnAttacks |= utils::shiftSquareByDirection(bitboard, westDirection) & constants::bit_masks::EXCLUDE_FILE_H;

        return potentialPawnAttacks;
    }

    Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard)
    {
        Bitboard potentialKnightAttacks;

        // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, 2 * NORTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;    
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, 2 * SOUTH + EAST) & constants::bit_masks::EXCLUDE_FILE_A;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, 2 * NORTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, 2 * SOUTH + WEST) & constants::bit_masks::EXCLUDE_FILE_H;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, NORTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, SOUTH + 2 * EAST) & constants::bit_masks::EXCLUDE_FILES_A_AND_B;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, NORTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;
        potentialKnightAttacks |= utils::shiftSquareByDirection(bitboard, SOUTH + 2 * WEST) & constants::bit_masks::EXCLUDE_FILES_H_AND_G;

        return potentialKnightAttacks;
    }

    Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard)
    {
        Bitboard legalKingAttacks;

        // If we perform a move and end up on the opposite side of the board, that is an off-board move and we need to exclude that move
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, NORTH);
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, SOUTH);
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, EAST) & constants::bit_masks::EXCLUDE_FILE_A;
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, WEST) & constants::bit_masks::EXCLUDE_FILE_H;
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, NORTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, SOUTH_WEST) & constants::bit_masks::EXCLUDE_FILE_H;
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, NORTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;
        legalKingAttacks |= utils::shiftSquareByDirection(bitboard, SOUTH_EAST) & constants::bit_masks::EXCLUDE_FILE_A;

        return legalKingAttacks;
    }

    void initializeAttacksForLeaperPieces()
    {
        for (int square = 0; square < Square::NUMBER_OF_SQUARES; square++)
        {
            Bitboard squareBitboard(square);

            PAWN_ATTACKS[Color::WHITE][square] = calculatePawnAttacksFromSquare(Color::WHITE, squareBitboard);
            PAWN_ATTACKS[Color::BLACK][square] = calculatePawnAttacksFromSquare(Color::BLACK, squareBitboard);
            KNIGHT_ATTACKS[square] = calculateKnightAttacksFromSquare(squareBitboard);
            KING_ATTACKS[square] = calculateKingAttacksFromSquare(squareBitboard);
        }
    }

    void initializeAttacksForSliderPieces()
    {
        magic_bitboards::init();
    }

} // anonymous namespace

Bitboard PAWN_ATTACKS[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
Bitboard KNIGHT_ATTACKS[Square::NUMBER_OF_SQUARES];
Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][magic_bitboards::LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS];
Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][magic_bitboards::LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];
Bitboard KING_ATTACKS[Square::NUMBER_OF_SQUARES];

void init()
{
    initializeAttacksForLeaperPieces();
    initializeAttacksForSliderPieces();
}

Bitboard getAttacks(const Chessboard & gameState, const Color color)
{
    Bitboard attacks;

    for (auto pieceType : {PieceType::PAWN, PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN, PieceType::KING})
    {
        Bitboard pieces = gameState.getBitboard(color, pieceType);
        const int numberOfPieces = pieces.numberOfSetBits();
        for (int i = 0; i < numberOfPieces; i++)
        {
            const Square startingSquare = (Square)(pieces.clearAndReturnLSB());
            attacks |= getAttacks(color, pieceType, startingSquare, gameState.getOccupiedSquares());
        }
    }

    return attacks;
}

Bitboard getAttacks(const Color color, const PieceType pieceType, const Square square, const Bitboard & occupiedSquares)
{
    switch (pieceType)
    {
        case PieceType::PAWN:
        case PieceType::KNIGHT:
        case PieceType::KING:
            return getLeaperPieceAttacks((LeaperPiece)pieceType, square, color);
        case PieceType::BISHOP:
        case PieceType::ROOK:
        case PieceType::QUEEN:
            return getSliderPieceAttacks((SliderPiece)pieceType, square, occupiedSquares);
        default:
            std::__throw_invalid_argument("pieceType must be one of the following piece types: 'pawn', 'knight', 'bishop', 'rook', 'queen', or 'king'.");
        }
}

Bitboard getLeaperPieceAttacks(const LeaperPiece leaperPiece, const Square square, const Color color)
{
    switch (leaperPiece)
    {
        case LeaperPiece::PAWN:
            return PAWN_ATTACKS[color][square];
        case LeaperPiece::KNIGHT:
            return KNIGHT_ATTACKS[square];
        case LeaperPiece::KING:
            return KING_ATTACKS[square];
    }
}

Bitboard getSliderPieceAttacks(const SliderPiece sliderPiece, const Square square, const Bitboard & boardState)
{
    magic_bitboards::HashingParameters hashingParameters;
    Bitboard * attackDatabase;

    switch (sliderPiece)
    {
        case SliderPiece::BISHOP:
            hashingParameters = magic_bitboards::BISHOP_HASHING_PARAMETERS_LOOKUP[square];
            attackDatabase = BISHOP_ATTACKS[square];
            break;
        case SliderPiece::ROOK:
            hashingParameters = magic_bitboards::ROOK_HASHING_PARAMETERS_LOOKUP[square];
            attackDatabase = ROOK_ATTACKS[square];
            break;
        case SliderPiece::QUEEN:
            Bitboard bishopAttacks = getSliderPieceAttacks(SliderPiece::BISHOP, square, boardState);
            Bitboard rookAttacks = getSliderPieceAttacks(SliderPiece::ROOK, square, boardState);
            return bishopAttacks | rookAttacks;
    }

    const Bitboard blockers = boardState & hashingParameters.blockerMask;
    const int hashedIndex = magic_bitboards::hashBlockerVariation(blockers, hashingParameters.magicNumber, hashingParameters.shiftAmount);
    return attackDatabase[hashedIndex];;
}

} // attack_tables namespace