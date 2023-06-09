#include "movegenerator.h"

std::vector<Move> MoveGenerator::generatePsuedoLegalMoves(const Chessboard & chessboard)
{
    // std::vector<Move> pawnMoves = getPawnMoves();
    // std::vector<Move> knightMoves = getKnightMoves();
    // std::vector<Move> bishopMoves = getBishopMoves();
    // std::vector<Move> rookMoves = getRookMoves();
    // std::vector<Move> queenMoves = getQueenMoves();
    // std::vector<Move> kingMoves = getKingMoves();
}

std::vector<Move> MoveGenerator::generatePawnMoves(const Chessboard & chessboard)
{
    std::vector<Move> moveVector;

    Bitboard pawns = chessboard.getBitboard(chessboard.getSideToMove(), PAWN);
    // int numberOfPawnsOnBoard = whitePawns.populationCount();
    // for (int i = 0; i < numberOfPawnsOnBoard; i++)
    // {
    //     // popLSB() should return the index of the first bit it sees that is set to 1
    //     int startingSquare = whitePawns.popLeastSignificantBitIndex();

    //     // pawnAttackTable is an array of 64, 64-bit integers.
    //     // pawnAttackTable[0] is the 64-bit integer representing the valid pawn moves for Square 0 (aka square A1).
    //     // pawnAttackTable[1] is the 64-bit integer representing the valid pawn moves for Square 1 (aka square B1).
    //     // ...
    //     // pawnAttackTable[63] is the 64-bit integer representing the valid pawn moves for Square 63 (aka Square H8)
    //     // Obviously there can be some effeciences here because a white pawn will never be on the 1st rank
    //     // and the black pawns will never be on the 8th rank
    //     // We also have to keep track of point of view. pawnAttackTable only works for a specific point of view.
    //     // pawnAttackTable[8] (square A2 from white's POV) will say the pawn can go to square A3 or capture on B3 (if there's an opponent on B3).
    //     // But this won't work if we're masking this against black pawns because a black pawn on square A2 can only go to A1 or capture on B1
    //     // (if there's an opponent's piece).
    //     Bitboard psuedoLegalPawnMoves = pawnAttackTable[startingSquare]

    //     // Iterate over every psuedo legal pawn move, encode the move into an object, and append the move to the vector
    //     int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.populationCount();
    //     for (int i = 0; i < numberOfPsuedoLegalPawnMoves; i++)
    //     {
    //         ithTargetSquaure = psuedoLegalPawnMoves.popLeastSignificantBit();
    //         Move m(COLOR, PIECE, startingSquare, ithTargetSquare);
    //         moveVector.append(m);
    //     }
    // }

    return moveVector;
}