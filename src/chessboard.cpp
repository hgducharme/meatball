#include "chessboard.h"

void ChessBoard::init()
{
    whitePawns.setBoard(bitboard::DEFAULT_WHITE_PAWN_STRUCTURE);
    whiteKnights.setBoard(bitboard::DEFAULT_WHITE_KNIGHT_STRUCTURE);
    whiteBishops.setBoard(bitboard::DEFAULT_WHITE_BISHOP_STRUCTURE);
    whiteRooks.setBoard(bitboard::DEFAULT_WHITE_ROOK_STRUCTURE);
    whiteQueen.setBoard(bitboard::DEFAULT_WHITE_QUEEN_STRUCTURE);
    whiteKing.setBoard(bitboard::DEFAULT_WHITE_KING_STRUCTURE);

    blackPawns.setBoard(bitboard::DEFAULT_BLACK_PAWN_STRUCTURE);
    blackKnights.setBoard(bitboard::DEFAULT_BLACK_KNIGHT_STRUCTURE);
    blackBishops.setBoard(bitboard::DEFAULT_BLACK_BISHOP_STRUCTURE);
    blackRooks.setBoard(bitboard::DEFAULT_BLACK_ROOK_STRUCTURE);
    blackQueen.setBoard(bitboard::DEFAULT_BLACK_QUEEN_STRUCTURE);
    blackKing.setBoard(bitboard::DEFAULT_BLACK_KING_STRUCTURE);
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