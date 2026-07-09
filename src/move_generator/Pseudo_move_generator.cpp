#include "../../include/move_generator/Pseudo_move_generator.h"
#include "../../include/move_generator/attack_tables.h"
using BitBoard=uint64_t;
using namespace Board_variables;
inline void PseudoGen::addMove(int from,int to,int flag,moveList &depth)
{
    depth.moves[depth.count]=from|(to<<6)|(flag<<12);
    depth.count++;
}
inline void PseudoGen::knightCapGen(const BitBoard& knightSquares,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard tempAttackTable;
    BitBoard knightSq=knightSquares;
    int square;
    int attackSquare;
    int flag;
    while(knightSq)
    {
        square=__builtin_ctzll(knightSq);
        tempAttackTable=AttackTables::knightAttacks[square]& enemy_pieces;
        while(tempAttackTable)
        {
            attackSquare=__builtin_ctzll(tempAttackTable);
            addMove(square,attackSquare,4,depth);//add capture move to moves list 4 flag is capture
            tempAttackTable&= (tempAttackTable-1);//remove square after add it to move list
        }
        knightSq&= (knightSq-1);
    }
}
inline void PseudoGen::knightQuGen(const BitBoard& friendly_pieces,const BitBoard& knightSquare,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard tempAttackTable;
    BitBoard knightSq=knightSquare;
    int square;
    int attackSquare;
    int flag;
    while(knightSq)
    {
        square=__builtin_ctzll(knightSq);
        tempAttackTable=(AttackTables::knightAttacks[square]& ~friendly_pieces)& ~enemy_pieces;
        while(tempAttackTable)
        {
            attackSquare=__builtin_ctzll(tempAttackTable);
            addMove(square,attackSquare,0,depth);//add quiet move to move list 0 flag is quiet 
            tempAttackTable&= (tempAttackTable-1);//remove square after add it to move list
        }
        knightSq&= (knightSq-1);
    }
}    
void PseudoGen::QuMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightQuGen(BlackPieces,board_table[static_cast<int>(pieces::Black_knights)],WhitePieces,depth);
        return;
    }
        knightQuGen(WhitePieces,board_table[static_cast<int>(pieces::White_knights)],BlackPieces,depth);
}
void PseudoGen::CapMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightCapGen(board_table[static_cast<int>(pieces::Black_knights)],WhitePieces,depth);
        return;
    }
        knightCapGen(board_table[static_cast<int>(pieces::White_knights)],BlackPieces,depth);
}