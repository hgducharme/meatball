#pragma once

#include "types.h"

class Bitboard {
    private:
        u64 board_ = 0;

    public:
        Bitboard() = default;
        Bitboard(u64 boardState);
        inline u64 getBoard() const { return board_; }
        inline void setBoard(const u64 boardState) { board_ = boardState; };
        void setBit(int n);
        void clearBit(int n);
        int getBit(int n) const;
        void reset();
        int numberOfSetBits() const;
        int findIndexLSB() const;
        int findIndexMSB() const;

        // Shorthand union between this bitboard and another bitboard
        Bitboard & operator |= (const Bitboard & rhs) { 
            this->setBoard(this->board_ | rhs.getBoard());
            return *this;
        }

        // Union between two bitboards
        friend Bitboard operator | (const Bitboard & a, const Bitboard & b) {
            return Bitboard(a.getBoard() | b.getBoard());
        }

        // Shorthand intersection between this bitboard and another bitboard
        Bitboard & operator &= (const Bitboard & rhs)
        {
            this->setBoard(this->board_ & rhs.getBoard());
            return *this;
        }

        // Intersection between two bitboards
        friend Bitboard operator & (const Bitboard & a, const Bitboard & b)
        {
            return Bitboard(a.getBoard() & b.getBoard());
        }

};