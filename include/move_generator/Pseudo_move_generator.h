#pragma once 
#include <cstdint>
using BitBoard= uint64_t;
struct moveList{
    BitBoard moves[257];
    int count=0;
};
class PseudoGen
{
    private:
        void addMove(int from,int to,int flag, moveList &depth);//helper function to add a move to 
        void knightCapGen(const BitBoard& knightSquares,const BitBoard& enemy_pieces,moveList &depth);
        void knightQuGen(const BitBoard& friendly_pieces,const BitBoard& knightSquare,const BitBoard& knightSquares,moveList &depth);
    public:
        void CapMoveGen(moveList &depth);
        void QuMoveGen(moveList &depth);
};