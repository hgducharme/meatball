#pragma once

#include "types.h"

#include <vector>

struct Node {
   Color currentPlayer;
   bool endsGame;
   std::vector<Node> children;
};