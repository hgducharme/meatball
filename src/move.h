#pragma once

#include "types.h"

#include <optional>

namespace
{
    /* The positions of the information that is packed into the encoded move member variable. */
    enum EncodingMasks
    {
        COLOR = 0b1,
        PIECE_TYPE = 0b1110,
        START_SQUARE = 0b1111110000,
        END_SQUARE = 0b1111110000000000,
    };
}

class Move
{
    private:
        /* An integer that is packed with all the information about the move. */
        uint32_t _encoded = 0;
        uint8_t _flags = 0;
        std::optional<CapturedPiece> _capturedPiece;

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
        std::optional<CapturedPiece> capturedPiece() const;
        void setCapturedPiece(const CapturedPiece p);

        Color color() const;
        PieceType pieceType() const;
        Square startSquare() const;
        Square endSquare() const;
};

inline bool operator == (const Move & lhs, const Move & rhs)
{
    return (lhs.getEncoded() == rhs.getEncoded());}