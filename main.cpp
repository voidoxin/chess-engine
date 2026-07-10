#include <iostream>
#include <cstdint>
#include "include/board/board.h"
#include "include/move_generator/attack_tables.h"
#include "include/move_generator/Pseudo_move_generator.h"
#include <chrono>
using namespace std;
int main()
{
    auto start=chrono::high_resolution_clock::now();
    Board board;
    LUT_gen LUT;
    PseudoGen Gen;
    moveList depth1;
    Gen.CapMoveGen(depth1);
    Gen.QuMoveGen(depth1);
    board.print_board();
    auto end=chrono::high_resolution_clock::now();
    auto dur=end-start;
    cout<<"ms:"<<chrono::duration_cast<chrono::milliseconds>(dur).count()<<endl;
    cout<<"nano:"<<chrono::duration_cast<chrono::nanoseconds>(dur).count()<<endl;   
return 0;
}