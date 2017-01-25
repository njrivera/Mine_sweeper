#include "stdafx.h"
#include "Solver.h"
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void GotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

int main()
{

	srand(time(NULL));
	bool gameOver = false;
	string move = "1";
	string answer = "-1";

	while (answer.at(0) != '0')
	{
		int x = 0, y = 0, flags = 0, unopened = 0;
		int numMines = 0;
		bool win = false, ai = false;
		do
		{
			cout << " Grid Size" << endl;
			cout << " Width: ";
			cin >> x;
			cout << " Height: ";
			cin >> y;
			if (x < 5 || y < 5)
				cout << " Grid is too small." << endl;
			if (x > 75 || y > 45)
				cout << " Grid is too big." << endl;
		} while (x < 5 || y < 5 || x > 75 || y > 45);
		while (numMines > x * y - 9 || numMines < 1)
		{
			cout << " How many mines? ";
			cin >> numMines;
			if (numMines < 1)
				cout << " Not enough mines" << endl;
			if (numMines > x * y - 9)
				cout << " Too many mines" << endl;
		}

		string comp = "0";
		cout << " Human (1) or Computer (2)? ";
		while (comp.at(0) != '1' && comp.at(0) != '2')
			cin >> comp;

		if (comp.at(0) == '2')
		{
			int games = 1, wins = 0, losses = 0;
			cout << " How many games? ";
			cin >> games;
			while (games > 0)
			{
				gameOver = false;
				int mines = numMines;
				unopened = x * y;
				int** matrix = new int*[y];
				for (int i = 0; i < y; ++i)
					matrix[i] = new int[x];
				system("CLS");
				cout << endl;
				for (int i = 0; i < y; ++i)
				{
					cout << " ";
					for (int j = 0; j < x; ++j)
					{
						matrix[i][j] = -1;
						cout << '=';
					}
					cout << endl;
				}
				int xBegin = rand() % x, yBegin = rand() % y;
				FillMatrix(xBegin + 1, yBegin + 1, x, y, matrix);
				int xPos = rand() % x, yPos = rand() % y;
				for (int i = 0; i < numMines; ++i)
				{
					while (matrix[yPos][xPos] == -2 || matrix[yPos][xPos] == 9)
					{
						xPos = rand() % x;
						yPos = rand() % y;
					}
					matrix[yPos][xPos] = -2;
				}
				FillMatrix2(xBegin + 1, yBegin + 1, x, y, matrix);
				Scan(xBegin, yBegin, x, y, unopened, matrix);
				DisplayGrid(x, y, gameOver, matrix);
				while (gameOver == false)
				{
					SolveField(x, y, unopened, gameOver, matrix);
					int prevX = CursorPosition.X, prevY = CursorPosition.Y;
					GotoXY(1, y + 1);
					cout << "Mines: " << mines;
					GotoXY(prevX, prevY);
					if (unopened == numMines)
					{
						win = true;
						GameOver(x, y, win, matrix);
						answer = "1";
						gameOver = true;
						wins++;
						break;
					}
					int xPos = rand() % x, yPos = rand() % y;
					while (matrix[yPos][xPos] != -1 && matrix[yPos][xPos] != -2)
					{
						xPos = rand() % x;
						yPos = rand() % y;
					}
					Scan(xPos, yPos, x, y, unopened, matrix);
					if (matrix[yPos][xPos] == -2)
					{
						win = false;
						GameOver(x, y, win, matrix);
						answer = "1";
						gameOver = true;
						losses++;
						break;
					}
				}
				games--;
				for (int i = 0; i < y; ++i)
					delete matrix[i];
				delete matrix;
			}
			cout << " Wins: " << wins << endl << " Losses: " << losses << endl;
			gameOver = false;
			cout << "0 - Quit" << endl;
			cout << "Press any other key to play again." << endl;
			cin >> answer;
			system("CLS");
		}

		else
		{
			int mines = numMines;
			unopened = x * y;
			int** matrix = new int*[y];
			for (int i = 0; i < y; ++i)
				matrix[i] = new int[x];
			system("CLS");
			cout << endl;
			for (int i = 0; i < y; ++i)
			{
				cout << " ";
				for (int j = 0; j < x; ++j)
				{
					matrix[i][j] = -1;
					cout << '=';
				}
				cout << endl;
			}
			GotoXY(1, 1);
			while (move.at(0) != '0' && !gameOver)
			{
				move = _getch();
				switch (move.at(0))
				{
				case 'w':
				{
					if (CursorPosition.Y != 1)
						GotoXY(CursorPosition.X, CursorPosition.Y - 1);
				}
				break;
				case 's':
				{
					if (CursorPosition.Y != y)
						GotoXY(CursorPosition.X, CursorPosition.Y + 1);
				}
				break;
				case 'a':
				{
					if (CursorPosition.X != 1)
						GotoXY(CursorPosition.X - 1, CursorPosition.Y);
				}
				break;
				case 'd':
				{
					if (CursorPosition.X != x)
						GotoXY(CursorPosition.X + 1, CursorPosition.Y);
				}
				break;
				case ' ':
				{
					FillMatrix(CursorPosition.X, CursorPosition.Y, x, y, matrix);
					int xPos = rand() % x, yPos = rand() % y;
					for (int i = 0; i < numMines; ++i)
					{
						while (matrix[yPos][xPos] == -2 || matrix[yPos][xPos] == 9)
						{
							xPos = rand() % x;
							yPos = rand() % y;
						}
						matrix[yPos][xPos] = -2;
					}
					FillMatrix2(CursorPosition.X, CursorPosition.Y, x, y, matrix);
					Scan(CursorPosition.X - 1, CursorPosition.Y - 1, x, y, unopened, matrix);
					DisplayGrid(x, y, gameOver, matrix);
					while (move.at(0) != '0' && !gameOver)
					{
						move = _getch();
						switch (move.at(0))
						{
						case 'w':
						{
							if (CursorPosition.Y != 1)
								GotoXY(CursorPosition.X, CursorPosition.Y - 1);
						}
						break;
						case 's':
						{
							if (CursorPosition.Y != y)
								GotoXY(CursorPosition.X, CursorPosition.Y + 1);
						}
						break;
						case 'a':
						{
							if (CursorPosition.X != 1)
								GotoXY(CursorPosition.X - 1, CursorPosition.Y);
						}
						break;
						case 'd':
						{
							if (CursorPosition.X != x)
								GotoXY(CursorPosition.X + 1, CursorPosition.Y);
						}
						break;
						case ' ':
						{
							Scan(CursorPosition.X - 1, CursorPosition.Y - 1, x, y, unopened, matrix);
							if (matrix[CursorPosition.Y - 1][CursorPosition.X - 1] == -2 || unopened == numMines)
							{
								if (unopened == numMines)
									win = true;
								GameOver(x, y, win, matrix);
								cout << "0 - Quit" << endl;
								cout << "Press any other key to play again." << endl;
								cin >> answer;
								gameOver = true;
								break;
							}
							DisplayGrid(x, y, gameOver, matrix);
							int prevX = CursorPosition.X, prevY = CursorPosition.Y;
							GotoXY(1, y + 1);
							cout << "Mines: " << mines;
							GotoXY(prevX, prevY);
						}
						break;
						case '1': Flag2(CursorPosition.X - 1, CursorPosition.Y - 1, y, mines, matrix);
							break;
						case 'z':
						{
							SolveFlag(x, y, matrix);
							SolveScan(1, 1, x, y, unopened, matrix);
							DisplayGrid(x, y, gameOver, matrix);
						}
						break;
						case 'x':
						{
							SimFlag(x, y, matrix);
							DisplayGrid(x, y, gameOver, matrix);
						}
						break;
						case 'c':
						{
							vector<SimCoord> scanList;
							SharedFlags(x, y, unopened, matrix, scanList);
							for (int i = 0; i < scanList.size(); i++)
								Scan(scanList.at(i).x, scanList.at(i).y, x, y, unopened, matrix);
							DisplayGrid(x, y, gameOver, matrix);
						}
						break;
						default: break;
						}
						while (move.at(0) == '0')
						{
							string quit = "";
							int prevX = CursorPosition.X, prevY = CursorPosition.Y;
							GotoXY(1, y + 2);
							cout << " Are you sure you want to quit? (Y/N) ";
							cin >> quit;
							if (quit.at(0) == 'y' || quit.at(0) == 'Y')
								break;
							else if (quit.at(0) == 'n' || quit.at(0) == 'N')
								move = "1";
							else
								cout << " Invalid Input" << endl;
							GotoXY(prevX, prevY);
						}
					}
				}
				break;
				default: break;
				}
			}
			for (int i = 0; i < y; ++i)
				delete matrix[i];
			delete matrix;
			gameOver = false;
			system("CLS");
			if (move.at(0) == '0')
				answer = "0";
		}
	}
	return 0;
}


