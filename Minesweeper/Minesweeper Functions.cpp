#include "stdafx.h"
#include "Minesweeper Functions.h"
using namespace std;

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forground color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void FillMatrix(int xPos, int yPos, int xDim, int yDim, int** matrix)
{
	if (xPos > 1 && yPos > 1 && xPos < xDim && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 2] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos - 2][xPos] = 9;
		matrix[yPos - 1][xPos] = 9;
		matrix[yPos][xPos] = 9;
		matrix[yPos][xPos - 1] = 9;
		matrix[yPos][xPos - 2] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos == 1 && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 1][xPos] = 9;
		matrix[yPos][xPos] = 9;
		matrix[yPos][xPos - 1] = 9;
	}
	if (xPos > 1 && xPos < xDim && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 1][xPos] = 9;
		matrix[yPos][xPos] = 9;
		matrix[yPos][xPos - 1] = 9;
		matrix[yPos][xPos - 2] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos == xDim && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos][xPos - 1] = 9;
		matrix[yPos][xPos - 2] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos == xDim && yPos > 1 && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 2] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos][xPos - 1] = 9;
		matrix[yPos][xPos - 2] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos == xDim && yPos == 20)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 2] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos > 1 && xPos < xDim && yPos == yDim)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 2] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos - 2][xPos] = 9;
		matrix[yPos - 1][xPos] = 9;
		matrix[yPos - 1][xPos - 2] = 9;
	}
	if (xPos == 1 && yPos == yDim)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos - 2][xPos] = 9;
		matrix[yPos - 1][xPos] = 9;
	}
	if (xPos == 1 && yPos > 1 && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = 9;
		matrix[yPos - 2][xPos - 1] = 9;
		matrix[yPos - 2][xPos] = 9;
		matrix[yPos - 1][xPos] = 9;
		matrix[yPos][xPos] = 9;
		matrix[yPos][xPos - 1] = 9;
	}
}

void FillMatrix2(int xPos, int yPos, int xDim, int yDim, int** matrix)
{
	if (xPos > 1 && yPos > 1 && xPos < xDim && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 2] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos - 2][xPos] = -1;
		matrix[yPos - 1][xPos] = -1;
		matrix[yPos][xPos] = -1;
		matrix[yPos][xPos - 1] = -1;
		matrix[yPos][xPos - 2] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos == 1 && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 1][xPos] = -1;
		matrix[yPos][xPos] = -1;
		matrix[yPos][xPos - 1] = -1;
	}
	if (xPos > 1 && xPos < xDim && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 1][xPos] = -1;
		matrix[yPos][xPos] = -1;
		matrix[yPos][xPos - 1] = -1;
		matrix[yPos][xPos - 2] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos == xDim && yPos == 1)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos][xPos - 1] = -1;
		matrix[yPos][xPos - 2] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos == xDim && yPos > 1 && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 2] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos][xPos - 1] = -1;
		matrix[yPos][xPos - 2] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos == xDim && yPos == 20)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 2] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos > 1 && xPos < xDim && yPos == yDim)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 2] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos - 2][xPos] = -1;
		matrix[yPos - 1][xPos] = -1;
		matrix[yPos - 1][xPos - 2] = -1;
	}
	if (xPos == 1 && yPos == yDim)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos - 2][xPos] = -1;
		matrix[yPos - 1][xPos] = -1;
	}
	if (xPos == 1 && yPos > 1 && yPos < yDim)
	{
		matrix[yPos - 1][xPos - 1] = -1;
		matrix[yPos - 2][xPos - 1] = -1;
		matrix[yPos - 2][xPos] = -1;
		matrix[yPos - 1][xPos] = -1;
		matrix[yPos][xPos] = -1;
		matrix[yPos][xPos - 1] = -1;
	}
}

