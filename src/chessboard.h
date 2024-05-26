#pragma once

#include "bitboard.h"
#include "types.h"
#include "move.h"

#include <vector>
#include <string>
#include <optional>

class Chessboard {
    private:
        Bitboard pieceBitboards_[PieceType::NUMBER_OF_PIECES];
        Bitboard colorBitboards_[Color::NUMBER_OF_COLORS];
        CastleRights castleRights[Color::NUMBER_OF_COLORS];
        Color activePlayer_ = Color::WHITE;
        Color nonActivePlayer_ = Color::BLACK;
        std::vector<Move> moveHistory;

        /* We freeze the castle rights state before a move is applied in the event
         * that the move is later undone, then we can restore the castle rights after undoing the move. */
        CastleRights previousCastleRightsState;

    public:
        File static squareToFile(const int square);
        Rank static squareToRank(const int square);

        Chessboard();
        const Bitboard getOccupiedSquares() const;
        const Bitboard & getBitboard(const PieceType piece) const;
        const Bitboard & getBitboard(const Color color) const;
        Bitboard getBitboard(const Color color, const PieceType piece) const;
        void applyMove(const Move & move);
        void toggleActivePlayer();
        Color getActivePlayer() const;
        Color getNonActivePlayer() const;
        void undoMove(const Move & move);
        const std::optional<const Move> getLastMove() const;
        CastleRights getCastleRights(const Color color) const;
        std::optional<Piece> getPieceAt(const Square square) const;
        bool squareIsOccupied(const Square square);

        bool operator==(const Chessboard & other) const;

     private:
        void movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void addPiece(const Color color, const PieceType piece, const Square square);
        void removePiece(const Color color, const PieceType piece, const Square square);
        void updateCastleRights(const Move &move);
        void raiseExceptionIfSquareIsOccupied(const Square square);
        void raiseExceptionIfMoveIsNotLastMove(const Move &move, const std::string &errorMessage) const;
        void raiseExceptionIfMoveHistoryIsEmpty(const std::string & errorMessage) const;
};

inline bool Chessboard::operator == (const Chessboard & other) const {
    for (int i = 0; i < PieceType::NUMBER_OF_PIECES; ++i) {
        if (pieceBitboards_[i] != other.pieceBitboards_[i]) {
            return false;
        }
    }

    for (int i = 0; i < Color::NUMBER_OF_COLORS; ++i) {
        if (colorBitboards_[i] != other.colorBitboards_[i] ||
            castleRights[i] != other.castleRights[i]) {
            return false;
        }
    }

    if (activePlayer_ != other.activePlayer_ ||
        nonActivePlayer_ != other.nonActivePlayer_ ||
        moveHistory != other.moveHistory ||
        previousCastleRightsState != other.previousCastleRightsState)
    {
        return false;
    }

    return true;
}