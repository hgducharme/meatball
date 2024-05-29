#pragma once

#include "bitboard.h"
#include "types.h"
#include "move.h"

#include <string>
#include <optional>

class Chessboard {
    private:
        Bitboard pieceBitboards_[PieceType::NUMBER_OF_PIECES];
        Bitboard colorBitboards_[Color::NUMBER_OF_COLORS];
        CastleRights castleRights[Color::NUMBER_OF_COLORS];
        Color activePlayer_ = Color::WHITE;
        Color nonActivePlayer_ = Color::BLACK;
        MoveVector moveHistory;
        Square enPassantSquare_ = Square::NO_SQUARE;
        int halfMoveClock_ = 0;
        int moveNumber_ = 0;

        /* We freeze the castle rights state before a move is applied in the event
         * that the move is later undone, then we can restore the castle rights after undoing the move. */
        CastleRights previousCastleRightsState;

    public:
        static File squareToFile(const int square);
        static Rank squareToRank(const int square);
        static Square coordinatesToSquare(const int rank, const int file);
        static const GameState parseFEN(const std::string & fen);
        static const GameState parsePiecePositions(const std::string & piecePositionsFEN);
        static Color parseActivePlayer(const std::string & colorFEN);
        static const std::pair<CastleRights, CastleRights> parseCastleRights(const std::string & castleRightsFEN);
        static Square parseEnPassantSquare(const std::string & enPassantSquareFEN);
        static int parseHalfMoveClock(const std::string & halfMoveClockFEN);
        static int parseMoveNumber(const std::string & moveNumberFEN);

        Chessboard();
        Chessboard(const std::string & fen);
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
        Square getEnPassantSquare() const;
        int getHalfMoveClock() const;
        int getMoveNumber() const;

        bool operator==(const Chessboard & other) const;

     private:
        void movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare);
        void addPiece(const Color color, const PieceType piece, const Square square);
        void removePiece(const Color color, const PieceType piece, const Square square);
        void raiseExceptionIfPieceIsNotOnSquare(const Color color, const PieceType piece, const Square square, const std::string & errorMessage);
        void updateCastleRights(const Move &move);
        void raiseExceptionIfSquareIsOccupied(const Square square, const std::string & errorMessage);
        void raiseExceptionIfMoveIsNotLastMove(const Move &move, const std::string &errorMessage) const;
        void raiseExceptionIfMoveHistoryIsEmpty(const std::string & errorMessage) const;
};

inline bool Chessboard::operator == (const Chessboard & other) const {
    // Check piece bitboards
    for (int i = 0; i < PieceType::NUMBER_OF_PIECES; ++i) {
        if (pieceBitboards_[i] != other.pieceBitboards_[i]) {
            return false;
        }
    }

    // Check color occupancy sets
    for (int i = 0; i < Color::NUMBER_OF_COLORS; ++i) {
        if (colorBitboards_[i] != other.colorBitboards_[i]) {
            return false;
        }
    }

    // Check castle rights
    for (int i = 0; i < Color::NUMBER_OF_COLORS; ++i) {
        if (castleRights[i] != other.castleRights[i]) {
            return false;
        }
    }

    // Check all other member variables
    if (activePlayer_ != other.activePlayer_ ||
        nonActivePlayer_ != other.nonActivePlayer_ ||
        moveHistory != other.moveHistory ||
        previousCastleRightsState != other.previousCastleRightsState ||
        enPassantSquare_ != other.enPassantSquare_ ||
        halfMoveClock_ != other.halfMoveClock_ ||
        moveNumber_ != other.moveNumber_)
    {
        return false;
    }

    return true;
}