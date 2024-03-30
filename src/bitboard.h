#pragma once

#include "types.h"
#include "constants.h"

#include <iostream>

class Bitboard {
    private:
        u64 board_ = constants::EMPTY_BOARD;

    public:
        Bitboard() = default;
        Bitboard(u64 boardState);
        Bitboard(int bit);
        inline u64 getBoard() const { return board_; }
        inline void setBoard(const u64 boardState) { board_ = boardState; };
        void setBit(int n);
        void clearBit(int n);
        int getBit(int n) const;
        void reset();
        int numberOfSetBits() const;
        int findIndexLSB() const;
        int findIndexMSB() const;
        int clearAndReturnLSB();
        int clearAndReturnMSB();
        Bitboard getNeighbor(Direction direction) const;

        private:
            void raiseExceptionIfBitIsOutOfRange(int n) const;
};

/* Relational operator overloading */
inline bool operator == (const Bitboard & lhs, const u64 rhs) { return lhs.getBoard() == rhs; }
inline bool operator == (const Bitboard & lhs, const Bitboard & rhs) { return lhs.getBoard() == rhs.getBoard(); }

/* Bitwise operator overloading */
inline Bitboard operator << (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() << rhs; }
inline Bitboard operator >> (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() >> rhs; }
inline Bitboard operator & (const Bitboard & a, const Bitboard & b) { return Bitboard(a.getBoard() & b.getBoard()); }
inline Bitboard operator | (const Bitboard & a, const Bitboard & b) { return Bitboard(a.getBoard() | b.getBoard()); }
inline Bitboard operator ~ (const Bitboard & a) { return Bitboard( ~(a.getBoard()) ); }
inline Bitboard & operator &= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.getBoard() & rhs.getBoard()); return lhs; }
inline Bitboard & operator |= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.getBoard() | rhs.getBoard()); return lhs; }

/* Arithmetic operator overloading */
inline u64 operator * (const Bitboard & lhs, const u64 rhs) { return lhs.getBoard() * rhs; }
inline u64 operator * (const u64 lhs, const Bitboard & rhs) { return lhs * rhs.getBoard(); }

/* Stream operator overloading */
inline std::ostream & operator << (std::ostream& out, const Bitboard & b) { out << b.getBoard(); return out; }