void Scan(int xPos, int yPos, int xDim, int yDim, int& unopened, int** matrix)
{
	if (matrix[yPos][xPos] != -1)
		return;
	unopened--;
	int numMines = 0;
	if (xPos + 1 > 1 && yPos + 1 > 1 && xPos + 1 < xDim && yPos + 1 < yDim)
	{
		if (matrix[yPos - 1][xPos - 1] == -2 || matrix[yPos - 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos + 1] == -2 || matrix[yPos - 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos + 1] == -2 || matrix[yPos + 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos - 1] == -2 || matrix[yPos + 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == 1 && yPos + 1 == 1)
	{
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos + 1] == -2 || matrix[yPos + 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 > 1 && xPos + 1 < xDim && yPos + 1 == 1)
	{
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos + 1] == -2 || matrix[yPos + 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos - 1] == -2 || matrix[yPos + 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == xDim && yPos + 1 == 1)
	{
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos - 1] == -2 || matrix[yPos + 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == xDim && yPos + 1 > 1 && yPos + 1 < yDim)
	{
		if (matrix[yPos - 1][xPos - 1] == -2 || matrix[yPos - 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos - 1] == -2 || matrix[yPos + 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == xDim && yPos + 1 == yDim)
	{
		if (matrix[yPos - 1][xPos - 1] == -2 || matrix[yPos - 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 > 1 && xPos + 1 < xDim && yPos + 1 == yDim)
	{
		if (matrix[yPos - 1][xPos - 1] == -2 || matrix[yPos - 1][xPos - 1] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos + 1] == -2 || matrix[yPos - 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos][xPos - 1] == -2 || matrix[yPos][xPos - 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos - 1] == -1)
				Scan(xPos - 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos - 1] == -1)
				Scan(xPos - 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == 1 && yPos + 1 == yDim)
	{
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos + 1] == -2 || matrix[yPos - 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
		}
	}
	if (xPos + 1 == 1 && yPos + 1 > 1 && yPos + 1 < yDim)
	{
		if (matrix[yPos - 1][xPos] == -2 || matrix[yPos - 1][xPos] == -4)
			numMines++;
		if (matrix[yPos - 1][xPos + 1] == -2 || matrix[yPos - 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos][xPos + 1] == -2 || matrix[yPos][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos + 1] == -2 || matrix[yPos + 1][xPos + 1] == -4)
			numMines++;
		if (matrix[yPos + 1][xPos] == -2 || matrix[yPos + 1][xPos] == -4)
			numMines++;
		matrix[yPos][xPos] = numMines;
		if (matrix[yPos][xPos] == 0)
		{
			if (matrix[yPos - 1][xPos] == -1)
				Scan(xPos, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos - 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos - 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos][xPos + 1] == -1)
				Scan(xPos + 1, yPos, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos + 1] == -1)
				Scan(xPos + 1, yPos + 1, xDim, yDim, unopened, matrix);
			if (matrix[yPos + 1][xPos] == -1)
				Scan(xPos, yPos + 1, xDim, yDim, unopened, matrix);
		}
	}
}

void Flag(int xPos, int yPos, int** matrix)
{
	if (matrix[yPos][xPos] == -1)
	{
		matrix[yPos][xPos] = -3;
		cout << "!";
		GotoXY(xPos + 1, yPos + 1);
		return;
	}
	if (matrix[yPos][xPos] == -2)
	{
		matrix[yPos][xPos] = -4;
		cout << "!";
		GotoXY(xPos + 1, yPos + 1);
		return;
	}
	if (matrix[yPos][xPos] == -3)
	{
		matrix[yPos][xPos] = -1;
		cout << "=";
		GotoXY(xPos + 1, yPos + 1);
		return;
	}
	if (matrix[yPos][xPos] == -4)
	{
		matrix[yPos][xPos] = -2;
		cout << "=";
		GotoXY(xPos + 1, yPos + 1);
		return;
	}
}

void GameOver(int x, int y, bool win, int** matrix)
{
	system("CLS");
	cout << endl;
	for (int i = 0; i < y; ++i)
	{
		cout << " ";
		for (int j = 0; j < x; ++j)
		{
			switch (matrix[i][j])
			{
			case -1: cout << '-';
				break;
			case -2: cout << '+';
				break;
			case -3: cout << 'X';
				break;
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
			case 0: cout << ' ';
				break;
			default: break;
			}
		}
		cout << endl;
	}
	GotoXY(1, y + 2);
	if (win)
		cout << "CONGRATULATIONS! YOU WON!!!" << endl << endl;
	else
		cout << "GAME OVER - YOU LOSE" << endl << endl;
}