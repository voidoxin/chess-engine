#include "../../include/move_generator/Pseudo_move_generator.h"
#include "../../include/move_generator/attack_tables.h"
using BitBoard=uint64_t;
using namespace Board_variables;
using namespace masks;
inline void PseudoGen::addMove(int from,int to,int flag,moveList &depth)
{
    depth.moves[depth.count]=to|(from<<6)|(flag<<12);
    depth.count++;
}
inline int PseudoGen::bishopIndexCalc(const int square)
{
    return (((occupied & AttackTables::bishopBlindAttacks[square])*magicUtils::bishop_magicN[square])>>magicUtils::bishop_shift_number[square]);//index formula by magic numbers
}
inline int PseudoGen::rookIndexCalc(const int square)
{
    return (((occupied & AttackTables::rookBlindAttacks[square])*magicUtils::rook_magicN[square])>>magicUtils::rook_shift_number[square]);
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
inline void PseudoGen::knightQuGen(const BitBoard& knightSquare,moveList &depth)
{
    BitBoard tempAttackTable;
    BitBoard knightSq=knightSquare;
    int square;
    int attackSquare;
    int flag;
    while(knightSq)
    {
        square=__builtin_ctzll(knightSq);
        tempAttackTable=AttackTables::knightAttacks[square]& ~occupied;
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
inline void PseudoGen::kingQuGen(const BitBoard& kingSquares,moveList &depth)
{
    BitBoard tempAttackTable;
    BitBoard kingSq=kingSquares;
    int square;//king square
    int attackSquare;
    square=__builtin_ctzll(kingSq);
    tempAttackTable=AttackTables::kingAttacks[square]& ~occupied;
    //normal quiet move
    while(tempAttackTable)
    {
            attackSquare=__builtin_ctzll(tempAttackTable);
            addMove(square,attackSquare,0,depth);//add quiet move to moves list 0 flag is quiet
            tempAttackTable&= (tempAttackTable-1);//remove square after add it to move list
    }
}
inline void PseudoGen::WhitekingCastleGen(moveList &depth)
{
    if(castlingRights & 1 && !(occupied & (squareMask[G1]|squareMask[F1])))
    {
        addMove(E1,G1,2,depth);
    }
    if(castlingRights & 2 && !(occupied & (squareMask[B1]|squareMask[C1]|squareMask[D1])))
    {
        addMove(E1,C1,3,depth);
    }
}
inline void PseudoGen::BlackkingCastleGen(moveList &depth)
{
    if(castlingRights & 4 && !(occupied &occupied & (squareMask[G8]|squareMask[F8])))
    {
        addMove(E8,G8,2,depth);
    }
    if(castlingRights & 8 && !(occupied & (squareMask[B8]|squareMask[C8]|squareMask[D8])))
    {
        addMove(E8,C8,3,depth);
    }
}
inline void PseudoGen::WhitePawnQuGen(moveList &depth)
{
    BitBoard OneStep=((board_table[static_cast<int>(pieces::White_pawns)]& ~rank7)<<8)& ~occupied;
    BitBoard doubleStep=((OneStep & rank3)<<8)& ~occupied;
    int attackSq;//square the pawn will be moved to
    while(OneStep)
    {
        attackSq=__builtin_ctzll(OneStep);
        addMove(attackSq-8,attackSq,0,depth);
        OneStep&= (OneStep-1);
    }
    while(doubleStep)
    {
        attackSq=__builtin_ctzll(doubleStep);
        addMove(attackSq-16,attackSq,1,depth);
        doubleStep&= (doubleStep-1);
    }
    OneStep=((board_table[static_cast<int>(pieces::White_pawns)]& rank7)<<8)& ~occupied;
    while(OneStep)
    {
        attackSq=__builtin_ctzll(OneStep);
        addMove(attackSq-8,attackSq,11,depth);//promotion to queen
        addMove(attackSq-8,attackSq,10,depth);//promotion to rook
        addMove(attackSq-8,attackSq,8,depth);//promotion to knight
        addMove(attackSq-8,attackSq,9,depth);//promotion to bishop
        OneStep&=(OneStep-1);
    }
}
inline void PseudoGen::BlackPawnQuGen(moveList &depth)
{
    BitBoard OneStep=((board_table[static_cast<int>(pieces::Black_pawns)]& ~rank2)>>8)& ~occupied;
    BitBoard doubleStep=((OneStep & rank6)>>8)& ~occupied;
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
        addMove(attackSq+16,attackSq,1,depth);
        doubleStep&= (doubleStep-1);
    }
    OneStep=((board_table[static_cast<int>(pieces::White_pawns)]& rank7)<<8)& ~occupied;
    while(OneStep)
    {
        attackSq=__builtin_ctzll(OneStep);
        addMove(attackSq+8,attackSq,11,depth);//promotion to queen
        addMove(attackSq+8,attackSq,10,depth);//promotion to rook
        addMove(attackSq+8,attackSq,8,depth);//promotion to knight
        addMove(attackSq+8,attackSq,9,depth);//promotion to bishop
        OneStep&=(OneStep-1);
    }
}
inline void PseudoGen::WhitePawnCapGen(moveList &depth)
{   
    BitBoard PawnSq=board_table[static_cast<int>(pieces::White_pawns)] & ~rank7;//BitBoard of all white pawns on the board
    int PawnSquare;//the square of one pawn
    BitBoard attack_squares;
    int TheAttackSquare;
    BitBoard SqCanCap;
    BitBoard PawnsCanCap;
    while(PawnSq)//normal capture move
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        attack_squares=AttackTables::pawnAttacks[0][PawnSquare] & BlackPieces;
        while(attack_squares)
        {
            addMove(PawnSquare,__builtin_ctzll(attack_squares),4,depth);
            attack_squares&=(attack_squares-1);
        }
        PawnSq&= (PawnSq-1);
    }
    if(enPassantSq!=-1)//capture en pasant
    {
        SqCanCap=AttackTables::pawnAttacks[1][enPassantSq];//i used the enemy pawn attacks in enPasant square to know square should pawn be to capture en passant
        PawnsCanCap=SqCanCap & board_table[static_cast<int>(pieces::White_pawns)];
        while(PawnsCanCap)
        {
            addMove(__builtin_ctzll(PawnsCanCap),enPassantSq,5,depth);
            PawnsCanCap&=(PawnsCanCap-1);
        }
    }
    PawnSq=board_table[static_cast<int>(pieces::White_pawns)] & rank7;
    while(PawnSq)//promotion with capture
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        attack_squares=AttackTables::pawnAttacks[0][PawnSquare]& BlackPieces;
        while(attack_squares)
        {
            TheAttackSquare=__builtin_ctzll(attack_squares);
            addMove(PawnSquare,TheAttackSquare,12,depth);
            addMove(PawnSquare,TheAttackSquare,13,depth);
            addMove(PawnSquare,TheAttackSquare,14,depth);
            addMove(PawnSquare,TheAttackSquare,15,depth);
            attack_squares&=(attack_squares-1);
        }
        PawnSq&=(PawnSq-1);
    }
}
inline void PseudoGen::BlackPawnCapGen(moveList &depth)
{   
    BitBoard PawnSq=board_table[static_cast<int>(pieces::Black_pawns)] & ~rank2;//BitBoard of all white pawns on the board
    int PawnSquare;//the square of one pawn
    BitBoard attack_squares;
    int TheAttackSquare;
    BitBoard SqCanCap;
    BitBoard PawnsCanCap;
    while(PawnSq)//normal capture move
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        attack_squares=AttackTables::pawnAttacks[1][PawnSquare] & BlackPieces;
        while(attack_squares)
        {
            addMove(PawnSquare,__builtin_ctzll(attack_squares),4,depth);
            attack_squares&=(attack_squares-1);
        }
        PawnSq&= (PawnSq-1);
    }
    if(enPassantSq!=-1)//capture en pasant
    {
        SqCanCap=AttackTables::pawnAttacks[0][enPassantSq];//i used the enemy pawn attacks in enPasant square to know square should pawn be to capture en passant
        PawnsCanCap=SqCanCap & board_table[static_cast<int>(pieces::Black_pawns)];
        while(PawnsCanCap)
        {
            addMove(__builtin_ctzll(PawnsCanCap),enPassantSq,5,depth);
            PawnsCanCap&=(PawnsCanCap-1);
        }
    }
    PawnSq=board_table[static_cast<int>(pieces::White_pawns)] & rank2;
    while(PawnSq)//promotion with capture
    {
        PawnSquare=__builtin_ctzll(PawnSq);
        attack_squares=AttackTables::pawnAttacks[1][PawnSquare]& BlackPieces;
        while(attack_squares)
        {
            TheAttackSquare=__builtin_ctzll(attack_squares);
            addMove(PawnSquare,TheAttackSquare,12,depth);
            addMove(PawnSquare,TheAttackSquare,13,depth);
            addMove(PawnSquare,TheAttackSquare,14,depth);
            addMove(PawnSquare,TheAttackSquare,15,depth);
            attack_squares&=(attack_squares-1);
        }
        PawnSq&=(PawnSq-1);
    }
}
inline void PseudoGen::queenCapGen(const BitBoard& QueenSquares,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard queenSquares=QueenSquares;
    BitBoard attack_squares;
    int queenSq;
    while(queenSquares)
    {
        queenSq=__builtin_ctzll(queenSquares);
        attack_squares=LUT_gen::queenAttacks(queenSq)& enemy_pieces;
        while(attack_squares)
        {
            addMove(queenSq,__builtin_ctzll(attack_squares),4,depth);
            attack_squares&=(attack_squares-1);
        }
        queenSquares&=(queenSquares-1);
    }
}
inline void PseudoGen::queenQuGen(const BitBoard& QueenSquares,moveList &depth)
{
    BitBoard queenSquares=QueenSquares;
    BitBoard attack_squares;
    int queenSq;
    while(queenSquares)
    {
        queenSq=__builtin_ctzll(queenSquares);
        attack_squares=LUT_gen::queenAttacks(queenSq)& ~occupied;
        while(attack_squares)
        {
            addMove(queenSq,__builtin_ctzll(attack_squares),0,depth);
            attack_squares&=(attack_squares-1);
        }
        queenSquares&=(queenSquares-1);
    }
}
inline void PseudoGen::bishopCapGen(const BitBoard& bishopSquares,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard bishop_squares=bishopSquares;
    BitBoard attack_squares;
    int bishopSq;
    while(bishop_squares)
    {
        bishopSq=__builtin_ctzll(bishop_squares);
        attack_squares=AttackTables::bishopAttacks[bishopSq][bishopIndexCalc(bishopSq)]& enemy_pieces;
        while(attack_squares)
        {
            addMove(bishopSq,__builtin_ctzll(attack_squares),4,depth);
            attack_squares&=(attack_squares-1);
        }
        bishop_squares&=(bishop_squares-1);
    }
}
inline void PseudoGen::bishopQuGen(const BitBoard& bishopSquares,moveList &depth)
{
    BitBoard bishop_squares=bishopSquares;
    BitBoard attack_squares;
    int bishopSq;
    while(bishop_squares)
    {
        bishopSq=__builtin_ctzll(bishop_squares);
        attack_squares=AttackTables::bishopAttacks[bishopSq][bishopIndexCalc(bishopSq)]& ~occupied;
        while(attack_squares)
        {
            addMove(bishopSq,__builtin_ctzll(attack_squares),0,depth);
            attack_squares&=(attack_squares-1);
        }
        bishop_squares&=(bishop_squares-1);
    }
}
inline void PseudoGen::rookCapGen(const BitBoard& rookSquares,const BitBoard& enemy_pieces,moveList &depth)
{
    BitBoard rook_squares=rookSquares;
    int rookSq;
    BitBoard attack_squares;
    while(rook_squares)
    {
        rookSq=__builtin_ctzll(rook_squares);
        attack_squares=AttackTables::rookAttacks[rookSq][rookIndexCalc(rookSq)]& enemy_pieces;
        while(attack_squares)
        {
            addMove(rookSq,__builtin_ctzll(attack_squares),4,depth);
            attack_squares&=(attack_squares-1);
        }
        rook_squares&=(rook_squares-1);
    }
}
inline void PseudoGen::rookQuGen(const BitBoard& rookSquares,moveList &depth)
{
    BitBoard rook_squares=rookSquares;
    int rookSq;
    BitBoard attack_squares;
    while(rook_squares)
    {
        rookSq=__builtin_ctzll(rook_squares);
        attack_squares=AttackTables::rookAttacks[rookSq][rookIndexCalc(rookSq)]& ~occupied;
        while(attack_squares)
        {
            addMove(rookSq,__builtin_ctzll(attack_squares),0,depth);
            attack_squares&=(attack_squares-1);
        }
        rook_squares&=(rook_squares-1);
    }
}
void PseudoGen::QuMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightQuGen(board_table[static_cast<int>(pieces::Black_knights)],depth);
        kingQuGen(board_table[static_cast<int>(pieces::Black_king)],depth);
        BlackkingCastleGen(depth);
        BlackPawnQuGen(depth);
        queenQuGen(board_table[static_cast<int>(pieces::Black_queen)],depth);
        bishopQuGen(board_table[static_cast<int>(pieces::Black_bishops)],depth);
        rookQuGen(board_table[static_cast<int>(pieces::Black_rooks)],depth);
        return;
    }
        knightQuGen(board_table[static_cast<int>(pieces::White_knights)],depth);
        kingQuGen(board_table[static_cast<int>(pieces::White_king)],depth);
        WhitekingCastleGen(depth);
        WhitePawnQuGen(depth);
        queenQuGen(board_table[static_cast<int>(pieces::White_queen)],depth);
        bishopQuGen(board_table[static_cast<int>(pieces::White_bishops)],depth);
        rookQuGen(board_table[static_cast<int>(pieces::White_rooks)],depth);
}
void PseudoGen::CapMoveGen(moveList &depth)
{
    if(side_to_move)
    {
        knightCapGen(board_table[static_cast<int>(pieces::Black_knights)],WhitePieces,depth);
        kingCapGen(board_table[static_cast<int>(pieces::Black_king)],WhitePieces,depth);
        BlackPawnCapGen(depth);
        queenCapGen(board_table[static_cast<int>(pieces::Black_queen)],WhitePieces,depth);
        bishopCapGen(board_table[static_cast<int>(pieces::Black_bishops)],WhitePieces,depth);
        rookCapGen(board_table[static_cast<int>(pieces::Black_rooks)],WhitePieces,depth);
        return;
    }
        knightCapGen(board_table[static_cast<int>(pieces::White_knights)],BlackPieces,depth);
        kingCapGen(board_table[static_cast<int>(pieces::White_king)],BlackPieces,depth);
        WhitePawnCapGen(depth);
        queenCapGen(board_table[static_cast<int>(pieces::White_queen)],BlackPieces,depth);
        bishopCapGen(board_table[static_cast<int>(pieces::White_bishops)],BlackPieces,depth);
        rookCapGen(board_table[static_cast<int>(pieces::White_rooks)],BlackPieces,depth);
}