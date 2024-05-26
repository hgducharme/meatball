#pragma once

#include "types.h"

#include <optional>

struct Move
{
    Move(const Color c, const PieceType p, const Square start, const Square end);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isCastle, const bool isEnPassant, const bool isCapture, const CapturedPiece capturedPiece);
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
    bool isPawnPromotion = false;
    bool isPawnDoublePush = false;
    bool isCastle = false;

    /* Whether or not this move is an en passant capture. This flag, instead of the 'isCapture' flag, should be used for en passant captures */
    bool isEnPassant = false;

    /* Whether or not this move captures a piece. If this move is an en passant capture, this flag should NOT be used! */
    bool isCapture = false;

    std::optional<CapturedPiece> capturedPiece;
};

// TODO: This doesn't account for flags.
inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.color == rhs.color) && (lhs.piece == rhs.piece) && (lhs.startSquare == rhs.startSquare) && (lhs.endSquare == rhs.endSquare);
}