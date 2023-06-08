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
    for (int color = 0; color < static_cast<int>(sizeof(board_)/sizeof(board_[0])); color++)
    {
        for (int piece = 0; piece < static_cast<int>(sizeof(board_[color])/sizeof(board_[color][0])); piece++)
        {
            if (color == WHITE)
            {
                whiteOccupied_ |= board_[color][piece];
            }
            if (color == BLACK)
            { 
                blackOccupied_ |= board_[color][piece];
            }
        }
    }

    // Initialize the occupiedSquares bitboard
    occupiedSquares_ = whiteOccupied_ | blackOccupied_;
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