#include "chessboard.h"

Chessboard::Chessboard()
{
    // Initialize the bitboards for each piece of each color
    board_[WHITE][PAWN].setBoard(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
    board_[WHITE][KNIGHT].setBoard(bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
    board_[WHITE][BISHOP].setBoard(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
    board_[WHITE][ROOK].setBoard(bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
    board_[WHITE][QUEEN].setBoard(bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
    board_[WHITE][KING].setBoard(bitboard::DEFAULT_WHITE_KING_STRUCTURE);
    board_[BLACK][PAWN].setBoard(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
    board_[BLACK][KNIGHT].setBoard(bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
    board_[BLACK][BISHOP].setBoard(bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
    board_[BLACK][ROOK].setBoard(bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
    board_[BLACK][QUEEN].setBoard(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
    board_[BLACK][KING].setBoard(bitboard::DEFAULT_BLACK_KING_STRUCTURE);

    // Initialize the 'whitePieces' and 'blackPieces' bitboards
    whiteOccupied_ = bitboard::DEFAULT_WHITE_OCCUPIED;
    blackOccupied_ = bitboard::DEFAULT_BLACK_OCCUPIED;

    // Initialize the occupiedSquares bitboard
    occupiedSquares_ = bitboard::DEFAULT_WHITE_OCCUPIED | bitboard::DEFAULT_BLACK_OCCUPIED;
}

Bitboard & Chessboard::getPieceBitboard(Color color, PieceType piece)
{
    return board_[color][piece];
}

Bitboard & Chessboard::getColorBitboard(Color color)
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

void Chessboard::movePiece(Color color, PieceType piece, Square startingSquare, Square endingSquare)
{
    board_[color][piece].clearBit(startingSquare);
    board_[color][piece].setBit(endingSquare);
}

void Chessboard::generateMoves()
{
    // loop over the colors
    for (const auto & bitboardArray : board_)
    {
        // loop over each piece's bitboard
        for (const auto & bitboard : bitboardArray)
        {
            // std::cout << bitboard.getBoard() << std::endl;
        }
    }
}