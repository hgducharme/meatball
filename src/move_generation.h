#pragma once

#include "chessboard.h"

namespace move_generation
{
   MoveVector generateLegalMoves(const Chessboard & gameState);
}