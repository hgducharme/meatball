#pragma once

#include "types.h"

#include <optional>

struct Move
{
    Move(const Color c, const PieceType p, const Square start, const Square end);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isEnPassant, const bool isCapture);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isEnPassant, const bool isCapture, const Piece capturedPiece);
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
    bool isPawnPromotion = false;
    bool isPawnDoublePush = false;
    bool isEnPassant = false;
    bool isCapture = false;
    std::optional<Piece> capturedPiece;
};

// TODO: This doesn't account for flags.
inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.color == rhs.color) && (lhs.piece == rhs.piece) && (lhs.startSquare == rhs.startSquare) && (lhs.endSquare == rhs.endSquare);
}