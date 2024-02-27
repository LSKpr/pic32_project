//  space invaders 
//  Kacper Lisik
//
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define MAXX 128
#define MAXY 32 
#define Yship   125
#define Yship2   7
#define LOADING_TIME    5
char leaderboard[3][3] = {"XXX","XXX","XXX"};
char scorestring[16] = "               ";
int score[3] = {0,0,0};
int scorenow;
int aliens_left;
int Xship = 63;
int Xship2 = 65;
char GAMEOVER = 0;
char PLR_WIN = 0;
char WAVE = 0;
int mode = 0;
struct alien
{
    char x , y;
    char stage;
};
/*
    1 - bunker
    2 - ship
    4 - plr2 ship
    8 - bullet
    16 - alien bullet
    32 - aliens
    64
    128




*/
char board2 [128][32] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

char screen[128][32];
void clear()
{
   int i;
   for ( i = 0; i < MAXX; i++)
   {
        int j;
        for ( j = 0; j < MAXY; j++)
        {
            screen[i][j] = board2[i][j]?1:0;
            board[i][j] = board2[i][j];
        }    
   }
    
}
void killl(int x, int y)
{
    // delay(1);
    if(x > 127 || x < 0 || y > 31 || y < 0) return;
    x = in_range(x, 0, 127);
    y = in_range(y, 0, 31);
    if(board[x][y] == 32)
    {
        board[x][y] = 0; 
        killl(x-1,y);
        killl(x+1,y);
        killl(x,y+1);
        killl(x,y-1);
    }
    
}
void destroy(int x, int y, int power)
{
    x = in_range(x, 0, 127);
    y = in_range(y, 0, 31);
    if(board[x][y] == 0)   return;
    board[x][y] = 0;
    if(power != 0 || (rrand(power)%power == 1)) return;  
    destroy(x-1, y, ++power);
    destroy(x+1, y, ++power);
    destroy(x, y+1, ++power);
    destroy(x, y-1, ++power);
}
void animate_bullets()
{
    int i;
    for ( i = 1; i < MAXX-1; i++)
    {
        int j;
        for ( j = 1; j < MAXY-1; j++)
        {
            if(j == 1)//last row bullets disapear
            {
                board[i][j] &= !(8);
                continue;
            }
            if(board[i][j] & 8)
            {
                if((board[i][j-1] & (4)) && (mode == 2))    //player 1 wins 
                {
                    GAMEOVER = 1;
                    PLR_WIN = 1;
                    return;
                }  
                if(board[i][j-1] == 1) 
                {
                    destroy(i,j-1,0);
                    board[i][j] = 0;
                }
                else if(board[i][j-1] == 32) 
                {
                    killl(i,j-1);
                    scorenow++;
                    aliens_left--;
                    board[i][j] = 0;
                }
                else
                {
                    board[i][j-1] = 8;
                    board[i][j] = 0;
                }
            }
        }
    }
    for ( i = 1; i < MAXX-1; i++)
    {
        int j;
        for ( j = MAXY-1; j > 0; j--)
        {
            if(board[i][j] & 16) 
            {
                if(j == 31) //last row bullets disapear
                {
                    board[i][j] &= !(16);
                    continue;
                }
                if((board[i][j+1] & (2))) //if next == ship => gameover
                {
                    GAMEOVER = 1;
                    PLR_WIN = 2;
                    return;
                }  
                if(board[i][j+1] == 1) 
                {
                    destroy(i,j+1,0);
                    board[i][j] = 0;
                }
                else
                {
                    board[i][j+1] = 16;
                    board[i][j] = 0;
                }
            }
        }
           
    }    
}
   


