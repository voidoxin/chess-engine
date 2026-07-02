#pragma once
#include <string>
using namespace std;
using BitBoard uint64_t;
struct WhitePieces{
        BitBoard king;
        BitBoard queen;
        BitBoard Pawns;
        BitBoard knights;
        BitBoard Bishops;
        BitBoard Rooks;
            void refresh_board();
            void move(int old_square,int new_square);
            // clculations
}
struct BlackPieces{
        BitBoard king;
        BitBoard queen;
        BitBoard Pawns;
        BitBoard knights;
        BitBoard Bishops;
        BitBoard Rooks;
            void refresh_board();
            void move(int old_square,int new_square);
            // clculations
}