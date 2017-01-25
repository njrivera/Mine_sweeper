#include "stdafx.h"
#include "Solver.h"
using namespace std;

int Flag(int xPos, int yPos, int** matrix)
{
	if (matrix[yPos][xPos] == -1)
	{
		matrix[yPos][xPos] = -3;
		return 1;
	}
	if (matrix[yPos][xPos] == -2)
	{
		matrix[yPos][xPos] = -4;
		return 1;
	}
	return 0;
}

void SolveField(int x, int y, int& unopened, bool gameOver, int** matrix)
{
	int changes = 1;
	while (changes > 0)
	{
		while (changes > 0)
		{
			while (changes > 0)
			{
				changes = 0;
				changes += SolveFlag(x, y, matrix);
				DisplayGrid(x, y, gameOver, matrix);
			}
			changes += SimFlag(x, y, matrix);
			DisplayGrid(x, y, gameOver, matrix);
		}
		vector<SimCoord> scanList;
		SharedFlags(x, y, unopened, matrix, scanList);
		for (int i = 0; i < scanList.size(); i++)
			Scan(scanList.at(i).x, scanList.at(i).y, x, y, unopened, matrix);
		changes += SolveScan(1, 1, x, y, unopened, matrix);
		DisplayGrid(x, y, gameOver, matrix);
	}
	DisplayGrid(x, y, gameOver, matrix);
}

int SolveFlag(int x, int y, int** matrix)
{
	int changes = 0;
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < y - 1 && j > 0 && j < x - 1)
				{
					int unopened = 0;
					if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
						unopened++;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
						unopened++;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
							changes += Flag(j - 1, i - 1, matrix);
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
							changes += Flag(j + 1, i - 1, matrix);
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
						if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
							changes += Flag(j + 1, i + 1, matrix);
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
						if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
							changes += Flag(j - 1, i + 1, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i == 0 && j == 0)
				{
					int unopened = 0;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
						if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
							changes += Flag(j + 1, i + 1, matrix);
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
					}
				}
				if (i == 0 && j > 0 && j < x - 1)
				{
					int unopened = 0;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
						if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
							changes += Flag(j + 1, i + 1, matrix);
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
						if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
							changes += Flag(j - 1, i + 1, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i == 0 && j == x - 1)
				{
					int unopened = 0;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
						if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
							changes += Flag(j - 1, i + 1, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i > 0 && i < y - 1 && j == x - 1)
				{
					int unopened = 0;
					if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
						unopened++;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
							changes += Flag(j - 1, i - 1, matrix);
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
						if (matrix[i + 1][j - 1] <= -1 && matrix[i + 1][j - 1] >= -4)
							changes += Flag(j - 1, i + 1, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i == y - 1 && j == x - 1)
				{
					int unopened = 0;
					if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
						unopened++;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
							changes += Flag(j - 1, i - 1, matrix);
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i == y - 1 && j > 0 && j < x - 1)
				{
					int unopened = 0;
					if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
						unopened++;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
						unopened++;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] <= -1 && matrix[i - 1][j - 1] >= -4)
							changes += Flag(j - 1, i - 1, matrix);
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
							changes += Flag(j + 1, i - 1, matrix);
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
						if (matrix[i][j - 1] <= -1 && matrix[i][j - 1] >= -4)
							changes += Flag(j - 1, i, matrix);
					}
				}
				if (i == y - 1 && j == 0)
				{
					int unopened = 0;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
						unopened++;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
							changes += Flag(j + 1, i - 1, matrix);
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
					}
				}
				if (i > 0 && i < y - 1 && j == 0)
				{
					int unopened = 0;
					if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
						unopened++;
					if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
						unopened++;
					if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
						unopened++;
					if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
						unopened++;
					if (unopened == matrix[i][j])
					{
						if (matrix[i - 1][j] <= -1 && matrix[i - 1][j] >= -4)
							changes += Flag(j, i - 1, matrix);
						if (matrix[i - 1][j + 1] <= -1 && matrix[i - 1][j + 1] >= -4)
							changes += Flag(j + 1, i - 1, matrix);
						if (matrix[i][j + 1] <= -1 && matrix[i][j + 1] >= -4)
							changes += Flag(j + 1, i, matrix);
						if (matrix[i + 1][j + 1] <= -1 && matrix[i + 1][j + 1] >= -4)
							changes += Flag(j + 1, i + 1, matrix);
						if (matrix[i + 1][j] <= -1 && matrix[i + 1][j] >= -4)
							changes += Flag(j, i + 1, matrix);
					}
				}
			}
		}
	}
	return changes;
}

