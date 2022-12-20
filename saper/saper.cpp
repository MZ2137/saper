#include <iostream>
#include <random>
#include <vector>

const int ROWS = 10;
const int COLUMNS = 10;
const int MINES = 15;

using namespace std;

vector<vector<int>> generateBoard()
{
    vector<vector<int>> board(ROWS, vector<int>(COLUMNS, 0));

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
    vector<vector<int>> board = generateBoard();

    /*
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    */

    return EXIT_SUCCESS;
}
