#pragma once

#include "types.h"

class Bitboard {
    private:
        u64 board_ = 0;

    public:
        Bitboard() = default;
        Bitboard(u64 boardState);
        inline u64 getBoard() { return board_; }
        inline void setBoard(const u64 boardState) { board_ = boardState; };
        void setBit(int n);
        void clearBit(int n);
        int getBit(int n);
        void reset();
};