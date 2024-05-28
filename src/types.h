#pragma once

#include <cstdint>

using u64 = std::uint64_t;

enum PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NUMBER_OF_PIECES = 6
};

enum class SliderPiece
{
    BISHOP = PieceType::BISHOP,
    ROOK = PieceType::ROOK,
    QUEEN = PieceType::QUEEN
};

enum class LeaperPiece
{
    PAWN = PieceType::PAWN,
    KNIGHT = PieceType::KNIGHT,
    KING = PieceType::KING
};

// This enum maps the concept of a direction on a chessboard to a corresponding number of bits
// - one move to the north west corresponds to the bit 7 positions larger than the current bit
// - one move to the north      corresponds to the bit 8 positions larger than the current bit
// - one move to the north east corresponds to the bit 9 positions larger than the current bit
enum Direction
{
    NORTH = 8,
    SOUTH = -8,
    NORTH_EAST = 9,
    SOUTH_WEST = -9,
    NORTH_WEST = 7,
    SOUTH_EAST = -7,
    EAST = 1,
    WEST = -1,
};

enum Square
{
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    NUMBER_OF_SQUARES = 64,
};

enum Color
{
    WHITE,
    BLACK,
    NUMBER_OF_COLORS = 2
};

enum File
{
   FILE_A,
   FILE_B,
   FILE_C,
   FILE_D,
   FILE_E,
   FILE_F,
   FILE_G,
   FILE_H,
   NUMBER_OF_FILES = 8
};

enum Rank
{
   RANK_1,
   RANK_2,
   RANK_3,
   RANK_4,
   RANK_5,
   RANK_6,
   RANK_7,
   RANK_8,
   NUMBER_OF_RANKS = 8
};

enum class CastleRights
{
    KING_AND_QUEEN_SIDE,
    ONLY_KING_SIDE,
    ONLY_QUEEN_SIDE,
    NONE,
    NUMBER_OF_CASTLE_STATES = 4
};

struct CastleMove
{
    Square kingStart;
    Square kingEnd;
    Square rookStart;
    Square rookEnd;

    constexpr CastleMove(Square kingStart, Square kingEnd, Square rookStart, Square rookEnd)
    : kingStart(kingStart), kingEnd(kingEnd), rookStart(rookStart), rookEnd(rookEnd) {}
};

enum class CastleSide {
    KINGSIDE,
    QUEENSIDE,
    NUMBER_OF_CASTLE_SIDES = 2
};

struct Piece
{
    Color color;
    PieceType type;

    inline Piece() {}
    inline Piece(const Color c, const PieceType pt) : color(c), type(pt) {}

    inline bool operator == (const Piece & rhs) const { return ( (color == rhs.color) && (type == rhs.type) ); }
};

struct CapturedPiece : public Piece
{
    Square square;

    inline CapturedPiece() {}
    inline CapturedPiece(const Color c, const PieceType pt, const Square loc) : Piece(c, pt), square(loc) {}

    inline bool operator == (const CapturedPiece & rhs) const {
        return Piece::operator==(rhs) && (square == rhs.square);
    }
};

struct GameState
{
    u64 pawns = 0;
    u64 knights = 0;
    u64 bishops = 0;
    u64 rooks = 0;
    u64 queens = 0;
    u64 kings = 0;
    u64 whiteOccupied = 0;
    u64 blackOccupied = 0;
    Color activePlayer;
    CastleRights whiteCastleRights;
    CastleRights blackCastleRights;
    Square enPassantTargetSquare;
    int halfMoveClock;
    int fullMoveNumber;
};