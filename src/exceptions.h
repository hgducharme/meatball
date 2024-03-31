#pragma once

#include <stdexcept>
#include <string>

namespace exceptions
{

   class UndoMoveError : public std::runtime_error
   {
      public:
         explicit UndoMoveError(const std::string & message) : std::runtime_error(message) {};
   };
}