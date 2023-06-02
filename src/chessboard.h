#include "bitboard.h"
#include "types.h"

struct ChessBoard {
    Bitboard whitePawns;
    Bitboard whiteKnights;
    Bitboard whiteBishops;
    Bitboard whiteRooks;
    Bitboard whiteQueen;
    Bitboard whiteKing;
    Bitboard blackPawns;
    Bitboard blackKnights;
    Bitboard blackBishops;
    Bitboard blackRooks;
    Bitboard blackQueen;
    Bitboard blackKing;

    void init();
    Bitboard getPieceBitboard(Color color, Piece piece);
};