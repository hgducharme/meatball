#include "bitboard.h"
#include "chessboard.h"

#include <iostream>

int main ()
{
  ChessBoard chessboard;
  std::cout << chessboard.getPieceBitboard(Color::WHITE, Piece::PAWN).getBoard() << std::endl;

  return 0;
}