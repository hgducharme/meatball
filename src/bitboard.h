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
        int getBit(int n);
        void reset();

        // Shorthand union between this bitboard and another bitboard
        Bitboard & operator |= (const Bitboard & rhs) { 
            u64 bitwiseORResult = this->board_ | rhs.getBoard();
            this->setBoard(bitwiseORResult);
            return *this;
        }

        // Union between two bitboards
        friend Bitboard operator | (Bitboard & a, const Bitboard & b) {
            Bitboard bitwiseORResult = a.getBoard() | b.getBoard();
            return bitwiseORResult;
        }

        // Shorthand intersection between this bitboard and another bitboard
        Bitboard & operator &= (const Bitboard & rhs)
        {
            u64 bitwiseANDResult = this->board_ & rhs.getBoard();
            this->setBoard(bitwiseANDResult);
            return *this;
        }

        // Intersection between two bitboards
        friend Bitboard operator & (Bitboard & a, const Bitboard & b)
        {
            Bitboard bitwiseANDResult = a.getBoard() & b.getBoard();
            return bitwiseANDResult;
        }

};