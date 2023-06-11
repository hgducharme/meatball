#pragma once

#include "bitboard.h"
#include "types.h"
#include "constants.h"

class Chessboard {
    private:
        Bitboard pieceBitboards_[NUMBER_OF_PIECES];
        Bitboard colorBitboards_[NUMBER_OF_COLORS];
        Color sideToMove_ = WHITE;

    public:
        File static squareToFile(Square s);
        Rank static squareToRank(Square s);

        Chessboard();
        const Bitboard & getOccupiedSquares();
        const Bitboard & getBitboard(const PieceType piece) const;
        const Bitboard & getBitboard(const Color color) const;
        Bitboard getBitboard(const Color color, const PieceType piece) const;
        void movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        Color getSideToMove() const;
};