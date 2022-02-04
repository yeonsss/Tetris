#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <list>
#include <map>
#include <queue>
#include "conio.h"
#include <stack>
#include <set>

using namespace std;

enum GameType {
	SINGLE = 0,
	MULTI,
};

const int FULLDOWN = 70;
const int LEFT = 75;
const int RIGHT = 77;
const int SHAPECHANGE = 99;

const int Vertical = 24;
const int Horizontal = 14;

const int LeftEndIndex = 2;
const int RightEndIndex = 12;
const int BottomEndIndex = 22;
const int TopEndIndex = 2;

const ULONGLONG MOVE_TICK = 500;
