#include "bitboard.h"
#include "types.h"

struct Chessboard {
    private:
        Bitboard pieceBitboards_[NUMBER_OF_PIECES];
        Bitboard whiteOccupied_;
        Bitboard blackOccupied_;
        Color sideToMove_ = WHITE;

    public:
        Chessboard();
        const Bitboard & getOccupiedSquares();
        Bitboard & getBitboard(PieceType piece);
        Bitboard & getBitboard(Color color);
        const Bitboard & getBitboard(Color color, PieceType piece);
        void movePiece(Color color, PieceType piece, Square startingSquare, Square endingSquare);
        void generateMoves();
};