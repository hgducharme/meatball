#pragma once

#include "bitboard.h"
#include "types.h"
#include "move.h"

#include <vector>
#include <string>

class Chessboard {
    private:
        Bitboard pieceBitboards_[PieceType::NUMBER_OF_PIECES];
        Bitboard colorBitboards_[Color::NUMBER_OF_COLORS];
        Color activePlayer_ = Color::WHITE;
        Color nonActivePlayer_ = Color::BLACK;
        std::vector<Move> moveHistory;

    public:
        File static squareToFile(const int square);
        Rank static squareToRank(const int square);

        Chessboard();
        const Bitboard getOccupiedSquares() const;
        const Bitboard & getBitboard(const PieceType piece) const;
        const Bitboard & getBitboard(const Color color) const;
        Bitboard getBitboard(const Color color, const PieceType piece) const;
        void applyMove(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void applyMove(const Move & move);
        void toggleActivePlayer();
        Color getActivePlayer() const;
        Color getNonActivePlayer() const;
        void undoMove(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void undoMove(const Move & move);

     private:
        void updateBitboards(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void raiseExceptionIfMoveIsNotLastMove(const Move & move, const std::string & errorMessage) const;
        void raiseExceptionIfMoveHistoryIsEmpty(const std::string & errorMessage) const;
};