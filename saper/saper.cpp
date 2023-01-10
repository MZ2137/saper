#include <iostream>

using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // (25 * 25 - 99)

int SIDE; 
int MINES; 
bool flag[24][24];

using namespace std;


void clearFLags() {
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			flag[i][j] = false;
		}
	}
}

bool isValid(int row, int col)
{

	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}


bool isMine(int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}


void makeMove(int* x, int* y)
{
	int a, b;
	cout << "Wpisz x i y nastepnego ruchu -> " << endl;
	cin >> a;
	cin >> b;
	*x = a;
	*y = b;
}
void makeFlag(int* x, int* y)
{
	int fx, fb;
	cout << "Wpisz x i y flagi -> " << endl;
	cin >> fx;
	cin >> fb;
	*x = fx;
	*y = fb - 1;
	if (flag[fx][fb] == true) {
		flag[fx][fb] = false;
	}
	else {
		flag[fx][fb] = true;
	}
	
}


void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	cout <<(" ");

	for (i = 0; i < SIDE; i++)
		cout << "\t" << i;

	cout <<("\n");

	for (i = 0; i < SIDE; i++)
	{
		cout << i << "\t";

		for (j = 0; j < SIDE; j++)
			if (flag[i][j] == true) {
				cout << "X\t";
			}
			else {
				cout << myBoard[i][j] << "\t";
			}
			
		cout <<("\n");
	}
}


int countAdjacentMines(int row, int col, int mines[][2],
	char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;

	

	if (isValid(row - 1, col) == true)
	{
		if (isMine(row - 1, col, realBoard) == true)
			count++;
	}

	if (isValid(row + 1, col) == true)
	{
		if (isMine(row + 1, col, realBoard) == true)
			count++;
	}

	if (isValid(row, col + 1) == true)
	{
		if (isMine(row, col + 1, realBoard) == true)
			count++;
	}

	if (isValid(row, col - 1) == true)
	{
		if (isMine(row, col - 1, realBoard) == true)
			count++;
	}

	if (isValid(row - 1, col + 1) == true)
	{
		if (isMine(row - 1, col + 1, realBoard) == true)
			count++;
	}

	if (isValid(row - 1, col - 1) == true)
	{
		if (isMine(row - 1, col - 1, realBoard) == true)
			count++;
	}

	if (isValid(row + 1, col + 1) == true)
	{
		if (isMine(row + 1, col + 1, realBoard) == true)
			count++;
	}

	if (isValid(row + 1, col - 1) == true)
	{
		if (isMine(row + 1, col - 1, realBoard) == true)
			count++;
	}

	return (count);
}


bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
	int mines[][2], int row, int col, int* movesLeft)
{

	if (myBoard[row][col] != '-')
		return (false);

	int i, j;


	if (realBoard[row][col] == '*')
	{
		myBoard[row][col] = '*';

		for (i = 0; i < MINES; i++)
			myBoard[mines[i][0]][mines[i][1]] = '*';
		system("cls");
		printBoard(myBoard);
		cout <<("\nPrzegrales!\n");
		return (true);
	}

	else
	{
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{
			if (isValid(row - 1, col) == true)
			{
				if (isMine(row - 1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col, movesLeft);
			}

			if (isValid(row + 1, col) == true)
			{
				if (isMine(row + 1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col, movesLeft);
			}

			if (isValid(row, col + 1) == true)
			{
				if (isMine(row, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col + 1, movesLeft);
			}

			if (isValid(row, col - 1) == true)
			{
				if (isMine(row, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col - 1, movesLeft);
			}

			if (isValid(row - 1, col + 1) == true)
			{
				if (isMine(row - 1, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
			}

			if (isValid(row - 1, col - 1) == true)
			{
				if (isMine(row - 1, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
			}

			if (isValid(row + 1, col + 1) == true)
			{
				if (isMine(row + 1, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
			}

			if (isValid(row + 1, col - 1) == true)
			{
				if (isMine(row + 1, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
			}
		}

		return (false);
	}
}

void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE * MAXSIDE];

	memset(mark, false, sizeof(mark));

	for (int i = 0; i < MINES; )
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		if (mark[random] == false)
		{
			mines[i][0] = x;
			mines[i][1] = y;

			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
}


void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	srand(time(NULL));
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}
}


void replaceMine(int row, int col, char board[][MAXSIDE])
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{

			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
			}
		}
	}
}




void playMinesweeper()
{

	bool gameOver = false;


	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; 

	initialise(realBoard, myBoard);


	placeMines(mines, realBoard);

	

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		system("cls");
		printBoard(myBoard);
		int in;
		cout << "0. zaznacz puste" << endl;
		cout << "1. zaznacz flage" << endl;
		cin >> in;
		if (in == 0) {
			makeMove(&x, &y);
			if (currentMoveIndex == 0)
			{
				if (isMine(x, y, realBoard) == true)
					replaceMine(x, y, realBoard);
			}

			currentMoveIndex++;

			gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);

			if ((gameOver == false) && (movesLeft == 0))
			{
				cout << ("\nWygrales!\n");
				gameOver = true;
			}
		}
		else if(in == 1) {
			makeFlag(&x, &y);
		}
		
	}
}


void chooseDifficultyLevel()
{


	int level;

	cout <<("Enter the Difficulty Level\n");
	cout <<("Press 0 for BEGINNER (9 X 9 Cells and 10 Mines)\n");
	cout <<("Press 1 for INTERMEDIATE (16 X 16 Cells and 40 Mines)\n");
	cout <<("Press 2 for ADVANCED (24 X 24 Cells and 99 Mines)\n");

	cin >> level;

	if (level == BEGINNER)
	{
		SIDE = 9;
		MINES = 10;
	}

	if (level == INTERMEDIATE)
	{
		SIDE = 16;
		MINES = 40;
	}

	if (level == ADVANCED)
	{
		SIDE = 24;
		MINES = 99;
	}
}

int main()
{
	clearFLags();

	chooseDifficultyLevel();

	playMinesweeper();

	return EXIT_SUCCESS;
}
