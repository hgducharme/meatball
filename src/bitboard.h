#pragma once

#include "types.h"

#include <stdexcept>
#include <cstdlib>
#include <string>

class Bitboard {
    private:
        u64 board_ = bitboard::EMPTY_BOARD;

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

        // Shorthand union between this bitboard and another bitboard
        Bitboard & operator |= (const Bitboard & rhs) { 
            setBoard(board_ | rhs.getBoard());
            return *this;
        }

        // Union between two bitboards
        friend Bitboard operator | (const Bitboard & a, const Bitboard & b) {
            return Bitboard(a.getBoard() | b.getBoard());
        }

        // Shorthand intersection between this bitboard and another bitboard
        Bitboard & operator &= (const Bitboard & rhs)
        {
            setBoard(board_ & rhs.getBoard());
            return *this;
        }

        // Intersection between two bitboards
        friend Bitboard operator & (const Bitboard & a, const Bitboard & b)
        {
            return Bitboard(a.getBoard() & b.getBoard());
        }

        private:
            void raiseExceptionIfBitIsOutOfRange(int n) const;
};

inline bool operator == (const Bitboard & lhs, const u64 rhs) { return lhs.getBoard() == rhs; }
inline bool operator == (const Bitboard & lhs, const Bitboard & rhs) { return lhs.getBoard() == rhs.getBoard(); }

inline Bitboard operator << (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() << rhs; }
inline Bitboard operator >> (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() >> rhs; }