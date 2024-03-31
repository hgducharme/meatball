#pragma once

#include "types.h"

struct Move
{
    Move(Color c, PieceType p, Square start, Square end);
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
};

inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.color == rhs.color) && (lhs.piece == rhs.piece) && (lhs.startSquare == rhs.startSquare) && (lhs.endSquare == rhs.endSquare);
}