void ldrbrd()
{
    display_string(0, "  LEADERBOARD");
    display_string(1, leaderboard[1]);
    display_string(2, leaderboard[2]);
    display_string(3, leaderboard[3]);
}
void move()
{
    char ch;
    if(getbtns()&0x8)//shoot
    {
        if(ammo > LOADING_TIME){

            ammo = 0;
            board[Xship][Yship - 1] = 8;
            // board[Xship][Yship - 2] = 3;
        }
    }

    if(getbtns()&0x2)   Xship = in_range(--Xship,2,121);//left
    else    if(getbtns()&0x1)   Xship = in_range(++Xship,2,121);//right
    
}
void move2()
{
    char ch;
    if(getsw()&0x8)//shoot
    {
        if(ammo2 > LOADING_TIME){

            ammo2 = 0;
            board[Xship2][Yship2 + 1] = 16;
        }
    }
    if(getsw()&0x2)   Xship2 = in_range(++Xship2,3,123);
    else    if(getsw()&0x1)   Xship2 = in_range(--Xship2,3,123);
    
}
void print_ship(int player)
{
    // ...#...
    // ..###..
    //. #####.
    int offset = (player==1)?0:(Yship2 - Yship);
    int zero = (player==1)?0:4;
    int ship = (player==1)?2:0;
    int ship2 = (player == 1)?2:4;
    int x = (player == 1)?Xship:Xship2;
    int i;
    for (i = 0; i < 128; i++)
    {
        board[i][Yship + offset] &= ~(0x7);
        board[i][Yship + offset + 1] &= ~(0x7);
        board[i][Yship + offset + 2] &= ~(0x7);
        board[i][127] &= (0x7);
        board[i][126] &= (0x7);
    }
    
    board[x + 3][Yship + offset] |= 0;
    board[x - 3][Yship + offset] |= 0;
    board[x + 2][Yship + offset] |= zero;
    board[x - 2][Yship + offset] |= zero;
    board[x + 1][Yship + offset] |= zero;
    board[x - 1][Yship + offset] |= zero;
    board[x][Yship + offset] |= ship2;
   
    board[x + 3][Yship + offset + 1] |= 0;
    board[x - 3][Yship + offset + 1] |= 0;
    board[x + 2][Yship + offset + 1] |= 0;
    board[x - 2][Yship + offset + 1] |= 0;
    board[x + 1][Yship + offset + 1] |= ship2;
    board[x - 1][Yship + offset + 1] |= ship2;
    board[x][Yship + offset + 1] |= ship2;

    board[x + 3][Yship + offset + 2] |= 0;
    board[x - 3][Yship + offset + 2] |= 0;
    board[x + 2][Yship + offset + 2] |= ship;
    board[x - 2][Yship + offset + 2] |= ship;
    board[x + 1][Yship + offset + 2] |= ship;
    board[x - 1][Yship + offset + 2] |= ship;
    board[x][Yship + offset + 2] |= ship2;
}
void print_screen()
{
    int j;
    for ( j = 0; j < MAXX; j++)
    {
        board[j][0] = 0;
        board[j][1] = 0;
    }    
    int i;
    for ( i = 0; i < MAXX; i++)
    {
        int j;
        for ( j = 0; j < MAXY; j++)
        {
            screen[i][j] = board[i][j]?1:0;
        }    
    }
    toTable(screen);
    display_image(0,screen2);
}

