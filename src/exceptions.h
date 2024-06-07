#pragma once

#include <stdexcept>
#include <string>

namespace exceptions
{
   namespace chessboard
   {
      class UndoMoveError : public std::runtime_error
      {
         public:
            explicit UndoMoveError(const std::string & message) : std::runtime_error(message) {};
      };

      class MoveHistoryIsEmpty : public std::runtime_error
      {
         public:
            explicit MoveHistoryIsEmpty(const std::string & message) : std::runtime_error(message) {};
      };

      class SquareAlreadyOccupied : public std::runtime_error
      {
         public:
            explicit SquareAlreadyOccupied(const std::string & message) : std::runtime_error(message) {};
      };

      class InvalidMove : public std::runtime_error
      {
         public:
            explicit InvalidMove(const std::string & message) : std::runtime_error(message) {};
      };
   } // end chessboard namespace

   namespace fen
   {
      class InvalidFEN : public std::runtime_error
      {
         public:
            explicit InvalidFEN(const std::string & message) : std::runtime_error(message) {};
      };

   } // end fen namespace
}