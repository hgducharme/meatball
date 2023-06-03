#include "chessboard.h"

void ChessBoard::init()
{
    board[WHITE][0].setBoard(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
    board[WHITE][1].setBoard(bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
    board[WHITE][2].setBoard(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
    board[WHITE][3].setBoard(bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
    board[WHITE][4].setBoard(bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
    board[WHITE][5].setBoard(bitboard::DEFAULT_WHITE_KING_STRUCTURE);

    board[BLACK][0].setBoard(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
    board[BLACK][1].setBoard(bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
    board[BLACK][2].setBoard(bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
    board[BLACK][3].setBoard(bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
    board[BLACK][4].setBoard(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
    board[BLACK][5].setBoard(bitboard::DEFAULT_BLACK_KING_STRUCTURE);
}

Bitboard ChessBoard::getPieceBitboard(Color color, PieceType piece)
{
    return board[color][piece];
}