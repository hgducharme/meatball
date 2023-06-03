#include "chessboard.h"

void ChessBoard::init()
{
    board[0][0].setBoard(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
    board[0][1].setBoard(bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
    board[0][2].setBoard(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
    board[0][3].setBoard(bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
    board[0][4].setBoard(bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
    board[0][5].setBoard(bitboard::DEFAULT_WHITE_KING_STRUCTURE);

    board[1][0].setBoard(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
    board[1][1].setBoard(bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
    board[1][2].setBoard(bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
    board[1][3].setBoard(bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
    board[1][4].setBoard(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
    board[1][5].setBoard(bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

Bitboard ChessBoard::getPieceBitboard(Color color, PieceType piece)
{
    return board[color][piece];
}