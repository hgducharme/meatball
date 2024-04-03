#pragma once

#include "types.h"

struct Move
{
    Move(const Color c, const PieceType p, const Square start, const Square end);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush);
    Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isEnPessant);
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
    bool isPawnPromotion = false;
    bool isPawnDoublePush = false;
    bool isEnPessant = false;
};

inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.color == rhs.color) && (lhs.piece == rhs.piece) && (lhs.startSquare == rhs.startSquare) && (lhs.endSquare == rhs.endSquare);
}