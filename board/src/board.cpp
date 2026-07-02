#include "../include/board.h"
#include <iostream>
#include <cstdint>
static void refresh(int king_square,int queen_square)
{
    // remove old board
    king=0;
    queen=0;
    knights=0;
    Rooks=0;
    Bishops=0;
    Pawns=0;
    // new board init
    king= 1ULL << king_square;
    queen= 1ULL << queen_square;
    //pawns
    for(int pawn=8,pawn<=15,pawn++;)
    {
        Pawns |= (1ULL << pawn);
    }
    rooks |= (1ULL << 0);
    rooks |= (1ULL << 7);
    knights |= (1ULL << 6);
    knights |= (1ULL << 1);
    Bishops |= (1ULL << 5);
    Bishops |= (1ULL << 2);
}
void WhitePieces::refresh_board()
{
    refresh(4,3);
}
void BlackPieces::refresh_board()
{
    refresh(3,4);
}
