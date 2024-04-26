#pragma once

#include "chessboard.h"

#include <vector>

using MoveVector = std::vector<Move>;

class MoveGenerator
{
   public:
      virtual MoveVector generateLegalMoves(const Chessboard & gameState) = 0;
};

class LegalMoveGenerator : public MoveGenerator
{
   public:
      LegalMoveGenerator() = default;
      MoveVector generateLegalMoves(const Chessboard & gameState) override;

   private:
      MoveVector generatePsuedoLegalMoves(const Chessboard & gameState) const;
      MoveVector getMovesByPiece(const PieceType pieceType, const Chessboard &gameState) const;
      Bitboard getPawnPushes(const Color activePlayer, const Square startingSquare) const;
      Bitboard getPawnSinglePush(const Color activePlayer, const Square startingSquare, Direction direction) const;
      Bitboard getPawnDoublePush(const Color activePlayer, const Square startingSquare, Direction direction) const;
      bool pawnHasNotMoved(const Color activePlayer, const Square pawnLocation) const;
      bool pawnHasMoved(const Color activePlayer, const Square pawnLocation) const;
      bool isEnPassant(const Color activePlayer, const Square startingSquare, const Chessboard & gameState) const;
      bool isPawnDoublePush(const Square startingSquare, const Square targetSquare) const;
      Bitboard getCastles(const Color activePlayer, const Square startingSquare) const;
      bool isPawnPromotion(const Square targetSquare) const;
      void filterOutIllegalMoves(MoveVector & psuedoLegalMoves) const;
};