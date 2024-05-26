#include "move.h"

Move::Move(const Color c, const PieceType p, const Square start, const Square end)
{
    _encoded = static_cast<uint32_t>(c) << 0 | static_cast<uint32_t>(p) << 1 | static_cast<uint32_t>(start) << 4 | static_cast<uint32_t>(end) << 10;
}

Move::Move(const Color c, const PieceType p, const Square start, const Square end, const uint8_t flags) : _flags(flags)
{
    _encoded = static_cast<uint32_t>(c) << 0 | static_cast<uint32_t>(p) << 1 | static_cast<uint32_t>(start) << 4 | static_cast<uint32_t>(end) << 10 | static_cast<uint32_t>(flags) << 16;
}

uint32_t Move::getEncoded() const
{
    return _encoded;
}

uint8_t Move::getFlags() const
{
    return _flags;
}

void Move::setFlag(const Move::Type flag)
{
    _flags |= flag;
}

void Move::setFlags(const uint8_t flags)
{
    _flags = flags;
}

bool Move::isCapture() const
{

    return isFlagSet(Move::CAPTURE);
}

bool Move::isFlagSet(const Move::Type moveFlag) const
{
    return static_cast<bool>(_flags & moveFlag);
}

bool Move::isPromotion() const
{
    return isFlagSet(Move::PROMOTION);
}

bool Move::isPawnDoublePush() const
{
    return isFlagSet(Move::PAWN_DOUBLE_PUSH);
}

bool Move::isEnPassant() const
{
    return isFlagSet(Move::EN_PASSANT);
}

bool Move::isKingsideCastle() const
{
    return isFlagSet(Move::KINGSIDE_CASTLE);
}

bool Move::isQueensideCastle() const
{
    return isFlagSet(Move::QUEENSIDE_CASTLE);
}

bool Move::isCastle() const
{
    return isFlagSet(Move::KINGSIDE_CASTLE) || isFlagSet(Move::QUEENSIDE_CASTLE);
}

Color Move::color() const
{
    return static_cast<Color>(_encoded & EncodingMasks::COLOR);
}

PieceType Move::pieceType() const
{
    return static_cast<PieceType>( (_encoded & EncodingMasks::PIECE_TYPE) >> 1 );
}

Square Move::startSquare() const
{
    return static_cast<Square>( (_encoded & EncodingMasks::START_SQUARE) >> 4 );
}

Square Move::endSquare() const
{
    return static_cast<Square>( (_encoded & EncodingMasks::END_SQUARE) >> 10 );
}

std::optional<CapturedPiece> Move::capturedPiece() const
{
    return _capturedPiece;
}

void Move::setCapturedPiece(const CapturedPiece p)
{
    _capturedPiece = p;
}