#include "graphics.h"
#include "mmsystem.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

const int CELL_SIZE = 18;
const int EMPTY = 0;
const int BODY = 1;
const int APPLE = 2;
const int WALL = 3;
const int WALLED_APPLE = 4;
enum directions {UP, DOWN, LEFT, RIGHT};
directions SnakeDirection = DOWN;

struct Location
{
    int r;
    int c;
};

bool isFireStarted;
Location fireLocation;
directions fireDirection;

Location appleLoc;

queue<Location> SnakeBody;

bool isGameOver = false;

int count = 0; //score counter

int board [35][60] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

int nameboard [35][60] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,0,3,0,3,0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,0,0,3,3,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,3,3,0,0,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,3,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,3,0,0,0,0,0,3,3,3,3,3,0,0,3,3,3,3,3,0,0,3,0,0,0,0,3,3,3,3,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,3,0,0,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,0,3,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,3,3,3,0,3,3,3,3,3,0,3,3,3,0,0,0,4,0,0,0,0,0,1,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,3,3,3,3,0,0,0,3,3,3,3,0,3,0,0,0,3,0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,3,3,3,0,0,0,0,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,3,3,3,3,0,3,3,3,3,0,0,0,3,3,3,3,0,0,3,3,3,3,3,0,0,3,3,3,3,3,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,3},
    {3,0,0,3,0,0,0,3,0,3,3,3,3,3,0,3,3,3,3,0,0,0,3,0,0,0,3,0,3,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,2,0,1,1,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
};

void drawFire(int r, int c)
{
    int top = r * CELL_SIZE;
    int left = c * CELL_SIZE;

    readimagefile ("fire.ico",
                   left , top , left + 17 , top + 17 );
}

void eraseFire( int r , int c)
{
    int x = c * 18;
    int y = r * 18;
    setfillstyle(SOLID_FILL,BLACK);
    bar( x , y , x + 18 , y + 18);
}

void drawWall(int r,int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, RED);
    bar ( x , y , x + 18 , y + 18);

    setcolor(BLACK);
    setlinestyle (SOLID_LINE,1,NORM_WIDTH);
    line( x , y , x + 18 , y );
    line( x , y + 9 , x + 18 , y + 9 );
    line( x , y + 18 , x + 18 , y + 18 );

    line( x + 12 , y , x + 12 , y + 9 );
    line( x + 6 , y + 9 , x + 6 , y + 18 );
}

void drawApple (int r , int c)
{
    int top = r * CELL_SIZE;
    int left = c * CELL_SIZE;

    readimagefile ("Green_apple16.ico",
                   left , top , left + 17 , top + 17 );
}

void drawWalledApple (int r , int c)
{
    int top = r * CELL_SIZE;
    int left = c * CELL_SIZE;

    readimagefile ("Walled_Green_apple16.ico",
                   left , top , left + 17 , top + 17 );
}

void drawSnakeBody(int r, int c)
{
    int x = c * 18;
    int y = r * 18;
    setfillstyle(DOTTED_LINE,GREEN);
    bar( x + 1 , y + 1 , x + 17 , y + 17 );
}

void eraseSnakeBody( int r , int c)
{
    int x = c * 18;
    int y = r * 18;
    setfillstyle(SOLID_FILL,BLACK);
    bar( x , y , x + 18 , y + 18);
}

void drawnameboard ()
{
    for(int row=0; row<35; row++)
    {
        for(int col=0; col<60; col++)
        {
            switch(nameboard[row][col])
            {
            case BODY:
                drawSnakeBody(row,col);
                break;
            case APPLE:
                drawApple(row,col);
                break;
            case WALL:
                drawWall(row,col);
                break;
            case WALLED_APPLE:
                drawWalledApple(row,col);
                break;
            }
        }
    }
}

void score()
{
    settextstyle(6,0,1);
    char arr[50];
    setcolor(WHITE);

    sprintf(arr,"SCORE = %d",count);
    outtextxy(920,75,arr);
    count += 2;
}

void drawBoard ()
{
    settextstyle(6,0,1);
    setcolor(WHITE);
    outtextxy(920,260, "how to play:");
    outtextxy(905,380, "use arrow keys");
    outtextxy(935,400, "to move");
    outtextxy(918,460, "use spacebar");
    outtextxy(948,480, "to fire");
    score();
    for(int r = 0; r < 35; r++)
    {
        for(int c = 0; c < 60; c++)
        {
            switch(board[r][c]){
                case EMPTY:
                    break;
                case BODY:
                    drawSnakeBody(r,c);
                    break;
                case APPLE:
                    drawApple(r,c);
                    break;
                case WALL:
                    drawWall(r,c);
                    break;
                case WALLED_APPLE:
                    drawWalledApple(r,c);
                    break;
            }
        }
    }
}

void initsnake()
{
    Location loc;
    loc.r = 10;
    loc.c = 20;
    for (int i = 0; i <= 4; i++)
    {
        SnakeBody.push(loc);
        board[loc.r][loc.c] = 1;
        loc.r += 1;
    }
}

Location getNextHead()
{
    Location head = SnakeBody.back();
    switch (SnakeDirection)
        {
            case UP:
            head.r -= 1; break;
            case DOWN:
            head.r += 1; break;
            case LEFT:
            head.c -= 1; break;
            case RIGHT:
            head.c += 1; break;
        }
    return head;
}

