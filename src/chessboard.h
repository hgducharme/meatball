#include "bitboard.h"
#include "types.h"

struct ChessBoard {
    Bitboard board[2][6];
    
    ChessBoard();
    Bitboard getPieceBitboard(Color color, PieceType piece);
};