int SolveScan(int xPos, int yPos, int xDim, int yDim, int& unopened, int** matrix)
{
	int changes = 0;
	for (int i = 0; i < yDim; ++i)
	{
		for (int j = 0; j < xDim; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < yDim - 1 && j > 0 && j < xDim - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] == -1)
						{
							Scan(j - 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j + 1] == -1)
						{
							Scan(j + 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j + 1] == -1)
						{
							Scan(j + 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j - 1] == -1)
						{
							Scan(j - 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == 0 && j == 0)
				{
					int flagged = 0;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j + 1] == -1)
						{
							Scan(j + 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == 0 && j > 0 && j < xDim - 1)
				{
					int flagged = 0;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j + 1] == -1)
						{
							Scan(j + 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j - 1] == -1)
						{
							Scan(j - 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == 0 && j == xDim - 1)
				{
					int flagged = 0;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j - 1] == -1)
						{
							Scan(j - 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i > 0 && i < yDim - 1 && j == xDim - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] == -1)
						{
							Scan(j - 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j - 1] == -1)
						{
							Scan(j - 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == yDim - 1 && j == xDim - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] == -1)
						{
							Scan(j - 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == yDim - 1 && j > 0 && j < xDim - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j - 1] == -1)
						{
							Scan(j - 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j + 1] == -1)
						{
							Scan(j + 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j - 1] == -1)
						{
							Scan(j - 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i == yDim - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j + 1] == -1)
						{
							Scan(j + 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
				if (i > 0 && i < yDim - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -4)
						flagged++;
					if (flagged == matrix[i][j])
					{
						if (matrix[i - 1][j] == -1)
						{
							Scan(j, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i - 1][j + 1] == -1)
						{
							Scan(j + 1, i - 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i][j + 1] == -1)
						{
							Scan(j + 1, i, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j + 1] == -1)
						{
							Scan(j + 1, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
						if (matrix[i + 1][j] == -1)
						{
							Scan(j, i + 1, xDim, yDim, unopened, matrix);
							changes++;
						}
					}
				}
			}
		}
	}
	return changes;
}

int SimFlag(int x, int y, int** matrix)
{
	int changes = 0;
	SimCoord simCoord;
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < y - 1 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -3 || matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -3 || matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -3 || matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -3 || matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j - 1] == -1 || matrix[i - 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j + 1] == -1 || matrix[i - 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j + 1] == -1 || matrix[i + 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j - 1] == -1 || matrix[i + 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == 0 && j == 0)
				{
					int flagged = 0;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -3 || matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j + 1] == -1 || matrix[i + 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == 0 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -3 || matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -3 || matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j + 1] == -1 || matrix[i + 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j - 1] == -1 || matrix[i + 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == 0 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -3 || matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j - 1] == -1 || matrix[i + 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i > 0 && i < y - 1 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -3 || matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (matrix[i + 1][j - 1] == -3 || matrix[i + 1][j - 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j - 1] == -1 || matrix[i - 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j - 1] == -1 || matrix[i + 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == y - 1 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -3 || matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j - 1] == -1 || matrix[i - 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == y - 1 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] == -3 || matrix[i - 1][j - 1] == -4)
						flagged++;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -3 || matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i][j - 1] == -3 || matrix[i][j - 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j - 1] == -1 || matrix[i - 1][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j + 1] == -1 || matrix[i - 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j - 1] == -1 || matrix[i][j - 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j - 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i == y - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -3 || matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j + 1] == -1 || matrix[i - 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						changes += SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
				if (i > 0 && i < y - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] == -3 || matrix[i - 1][j] == -4)
						flagged++;
					if (matrix[i - 1][j + 1] == -3 || matrix[i - 1][j + 1] == -4)
						flagged++;
					if (matrix[i][j + 1] == -3 || matrix[i][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j + 1] == -3 || matrix[i + 1][j + 1] == -4)
						flagged++;
					if (matrix[i + 1][j] == -3 || matrix[i + 1][j] == -4)
						flagged++;
					if (flagged < matrix[i][j])
					{
						vector<SimCoord> simArray;
						if (matrix[i - 1][j] == -1 || matrix[i - 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						if (matrix[i - 1][j + 1] == -1 || matrix[i - 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i - 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i][j + 1] == -1 || matrix[i][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j + 1] == -1 || matrix[i + 1][j + 1] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j + 1;
							simArray.push_back(simPos);
						}
						if (matrix[i + 1][j] == -1 || matrix[i + 1][j] == -2)
						{
							SimCoord simPos;
							simPos.y = i + 1;
							simPos.x = j;
							simArray.push_back(simPos);
						}
						int n = simArray.size();
						int r = matrix[i][j] - flagged;
						SimCombos(x, y, n, r, matrix[i][j], simArray, matrix);
					}
				}
			}
		}
	}
	return changes;
}

