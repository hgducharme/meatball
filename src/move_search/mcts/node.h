#pragma once

#include "types.h"

#include <vector>

struct Node {
   Node() = default;
   Color currentPlayer;
   bool endsGame = false;
   std::vector<Node> children;
};