//side = 1 x,y botom left
void print_alien(int x, int y, int side)
{
    int i;
    for ( i = 0; i < 3; i++)
    {
        int j;
        int offset = 2;
        if(side == 1)   offset = 0;
        for ( j = 0; j < 3; j++)
        {
            if(board[i + x - offset][j + y - 2] == 1)   
            {
                destroy(i + x - offset,j + y - 2,0);
                destroy(i + x - offset,j + y - 1,0);
            }
            board[i + x - offset][j + y - 2] |= 32;
        }
        
    }
}
void create_aliens(char y, int amount)
{
    amount = in_range(amount,1 ,30);
    aliens_left = amount;
    char currentX = 3, currentY = in_range(currentY,6,20);
    int i;
    for (i = 0; i < amount; i++)
    {
        print_alien(currentX,currentY,1);
        currentX += 8;
        if(currentX + 8 > 127)
        {
            currentX = 2 + rrand(1) % 4;
            currentY += 7;
        }
    }
    
}
char mincords = 127;
char maxcords = 0;
char maxYY = 0; // max y alien cordinate - if too big -> gameover
void find_cords()
{
    mincords = 127;
    maxcords = 0;
    maxYY = 0;
    int i;
    for ( i = MAXX-1 ; i > 0; i--)
    {
        int j;
        for ( j = 0; j < MAXY; j++)
        {
            if(board[i][j] == 32)
            {
                if(i > maxcords)    maxcords = i;
                if(i < mincords)    mincords = i;
                if(j > maxYY)   maxYY = j;
            }
        }
        
        
    }
}
char rightleft = 1; // 1 - right 0 - left 
void move_down()
{
    int j;
    int Yalien = 0;
    for ( j = MAXY-5; j > 0; j--)
    {
        int i;
        for ( i = 0; i < MAXX; i++)
        {
            if(board[i][j] == 32)
            {
                killl(i,j);
                print_alien(i,j+1,1);
                i+=7;
                Yalien = j;
            }
        }
        if (Yalien !=0 )    j-=6;
        
    }
}
void alien_shoot(int chance)
{
    int j;
    int Yalien = 0;
    for ( j = MAXY-5; j > 0; j--)
    {
        int i;
        for ( i = 0; i < MAXX; i++)
        {
            if(board[i][j] == 32)
            {
                if(rrand(scorenow)%100000 < chance)   board[i+1][j+1] |= 16;
                i+=7;
                Yalien = j;
            }
        }
        if (Yalien !=0 )    j-=6;
        
    }
}
void move_aliens()
{
    int j;
    int Yalien = 0;
    find_cords();
    if(mincords <=1 && rightleft == 0)
    {
        move_down();
        rightleft = 1;
    }
    else    if(maxcords >= 126 && rightleft == 1)
    {
        //go down
        rightleft = 0;
    }
    if(rightleft)
    {
        for ( j = MAXY-5; j > 0; j--)
        {
            int i;
            for ( i = 0; i < MAXX; i++)
            {
                if(board[i][j] == 32)
                {
                    killl(i,j);
                    print_alien(i+1,j,1);
                    i+=7;
                    Yalien = j;
                }
            }
            if (Yalien !=0 )    j-=6;
            
        }
    }
    else if(rightleft == 0)
    {
        for ( j = MAXY-5; j > 0; j--)
        {
            int i;
            for ( i = MAXX-1; i > 0 ; i--)
            {
                if(board[i][j] == 32)
                {
                    killl(i,j);
                    print_alien(i-1,j,0);
                    i-=7;
                    Yalien = j;
                }
            }
            if (Yalien !=0 )    j-=6;
            
        }
    }
}
    
