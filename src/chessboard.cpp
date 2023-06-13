#include "chessboard.h"

File Chessboard::squareToFile(Square s)
{
   /*
   Let n be the square's rank [0, 8]
   A file squares are multiples of 8
   B file squares are multiples of 8n + 1
   ...
   H file squares are multiples of 8n + 7
   Therefore, file = square % 8
   */
   return static_cast<File>(static_cast<int>(s) % 8);
}

Rank Chessboard::squareToRank(Square s)
{
   /*
   Let n be the square's file [0, 8]
   Rank 0 squares are in the range [0, 7] (less than 8*1)
   Rank 1 squares are in the range [8, 15] (between 8*1 and 8*2)
   ...
   Rank 8 squares are in the range [56, 63] (between 8*7 and 8*8)
   Therefore, rank = floor(square / 8)
   Since integer division in C++ truncates towards zero, (square / 8) will produce the same result.
   */
   return static_cast<Rank>( (static_cast<int>(s) / 8) );
}

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

void Chessboard::applyMove(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare)
{
    if (color != activePlayer_) { return; }

    // Update the piece bitboard
    pieceBitboards_[piece].clearBit(startingSquare);
    pieceBitboards_[piece].setBit(endingSquare);

    // Update the color bitboard
    colorBitboards_[color].clearBit(startingSquare);
    colorBitboards_[color].setBit(endingSquare);

    toggleActivePlayer();
}

void Chessboard::applyMove(const Move & move)
{
    applyMove(move.color, move.piece, move.startSquare, move.endSquare);
}

void Chessboard::toggleActivePlayer()
{
    if (activePlayer_ == WHITE) 
    {
        activePlayer_ = BLACK;
    }
    else {
        activePlayer_ = WHITE;
    }
}

Color Chessboard::getActivePlayer() const
{
    return activePlayer_;
}