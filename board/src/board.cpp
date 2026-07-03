#include "../include/board.h"
#include <string>
#include <cstdint>
using namespace std;
void initSqMask ()
{
    for(int sq=0;sq<64;sq++)
    {
        squareMask[sq]= (1ULL << sq);
    }
}
void Board::delete_piece(pieces piece,int square)
{
    board_table[static_cast<int>(piece)] ^= squareMask[square];
    MailBox[square]=piece;
    occupied^=squareMask[square];
    if(static_cast<int>(p)& 0b1000){
        BlackPieces^=squareMask[square];
        return;
    }
    WhitePieces ^= squareMask[square];
}
void Board::add_piece(pieces p,int square)
{
    board_table[static_cast<int>(p)] |= squareMask[square];
    MailBox[square]=p;
    occupied|=squareMask[square];
    if(static_cast<int>(p)& 0b1000){
        BlackPieces|=squareMask[square];
        return;
    }
    WhitePieces |=squareMask[square];
}
void Board::init()
{
    occupied=0ULL;
    BlackPieces=0ULL;
    WhitePieces=0ULL;
    for (int i=0;i<=13;i++)
    {

        board_table[i]=0ULL;
    }//delete evrything
    add_piece(pieces::Black_king,60);
    add_piece(pieces::Black_queen,59);
    add_piece(pieces::Black_rooks,56);
    add_piece(pieces::Black_rooks,63);
    add_piece(pieces::Black_knights,57;
    add_piece(pieces::Black_knights,62);
    add_piece(pieces::Black_bishops,58);
    add_piece(pieces::Black_bishops,61);
    for(int pawn=48;pawn<=55;pawn++)
    {
        add_piece(pieces::Black_pawns,pawn);
    }
    add_piece(pieces::White_king,4);
    add_piece(pieces::White_queen,3);
    add_piece(pieces::White_rooks,0);
    add_piece(pieces::White_rooks,7);
    add_piece(pieces::White_knights,1);
    add_piece(pieces::White_knights,6);
    add_piece(pieces::White_bishops,2);
    add_piece(pieces::White_bishops,5);
    for(int pawn=8;pawn<=15;pawn++)
    {
        add_piece(pieces::White_pawns,pawn);
    }
    
}
Board::Board(){
    initSqMask();
    init();
}
void Board::move_piece(pieces piece,int from,int to)
{
    int start=2+(side_to_move==0 ? 6 : 0);
    int end= start+5;
    for (int i=start;i<=end;i++)
    {
        if(board_table[i] & squareMask[to] =!0)
        {
            delete_piece(static_cast<pieces>(i),to);
            counter=-1;
            break;
        }
    }//capturing
    if(!((static_cast<int>(pieces)^7)&11))
    {
        counter=-1;
    }
        delete_piece(pieces::piece,from);
        add_piece(pices::piece,to);
    side_to_move ^=1;
    counter++;
}
pieces Board::get_piece(int square){return MailBox[square];}