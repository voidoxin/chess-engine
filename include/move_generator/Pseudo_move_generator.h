#pragma once 
#include <cstdint>
using BitBoard= uint64_t;
struct moveList{
    uint16_t moves[257];
    int count=0;
};
/*
flags in moves array in decimal
0:quiet move
1:Pawn double jump 
2:king-side castle
3:queen-side castle
4:captures
5:En-passant capture
8:promotion to knight
9:promotion to bishop
10:promotion to rook
11:promotion to queen
12:promotion to knight with capture
13:promotion to bishop with capture
14:promotion to rook with capture
15:promotion to queen with capture
*/
class PseudoGen
{
    private:
        //helper functions
        void addMove(const int from,const int to,const int flag, moveList &depth);//helper function to add a move to 
        int bishopIndexCalc(const int square,const BitBoard& occupancy);
        int rookIndexCalc(const int square,const BitBoard& occupancy);
        //capture moves generators
        void kingCapGen(const BitBoard& kingSquares,const BitBoard& enemy_pieces,moveList &depth);
        void knightCapGen(const BitBoard& knightSquares,const BitBoard& enemy_pieces,moveList &depth);
        void WhitePawnCapGen(moveList &depth);
        void BlackPawnCapGen(moveList &depth);
        void queenCapGen(moveList &depth,BitBoard& enemy_pieces,BitBoard& QueenSquares);
        //quiet move generator 
        void knightQuGen(const BitBoard& friendly_pieces,const BitBoard& knightSquare,const BitBoard& knightSquares,moveList &depth);
        void kingQuGen(const BitBoard& friendly_pieces,const BitBoard& kingSquares,const BitBoard& enemy_pieces,moveList &depth);
        void WhitePawnQuGen(moveList &depth);
        void BlackPawnQuGen(moveList &depth);
        void queenQuGen(moveList &depth,BitBoard& enemy_pieces,BitBoard& friendly_pieces,BitBoard& QueenSquares);
    public:
        void CapMoveGen(moveList &depth);
        void QuMoveGen(moveList &depth);
};