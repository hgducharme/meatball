#pragma once

#include "types.h"
#include <cstdlib>

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

inline bool operator == (const Bitboard & lhs, const u64 rhs) { return lhs.getBoard() == rhs; }
inline bool operator == (const Bitboard & lhs, const Bitboard & rhs) { return lhs.getBoard() == rhs.getBoard(); }

inline Bitboard operator << (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() << rhs; }
inline Bitboard operator >> (const Bitboard & lhs, const unsigned int rhs) { return lhs.getBoard() >> rhs; }

// Return all legal knight attacks from a given square on the chessboard
Bitboard applyKnightAttackMask(const Bitboard & bitboard)
{
    // north 2 east 1 -- this corresponds to 17 bits ahead of current square
    Bitboard north2East1 = (bitboard << 17);

    // north 2 west 1 -- this corresponds to 15 bits ahead of current square
    Bitboard north2West1 = (bitboard << 15);

    // north 1 east 2 -- this corresponds to 10 bits ahead of current square
    Bitboard north1East2 = (bitboard << 10);

    // north 1 west 2 -- this corresponds to 6 bits ahead of current square
    Bitboard north1West2 = (bitboard << 6);

    // south 2 east 1 -- this corresponds to 15 bits behind current square
    Bitboard south2East1 = (bitboard >> 15);
    
    // south 2 west 1 -- this corresponds to 17 bits behind current square
    Bitboard south2West1 = (bitboard >> 17);

    // south 1 east 2 -- this corresponds to 6 bits behind current square
    Bitboard south1East2 = (bitboard >> 6);

    // south 1 west 2 -- this corresponds to 10 bits behind current square
    Bitboard south1West2 = (bitboard >> 8);

    Bitboard knightAttacks = north2East1 | north2West1 | north1East2 | north1West2 |
                             south2East1 | south2West1 | south1East2 | south1West2;

    return knightAttacks;
}