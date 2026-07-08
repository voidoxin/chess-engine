#pragma once
#include "../board/board.h"
#include <vector>
using BitBoard = uint64_t;
struct magicUtils {
    static int bishop_shift_number[64];//shift numbers to generate index for bishop
    static int rook_shift_number[64];//shift numbers for rook
    static const BitBoard bishop_magicN[64];//ready bishop magic numbers for every square
    static const BitBoard rook_magicN[64];//ready rook magic numbers for every square
};
struct AttackTables {
    static BitBoard kingAttacks[64];
    static BitBoard knightAttacks[64];
    static BitBoard pawnAttacks[2][64];//0 is white 1 is black 
    //i can use it like this pawnAttacks[side_to_move][square]
    static BitBoard bishopAttacks[64][512];
    static BitBoard rookAttacks[64][4096];
    static BitBoard bishopBlindAttacks[64];
    static BitBoard rookBlindAttacks[64];
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
        int N;//number of squares slider can move i need it in shiftGens
        void fileRankGen();//init files and ranks i need 
        void bishopMaskGen();//init bishopBlindAttacks[]
        std::vector<BitBoard> occupancyGen(BitBoard bishopMask);//return a vector by all possible occupancy on the situation(square)
        BitBoard bishopAttacksGen(int sq,BitBoard occupancy);//generate attack bitboard with square and occupancy for bishop
        void bishopShiftGen(int N,int sq);//generate shift numbers for bishop
        void rookShiftGen(int N,int sq);//generate shift numbers for rook
        void rookMaskGen ();//init rookBlindAttacks[]
        BitBoard rookAttackGen(int square,BitBoard occupancy);//create attack bitboard with square and occupancy for rook
        //pieces gen 
        void kingGen();
        void knightGen();
        void pawnGen();
        void bishopGen();
        void rookGen();
    public:
        LUT_gen();
        BitBoard queenGen(int square,BitBoard occupancy);
};