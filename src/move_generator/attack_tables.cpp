#include"../../include/move_generator/attack_tables.h"
#include <iostream>
#include "../../include/board/board.h"
#include <vector>
using namespace std;
using BitBoard = uint64_t; 
BitBoard AttackTables::kingAttacks[64];
BitBoard AttackTables::knightAttacks[64];
BitBoard AttackTables::pawnAttacks[2][64];
BitBoard AttackTables::bishopAttacks[64][512];
BitBoard AttackTables::rookAttacks[64][4096];
BitBoard AttackTables::bishopBlindAttacks[64];
BitBoard AttackTables::rookBlindAttacks[64];
int magicUtils::bishop_shift_number[64];
int magicUtils::rook_shift_number[64];
const BitBoard magicUtils::bishop_magicN[64]= {
    0x89a1121896040240ULL, 0x2004844802002010ULL, 0x200600810c0200c1ULL, 0x2044000841000200ULL,
    0x2100140008044200ULL, 0x8408009100c00010ULL, 0x20a0080820022100ULL, 0x438a001088440010ULL,
    0x400400180208200ULL,  0x84000c0810110020ULL, 0x440c040200110044ULL, 0x510008204140002ULL,
    0x110202440c020100ULL, 0x1248041000800801ULL, 0x2440100408104200ULL, 0x1100824080200c00ULL,
    0x1208204000201ULL,    0x42041208040d0010ULL, 0x44200a00040024ULL,   0x10d0041240802ULL,
    0x1014020210004ULL,    0x4802020480004ULL,    0x4104080041100044ULL, 0x3010100d00200020ULL,
    0x40102011000cULL,     0x481100044004ULL,     0x2500c00224ULL,       0x880400101c02ULL,
    0x111004008011ULL,     0x208801100c02ULL,     0x20110008004ULL,      0x40114002200840ULL,
    0x204004404005ULL,     0x20140042004ULL,      0x8110041ULL,          0x8c00400c0220ULL,
    0x218400a00c0ULL,      0x1010022402020ULL,    0x81000a0c004040ULL,   0x410220011ULL,
    0x1208820400ULL,       0x2424041002ULL,       0x20410044010ULL,      0x12404204ULL,
    0x124082200100ULL,     0xe050402008ULL,       0x21004010004ULL,      0x110410400ULL,
    0x4002008080080200ULL, 0x8101020004050ULL,    0x8848010002002ULL,    0x8081240040ULL,
    0x81008460010011ULL,   0x41008101020004ULL,   0x80081204060ULL,      0x4004008100c080ULL,
    0x8021004080ULL,       0x204040110200ULL,     0x240100402100ULL,     0x20400040120ULL,
    0x5400202002ULL,       0x12200420ULL,         0x1410100400010ULL,    0x20a010402ULL
};
const BitBoard magicUtils::rook_magicN[64] = {
    0x8a80104000800020ULL, 0x14000a0004000200ULL, 0x280480a008000400ULL, 0x1000820100400020ULL,
    0x8080200010008020ULL, 0x2000080100040000ULL, 0x20000100000000ULL, 0x80080000200000ULL,
    0x40000801000000ULL, 0x1000402000800ULL, 0x400200010000ULL, 0x100040000000ULL,
    0x4000400000000ULL, 0x400080000ULL, 0x8000000000ULL, 0x8000000000ULL,
    0x20000000000ULL, 0x20080000ULL, 0x20000000000ULL, 0x40000000000ULL,
    0x40000000000ULL, 0x40080000000ULL, 0x40000000000ULL, 0x40000000000ULL,
    0x40000000000ULL, 0x40000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL,
    0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL, 0x80000000000ULL
};
LUT_gen::LUT_gen()
{
    fileRankGen();
    kingGen();
    knightGen();
    pawnGen();
    bishopGen();
    rookGen();
}
void LUT_gen::fileRankGen()
{
    for(int square=0;square<=56;square+=8)//fileA
    {
        fileA |= squareMask[square];
    }
    fileB=fileA<<1;//fileB
    fileG=fileA<<6;//fileG
    fileH=fileA<<7;//fileH
    for(int sq=0;sq<=7;sq++)//rank1
    {
        rank1 |= squareMask[sq];
    }
    rank2=rank1 <<  8;
    rank7=rank1 << 48;
    rank8=rank1 << 56;
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
               AttackTables::pawnAttacks[color][square]=0ULL;
               AttackTables::pawnAttacks[color][square] |= (squareMask[square] << 9) & ~fileA;//up-right
               AttackTables::pawnAttacks[color][square] |= (squareMask[square] << 7) & ~fileH;//up-left
            }else
            {
               AttackTables::pawnAttacks[color][square]=0ULL;
               AttackTables::pawnAttacks[color][square] |= (squareMask[square] >> 7) & ~fileA;//down-right
               AttackTables::pawnAttacks[color][square] |= (squareMask[square] >> 9) & ~fileH;//down-left
            }            
        }
    }
}
void LUT_gen::bishopMaskGen()
{
    int file;
    int rank;
    for(int square=0;square<64;square++)
    {
        rank= (square / 8);
        file= (square % 8);
        BitBoard value=0ULL;
        while(rank<7&&file<7)//up-right
        {
           rank++;
           file++;
           value|=squareMask[(rank*8)+file];
        }
        rank=(square / 8);
        file=(square % 8);
        while(rank<7&&file>0)//up-left
        {
            rank++;
            file--;
            value|=squareMask[(rank*8)+file];
        }
        rank=(square / 8);
        file=(square % 8);
        while(rank>0&&file<7)//down-right
        {
            rank--;
            file++;
            value|=squareMask[(rank*8)+file];
        }
        rank=(square / 8);
        file=(square % 8);
        while(rank>0&&file>0)//down-left
        {
            rank--;
            file--;
            value|=squareMask[(rank*8)+file];
        }
        AttackTables::bishopBlindAttacks[square]=(value & ~(fileA|fileH|rank1|rank8));
    }
}
vector<BitBoard> LUT_gen::occupancyGen(BitBoard sliderMask)
{
    int squaresNm[14];//squares slider can go
    int sqNumber=0;//how many squares slider can go 
    BitBoard occupancy=0ULL;
    vector<BitBoard> occupancies;
    occupancies.clear();
    for(int sq=0;sq<64;sq++)//get from sliderMask the number of squares the slider can go
    {
        if((sliderMask & squareMask[sq])!=0)
        {
            squaresNm[sqNumber]=sq;
            sqNumber++;
        }
    }
        N=sqNumber;
    for(int p=0;p<(1 << sqNumber);p++)//loop to all occupancies possible
    {
        occupancy=0ULL;
        for(int bit=0;bit<sqNumber;bit++)//loop for evry bit in p
        {
            if((p >> bit)& 1)
            {
                occupancy |= squareMask[squaresNm[bit]];
            }
        }
        occupancies.push_back(occupancy);
    }
    return occupancies;
}
BitBoard LUT_gen::bishopAttacksGen(int sq,BitBoard occupancy)
{
    int rank= (sq / 8);
    int file= (sq % 8);
    BitBoard attack_squares=0ULL;
    int bishopSquare=sq;//the startup square
    while(rank<7&&file<7)//up-right
    {
        rank++;
        file++;
        sq=((rank*8)+file);
        attack_squares |= squareMask[sq];
        if((squareMask[sq] & occupancy) != 0)//if the square is in occupancy
        {
            break;
        }
    }
    rank= (bishopSquare / 8);
    file= (bishopSquare % 8);
    while(rank<7&&file>0)//up-left
    {
        rank++;
        file--;
        sq=((rank*8)+file);
        attack_squares |= squareMask[sq];
        if((squareMask[sq] & occupancy) != 0)//if the square is in occupancy
        {
            break;
        }
    }
    rank= (bishopSquare / 8);
    file= (bishopSquare % 8);
    while(rank>0&&file<7)//down-right
    {
        rank--;
        file++;
        sq=((rank*8)+file);
        attack_squares |= squareMask[sq];
        if((squareMask[sq] & occupancy) != 0)//if the square is in occupancy
        {
            break;
        }
    }
    rank= (bishopSquare / 8);
    file= (bishopSquare % 8);
    while(rank>0&&file>0)//down-left
    {
        rank--;
        file--;
        sq=((rank*8)+file);
        attack_squares |= squareMask[sq];
        if((squareMask[sq] & occupancy) != 0)//if the square is in occupancy
        {
            break;
        }
    }
    return (attack_squares);
}
inline void LUT_gen::bishopShiftGen(int N,int sq)
{
    magicUtils::bishop_shift_number[sq]=64-N;
}
inline void LUT_gen::rookShiftGen(int N,int sq)
{
    magicUtils::rook_shift_number[sq]=64-N;
}
void LUT_gen::bishopGen()
{
    bishopMaskGen();//init bishopBlindAttacks by masks
    for(int sq=0;sq<64;sq++)
    {
        vector<BitBoard> occupancies=occupancyGen(AttackTables::bishopBlindAttacks[sq]);
        bishopShiftGen(N,sq);//generate shift number for every square
        for(int i=0;i<occupancies.size();i++)
        {
            AttackTables::bishopAttacks[sq][(occupancies[i]*magicUtils::bishop_magicN[sq])>>magicUtils::bishop_shift_number[sq]]=bishopAttacksGen(sq,occupancies[i]);
        }
    }
}
void LUT_gen::rookMaskGen()
{
    int file;
    int rank;
    for(int square=0;square<64;square++)
    {
        rank= (square / 8);
        file= (square % 8);
        BitBoard value=0ULL;
        while(rank<7)
        {
            rank++;
            value |=squareMask[(rank*8)+file];  
        }
        rank=(square / 8);
        file=(square % 8);
        while(rank>0)
        {
            rank--;
            value |=squareMask[(rank*8)+file];          
        }
        rank=(square / 8);
        file=(square % 8);
        while(file<7)
        {
        file++;
        value |=squareMask[(rank*8)+file];  
        }
        rank=(square / 8);
        file=(square % 8);
        while(file>0)
        {
            file--;
            value |=squareMask[(rank*8)+file];
        }
       AttackTables::rookBlindAttacks[square]=(value & ~(fileA|fileH|rank1|rank8));
    }
}
BitBoard LUT_gen::rookAttackGen(int square,BitBoard occupancy)
{
    int rank= (square / 8);
    int file= (square % 8);
    BitBoard value=0ULL;
    int rookSquare=square;
    while(rank<7)
    {
        rank++;
        square=(rank*8)+file;
        value |=squareMask[square];
        if((occupancy & squareMask[square]) !=0)
        {
            break;
        }
    }
    rank= (rookSquare / 8);
    file= (rookSquare % 8);
    while(rank>0)
    {
        rank--;
        square=(rank*8)+file;
        value |=squareMask[square];
        if((occupancy & squareMask[square]) !=0)
        {
            break;
        }
    }
    rank= (rookSquare / 8);
    file= (rookSquare % 8);
    while(file<7)
    {
        file++;
        square=(rank*8)+file;
        value |=squareMask[square];
        if((occupancy & squareMask[square]) !=0)
        {
            break;
        }
    }
    rank= (rookSquare / 8);
    file= (rookSquare % 8);
    while(file>0)
    {
        file--;
        square=(rank*8)+file;
        value |=squareMask[square];
        if((occupancy & squareMask[square]) !=0)
        {
            break;
        }
    }
        return value;
}
void LUT_gen::rookGen()
{
    rookMaskGen();//init bishopBlindAttacks by masks
    for(int sq=0;sq<64;sq++)
    {
        vector<BitBoard> occupancies=occupancyGen(AttackTables::rookBlindAttacks[sq]);
        rookShiftGen(N,sq);//generate shift number for every square
        for(int i=0;i<occupancies.size();i++)
        {
            AttackTables::rookAttacks[sq][(occupancies[i]*magicUtils::rook_magicN[sq])>>magicUtils::rook_shift_number[sq]]=rookAttackGen(sq,occupancies[i]);
        }
    }
}