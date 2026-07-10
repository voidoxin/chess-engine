#include "../../include/move_generator/Pseudo_move_generator.h"
#include "../../include/move_generator/attack_tables.h"
using BitBoard=uint64_t;
using namespace Board_variables;
using namespace files_ranks;
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
inline void PseudoGen::kingCapGen(const BitBoard& kingSquares,const BitBoard& enemy_pieces,moveList &depth)    
{
    BitBoard tempAttackTable;
    BitBoard kingSq=kingSquares;
    int square;
    int attackSquare;
    int flag;
    square=__builtin_ctzll(kingSq);
    tempAttackTable=AttackTables::kingAttacks[square]& enemy_pieces;
    while(tempAttackTable)
    {
            attackSquare=__builtin_ctzll(tempAttackTable);
            addMove(square,attackSquare,4,depth);//add capture move to moves list 4 flag is capture
            tempAttackTable&= (tempAttackTable-1);//remove square after add it to move list
    }
}
inline void PseudoGen::kingQuGen(const BitBoard& friendly_pieces,const BitBoard& kingSquares,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard tempAttackTable;
    BitBoard kingSq=kingSquares;
    int square;
    int attackSquare;
    int flag;
    square=__builtin_ctzll(kingSq);
    tempAttackTable=(AttackTables::kingAttacks[square]& ~friendly_pieces)& ~enemy_pieces;
    while(tempAttackTable)
    {
            attackSquare=__builtin_ctzll(tempAttackTable);
            addMove(square,attackSquare,0,depth);//add quiet move to moves list 0 flag is quiet
            tempAttackTable&= (tempAttackTable-1);//remove square after add it to move list
    }
    kingSq&= (kingSq-1);
}
inline void PseudoGen::WhitePawnQuGen(moveList &depth)
{
    BitBoard OneStep=((board_table[static_cast<int>(pieces::White_pawns)]& ~rank7)<<8)& ~occupied;
    BitBoard doubleStep=((OneStep & rank3)<<8)& ~occupied;
    int attackSq;
    while(OneStep)
    {
        attackSq=__builtin_ctzll(OneStep);
        addMove(attackSq-8,attackSq,0,depth);
        OneStep&= (OneStep-1);
    }
    while(doubleStep)
    {
        attackSq=__builtin_ctzll(doubleStep);
        addMove(attackSq-8,attackSq,1,depth);
        doubleStep&= (doubleStep-1);
    }
}
inline void PseudoGen::BlackPawnQuGen(moveList &depth)
{
    BitBoard OneStep=((board_table[static_cast<int>(pieces::White_pawns)]& ~rank7)>>8)& ~occupied;
    BitBoard doubleStep=((OneStep & rank3)>>8)& ~occupied;
    int attackSq;
    while(OneStep)
    {
        attackSq=__builtin_ctzll(OneStep);
        addMove(attackSq+8,attackSq,0,depth);
        OneStep&= (OneStep-1);
    }
    while(doubleStep)
    {
        attackSq=__builtin_ctzll(doubleStep);
        addMove(attackSq+8,attackSq,1,depth);
        doubleStep&= (doubleStep-1);
    }
}
inline void PseudoGen::WhitePawnCapGen(moveList &depth)
{   
    BitBoard PawnSq=board_table[static_cast<int>(pieces::White_pawns)] & ~rank7;//BitBoard of all white pawns on the board
    int PawnSquare;//the square of one pawn
    int AttackSquare;
    BitBoard SqCanCap;
    BitBoard PawnsCanCap;
    while(PawnSq)//normal capture move
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        AttackSquare=AttackTables::pawnAttacks[0][PawnSquare] & BlackPieces;
        while(AttackSquare)
        {
            addMove(PawnSquare,__builtin_ctzll(AttackSquare),4,depth);
            AttackSquare&=(AttackSquare-1);
        }
        PawnSq&= (PawnSq-1);
    }
    if(enPassantSq!=-1)
    {
        SqCanCap=AttackTables::pawnAttacks[1][enPassantSq];//i used the enemy pawn attacks in enPasant square to know square should pawn be to capture en passant
        PawnsCanCap=SqCanCap & board_table[static_cast<int>(pieces::White_pawns)];
        while(PawnsCanCap)
        {
            addMove(__builtin_ctzll(PawnsCanCap),enPassantSq,5,depth);
            PawnsCanCap&=(PawnsCanCap-1);
        }
    }
}
inline void PseudoGen::BlackPawnCapGen(moveList &depth)
{   
    BitBoard PawnSq=board_table[static_cast<int>(pieces::Black_pawns)] & ~rank2;//BitBoard of all black pawns on the board
    int PawnSquare;//the square of one pawn
    int AttackSquare;
    BitBoard SqCanCap;//square where pawn can capture en passant
    BitBoard PawnsCanCap;//pawns squares who can capture en passant
    while(PawnSq)//normal capture move
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        AttackSquare=AttackTables::pawnAttacks[1][PawnSquare] & BlackPieces;
        while(AttackSquare)
        {
            addMove(PawnSquare,__builtin_ctzll(AttackSquare),4,depth);
            AttackSquare&=(AttackSquare-1);
        }
        PawnSq&= (PawnSq-1);
    }
    if(enPassantSq!=-1)
    {
        SqCanCap=AttackTables::pawnAttacks[0][enPassantSq];//i used the enemy pawn attacks in enPasant square to know square should pawn be to capture en passant
        PawnsCanCap=SqCanCap & board_table[static_cast<int>(pieces::Black_pawns)];
        while(PawnsCanCap)
        {
            addMove(__builtin_ctzll(PawnsCanCap),enPassantSq,5,depth);
            PawnsCanCap&=(PawnsCanCap-1);
        }
    }    
}
void PseudoGen::QuMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightQuGen(BlackPieces,board_table[static_cast<int>(pieces::Black_knights)],WhitePieces,depth);
        kingQuGen(BlackPieces,board_table[static_cast<int>(pieces::Black_king)],WhitePieces,depth);
        BlackPawnQuGen(depth);
        return;
    }
        knightQuGen(WhitePieces,board_table[static_cast<int>(pieces::White_knights)],BlackPieces,depth);
        kingQuGen(WhitePieces,board_table[static_cast<int>(pieces::White_king)],BlackPieces,depth);
        WhitePawnQuGen(depth);

}
void PseudoGen::CapMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightCapGen(board_table[static_cast<int>(pieces::Black_knights)],WhitePieces,depth);
        kingCapGen(board_table[static_cast<int>(pieces::Black_king)],WhitePieces,depth);
        BlackPawnCapGen(depth);
        return;
    }
        knightCapGen(board_table[static_cast<int>(pieces::White_knights)],BlackPieces,depth);
        WhitePawnCapGen(depth);
}