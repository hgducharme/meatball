#include "types.h"

struct Move
{
    Color color;
    PieceType piece;
    Square startSquare;
    Square endSquare;
};