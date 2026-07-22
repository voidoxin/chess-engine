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
class MoveGen
{
    private:
        //helper functions
        void addMove(const int from,const int to,const int flag, moveList &depth);//helper function to add a move to 
        int bishopIndexCalc(const int square);
        int rookIndexCalc(const int square);
        BitBoard PieceAttacked(BitBoard& pieceSquares,int& color);
        //capture moves generators
        void kingCapGen(const BitBoard& kingSquares,const BitBoard& enemy_pieces,moveList &depth);
        void knightCapGen(const BitBoard& knightSquares,const BitBoard& enemy_pieces,moveList &depth);
        void WhitePawnCapGen(moveList &depth);
        void BlackPawnCapGen(moveList &depth);
        void queenCapGen(const BitBoard& QueenSquares,const BitBoard& enemy_pieces,moveList &depth);
        void bishopCapGen(const BitBoard& bishopSquares,const BitBoard& enemy_pieces,moveList &depth);
        void rookCapGen(const BitBoard& rookSquares,const BitBoard& enemy_pieces,moveList &depth);
        //quiet move generators 
        void knightQuGen(const BitBoard& knightSquare,moveList &depth);
        void kingQuGen(const BitBoard& kingSquares,moveList &depth);
        void BlackkingCastleGen(moveList &depth);
        void WhitekingCastleGen(moveList &depth);
        void WhitePawnQuGen(moveList &depth);
        void BlackPawnQuGen(moveList &depth);
        void queenQuGen(const BitBoard& QueenSquares,moveList &depth);
        void bishopQuGen(const BitBoard& bishopSquares,moveList &depth);
        void rookQuGen(const BitBoard& rookSquares,moveList &depth);
        //checkMove generators
        void kingEscapeGen(const int& kingSquare,const BitBoard& dangerSquares,const BitBoard& friendly_pieces,moveList &depth);
        void knightCheckMoveGen(const BitBoard& knightSquares,const BitBoard& dangerSquare,const BitBoard& blockSquares,moveList &depth);//todo
        void WhitePawnCheckMoveGen(const BitBoard& pawnSquares,const BitBoard& dangerSquare,const BitBoard& blockSquares,moveList &depth);//todo
        void BlackPawnCheckMoveGen(const BitBoard& pawnSquares,const BitBoard& dangerSquare,const BitBoard& blockSquares,moveList &depth);//todo
    public:
        void CapMoveGen(moveList &depth);
        void QuMoveGen(moveList &depth);
        void CheckMoveGen(moveList &depth);
};