char wave_num[16] = "``WAVE``````"; 
void wave_edit(int x)
{
    wave_num[10] = x%10 + '0';
    wave_num[9] = (x/10)%10 +'0';
}
void score_to_string(int x)
{
    char i;
    for ( i = 0; i < 16; i++)   scorestring[i] = ' ';
    i = 14;
    while(x > 0)
    {
        scorestring[i] = x%10 + '0';
        i--;
        x /= 10; 
    }
}
char realname[3] = "AAA";
void swap(char* a, char* b)
{
    char help = *a;
    *a = *b;
    *b = help;
}
void update_leaderboard()
{
    int i;
    char j;
    if(score[2] < scorenow)
    {
        score[2] = scorenow;
        leaderboard[2][0] = realname[0]; 
        leaderboard[2][1] = realname[1]; 
        leaderboard[2][2] = realname[2]; 
    }
    display_string(0,"``LEADERBOARD``");
    for ( j = 0; j < 3; j++)
    {
        char ldrbrdspace[16] = "               "; 
        int k;
        for ( k = 0; k < 3; k++)    ldrbrdspace[k] = leaderboard[j][k];
        score_to_string(score[j]);
        for ( k = 3; k < 16; k++)   ldrbrdspace[k] = scorestring[k];
        display_string(j+1,ldrbrdspace);
    }
    display_update(1);
    delay(3);

    for ( i = 1; i >=0; i--)
    {
        if(score[i] < score[i+1])
        {
            swap(&(score[i]),&(score[i+1]));
            char help[3];
            for ( j = 0; j < 3; j++)    swap(&leaderboard[i][j], &leaderboard[i+1][j]);
            display_string(0,"``LEADERBOARD``");
            for ( j = 0; j < 3; j++)
            {
                char ldrbrdspace[16] = "               "; 
                int k;
                for ( k = 0; k < 3; k++)    ldrbrdspace[k] = leaderboard[j][k];
                score_to_string(score[j]);
                for ( k = 3; k < 16; k++)   ldrbrdspace[k] = scorestring[k];
                display_string(j+1,ldrbrdspace);
            }
            display_update(1);
            delay(4);
        }
    }

    delay(3);
    
}
void score_screen()
{
    PORTE = 0xff;
    char select_letter = 0;
    char name[] = "      AAA      ";
    realname[0] = 'A';
    realname[1] = 'A';
    realname[2] = 'A';
    score_to_string(scorenow);
    while(select_letter < 3)
    {
        if(getbtns() & 1)
        {
            realname[select_letter] = (realname[select_letter] - 'A' + 1) % 26 + 'A';
            while(getbtns() & 1)
            {}
        }
        if(getbtns() & 2)
        {
            realname[select_letter] = (realname[select_letter] - 'A' - 1) % 26 + 'A'; // modulo -1 is a feature not a bug :)
            while(getbtns() & 2)
            {}
        }
        if(getbtns() & 4)
        {
            select_letter--;
            if(select_letter < 0)   select_letter = 0;
            while(getbtns() & 4)
            {}
        }
        if(getbtns() & 8)
        {
            select_letter++;
            while(getbtns() & 8)
            {}
        }
                

        name[6] = realname[0];
        name[7] = realname[1];
        name[8] = realname[2];
        
        display_string(0, "ENTER YOUR NAME");
        display_string(1,name);
        display_string(2, "     SCORE     ");
        display_string(3, scorestring);
        display_update(2);
    }
    update_leaderboard();
}
void plr_1()
{
    clear();
    GAMEOVER = 0;
    scorenow = 0;
    char gameclock = 1;
    WAVE = 0;
    maxYY = 0;
    while(!GAMEOVER)
    {
        wave_edit(WAVE);
        display_string(0, " ");
        display_string(1,wave_num);
        display_string(2, " ");
        display_string(3, " ");
        display_update(2);
        delay(3);
        clear();
        create_aliens(0,10 * WAVE);
        while(aliens_left > 0)
        {
            PORTE = scorenow;
            move();
            print_ship(1);
            alien_shoot(WAVE * 10 * max(1,10 * WAVE - aliens_left));
            animate_bullets();
            print_screen();
            if(maxYY > 22) GAMEOVER = 1;
            if(GAMEOVER)    break;
            if(gameclock == 0)    move_aliens();
            gameclock++;
            gameclock %= max(1,(aliens_left - WAVE )  + 1);
        }
        WAVE++;

    }

    score_screen();


}
void plr2map()
{
    int i;
    for ( i = 0; i < MAXX; i++)
    {
        int j;
        for ( j = 0; j < MAXY/2; j++)
        {
            board[i][j+5] |= board2[MAXX-i-1][MAXY-j-1];
        }    
    }
    

}


void plr_2()
{
    clear();
    plr2map();
    GAMEOVER = 0;
    Xship2 = 65;
    Xship = 63;
    while(!GAMEOVER)
    {
        move();
        move2();
        print_ship(1);
        print_ship(2);
        animate_bullets();
        print_screen();
    }

    display_string(0, "```GAME`OVER```");
    display_string(1," ");
    if(PLR_WIN == 1)    display_string(2, "   PLAYER_1    ");
    if(PLR_WIN == 2)    display_string(2, "   PLAYER_2    ");
    display_string(3, "      WIN      ");
    display_update(1);
    delay(10);


}






void spcinvmenu()
{
    
    while(1)
    {
        scorenow = 0;
        display_string(0, "SPACE`INVADERS`");
        display_string(1, "   1_PLAYER");
        display_string(2, "   2_PLAYERS");
        display_string(3, "  LEADERBOARD");
        display_update(0x01 | (1<<mode));
        mode = in_range(mode,0,3);
        if(getbtns() & (1<<2))
        {
            mode++;
            while(getbtns() & (1<<2))
            {}
        }
        if(getbtns() & (1<<1))
        {
            mode--;
            while(getbtns() & (1<<1))
            {}
        }
        if(getbtns() & (1<<3))
        {
            
            while(getbtns() & (1<<3))
            {}
            display_clear();
            if(mode == 1)   plr_1();
            if(mode == 2)   plr_2();
            if(mode == 3)   update_leaderboard();
            if(mode == 0)   return;
            
        }
    }
}