int SimCombos(int x, int y, int n, int r, int pos, vector<SimCoord>& simArray, int** matrix)
{
	int changes = 0;
	switch (r)
	{
	case 1:
	{
		int successes = 0;
		for (int a = 0; a < n; a++)
		{
			matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
			if (SimScan(x, y, matrix) == 0)
			{
				simArray[a].successes++;
				successes++;
			}
			matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
		}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				 changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 2:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n; b++)
			{
				matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
				matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
				if (SimScan(x, y, matrix) == 0)
				{
					simArray[a].successes++;
					simArray[b].successes++;
					successes++;
				}
				matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
				matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
			}
		for (int i = 0; i < n; i++)
			if(simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 3:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n - 1; b++)
				for (int c = b + 1; c < n; c++)
				{
					matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
					matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
					matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -1) ? -5 : -6;
					if (SimScan(x, y, matrix) == 0)
					{
						simArray[a].successes++;
						simArray[b].successes++;
						simArray[c].successes++;
						successes++;
					}
					matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
					matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
					matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -5) ? -1 : -2;
				}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 4:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n - 2; b++)
				for (int c = b + 1; c < n - 1; c++)
					for (int d = c + 1; d < n; d++)
					{
						matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
						matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
						matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -1) ? -5 : -6;
						matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -1) ? -5 : -6;
						if (SimScan(x, y, matrix) == 0)
						{
							simArray[a].successes++;
							simArray[b].successes++;
							simArray[c].successes++;
							simArray[d].successes++;
							successes++;
						}
						matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
						matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
						matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -5) ? -1 : -2;
						matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -5) ? -1 : -2;
					}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 5:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n - 3; b++)
				for (int c = b + 1; c < n - 2; c++)
					for (int d = c + 1; d < n - 1; d++)
						for (int e = d + 1; e < n; e++)
						{
							matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
							matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
							matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -1) ? -5 : -6;
							matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -1) ? -5 : -6;
							matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -1) ? -5 : -6;
							if (SimScan(x, y, matrix) == 0)
							{
								simArray[a].successes++;
								simArray[b].successes++;
								simArray[c].successes++;
								simArray[d].successes++;
								simArray[e].successes++;
								successes++;
							}
							matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
							matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
							matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -5) ? -1 : -2;
							matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -5) ? -1 : -2;
							matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -5) ? -1 : -2;
						}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 6:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n - 4; b++)
				for (int c = b + 1; c < n - 3; c++)
					for (int d = c + 1; d < n - 2; d++)
						for (int e = d + 1; e < n - 1; e++)
							for (int f = e + 1; f < n; f++)
							{
								matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
								matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
								matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -1) ? -5 : -6;
								matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -1) ? -5 : -6;
								matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -1) ? -5 : -6;
								matrix[simArray[f].y][simArray[f].x] = (matrix[simArray[f].y][simArray[f].x] == -1) ? -5 : -6;
								if (SimScan(x, y, matrix) == 0)
								{
									simArray[a].successes++;
									simArray[b].successes++;
									simArray[c].successes++;
									simArray[d].successes++;
									simArray[e].successes++;
									simArray[f].successes++;
									successes++;
								}
								matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
								matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
								matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -5) ? -1 : -2;
								matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -5) ? -1 : -2;
								matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -5) ? -1 : -2;
								matrix[simArray[f].y][simArray[f].x] = (matrix[simArray[f].y][simArray[f].x] == -5) ? -1 : -2;
							}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	case 7:
	{
		int successes = 0;
		for (int a = 0; a <= n - r; a++)
			for (int b = a + 1; b < n - 5; b++)
				for (int c = b + 1; c < n - 4; c++)
					for (int d = c + 1; d < n - 3; d++)
						for (int e = d + 1; e < n - 2; e++)
							for (int f = e + 1; f < n - 1; f++)
								for (int g = f + 1; g < n; g++)
								{
									matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -1) ? -5 : -6;
									matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -1) ? -5 : -6;
									matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -1) ? -5 : -6;
									matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -1) ? -5 : -6;
									matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -1) ? -5 : -6;
									matrix[simArray[f].y][simArray[f].x] = (matrix[simArray[f].y][simArray[f].x] == -1) ? -5 : -6;
									matrix[simArray[g].y][simArray[g].x] = (matrix[simArray[g].y][simArray[g].x] == -1) ? -5 : -6;
									if (SimScan(x, y, matrix) == 0)
									{
										simArray[a].successes++;
										simArray[b].successes++;
										simArray[c].successes++;
										simArray[d].successes++;
										simArray[e].successes++;
										simArray[f].successes++;
										simArray[g].successes++;
										successes++;
									}
									matrix[simArray[a].y][simArray[a].x] = (matrix[simArray[a].y][simArray[a].x] == -5) ? -1 : -2;
									matrix[simArray[b].y][simArray[b].x] = (matrix[simArray[b].y][simArray[b].x] == -5) ? -1 : -2;
									matrix[simArray[c].y][simArray[c].x] = (matrix[simArray[c].y][simArray[c].x] == -5) ? -1 : -2;
									matrix[simArray[d].y][simArray[d].x] = (matrix[simArray[d].y][simArray[d].x] == -5) ? -1 : -2;
									matrix[simArray[e].y][simArray[e].x] = (matrix[simArray[e].y][simArray[e].x] == -5) ? -1 : -2;
									matrix[simArray[f].y][simArray[f].x] = (matrix[simArray[f].y][simArray[f].x] == -5) ? -1 : -2;
									matrix[simArray[g].y][simArray[g].x] = (matrix[simArray[g].y][simArray[g].x] == -5) ? -1 : -2;
								}
		for (int i = 0; i < n; i++)
			if (simArray[i].successes == successes)
				changes += Flag(simArray[i].x, simArray[i].y, matrix);
	}
		break;
	default: break;
	}
	return changes;
}

