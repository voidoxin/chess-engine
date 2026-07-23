#pragma once
#include <cstdint>
using BitBoard = uint64_t;
extern BitBoard squareMask[64];
void initSqMask();
enum Square {//square enum
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};
enum class pieces{//black pieces always : index & 0b1000 != 0
    //white pieces from 2 to 7
        empty=0,
        none=1,//testing 
        White_king=2,
        White_queen=3,
        White_rooks=4,
        White_bishops=5,
        White_knights=6,
        White_pawns=7,
        //black pieces from 8 to 13
        Black_king=8,
        Black_queen=9,
        Black_rooks=10,
        Black_bishops=11,
        Black_knights=12,
        Black_pawns=13        
};
namespace Board_variables{//all game variables
        inline BitBoard board_table[14];
        inline BitBoard WhitePieces;     
        inline BitBoard BlackPieces;
        inline BitBoard occupied;     
        inline pieces MailBox[64];
        inline int side_to_move=0;
        inline int draw_counter=0;    
        inline int enPassantSq=-1;
        inline uint8_t castlingRights=15;
}
class Board {
    private:
        void add_piece(pieces p,int square);
        void delete_piece(pieces piece,int square);
    public:
        Board();
        void board_init();
        void move_piece(pieces piece,int from,int to);
        pieces get_piece(int square) const;
        void print_board();

};