Location getNextFireLocation()
{
    Location NextFireLoc = fireLocation;
    switch (fireDirection)
        {
            case UP:
            NextFireLoc.r -= 1; break;
            case DOWN:
            NextFireLoc.r += 1; break;
            case LEFT:
            NextFireLoc.c -= 1; break;
            case RIGHT:
            NextFireLoc.c += 1; break;
        }
    return NextFireLoc;
}


void moveSnakeToNextLocation(Location Nexthead)
{
     SnakeBody.push(Nexthead);
     drawSnakeBody(Nexthead.r, Nexthead.c);
     board[Nexthead.r][Nexthead.c] = 1;

     //now to erase the tail
     Location tail = SnakeBody.front();
     SnakeBody.pop();

     eraseSnakeBody(tail.r, tail.c);
     board[tail.r][tail.c] = 0;
}

void moveAndGrowSnake(Location NextHead)
{
     SnakeBody.push(NextHead);
     drawSnakeBody(NextHead.r, NextHead.c);
     board[NextHead.r][NextHead.c] = 1;
}

void generateNextApple()
{
    Location CurrentAppleLoc = appleLoc;
    int x, y;
    do
    {
        x = (rand() % 35);
        y = (rand() % 50);
    }
    while( board[x][y] != EMPTY);
    appleLoc.r = x;
    appleLoc.c = y;
    board[x][y] = WALLED_APPLE;
    drawWalledApple(x , y);
}

void introScreen()
{
    settextstyle(3,0,6);

    outtextxy(200,480,"PRESS ENTER TO START");
    drawnameboard();

    cin.get();

    cleardevice();
}

void gameOver()
{
    isGameOver = true;

    setcolor(RED);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 7);
    settextjustify(CENTER_TEXT, CENTER_LINE);
    outtextxy(25 * CELL_SIZE, 17.5 * CELL_SIZE, "GameOver");

    Sleep(2000);

    outtextxy(25 * CELL_SIZE, 22 * CELL_SIZE, "better luck next time :)");
}

void movesnake()
{
    Location Nexthead = getNextHead();
    string sound = "eat_apple_sound.wav";
    switch( board[Nexthead.r][Nexthead.c]){
        case EMPTY:
            moveSnakeToNextLocation(Nexthead);
            break;
        case APPLE:
            moveAndGrowSnake(Nexthead);
            PlaySound(sound.c_str(),NULL,SND_ASYNC);
            generateNextApple();
            score();
            break;
        case WALLED_APPLE:
        case WALL:
        case BODY:
            gameOver();
            break;
    }
    switch (SnakeDirection)
        {
            case UP:
            Nexthead.r -= 1; break;
            case DOWN:
            Nexthead.r += 1; break;
            case LEFT:
            Nexthead.c -= 1; break;
            case RIGHT:
            Nexthead.c += 1; break;
        }

}

void ChangeSnakeDirection(char ch)
{
        switch(ch){
        case KEY_UP:
            if(SnakeDirection != DOWN)
                SnakeDirection = UP; break;
        case KEY_DOWN:
            if(SnakeDirection != UP)
                SnakeDirection = DOWN; break;
        case KEY_LEFT:
            if(SnakeDirection != RIGHT)
                SnakeDirection = LEFT; break;
        case KEY_RIGHT:
            if(SnakeDirection != LEFT)
                SnakeDirection = RIGHT; break;
    }
}

void startFire()
{
    isFireStarted = true;
    fireLocation = getNextHead();
    fireDirection = SnakeDirection;
    drawFire(fireLocation.r, fireLocation.c);
    string sound = "Fire.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC);
}

void stopFire()
{
    Location NextFireLoc = getNextFireLocation();
    eraseFire(fireLocation.r , fireLocation.c);
    isFireStarted = false;
}

void moveFire()
{
    if(isFireStarted == true){
        Location NextFireLoc = getNextFireLocation();

        switch(board[NextFireLoc.r][NextFireLoc.c])
        {
            case WALL:
                stopFire();
                drawWall(NextFireLoc.r,NextFireLoc.c);
                return;
            case WALLED_APPLE:
                stopFire();
                eraseFire(fireLocation.r,fireLocation.c);
                board[appleLoc.r][appleLoc.c] = APPLE;
                drawApple(appleLoc.r,appleLoc.c);
                return;
            case APPLE:
                stopFire();
                eraseFire(NextFireLoc.r,NextFireLoc.c);
                board[appleLoc.r][appleLoc.c] = EMPTY;
                generateNextApple();
                return;
            case BODY:
                gameOver();
                break;
        }

        drawFire(NextFireLoc.r , NextFireLoc.c);
        eraseFire(fireLocation.r , fireLocation.c);
        fireLocation = NextFireLoc;
    }
}

void CheckKeyinput()
{
    char ch;
    if(kbhit()){
        ch = getch();
        if(ch == 0){
            ch = getch();
            ChangeSnakeDirection(ch);
        }
        else if (ch == 32){ //spacebar = char (32)
            if(!isFireStarted)
            startFire();
        }
        else if (ch == 27){  //esc button = char (27)
            isGameOver = true;
            gameOver();
            }
    }
}

int main()
{
    isGameOver = false;

    initwindow(60 * CELL_SIZE,35 * CELL_SIZE);

    introScreen();

    drawBoard();
    initsnake();

    int gametimer = 0;
    while (!isGameOver)
    {

        if (gametimer == INT_MAX)
            gametimer = 0;
        if (gametimer % 2000000== 0)
            moveFire();
        if (gametimer % 5000000 == 0)
            movesnake();

        gametimer++;
        CheckKeyinput();
    }
    while(!kbhit());
    closegraph( );
}
