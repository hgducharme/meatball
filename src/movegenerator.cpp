#include "movegenerator.h"

std::vector<Move> MoveGenerator::generatePsuedoLegalMoves(const Chessboard & chessboard) const
{
    std::vector<Move> pawnMoves = generatePawnMoves(chessboard);
    // std::vector<Move> knightMoves = getKnightMoves();
    // std::vector<Move> bishopMoves = getBishopMoves();
    // std::vector<Move> rookMoves = getRookMoves();
    // std::vector<Move> queenMoves = getQueenMoves();
    // std::vector<Move> kingMoves = getKingMoves();

    return pawnMoves;
}

std::vector<Move> MoveGenerator::generatePawnMoves(const Chessboard & chessboard) const
{
    // What we use from chessboard: side to move, we get the position of the pawns, thats it
    std::vector<Move> moveVector;
    Color activePlayer = chessboard.getActivePlayer();

    Bitboard pawns = chessboard.getBitboard(activePlayer, PAWN);
    int numberOfPawnsOnBoard = pawns.numberOfSetBits();
    for (int i = 0; i < numberOfPawnsOnBoard; i++)
    {
        int startingSquare = pawns.clearAndReturnLSB();

        Bitboard psuedoLegalPawnMoves = attack_tables::pawn[activePlayer][startingSquare];

        // Iterate over every psuedo legal pawn moves, encode the move into an object, and append the move to the vector
        int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalPawnMoves; j++)
        {
            int targetSquare = psuedoLegalPawnMoves.clearAndReturnLSB();
            Move m(activePlayer, PAWN, static_cast<Square>(startingSquare), static_cast<Square>(targetSquare));
            moveVector.push_back(m);
        }
    }

    return moveVector;
}