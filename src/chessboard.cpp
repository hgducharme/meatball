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
    whiteOccupied_ = bitboard::DEFAULT_WHITE_OCCUPIED;
    blackOccupied_ = bitboard::DEFAULT_BLACK_OCCUPIED;
}

const Bitboard & Chessboard::getBitboard(const PieceType piece) const
{
    return pieceBitboards_[piece];
}

const Bitboard & Chessboard::getBitboard(const Color color) const
{
    if (color == WHITE)
    {
        return whiteOccupied_;
    }
    else
    {
        return blackOccupied_;
    }
}

const Bitboard & Chessboard::getBitboard(const Color color, const PieceType piece) const
{
    u64 bitwiseANDResult = pieceBitboards_[piece].getBoard() & getBitboard(color).getBoard();
    Bitboard b(bitwiseANDResult);
    return b;
}

void Chessboard::movePiece(const Color color, const PieceType piece, const Square startingSquare, const Square endingSquare)
{
    // Update the piece bitboard
    pieceBitboards_[piece].clearBit(startingSquare);
    pieceBitboards_[piece].setBit(endingSquare);

    // Update the occupiedSquares bitboard corresponding to the specified color
    switch (color)
    {
        case WHITE:
        {
            whiteOccupied_.clearBit(startingSquare);
            whiteOccupied_.setBit(endingSquare);
            break;
        }
        case BLACK:
        {
            blackOccupied_.clearBit(startingSquare);
            blackOccupied_.setBit(endingSquare);
            break;
        }
        case NUMBER_OF_COLORS: { break; }
    }

}

void Chessboard::generateMoves()
{
    // loop over the bitboards
    for (const auto & bitboard : pieceBitboards_)
    {
        // std::vector<Move> pawnMoves = this->getPawnMoves();
        // std::vector<Move> knightMoves = this->getKnightMoves();
        // std::vector<Move> bishopMoves = this->getBishopMoves();
        // std::vector<Move> rookMoves = this->getRookMoves();
        // std::vector<Move> queenMoves = this->getQueenMoves();
        // std::vector<Move> kingMoves = this->getKingMoves();
    }
}