#pragma once

#include "types.h"

class Bitboard {
    private:
        u64 board_ = bitboard::EMPTY_BOARD;

    public:
        Bitboard() = default;
        Bitboard(u64 boardState);
        Bitboard (Square square);
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

        // Implicit conversion from u64
        // Bitboard(u64);
        // Implicit conversion to u64
        // operator uint64_t();
        // operator u64 &() { return board_; }
        // u64 * operator &() { return &board_; }

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

};