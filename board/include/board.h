#pragma once
#include <string>
using namespace std;
using BitBoard uint64_t;
extern BitBoard squareMask[64];
void initSqMask();
enum class pieces{
        empty=0,
        White_king=2,
        White_queen=3,
        White_rooks=4,
        White_bishops=5,
        White_knights=6,
        White_pawns=7,

        Black_king=8,
        Black_queen=9,
        Black_rooks=10,
        Black_bishops=11,
        Black_knights=12,
        Black_pawns=13,        
}
class Board {
    private :
        BitBoard board_table[14];
        int side to move=0;
    public:
        Board();
        void board_init();
        void add_piece();
        void delete_piece(pieces piece,int square);
        void move_piece(pieces piece,int from,int to);
        void get_color();

};