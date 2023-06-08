#include "bitboard.h"
#include "types.h"

struct Chessboard {
    private:
        Bitboard pieceBitboards_[NUMBER_OF_PIECES];
        Bitboard colorBitboards_[NUMBER_OF_COLORS];
        Color sideToMove_ = WHITE;

    public:
        Chessboard();
        const Bitboard & getOccupiedSquares();
        const Bitboard & getBitboard(const PieceType piece) const;
        const Bitboard & getBitboard(const Color color) const;
        const Bitboard & getBitboard(const Color color, const PieceType piece) const;
        void movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void generateMoves();
};