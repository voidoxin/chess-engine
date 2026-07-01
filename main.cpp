#include <iostream>
int board [8][8]={
	{-4, -2, -3, -5, -6, -3, -2, -4},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1,  1},
        { 4,  2,  3,  5,  6,  3,  2,  4}
};
void printBoard()
{
	system("clear")
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            cout << chessBoard[row][col] << "\t"; 
        }
        cout << endl;
    }
}
int main()
{
  printBoard();



return 0;
}
