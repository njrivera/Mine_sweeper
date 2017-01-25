#pragma once
#include "stdafx.h"
#include "Minesweeper Functions.h"
using namespace std;

typedef struct
{
	int x = 0, y = 0, successes = 0;
} SimCoord;

int Flag(int, int, int**);
void SolveField(int, int, int&, bool, int**);
int SolveFlag(int, int, int**);
int SolveScan(int, int, int, int, int&, int**);
int SimFlag(int, int, int**);
int SimCombos(int, int, int, int, int, vector<SimCoord>&, int**);
int SimScan(int, int, int**);
void SharedFlags(int, int, int&, int**, vector<SimCoord>&);
void ScanRemain(int, int, int, int, int&, int**, vector<SimCoord>&);