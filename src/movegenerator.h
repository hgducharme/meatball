#include "chessboard.h"
#include "move.h"
#include "attacktables.h"

#include <vector>

class MoveGenerator
{
    MoveGenerator() = default;
    std::vector<Move> generatePsuedoLegalMoves(const Chessboard & chessboard);
    std::vector<Move> generatePawnMoves(const Chessboard & chessboard);
};