#pragma once

#include "types.h"

#include <optional>
#include <vector>

// TODO: merge _flags into _encoded. It's redundant to keep both.

namespace
{
    /* The starting bit for each piece of information. */
    constexpr int COLOR_POSITION = 0;
    constexpr int PIECE_TYPE_POSITION = 1;
    constexpr int START_SQUARE_POSITION = 4;
    constexpr int END_SQUARE_POSITION = 10;

    /* Bitmasks that will extract the desired information from the encoded move. */
    constexpr uint32_t COLOR_MASK = 0b1;
    constexpr uint32_t PIECE_TYPE_MASK = 0b1110;
    constexpr uint32_t START_SQUARE_MASK = 0b1111110000;
    constexpr uint32_t END_SQUARE_MASK = 0b1111110000000000;
}

class Move
{
    private:
        /* An integer that is packed with all the information about the move. */
        uint32_t _encoded = 0;
        uint8_t _flags = 0;
        std::optional<CapturedPiece> _capturedPiece;
        std::optional<PieceType> _promotionPiece;

    public:
        /* Flags to indicate what type of move this is. For en passant captures, only the en passant flag should be used, NOT the capture flag. */
        enum Type : uint8_t
        {
            CAPTURE =          0b000001,
            PROMOTION =        0b000010,
            PAWN_DOUBLE_PUSH = 0b000100,
            EN_PASSANT =       0b001000,
            KINGSIDE_CASTLE =  0b010000,
            QUEENSIDE_CASTLE = 0b100000,
            CHECK =            0b1000000,
        };

        Move(const Color c, const PieceType p, const Square start, const Square end);
        Move(const Color c, const PieceType p, const Square start, const Square end, const uint8_t flags);

        uint8_t getFlags() const;
        bool isFlagSet(const Move::Type moveFlag) const;
        void setFlag(const Move::Type flag);
        void setFlags(const uint8_t flags);
        uint32_t getEncoded() const;
        bool isCapture() const;
        bool isPromotion() const;
        bool isPawnDoublePush() const;
        bool isEnPassant() const;
        bool isKingsideCastle() const;
        bool isQueensideCastle() const;
        bool isCastle() const;
        bool isCheck() const;
        Color color() const;
        PieceType pieceType() const;
        Square startSquare() const;
        Square endSquare() const;
        std::optional<CastleSide> castleSide() const;
        std::optional<CapturedPiece> capturedPiece() const;
        void setCapturedPiece(const CapturedPiece p);
        std::optional<PieceType> promotionPiece() const;
        void setPromotionPiece(const PieceType pieceType);
};

inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.getEncoded() == rhs.getEncoded());
}

using MoveVector = std::vector<Move>;