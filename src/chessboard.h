#include "bitboard.h"
#include "types.h"

struct ChessBoard {
    Bitboard board[2][6];
    
    void init();
    Bitboard getPieceBitboard(Color color, PieceType piece);
};