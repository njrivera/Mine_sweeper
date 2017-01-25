#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

void SetColor(int);
void GotoXY(int, int);
void FillMatrix(int, int, int, int, int**);
void FillMatrix2(int, int, int, int, int**);
void Scan(int, int, int, int, int&, int**);
void Flag2(int, int, int, int&, int**);
void GameOver(int, int, bool, int**);
void DisplayGrid(int x, int y, bool gameOver, int** matrix);
