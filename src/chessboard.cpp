#include "chessboard.h"

void ChessBoard::init()
{
    // board[0][1].setBoard(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
}

Bitboard ChessBoard::getPieceBitboard(Color color, Piece piece)
{
    /*
    Find a rule to map:
    bb[0][0] = white pawns
    bb[0][1] = white knights
    bb[0][2] = white bishops
    bb[0][3] = white rooks
    
    ...

    bb[1][0] = black pawns
    bb[1][1] = black knights

    ...
    */

    // return
}