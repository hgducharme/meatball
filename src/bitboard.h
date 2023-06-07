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

        // Combine the states of this board and a different board
        Bitboard & operator |= (const Bitboard& rhs) { 
            u64 combinedBoard = this->board_ | rhs.getBoard();
            this->setBoard(combinedBoard);
            return *this;
        }

        friend Bitboard operator | (Bitboard & a, const Bitboard & b) { 
            a |= b;
            return a;
        }


};