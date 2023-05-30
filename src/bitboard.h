#pragma once

#include <cstdint>

class Bitboard {
    private:
        uint64_t _board;

    public:
        Bitboard() = default;
        void init();
        uint64_t getBoard();
};