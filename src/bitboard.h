#pragma once

#include "types.h"
#include "constants.h"

#include <iostream>
#include <string>

class Bitboard {
    private:
        u64 board_ = constants::EMPTY_BOARD;

    public:
        Bitboard() = default;
        Bitboard(u64 boardState);
        Bitboard(int bit);
        inline u64 toInt() const { return board_; }
        std::string toHex() const;
        std::string toBinary(bool spaces = false) const;
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
inline bool operator == (const Bitboard & lhs, const u64 rhs) { return lhs.toInt() == rhs; }
inline bool operator == (const Bitboard & lhs, const Bitboard & rhs) { return lhs.toInt() == rhs.toInt(); }

/* Bitwise operator overloading */
inline Bitboard operator << (const Bitboard & lhs, const unsigned int rhs) { return lhs.toInt() << rhs; }
inline Bitboard operator >> (const Bitboard & lhs, const unsigned int rhs) { return lhs.toInt() >> rhs; }
inline Bitboard operator & (const Bitboard & a, const Bitboard & b) { return Bitboard(a.toInt() & b.toInt()); }
inline Bitboard operator | (const Bitboard & a, const Bitboard & b) { return Bitboard(a.toInt() | b.toInt()); }
inline Bitboard operator ~ (const Bitboard & a) { return Bitboard( ~(a.toInt()) ); }
inline Bitboard & operator &= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.toInt() & rhs.toInt()); return lhs; }
inline Bitboard & operator |= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.toInt() | rhs.toInt()); return lhs; }

/* Arithmetic operator overloading */
inline u64 operator * (const Bitboard & lhs, const u64 rhs) { return lhs.toInt() * rhs; }
inline u64 operator * (const u64 lhs, const Bitboard & rhs) { return lhs * rhs.toInt(); }

/* Stream operator overloading */
inline std::ostream & operator << (std::ostream& out, const Bitboard & b) { out << b.toBinary(); return out; }