#pragma once

#include "chessboard.h"

/* TODO: This doesn't need to be a class because there is no state being persisted. Instead,
 * this can be turned into a namespace with free functions.
 */

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
      bool movePutsOpponentInCheck(const Chessboard & gameState, const Move & move) const;
      bool isKingInCheck(const Chessboard & gameState, const Color kingsColor) const;
      Bitboard getPawnPushes(const Color activePlayer, const Square startingSquare, const Bitboard opponentsPieces) const;
      Bitboard getPawnSinglePush(const Color activePlayer, const Square startingSquare, Direction direction, const Bitboard occupiedSquares) const;
      Bitboard getPawnDoublePush(const Color activePlayer, const Square startingSquare, Direction direction, const Bitboard occupiedSquares) const;
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
      bool moveIsCheckmate(const Chessboard & gameState, const Move & move) const;
};