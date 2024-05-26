#include "move.h"

Move::Move(const Color c, const PieceType p, const Square start, const Square end) : 
    color(c), piece(p), startSquare(start), endSquare(end)
    {}

Move::Move(const Color c, const PieceType p, const Square start, const Square end, const bool isPawnPromotion, const bool isPawnDoublePush, const bool isCastle, const bool isEnPassant, const bool isCapture, const CapturedPiece capturedPiece) :
    color(c), piece(p), startSquare(start), endSquare(end), isPawnPromotion(isPawnPromotion), isPawnDoublePush(isPawnDoublePush), isCastle(isCastle), isEnPassant(isEnPassant), isCapture(isCapture), capturedPiece(capturedPiece)
    {}