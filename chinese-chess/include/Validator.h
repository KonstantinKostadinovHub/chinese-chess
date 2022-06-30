#pragma once

#include "defines.h"

bool canMove(int2 coor);
bool isNumber(string data);		
vector<int2> giveUnavailableMoves(int2 coor, int N, int M);
void lineMoves(int2 coor, int N, int M, int _dir, vector<int2>& out);
bool inGrid(int2 coor, int N, int M);