#include "movegenerator.h"

#include "move.h"
#include "attacktables.h"

std::vector<Move> LegalMoveGenerator::generatePsuedoLegalMoves(const Chessboard & chessboard) const
{
    std::vector<Move> pawnMoves = generatePawnMoves(chessboard);
    // std::vector<Move> knightMoves = generateKnightMoves(chessboard);
    // std::vector<Move> bishopMoves = getBishopMoves();
    // std::vector<Move> rookMoves = getRookMoves();
    // std::vector<Move> queenMoves = getQueenMoves();
    // std::vector<Move> kingMoves = getKingMoves();

    return pawnMoves;
}

std::vector<Move> LegalMoveGenerator::generatePawnMoves(const Chessboard & chessboard) const
{
    // What we use from chessboard: side to move, we get the position of the pawns, thats it
    std::vector<Move> moveVector;
    Color activePlayer = chessboard.getActivePlayer();
    Bitboard pawns = chessboard.getBitboard(activePlayer, PAWN);
    
    int numberOfPawnsOnBoard = pawns.numberOfSetBits();
    for (int i = 0; i < numberOfPawnsOnBoard; i++)
    {
        int startingSquare = pawns.clearAndReturnLSB();

        Bitboard psuedoLegalPawnMoves = attack_tables::PAWN_ATTACKS[activePlayer][startingSquare];

        // Iterate over every psuedo legal pawn moves, encode the move into an object, and append the move to the vector
        int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalPawnMoves; j++)
        {
            int targetSquare = psuedoLegalPawnMoves.clearAndReturnLSB();
            
            // TODO: Remove moves that capture our own pieces
            // psuedoLegalPawnMoves &= ~(white pieces & psuedoLegalPawnMoves)

            Move m(activePlayer, PAWN, static_cast<Square>(startingSquare), static_cast<Square>(targetSquare));
            moveVector.push_back(m);
        }
    }

    return moveVector;
}

Bitboard LegalMoveGenerator::filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves)
{}

std::vector<Move> LegalMoveGenerator::generateLegalMoves(const Chessboard & chessboard) const
{}

// This is an example of a function that would be used in movegen.cpp
// And how we would use the magic bitboards as an end user
// Bitboard getBishopAttacks(const int square, const Bitboard & boardState)
// {
//     HashingParameters bishopHashingParameters = magic_bitboards::BISHOP_HASHING_PARAMETERS_LOOKUP[square];
//     Bitboard blockersToBishop = boardState & bishopHashingParameters.blockerMask;
//     int hashedIndex = hashBlockerVariation(blockersToBishop, bishopHashingParameters.magicNumber, bishopHashingParameters.shiftAmount)
//     return attack_tables::BISHOP_ATTACKS[square][hashedBlockerConfiguration];
// }