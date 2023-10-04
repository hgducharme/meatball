#pragma once

#include "bitboard.h"
#include "magicbitboard.h"
#include "chessboard.h"

namespace attack_tables
{
    
    extern Bitboard PAWN_ATTACKS[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
    extern Bitboard KNIGHT_ATTACKS[Square::NUMBER_OF_SQUARES];
    extern Bitboard BISHOP_ATTACKS[Square::NUMBER_OF_SQUARES][magic_bitboards::LARGEST_AMOUNT_OF_BISHOP_BLOCKER_CONFIGURATIONS];
    extern Bitboard ROOK_ATTACKS[Square::NUMBER_OF_SQUARES][magic_bitboards::LARGEST_AMOUNT_OF_ROOK_BLOCKER_CONFIGURATIONS];
    extern Bitboard KING_ATTACKS[Square::NUMBER_OF_SQUARES];

    void init();

    // TODO: These automatically assume the color to get the attacks for. We should make this agnostic
    Bitboard getAttacks(const PieceType pieceType, const Square square, const Chessboard & gameState);
    Bitboard getLeaperPieceAttacks(const LeaperPiece leaperPiece, const Square square, const Color activePlayer);
    Bitboard getSliderPieceAttacks(const SliderPiece sliderPiece, const Square square, const Bitboard & boardState);

namespace
{

    void initializeAttacksForLeaperPieces();
    Bitboard calculatePawnAttacksFromSquare(const Color color, const Bitboard & bitboard);
    Bitboard calculateKnightAttacksFromSquare(const Bitboard & bitboard);
    Bitboard calculateBishopAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateRookAttacksFromSquareClassical(const Bitboard & bitboard);
    Bitboard calculateKingAttacksFromSquare(const Bitboard & bitboard);
    void initializeAttacksForSliderPieces();

} // anonymous namespace

} // attack_tables namespace