#include "stdafx.h"
#include "Minesweeper Functions.h"
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
		bool win = false;
		do
		{
			cout << " Grid Size" << endl;
			cout << " Width: ";
			cin >> x;
			cout << " Height: ";
			cin >> y;
			if(x < 5 || y < 5)
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
				system("CLS");
				cout << endl;
				for (int i = 0; i < y; ++i)
				{
					cout << " ";
					for (int j = 0; j < x; ++j)
					{
						switch (matrix[i][j])
						{
						case -1:
						case -2: cout << '=';
							break;
						case 1:
						{
							SetColor(9);
							cout << 1;
							SetColor(7);
						}
						break;
						case 2:
						{
							SetColor(10);
							cout << 2;
							SetColor(7);
						}
						break;
						case 3:
						{
							SetColor(12);
							cout << 3;
							SetColor(7);
						}
						break;
						case 4:
						{
							SetColor(14);
							cout << 4;
							SetColor(7);
						}
						break;
						case 5:
						{
							SetColor(4);
							cout << 5;
							SetColor(7);
						}
						break;
						case 6:
						{
							SetColor(3);
							cout << 6;
							SetColor(7);
						}
						break;
						case 7:
						{
							SetColor(5);
							cout << 7;
							SetColor(7);
						}
						break;
						case 8:
						{
							SetColor(6);
							cout << 8;
							SetColor(7);
						}
						break;
						case 0: cout << ' ';
							break;
						default: break;
						}
					}
					cout << endl;
				}
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
						system("CLS");
						cout << endl;
						for (int i = 0; i < y; ++i)
						{
							cout << " ";
							for (int j = 0; j < x; ++j)
							{
								switch (matrix[i][j])
								{
								case -1:
								case -2: cout << '=';
									break;
								case -3:
								case -4: cout << '!';
									break;
								case 1:
								{
									SetColor(9);
									cout << 1;
									SetColor(7);
								}
								break;
								case 2:
								{
									SetColor(10);
									cout << 2;
									SetColor(7);
								}
								break;
								case 3:
								{
									SetColor(12);
									cout << 3;
									SetColor(7);
								}
								break;
								case 4:
								{
									SetColor(14);
									cout << 4;
									SetColor(7);
								}
								break;
								case 5:
								{
									SetColor(4);
									cout << 5;
									SetColor(7);
								}
								break;
								case 6:
								{
									SetColor(3);
									cout << 6;
									SetColor(7);
								}
								break;
								case 7:
								{
									SetColor(5);
									cout << 7;
									SetColor(7);
								}
								break;
								case 8:
								{
									SetColor(6);
									cout << 8;
									SetColor(7);
								}
								break;
								case 0: cout << ' ';
									break;
								default: break;
								}
							}
							cout << endl;
						}
						GotoXY(CursorPosition.X, CursorPosition.Y);
					}
					break;
					case '1': Flag(CursorPosition.X - 1, CursorPosition.Y - 1, matrix);
						break;
					default: break;
					}
				}
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
		for (int i = 0; i < y; ++i)
			delete matrix[i];
		delete matrix;
		gameOver = false;
		if (move.at(0) == '0')
			answer = "0";
	}
	return 0;
}

