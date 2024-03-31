#pragma once

#include <stdexcept>

namespace exceptions
{

   class UndoMoveError : public std::runtime_error
   {
      public:
         UndoMoveError() : std::runtime_error("The requested move can not be undone. Only the last move to be made can be undone.") { }
   };

}