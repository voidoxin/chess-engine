#include"../../include/move_generator/attack_tables.h"
using BitBoard = uint64_t; 
BitBoard AttackTables::kingAttacks[64];
void LUT_gen::fileRankGen()
{
    for(int square=0;square<=56;square=+8)//fileA
    {
        fileA |= squareMask[square];
    }
    fileB=fileA<<1;//fileB
    fileG=fileA<<6;//fileG
    fileH=fileA<<7;//fileH
    for(int square=0;square<=7;square++)//rank1
    {
        rank1 |= squareMask[square];
    }
    rank2=rank1 << 8;
    rank7=rank1 << 48;
    rank8=rank1 << 56;
}
LUT_gen::LUT_gen()
{
    fileRankGen();
    kingGen();
}
void LUT_gen::kingGen()
{
    for(int square;square<64;square++)
    {
        AttackTables::kingAttacks[square]=0ULL;//clean the array
        AttackTables::kingAttacks[square] |= squareMask[square] << 8;//attack up
        AttackTables::kingAttacks[square] |= squareMask[square] >> 8;//attack down
        AttackTables::kingAttacks[square] |= (squareMask[square] << 1) & ~fileA;//attack right
        AttackTables::kingAttacks[square] |= (squareMask[square] >> 1) & ~fileH;//attack left
        AttackTables::kingAttacks[square] |= (squareMask[square] << 9) & ~fileA;//attack up-right
        AttackTables::kingAttacks[square] |= (squareMask[square] << 7) & ~fileH;//attack up-left
        AttackTables::kingAttacks[square] |= (squareMask[square] >> 7) & ~fileA;//attack down-right
        AttackTables::kingAttacks[square] |= (squareMask[square] >> 9) & ~fileH;//attack down-left
    }
}