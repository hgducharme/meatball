#include "chessboard.h"

Chessboard::Chessboard()
{
    // Initialize the bitboards for each piece type
    pieceBitboards_[PAWN].setBoard(bitboard::DEFAULT_PAWN_STRUCTURE);
    pieceBitboards_[KNIGHT].setBoard(bitboard::DEFAULT_KNIGHT_STRUCTURE);
    pieceBitboards_[BISHOP].setBoard(bitboard::DEFAULT_BISHOP_STRUCTURE);
    pieceBitboards_[ROOK].setBoard(bitboard::DEFAULT_ROOK_STRUCTURE);
    pieceBitboards_[QUEEN].setBoard(bitboard::DEFAULT_QUEEN_STRUCTURE);
    pieceBitboards_[KING].setBoard(bitboard::DEFAULT_KING_STRUCTURE);

    // Initialize the 'whitePieces' and 'blackPieces' bitboards
    colorBitboards_[WHITE] = bitboard::DEFAULT_WHITE_OCCUPIED;
    colorBitboards_[BLACK] = bitboard::DEFAULT_BLACK_OCCUPIED;
}

const Bitboard & Chessboard::getBitboard(const PieceType piece) const
{
    return pieceBitboards_[piece];
}

const Bitboard & Chessboard::getBitboard(const Color color) const
{
    return colorBitboards_[color];
}

Bitboard Chessboard::getBitboard(const Color color, const PieceType piece) const
{
    return pieceBitboards_[piece] & colorBitboards_[color];
}

void Chessboard::movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare)
{
    // Update the piece bitboard
    pieceBitboards_[piece].clearBit(startingSquare);
    pieceBitboards_[piece].setBit(endingSquare);

    // Update the occupiedSquares bitboard corresponding to the specified color
    colorBitboards_[color].clearBit(startingSquare);
    colorBitboards_[color].setBit(endingSquare);
}

// void Chessboard::generateMoves()
// {
//     // loop over the bitboards
//     for (const auto & bitboard : pieceBitboards_)
//     {
//         // std::vector<Move> pawnMoves = getPawnMoves();
//         // std::vector<Move> knightMoves = getKnightMoves();
//         // std::vector<Move> bishopMoves = getBishopMoves();
//         // std::vector<Move> rookMoves = getRookMoves();
//         // std::vector<Move> queenMoves = getQueenMoves();
//         // std::vector<Move> kingMoves = getKingMoves();
//     }
// }

// std::vector<Move> getPawnMoves()
// {
//     std::vector<Move> moveVector;

//     Bitboard whitePawns = getBitboard(sideToMove_, PAWN);
//     int numberOfPawnsOnBoard = whitePawns.populationCount();
//     for (int i = 0; i < numberOfPawnsOnBoard; i++)
//     {
//         // popLSB() should return the index of the first bit it sees that is set to 1
//         int startingSquare = whitePawns.popLeastSignificantBitIndex();

//         // pawnAttackTable is an array of 64, 64-bit integers.
//         // pawnAttackTable[0] is the 64-bit integer representing the valid pawn moves for Square 0 (aka square A1).
//         // pawnAttackTable[1] is the 64-bit integer representing the valid pawn moves for Square 1 (aka square B1).
//         // ...
//         // pawnAttackTable[63] is the 64-bit integer representing the valid pawn moves for Square 63 (aka Square H8)
//         // Obviously there can be some effeciences here because a white pawn will never be on the 1st rank
//         // and the black pawns will never be on the 8th rank
//         // We also have to keep track of point of view. pawnAttackTable only works for a specific point of view.
//         // pawnAttackTable[8] (square A2 from white's POV) will say the pawn can go to square A3 or capture on B3 (if there's an opponent on B3).
//         // But this won't work if we're masking this against black pawns because a black pawn on square A2 can only go to A1 or capture on B1
//         // (if there's an opponent's piece).
//         Bitboard psuedoLegalPawnMoves = pawnAttackTable[startingSquare]

//         // Iterate over every psuedo legal pawn move, encode the move into an object, and append the move to the vector
//         int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.populationCount();
//         for (int i = 0; i < numberOfPsuedoLegalPawnMoves; i++)
//         {
//             ithTargetSquaure = psuedoLegalPawnMoves.popLeastSignificantBit();
//             Move m(COLOR, PIECE, startingSquare, ithTargetSquare);
//             moveVector.append(m);
//         }
//     }

//     return moveList;
// }