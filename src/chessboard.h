#include "bitboard.h"
#include "types.h"

struct ChessBoard {
    Bitboard board[12];
    
    void init();
    Bitboard getPieceBitboard(Color color, Piece piece);
};