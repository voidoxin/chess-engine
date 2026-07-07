#pragma once
#include "../board/board.h"
#include <vector>
using namespace std;
using BitBoard = uint64_t;
struct magicUtils {
    static int shift_number[64];//shift numbers to generate index
    static const BitBoard bishop_magicN[64];//ready bishop magic numbers for every square
};
struct AttackTables {
    static BitBoard kingAttacks[64];
    static BitBoard knightAttacks[64];
    static BitBoard pawnAttacks[2][64];//0 is white 1 is black 
    //i can use it like this pawnAttacks[side_to_move][square]
    static BitBoard bishopAttacks[64][515];
};
class LUT_gen {
    private:
        // utils func and variables for gen
        BitBoard fileA=0ULL;    
        BitBoard fileH=0ULL;    
        BitBoard fileB=0ULL;    
        BitBoard fileG=0ULL;    
        BitBoard rank1=0ULL;
        BitBoard rank2=0ULL;
        BitBoard rank7=0ULL;
        BitBoard rank8=0ULL;
        void fileRankGen();
        BitBoard bishopMaskGEN(int square);//return a bitboard by squares bishop can attack in that one square
        vector<BitBoard> occupancyGEN(int square,BitBoard bishopMask);//return a vector by all possible occupancy on the situation(square)
        BitBoard bishopAttacksGen(int square,BitBoard occupancy);//create attack bitboard with square and occupancy
        void shiftGen(int N,int sq);
        //pieces gen 
        void kingGen();
        void knightGen();
        void pawnGen();
        void bishopGen();
    public:
        LUT_gen();
};