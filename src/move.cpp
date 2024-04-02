#include "move.h"

Move::Move(Color c, PieceType p, Square start, Square end, bool isPawnPromotion) : 
    color(c), piece(p), startSquare(start), endSquare(end), isPawnPromotion(isPawnPromotion)
    {}