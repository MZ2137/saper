#include <iostream>
#include <random>
#include <vector>

const int ROWS = 10;
const int COLUMNS = 10;
const int MINES = 15;

using namespace std;

int** generateBoard()
{
    int** board = new int* [ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        board[i] = new int[COLUMNS];
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, ROWS - 1);

    int minesPlaced = 0;
    while (minesPlaced < MINES)
    {
        int row = uni(rng);
        int col = uni(rng);
        if (board[row][col] == 0)
        {
            board[row][col] = 9;
            minesPlaced++;
        }
    }

    return board;
}

int main()
{
    int** board = generateBoard();

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
           cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
