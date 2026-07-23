/*
    this file is board representation on bitboard and all game variables
*/
#include "../../include/board/board.h"
#include <string>
#include <iostream>
#include <cstdint>
using namespace std;
using namespace Board_variables;
BitBoard squareMask[64];
void initSqMask ()
{
    for(int sq=0;sq<64;sq++)
    {
        squareMask[sq]= (1ULL << sq);
    }
}
void Board::delete_piece(pieces piece,int square)
{
    board_table[static_cast<int>(piece)] &= ~squareMask[square];//remove piece from board []
    MailBox[square]=pieces::empty;//remove piece from MailBox[]
    occupied &= ~squareMask[square];
    if(static_cast<int>(piece)& 0b1000){//if color is black
        BlackPieces &= ~squareMask[square];
        return;
    }
    WhitePieces &= ~squareMask[square];
}
void Board::add_piece(pieces p,int square)
{
    board_table[static_cast<int>(p)] |= squareMask[square];//add piece to board[]
    MailBox[square]=p;//add piece to MailBox[]
    occupied|=squareMask[square];
    if(static_cast<int>(p)& 0b1000){//if color is black
        BlackPieces|=squareMask[square];
        return;
    }
    WhitePieces |=squareMask[square];
}
void Board::board_init()
{
    occupied=0ULL;
    BlackPieces=0ULL;
    WhitePieces=0ULL;
    for (int M=0;M<64;M++)
    {
        MailBox[M]=pieces::empty;
    }//make all squares on MailBox empty
    for (int i=0;i<=13;i++)
    {

        board_table[i]=0ULL;
    }//delete everything on board
    add_piece(pieces::Black_king,E8);
    add_piece(pieces::Black_queen,D8);
    add_piece(pieces::Black_rooks,A8);
    add_piece(pieces::Black_rooks,H8);
    add_piece(pieces::Black_knights,B8);
    add_piece(pieces::Black_knights,G8);
    add_piece(pieces::Black_bishops,C8);
    add_piece(pieces::Black_bishops,F8);
    for(int pawn=48;pawn<=55;pawn++)
    {
        add_piece(pieces::Black_pawns,pawn);
    }
    add_piece(pieces::White_king,E1);
    add_piece(pieces::White_queen,D1);
    add_piece(pieces::White_rooks,A1);
    add_piece(pieces::White_rooks,H1);
    add_piece(pieces::White_knights,B1);
    add_piece(pieces::White_knights,G1);
    add_piece(pieces::White_bishops,C1);
    add_piece(pieces::White_bishops,F1);
    for(int pawn=8;pawn<=15;pawn++)
    {
        add_piece(pieces::White_pawns,pawn);
    }
    //add the startup piece placement
}
Board::Board(){
    initSqMask();
    board_init();
}//constructor init board for first boot
void Board::move_piece(pieces piece,int from,int to)
{
    if(MailBox[from]!=pieces::empty)
    {//debug if statement remove before release
        if(MailBox[to]!=pieces::empty)
        {
            delete_piece(MailBox[to],to);
            draw_counter=-1;
        }//method
    if(!((static_cast<int>(piece)^7)&11))//check if the piece moved is pawn "!((static_cast<int>(piece)^7)&11)" return true if the piece is black
    {
        draw_counter=-1;
    }
        delete_piece(piece,from);
        add_piece(piece,to);
    side_to_move ^=1;
    draw_counter++;
    }else{cout<<"debug a piece moved from empty square is"<<from<<endl;}
}
pieces Board::get_piece(int square) const {return MailBox[square];}
void Board::print_board()
{
    for(int i=0;i<8;i++)
    {
        for(int x=0;x<8;x++)
        {
            cout<<"|";
            if(MailBox[(i*8)+x]==pieces::empty)
            {
                cout<<". ";
            }else {
                switch (static_cast<int>(MailBox[(i*8)+x])){
                    case static_cast<int>(pieces::Black_king):
                        cout<<"BK";
                        break;
                    case static_cast<int>(pieces::Black_queen):
                        cout<<"BQ";
                        break;
                    case static_cast<int>(pieces::Black_bishops):
                        cout<<"BB";
                        break;
                    case static_cast<int>(pieces::Black_knights):
                        cout<<"Bkn";
                        break;
                    case static_cast<int>(pieces::Black_rooks):
                        cout<<"BR";
                        break;
                    case static_cast<int>(pieces::Black_pawns):
                        cout<<"BP";
                        break;
                    case static_cast<int>(pieces::White_king):
                        cout<<"WK";
                        break;
                    case static_cast<int>(pieces::White_queen):
                        cout<<"WQ";
                        break;
                    case static_cast<int>(pieces::White_bishops):
                        cout<<"WB";
                        break;
                    case static_cast<int>(pieces::White_knights):
                        cout<<"Wkn";
                        break;
                    case static_cast<int>(pieces::White_rooks):
                        cout<<"WR";
                        break;
                    case static_cast<int>(pieces::White_pawns):
                        cout<<"WP";
                        break;
                }
            }           
        }   cout<<endl;
    }
}