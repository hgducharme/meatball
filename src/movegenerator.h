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
      bool isEnPassant(const Color activePlayer, const Square startingSquare, const Square targetSquare, const std::optional<const Move> opponentsPreviousMove) const;
      bool pawnMoveIsAttackWithNoCaptures(const Move & m, const Bitboard & opponentOccupancySet) const;
      bool isPawnDoublePush(const Square startingSquare, const Square targetSquare) const;
      Bitboard getCastles(const Chessboard & gameState) const;
      const std::pair<Square, u64> getKingSideCastleSquares(const Color activePlayer) const;
      const std::pair<Square, u64> getQueenSideCastleSquares(const Color activePlayer) const;
      const Bitboard computeCastleBitboard(const Chessboard & gameState, u64 squaresInBetweenKingAndRook, Square kingTargetSquare) const;
      bool isPawnPromotion(const Square targetSquare) const;
      void filterOutIllegalMoves(MoveVector & psuedoLegalMoves, const Chessboard & gameState) const;
};