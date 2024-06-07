#pragma once

#include "bitboard.h"
#include "move.h"

namespace utils
{

Bitboard getSquareInDirectionAsBitboard(const Square square, const int numberOfBits);

Bitboard getSquareInDirectionAsBitboard(const Bitboard & oldPosition, const int numberOfBits);

int calculateDistanceToEdgeOfBoard(const Square square, const Direction direction);

u64 getRandom64BitInteger();

u64 getSparselyPopulatedRandom64BitInteger();

std::string squareToString(Square square);

std::string pieceTypeToString(PieceType pieceType);

std::string colorToString(const Color color);

std::string moveToString(const Move & move);

std::string charToString(const char c);

std::vector<std::string> tokenizeString(const std::string & str);

int bigEndianRankFileToLittleEndianRankFile(const int position);

} // namespace utils