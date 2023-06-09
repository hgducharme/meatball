#include "chessboard.h"

Chessboard::Chessboard()
{
    // Initialize the bitboards for each piece type
    pieceBitboards_[PAWN].setBoard(bitboard::DEFAULT_PAWN_STRUCTURE);
    pieceBitboards_[KNIGHT].setBoard(bitboard::DEFAULT_KNIGHT_STRUCTURE);
    pieceBitboards_[BISHOP].setBoard(bitboard::DEFAULT_BISHOP_STRUCTURE);
    pieceBitboards_[ROOK].setBoard(bitboard::DEFAULT_ROOK_STRUCTURE);
    pieceBitboards_[QUEEN].setBoard(bitboard::DEFAULT_QUEEN_STRUCTURE);
    pieceBitboards_[KING].setBoard(bitboard::DEFAULT_KING_STRUCTURE);

    // Initialize the 'whitePieces' and 'blackPieces' bitboards
    colorBitboards_[WHITE] = bitboard::DEFAULT_WHITE_OCCUPIED;
    colorBitboards_[BLACK] = bitboard::DEFAULT_BLACK_OCCUPIED;
}

const Bitboard & Chessboard::getBitboard(const PieceType piece) const
{
    return pieceBitboards_[piece];
}

const Bitboard & Chessboard::getBitboard(const Color color) const
{
    return colorBitboards_[color];
}

Bitboard Chessboard::getBitboard(const Color color, const PieceType piece) const
{
    return pieceBitboards_[piece] & colorBitboards_[color];
}

void Chessboard::movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare)
{
    if (color != sideToMove_) { return; }

    // Update the piece bitboard
    pieceBitboards_[piece].clearBit(startingSquare);
    pieceBitboards_[piece].setBit(endingSquare);

    // Update the occupiedSquares bitboard corresponding to the specified color
    colorBitboards_[color].clearBit(startingSquare);
    colorBitboards_[color].setBit(endingSquare);

    // Toggle side to move variable
    if (color == WHITE) 
    {
        sideToMove_ = BLACK;
    }
    else {
        sideToMove_ = WHITE;
    }
}

Color Chessboard::getSideToMove() const
{
    return sideToMove_;
}