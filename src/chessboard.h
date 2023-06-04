#include "bitboard.h"
#include "types.h"

struct ChessBoard {
    Bitboard board[2][6];
    
    ChessBoard();
    Bitboard getPieceBitboard(Color color, PieceType piece);
    void movePiece(Color color, PieceType piece, Square startingSquare, Square endingSquare);
    /*
    movePiece(Color, Piece, a1, a2)
    */
};