#include "move.h"

Move::Move(const Color color, const PieceType pieceType, const Square start, const Square end)
{
    _encoded |= static_cast<uint32_t>(color) << COLOR_POSITION;
    _encoded |= static_cast<uint32_t>(pieceType) << PIECE_TYPE_POSITION;
    _encoded |= static_cast<uint32_t>(start) << START_SQUARE_POSITION;
    _encoded |= static_cast<uint32_t>(end) << END_SQUARE_POSITION;
}

Move::Move(const Color color, const PieceType pieceType, const Square start, const Square end, const uint8_t flags) : _flags(flags)
{
    _encoded |= static_cast<uint32_t>(color) << COLOR_POSITION;
    _encoded |= static_cast<uint32_t>(pieceType) << PIECE_TYPE_POSITION;
    _encoded |= static_cast<uint32_t>(start) << START_SQUARE_POSITION;
    _encoded |= static_cast<uint32_t>(end) << END_SQUARE_POSITION;
    _encoded |= static_cast<uint32_t>(flags) << 16;
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
    // TODO: This doesn't update _encoded
    
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

bool Move::isCheck() const
{

    return isFlagSet(Move::CHECK);
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
    return static_cast<Color>( (_encoded & COLOR_MASK) >> COLOR_POSITION );
}

PieceType Move::pieceType() const
{
    return static_cast<PieceType>( (_encoded & PIECE_TYPE_MASK) >> PIECE_TYPE_POSITION );
}

Square Move::startSquare() const
{
    return static_cast<Square>( (_encoded & START_SQUARE_MASK) >> START_SQUARE_POSITION );
}

Square Move::endSquare() const
{
    return static_cast<Square>( (_encoded & END_SQUARE_MASK) >> END_SQUARE_POSITION );
}

std::optional<CapturedPiece> Move::capturedPiece() const
{
    return _capturedPiece;
}

void Move::setCapturedPiece(const CapturedPiece p)
{
    _capturedPiece = p;
}

std::optional<CastleSide> Move::castleSide() const
{
    if (isKingsideCastle()) { return CastleSide::KINGSIDE; }
    if (isQueensideCastle()) { return CastleSide::QUEENSIDE; }

    return std::nullopt;
}

std::optional<PieceType> Move::promotionPiece() const
{
    return _promotionPiece;
}

void Move::setPromotionPiece(const PieceType pieceType)
{
    _promotionPiece = pieceType;
}