#include <iostream>
#include <cstdint>
#include "include/board/board.h"
#include "include/move_generator/attack_tables.h"
#include <chrono>
using namespace std;
int main()
{
    auto start=chrono::high_resolution_clock::now();
    Board board;
    LUT_gen LUT;
    board.print_board();
    auto end=chrono::high_resolution_clock::now();
    auto dur=end-start;
    cout<<"ms:"<<chrono::duration_cast<chrono::milliseconds>(dur).count()<<endl;
    cout<<"nano:"<<chrono::duration_cast<chrono::nanoseconds>(dur).count()<<endl;   
return 0;
}