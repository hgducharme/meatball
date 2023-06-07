#include "bitboard.h"
#include "types.h"

struct Chessboard {
    private:
        Bitboard board_[2][6];
        Bitboard whiteOccupied_;
        Bitboard blackOccupied_;
        Bitboard occupiedSquares_;
        Color sideToMove_ = WHITE;

    public:
        Chessboard();
        const Bitboard & getOccupiedSquares() const { return occupiedSquares_; }
        Bitboard & getPieceBitboard(Color color, PieceType piece);
        Bitboard & getColorBitboard(Color color);
        void movePiece(Color color, PieceType piece, Square startingSquare, Square endingSquare);
        void generateMoves();
};