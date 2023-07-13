#include "bitboard.h"
#include "chessboard.h"

#include <iostream>

int main ()
{
  Chessboard chessboard;
  std::cout << chessboard.getBitboard(WHITE, PAWN).getBoard() << std::endl;

  // chessboard.setState(FEN);
  // chessboard.generateMoves();

  return 0;
}