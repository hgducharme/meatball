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
    whiteOccupied_ = bitboard::DEFAULT_WHITE_OCCUPIED;
    blackOccupied_ = bitboard::DEFAULT_BLACK_OCCUPIED;

    // TODO: Initialize the occupiedSquares bitboard
    // occupiedSquares_ = bitboard::DEFAULT_WHITE_OCCUPIED | bitboard::DEFAULT_BLACK_OCCUPIED;
}

Bitboard & Chessboard::getBitboard(PieceType piece)
{
    return pieceBitboards_[piece];
}

Bitboard & Chessboard::getBitboard(Color color)
{
    if (color == WHITE)
    {
        return whiteOccupied_;
    }
    else
    {
        return blackOccupied_;
    }
}

// TODO: No idea why const works here. Remove it and we get an error.
const Bitboard & Chessboard::getBitboard(Color color, PieceType piece)
{
    Bitboard newBitboard = pieceBitboards_[piece].getBoard() & getBitboard(color).getBoard();
    return newBitboard;
}

void Chessboard::movePiece(Color color, PieceType piece, Square startingSquare, Square endingSquare)
{
    Bitboard bitboard = getBitboard(color, piece);
    bitboard.clearBit(startingSquare);
    bitboard.setBit(endingSquare);
}

void Chessboard::generateMoves()
{
    // loop over the bitboards
    for (const auto & bitboard : pieceBitboards_)
    {
        // std::vector<Move> pawnMoves = this->getPawnMoves();
        // std::vector<Move> knightMoves = this->getKnightMoves();
        // std::vector<Move> bishopMoves = this->getBishopMoves();
        // std::vector<Move> rookMoves = this->getRookMoves();
        // std::vector<Move> queenMoves = this->getQueenMoves();
        // std::vector<Move> kingMoves = this->getKingMoves();
    }
}