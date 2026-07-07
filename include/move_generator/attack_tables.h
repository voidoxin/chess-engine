#pragma once
#include "../board/board.h"
using BitBoard = uint64_t;
struct AttackTables {
    static BitBoard kingAttacks[64];
    static BitBoard knightAttacks[64];
    static BitBoard pawnAttacks[2][64];//0 is white 1 is black 
    //i can use it like this pawnAttacks[side_to_move][square]
};
class LUT_gen {
    private:
        BitBoard fileA=0ULL;    
        BitBoard fileH=0ULL;    
        BitBoard fileB=0ULL;    
        BitBoard fileG=0ULL;    
        BitBoard rank1=0ULL;
        BitBoard rank2=0ULL;
        BitBoard rank7=0ULL;
        BitBoard rank8=0ULL;
        void fileRankGen();
        void kingGen();
        void knightGen();
        void pawnGen();
    public:
        LUT_gen();
};