int SimScan(int x, int y, int** matrix)
{
	int failures = 0;
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < y - 1 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] <= -3 && matrix[i - 1][j - 1] >= -6)
						flagged++;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i - 1][j + 1] <= -3 && matrix[i - 1][j + 1] >= -6)
						flagged++;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j + 1] <= -3 && matrix[i + 1][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (matrix[i + 1][j - 1] <= -3 && matrix[i + 1][j - 1] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == 0 && j == 0)
				{
					int flagged = 0;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j + 1] <= -3 && matrix[i + 1][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == 0 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j + 1] <= -3 && matrix[i + 1][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (matrix[i + 1][j - 1] <= -3 && matrix[i + 1][j - 1] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == 0 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (matrix[i + 1][j - 1] <= -3 && matrix[i + 1][j - 1] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i > 0 && i < y - 1 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] <= -3 && matrix[i - 1][j - 1] >= -6)
						flagged++;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (matrix[i + 1][j - 1] <= -3 && matrix[i + 1][j - 1] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == y - 1 && j == x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] <= -3 && matrix[i - 1][j - 1] >= -6)
						flagged++;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == y - 1 && j > 0 && j < x - 1)
				{
					int flagged = 0;
					if (matrix[i - 1][j - 1] <= -3 && matrix[i - 1][j - 1] >= -6)
						flagged++;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i - 1][j + 1] <= -3 && matrix[i - 1][j + 1] >= -6)
						flagged++;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (matrix[i][j - 1] <= -3 && matrix[i][j - 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i == y - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i - 1][j + 1] <= -3 && matrix[i - 1][j + 1] >= -6)
						flagged++;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
				if (i > 0 && i < y - 1 && j == 0)
				{
					int flagged = 0;
					if (matrix[i - 1][j] <= -3 && matrix[i - 1][j] >= -6)
						flagged++;
					if (matrix[i - 1][j + 1] <= -3 && matrix[i - 1][j + 1] >= -6)
						flagged++;
					if (matrix[i][j + 1] <= -3 && matrix[i][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j + 1] <= -3 && matrix[i + 1][j + 1] >= -6)
						flagged++;
					if (matrix[i + 1][j] <= -3 && matrix[i + 1][j] >= -6)
						flagged++;
					if (flagged > matrix[i][j])
						failures++;
				}
			}
		}
	}
	return failures;
}

