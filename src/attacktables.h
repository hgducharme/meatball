#pragma once

#include "types.h"
#include "constants.h"
#include "bitboard.h"
#include "chessboard.h"

namespace attack_tables
{
    // We also have to keep track of point of view. pawnAttackTable only works for a specific point of view (the side to move POV).
    // pawnAttackTable[8] (square A2 from white's POV) will say the pawn can go to square A3 or capture on B3 (if there's an opponent on B3).
    // But this won't work if we're masking this against black pawns because a black pawn on square A2 can only go to A1 or capture on B1
    // (if there's an opponent's piece).

    // The valid pawn moves for each square on the chessboard, represented in the sideToMove reference frame
    extern Bitboard pawn[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];

    // The valid knight moves for each square on the chessboard, represented in the sideToMove reference frame
    extern Bitboard knight[Color::NUMBER_OF_COLORS][Square::NUMBER_OF_SQUARES];
    void init();
    void initializePawnAttackTable();
}