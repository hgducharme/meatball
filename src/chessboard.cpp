#include "chessboard.h"

#include "constants.h"

File Chessboard::squareToFile(const int square)
{
   /*
   Let n be the square's rank [0, 8]
   A file squares are multiples of 8
   B file squares are multiples of 8n + 1
   ...
   H file squares are multiples of 8n + 7
   Therefore, file = square % 8
   */
   return static_cast<File>(square % 8);
}

Rank Chessboard::squareToRank(const int square)
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
   return static_cast<Rank>(square/8);
}

Chessboard::Chessboard()
{
    // Initialize the bitboards for each piece type
    pieceBitboards_[PieceType::PAWN].setBoard(constants::DEFAULT_PAWN_STRUCTURE);
    pieceBitboards_[PieceType::KNIGHT].setBoard(constants::DEFAULT_KNIGHT_STRUCTURE);
    pieceBitboards_[PieceType::BISHOP].setBoard(constants::DEFAULT_BISHOP_STRUCTURE);
    pieceBitboards_[PieceType::ROOK].setBoard(constants::DEFAULT_ROOK_STRUCTURE);
    pieceBitboards_[PieceType::QUEEN].setBoard(constants::DEFAULT_QUEEN_STRUCTURE);
    pieceBitboards_[PieceType::KING].setBoard(constants::DEFAULT_KING_STRUCTURE);

    // Initialize the 'whitePieces' and 'blackPieces' bitboards
    colorBitboards_[Color::WHITE] = constants::DEFAULT_WHITE_OCCUPIED;
    colorBitboards_[Color::BLACK] = constants::DEFAULT_BLACK_OCCUPIED;
}

const Bitboard & Chessboard::getOccupiedSquares() const
{
    return getBitboard(Color::WHITE) | getBitboard(Color::BLACK);
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
    nonActivePlayer_ = activePlayer_;

    if (activePlayer_ == Color::WHITE) 
    {
        activePlayer_ = Color::BLACK;
    }
    else {
        activePlayer_ = Color::WHITE;
    }
}

Color Chessboard::getActivePlayer() const
{
    return activePlayer_;
}

Color Chessboard::getNonActivePlayer() const
{
    return nonActivePlayer_;
}