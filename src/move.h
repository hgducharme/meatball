#include "types.h"

struct Move
{
    Move(Color c, PieceType p, Square start, Square end);
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
};