void SharedFlags(int x, int y, int& unopened, int** matrix, vector<SimCoord>& scanList)
{
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < y - 1 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == 0 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == 0 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == 0 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i > 0 && i < y - 1 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == y - 1 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == y - 1 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i == y - 1 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
				if (i > 0 && i < y - 1 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					int flagged = 0, n = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
							n++;
					}
					if (matrix[i][j] > flagged)
					{
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -1)
								matrix[simArray[i].y][simArray[i].x] = -7;
							if (matrix[simArray[i].y][simArray[i].x] == -2)
								matrix[simArray[i].y][simArray[i].x] = -8;
						}
						ScanRemain(x, y, matrix[i][j] - flagged, n, unopened, matrix, scanList);
						for (int i = 0; i < simArray.size(); i++)
						{
							if (matrix[simArray[i].y][simArray[i].x] == -7)
								matrix[simArray[i].y][simArray[i].x] = -1;
							if (matrix[simArray[i].y][simArray[i].x] == -8)
								matrix[simArray[i].y][simArray[i].x] = -2;
						}
					}
				}
			}
		}
	}
}

void ScanRemain(int x, int y, int r, int n, int& unopened, int** matrix, vector<SimCoord>& scanList)
{
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if (matrix[i][j] > 0 && matrix[i][j] < 9)
			{
				if (i > 0 && i < y - 1 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == 0 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == 0 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == 0 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i > 0 && i < y - 1 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == y - 1 && j == x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == y - 1 && j > 0 && j < x - 1)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j - 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i == y - 1 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
				if (i > 0 && i < y - 1 && j == 0)
				{
					vector<SimCoord> simArray;
					SimCoord simPos;

					simPos.y = i - 1;
					simPos.x = j;
					simArray.push_back(simPos);

					simPos.y = i - 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j + 1;
					simArray.push_back(simPos);

					simPos.y = i + 1;
					simPos.x = j;
					simArray.push_back(simPos);

					int flagged = 0, shared = 0;
					for (int i = 0; i < simArray.size(); i++)
					{
						if (matrix[simArray[i].y][simArray[i].x] == -3 || matrix[simArray[i].y][simArray[i].x] == -4)
							flagged++;
						if (matrix[simArray[i].y][simArray[i].x] == -7 || matrix[simArray[i].y][simArray[i].x] == -8)
							shared++;
					}
					if (matrix[i][j] - flagged == r && shared == n)
						for (int i = 0; i < simArray.size(); i++)
							if (matrix[simArray[i].y][simArray[i].x] == -1 || matrix[simArray[i].y][simArray[i].x] == -2)
								scanList.push_back(simArray[i]);
				}
			}
		}
	}
}