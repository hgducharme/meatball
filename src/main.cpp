#include "bitboard.h"
#include "chessboard.h"

#include <iostream>

int main ()
{
  ChessBoard chessboard;
  std::cout << chessboard.getPieceBitboard(WHITE, PAWN).getBoard() << std::endl;

  // chessboard.setState(FEN);
  // chessboard.generateMoves();

  return 0;
}