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
        inline u64 toU64() const { return board_; }
        std::string toHex() const;
        std::string toBinary(bool includeSpaces = false) const;
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
        bool anyBitsSet() const;
        bool noBitsSet() const;
        explicit operator bool () const {return anyBitsSet(); }

        private:
            void raiseExceptionIfBitIsOutOfRange(int n) const;
};

/* Comparison operators */
inline bool operator == (const Bitboard & lhs, const u64 rhs) { return lhs.toU64() == rhs; }
inline bool operator == (const Bitboard & lhs, const Bitboard & rhs) { return lhs.toU64() == rhs.toU64(); }
inline bool operator!=(const Bitboard & lhs, const Bitboard & rhs) { return !(lhs == rhs); }

/* Bitwise arithmetic operator overloading */
inline Bitboard operator << (const Bitboard & lhs, const unsigned int rhs) { return (lhs.toU64() << rhs); }
inline Bitboard operator >> (const Bitboard & lhs, const unsigned int rhs) { return (lhs.toU64() >> rhs); }
inline Bitboard operator & (const Bitboard & a, const Bitboard & b) { return Bitboard(a.toU64() & b.toU64()); }
inline Bitboard operator | (const Bitboard & a, const Bitboard & b) { return Bitboard(a.toU64() | b.toU64()); }
inline Bitboard & operator &= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.toU64() & rhs.toU64()); return lhs; }
inline Bitboard & operator |= (Bitboard & lhs, const Bitboard & rhs) { lhs.setBoard(lhs.toU64() | rhs.toU64()); return lhs; }
inline Bitboard operator ~ (const Bitboard & a) { return Bitboard( ~(a.toU64()) ); }

/* Arithmetic operator overloading */
inline u64 operator * (const Bitboard & lhs, const u64 rhs) { return lhs.toU64() * rhs; }
inline u64 operator * (const u64 lhs, const Bitboard & rhs) { return lhs * rhs.toU64(); }

/* Stream operator overloading */
inline std::ostream & operator << (std::ostream& out, const Bitboard & b) { out << b.toBinary(); return out; }