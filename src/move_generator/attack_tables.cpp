/*
    this file is LUT generator to generate tables for every piece on every square
*/
#include"../../include/move_generator/attack_tables.h"
#include <iostream>
#include "../../include/board/board.h"
#include <vector>
using namespace std;
using namespace masks;
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
const BitBoard magicUtils::bishop_magicN[64]= {//bishop magic numbers ready to be used
    0x40108202082020ULL, 0x2500101010002ULL, 0x420a00c1000000ULL, 0x404040080080040ULL,
    0x4242001800400ULL, 0x102282008400000ULL, 0x94008808080000ULL, 0xa120104200400ULL,
    0x201410028100ULL, 0x40808050024ULL, 0x4100082004101ULL, 0xb008040400800000ULL,
    0x84120210800000ULL, 0x800028210400002ULL, 0x800100900c2000ULL, 0xc00008041082000ULL,
    0x4004008420400ULL, 0x420801004008080ULL, 0x1010000800841010ULL, 0x1011024028022ULL,
    0x6840404a00800ULL, 0x8000800b0080c000ULL, 0x4102084010800ULL, 0x84004200d000ULL,
    0x10080046200400ULL, 0x106200008010400ULL, 0x1000480010088030ULL, 0x6582022008008020ULL,
    0xc2002006008060ULL, 0x100049000a009200ULL, 0x8020011210100ULL, 0x1002001140101ULL,
    0x2104000440880ULL, 0x8410800100220ULL, 0x40802080440800ULL, 0x14080a0080480081ULL,
    0x220228400008020ULL, 0x203084100020101ULL, 0x8002020200240080ULL, 0x1004200810108ULL,
    0x2100208002040ULL, 0x5010120021000ULL, 0x402020202008101ULL, 0x8000c200841800ULL,
    0x400200a4004200ULL, 0x2001081001004090ULL, 0x4480081000404ULL, 0xc030401000020ULL,
    0x21041004040004ULL, 0x20a0082080040ULL, 0x400010088048040ULL, 0x8000004184040008ULL,
    0x101042060008ULL, 0x800200410108002ULL, 0x40050404820000ULL, 0x10020811002008ULL,
    0x8000210802012080ULL, 0x82c4022000ULL, 0x80424020800ULL, 0x2000000410208800ULL,
    0x108610900ULL, 0x4000802080210ULL, 0x2000100c10040040ULL, 0x2040060800408080ULL
};
const BitBoard magicUtils::rook_magicN[64] = {//rook magic numbers ready to be used
    0x84800012c0022581ULL, 0x1500204001018090ULL, 0x1900104301982000ULL, 0x4880080164500080ULL,
    0x6100022800305d00ULL, 0x6100083400110066ULL, 0x1200258411082200ULL, 0xa08001000131c580ULL,
    0x310800140042081ULL, 0xc0c3004000830024ULL, 0x116004030a20084ULL, 0x890a002200400910ULL,
    0x2802001084220018ULL, 0x52001042000894ULL, 0x462000200418804ULL, 0x40028008ea800100ULL,
    0x44808000a84014ULL, 0x20e001802c804000ULL, 0x820010023104500ULL, 0x14a02000a204090ULL,
    0x8122020004104920ULL, 0x890808002004401ULL, 0x1d40002101908ULL, 0x420a0004104881ULL,
    0x31c0014080006580ULL, 0xa07008404000a004ULL, 0x40b412c100200100ULL, 0x420500100082105ULL,
    0x6863040080080080ULL, 0x2983400801201004ULL, 0x1058102400014208ULL, 0x20486002c4401ULL,
    0x90418040088000b0ULL, 0x410e010086004022ULL, 0x8250402082001200ULL, 0x6418810804801000ULL,
    0x1001009801001184ULL, 0x808e000c82000910ULL, 0x410801300800200ULL, 0x90020c0a6000415ULL,
    0x3082b840048000ULL, 0x403001516000c004ULL, 0x8810220180920041ULL, 0x21002350030008ULL,
    0x1821000800910044ULL, 0x2c2000c90820008ULL, 0x111c8410a040010ULL, 0x201034186000cULL,
    0xa881020144902200ULL, 0x800103400480e900ULL, 0x1420c082005a00ULL, 0x114200441810a200ULL,
    0x241180064028080ULL, 0x80d008864000300ULL, 0x10300248811400ULL, 0x6004801300114080ULL,
    0x10014a08000c301ULL, 0x11e040018505ULL, 0x1102100842018122ULL, 0x130000420910009ULL,
    0x19200300528200aULL, 0x4302001004084922ULL, 0x8010810810021084ULL, 0xa200040101805026ULL
};
LUT_gen::LUT_gen()//constructor build all LUT tables
{
    masksGen();
    kingGen();
    knightGen();
    pawnGen();
    bishopGen();
    rookGen();
}
void LUT_gen::masksGen()//generate all masks needed
{
    for(int square=0;square<=56;square+=8)//fileA
    {
        fileA |= squareMask[square];
    }
    fileB=fileA<<1;
    fileG=fileA<<6;
    fileH=fileA<<7;
    for(int sq=0;sq<=7;sq++)//rank1
    {
        rank1 |= squareMask[sq];
    }
    rank2=rank1 <<  8;
    rank3=rank2 <<  8;
    rank7=rank1 << 48;
    rank8=rank1 << 56;
    rank6=rank7 >>  8;
    //castling mask generator
    for(int Square=0;Square<64;Square++)
    {
        castlingMask[Square]=15;
    }
    castlingMask[E1]=12;
    castlingMask[A1]=13;
    castlingMask[H1]=14;
    castlingMask[E8]=3;
    castlingMask[A8]=7;
    castlingMask[H8]=1;
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
        AttackTables::bishopBlindAttacks[square]=(value& ~(fileA|fileH|rank1|rank8));
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
        for(int bit=0;bit<sqNumber;bit++)//loop for every bit in p
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
        while(rank<6)
        {
            rank++;
            value |=squareMask[(rank*8)+file];  
        }
        rank=(square / 8);
        file=(square % 8);
        while(rank>1)
        {
            rank--;
            value |=squareMask[(rank*8)+file];          
        }
        rank=(square / 8);
        file=(square % 8);
        while(file<6)
        {
        file++;
        value |=squareMask[(rank*8)+file];  
        }
        rank=(square / 8);
        file=(square % 8);
        while(file>1)
        {
            file--;
            value |=squareMask[(rank*8)+file];
        }
       AttackTables::rookBlindAttacks[square]=value;
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
BitBoard LUT_gen::queenAttacks(int square)
{
    //i used uint64_t because it's faster and this func used too many times in a sec
    uint64_t bishop_index=((Board_variables::occupied&AttackTables::bishopBlindAttacks[square]) * magicUtils::bishop_magicN[square])>>magicUtils::bishop_shift_number[square];
    uint64_t rook_index=((Board_variables::occupied&AttackTables::rookBlindAttacks[square]) * magicUtils::rook_magicN[square])>>magicUtils::rook_shift_number[square];
    return (AttackTables::bishopAttacks[square][bishop_index]|AttackTables::rookAttacks[square][rook_index]);
}