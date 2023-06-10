#include "movegenerator.h"

std::vector<Move> MoveGenerator::generatePsuedoLegalMoves(const Chessboard & chessboard)
{
    std::vector<Move> pawnMoves = generatePawnMoves(chessboard);
    // std::vector<Move> knightMoves = getKnightMoves();
    // std::vector<Move> bishopMoves = getBishopMoves();
    // std::vector<Move> rookMoves = getRookMoves();
    // std::vector<Move> queenMoves = getQueenMoves();
    // std::vector<Move> kingMoves = getKingMoves();

    return pawnMoves;
}

std::vector<Move> MoveGenerator::generatePawnMoves(const Chessboard & chessboard)
{
    // What we use from chessboard: side to move, we get the position of the pawns, thats it
    std::vector<Move> moveVector;
    Color sideToMove = chessboard.getSideToMove();

    Bitboard pawns = chessboard.getBitboard(sideToMove, PAWN);
    int numberOfPawnsOnBoard = pawns.numberOfSetBits();
    for (int i = 0; i < numberOfPawnsOnBoard; i++)
    {
        int startingSquare = pawns.findIndexLSB();

        // pawnAttackTable is an array of 64, 64-bit integers.
        // pawnAttackTable[0] is the 64-bit integer representing the valid pawn moves for Square 0 (aka square A1).
        // pawnAttackTable[1] is the 64-bit integer representing the valid pawn moves for Square 1 (aka square B1).
        // ...
        // pawnAttackTable[63] is the 64-bit integer representing the valid pawn moves for Square 63 (aka Square H8)
        // Obviously there can be some effeciences here because a white pawn will never be on the 1st rank
        // and the black pawns will never be on the 8th rank
        // We also have to keep track of point of view. pawnAttackTable only works for a specific point of view (the side to move POV).
        // pawnAttackTable[8] (square A2 from white's POV) will say the pawn can go to square A3 or capture on B3 (if there's an opponent on B3).
        // But this won't work if we're masking this against black pawns because a black pawn on square A2 can only go to A1 or capture on B1
        // (if there's an opponent's piece).
        Bitboard psuedoLegalPawnMoves = attack_tables::pawn[startingSquare];

        // Iterate over every psuedo legal pawn moves, encode the move into an object, and append the move to the vector
        int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalPawnMoves; j++)
        {
            int currentTargetSquare = psuedoLegalPawnMoves.findIndexLSB();
            Move m(sideToMove, PAWN, static_cast<Square>(startingSquare), static_cast<Square>(currentTargetSquare));
            moveVector.push_back(m);
        }
    }

    return moveVector;
}