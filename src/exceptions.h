#pragma once

#include <stdexcept>

namespace exceptions
{

   class MoveNotFound : public std::runtime_error
   {
      public:
         MoveNotFound() : std::runtime_error("This move does not exist in the move history.") { }
   };

}