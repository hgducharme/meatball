#include "move.h"

Move::Move(const Color c, const PieceType p, const Square start, const Square end) : 
    color(c), piece(p), startSquare(start), endSquare(end)
    {}
    
Move::Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion) : 
    color(c), piece(p), startSquare(start), endSquare(end), isPawnPromotion(isPawnPromotion)
    {}

Move::Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush) : 
    color(c), piece(p), startSquare(start), endSquare(end), isPawnPromotion(isPawnPromotion), isPawnDoublePush(isPawnDoublePush)
    {}

Move::Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isEnPessant) :
    color(c), piece(p), startSquare(start), endSquare(end), isPawnPromotion(isPawnPromotion), isPawnDoublePush(isPawnDoublePush), isEnPessant(isEnPessant)
    {}