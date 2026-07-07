#include"../../include/move_generator/attack_tables.h"
using BitBoard = uint64_t; 
BitBoard AttackTables::kingAttacks[64];
BitBoard AttackTables::knightAttacks[64];
BitBoard AttackTables::pawnAttacks[2][64];
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
    knightGen();
    pawnGen();
}
void LUT_gen::kingGen()
{
    for(int square=0;square<64;square++)
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
void LUT_gen::knightGen()
{
    for(int square=0;square<64;square++)
    {
        AttackTables::knightAttacks[square]=0ULL;
        AttackTables::knightAttacks[square] |= (squareMask[square] << 17)& ~fileA;//2 up 1 right
        AttackTables::knightAttacks[square] |= (squareMask[square] << 15)& ~fileH;//2 up 1 left
        AttackTables::knightAttacks[square] |= (squareMask[square] << 10)& ~(fileA | fileB);//1 up 2 right
        AttackTables::knightAttacks[square] |= (squareMask[square] <<  6)& ~(fileG | fileH);//1 up 2 left
        AttackTables::knightAttacks[square] |= (squareMask[square] >> 17)& ~fileH;//2 down 1 left
        AttackTables::knightAttacks[square] |= (squareMask[square] >> 15)& ~fileA;//2 down 1 right
        AttackTables::knightAttacks[square] |= (squareMask[square] >> 10)& ~(fileG|fileH);//1 down 2 left
        AttackTables::knightAttacks[square] |= (squareMask[square] >> 6)& ~(fileA|fileB);//1 down 2 right

    }
}
void LUT_gen::pawnGen()
{
    for(int color=0;color<2;color++)
    {
        for(int square=0;square<64;square++)
        {
            if(!color)
            {
                pawnAttacks[color][square]=0ULL;
                pawnAttacks[color][square] |= (squareMask[square] << 9) & ~fileA;//up-right
                pawnAttacks[color][square] |= (squareMask[square] << 7) & ~fileH;//up-left
            }else
            {
                pawnAttacks[color][square]=0ULL;
                pawnAttacks[color][square] |= (squareMask[square] >> 7) & ~fileA;//down-right
                pawnAttacks[color][square] |= (squareMask[square] >> 9) & ~fileH;//down-left
            }            
        }
    }
}