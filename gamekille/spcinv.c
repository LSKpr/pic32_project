//  space invaders 
//  Kacper Lisik
//
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define MAXX 128
#define MAXY 32 
#define Yship   28
#define Yship2   7
char LOADING_TIME = 5;
char NEO_MODE = 0; //time slows down;
char leaderboard[3][3] = {"XXX","XXX","XXX"};
char scorestring[16] = "               ";
int score[3] = {0,0,0};
int scorenow;
int aliens_left;
int Xship = 63;
int Xship2 = 65;
char GAMEOVER = 0;
char PLR_WIN = 0;
int WAVE = 0;
int mode = 0;
int combo = 0;
int bombactive = 0;
int scoremult = 1;
struct bomb 
{
    char x , y;
    char stage;
};
struct bomb bomba;
/*
    1 - bunker
    2 - ship
    4 - plr2 ship
    8 - bullet
    16 - alien bullet
    32 - aliens
    64 - mothership
    128 - bomb
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
void killl(int x, int y, int type)
{
    // delay(1);
    if(x > 127 || x < 0 || y > 31 || y < 0) return;
    x = in_range(x, 0, 127);
    y = in_range(y, 0, 31);
    if(board[x][y] & type)
    {
        board[x][y] &= ~type; 
        killl(x-1,y, type);
        killl(x+1,y, type);
        killl(x,y+1, type);
        killl(x,y-1, type);
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
void plant_bomb(int x, int y)
{
    if(y < 2 || y>31 || x < 0 || x> 127)   return;
    board[x][y] |= 128;
}
void print_bomb()
{

    //square 
    int i, j;
    // for ( i = 0; i < 3; i++)
    // {
    //     for ( j = 0; j < 3; j++)
    //     {
    //         plant_bomb(bomba.x + i - 1, bomba.y + j - 1);
    //     }
        
    // }
    //cross
    for ( j = 0; j < 3; j++)
    {
        plant_bomb(bomba.x, bomba.y + j - 1);
        plant_bomb(bomba.x + j -1, bomba.y);
    }
    
}    
// void bomb_on_board(char x, char y)
// {
//     // if( x < 1 || x > 126 || y < 1 || y > 30)
//     // {
//     //     killl(x,y,128);
//     //     bombactive = 0;
//     //     bomba.stage = 0;
//     //     return;
//     // }
//     if(board[x][y] & 1) destroy(x,y,0);
//     if(board[x][y] & 32)
//     {
//         bomba.stage = 2;
//         killl(x,y,32);
//         scorenow += scorenow;
//         combo++;
//     }
// }
void bmb_clear()
{
    int i;
    for ( i = 0; i < MAXX; i++)
    {
        int j;
        for ( j = 0; j < MAXY; j++)
        {
            if (board[i][j] & 128)
            {
                if(board[i][j] & 32)
                {
                    killl(i,j,32);
                    // combo++;
                    scorenow += scoremult;
                    aliens_left--;
                    if(bomba.stage == 1) bomba.stage = 2;
                }
                if(board[i][j] & 1)
                {
                    destroy(i,j,0);
                    board[i][j] = 0;
                    if(bomba.stage == 1) bomba.stage = 2;
                }
                board[i][j] = 0;
            }
        }    
    }
}
void animate_bomb(char up)
{
    bmb_clear();
    char i, j;
    if(bomba.stage == 1)
    {
        // for ( i = 0; i < 3; i++)
        // {
        //     if(bomba.stage != 1)    break;
        //     for ( j = 0; j < 3; j++)
        //     {
        //         char x = bomba.x - 1 + i;
        //         char y = bomba.y - 1 + j; 
        //         // bomb_on_board(x,y);
        //     }
            
        // }
        if(up)  bomba.y--;
        if(bomba.y <= 1)
        {
            bmb_clear();
            bomba.stage = 0;
            bombactive = 0;
            return;
        }
        bmb_clear();
        print_bomb(bomba.x,bomba.y);
    }
    else if(bomba.stage == 2)
    {
        bmb_clear();
        for ( i = 1; i < MAXX-1; i++)
        {
            plant_bomb(i,bomba.y);
        }
        bomba.stage = 3;
    }
    else if(bomba.stage == 3)
    {
        for ( i = 1; i < MAXX-1; i++)
        {
            plant_bomb(i,bomba.y - 1);
            plant_bomb(i,bomba.y + 1);
            plant_bomb(i,bomba.y);
        }
        bmb_clear();
        for ( i = 1; i < MAXX-1; i++)
        {
            plant_bomb(i,bomba.y - 1);
            plant_bomb(i,bomba.y + 1);
            plant_bomb(i,bomba.y);
        }
        bomba.stage = 4; 
    }
    else if(bomba.stage == 4)
    {
        bmb_clear();
        for ( i = 1; i < MAXX-1; i++)
        {  
            plant_bomb(i,bomba.y);
        }
        bomba.stage = 5;
    }
    else if(bomba.stage == 5)   {bmb_clear();    bomba.stage = 0;} //nothing left 
    

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
                if(board[i][j] & 8 || board[i][j-1] & 8) combo = 0;
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
                    killl(i,j-1, 32);
                    scorenow += scoremult;
                    combo++;
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
    if(getbtns()&0x4 && ammo > 5)
    {
        if(bombactive)
        {
            ammo = 0;
            if(bomba.stage == 0)
            {
                bomba.stage = 1;
                bomba.x = Xship;
                bomba.y = Yship - 2;
                ammo+=3;
                print_bomb();
                combo = 0;
                // bombactive = 0;
            }
            else if(bomba.stage == 1)
            {
                bomba.stage++;
                bombactive = 0;
            }
            
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
    // int j;
    // for ( j = 0; j < MAXX; j++)
    // {
    //     board[j][0] = 0;
    //     board[j][1] = 0;
    // }    
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
                killl(i,j,32);
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
                if(rrand(scorenow) < chance)   board[i+1][j+1] |= 16;
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
                if(board[i][j] & 32)
                {
                    killl(i,j, 32);
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
                if(board[i][j] & 32)
                {
                    killl(i,j, 32);
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
            int swp = score[i];
            score[i] = score[i+1];
            score[i+1] = swp; 
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
    combo = 0;
    scorenow = 0;
    char gameclock = 1;
    WAVE = 0;
    bombactive = 0;
    maxYY = 0;
    int bomb_money = 20;
    bomba.stage = 0;
    int bomb_alarm = 0;
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
            PORTE = 0;
            scoremult = 1;
            LOADING_TIME = 5;
            NEO_MODE = 0;

            // if((scorenow > bomb_money) && bombactive == 0)  {bomb_money += 50; bombactive = 1;}
            if(bombactive || bomba.stage == 1)  PORTE = (++bomb_alarm % 15 < 7)?0xA:0x5;
            else    PORTE|= (combo & 0xf);
            bomb_alarm %= 15;

            if(combo > 2)   {LOADING_TIME = 2;  PORTE|= 0x80;}
            if(combo > 4)   {NEO_MODE = 1;  PORTE|= 0xC0;}
            if(combo > 7)   {LOADING_TIME = 1;  PORTE|= 0xE0;}
            if(combo > 9)   {scoremult = 2;PORTE|=0xf0;}
            if(combo > 11)  {bombactive = 1;}
            move();
            print_ship(1);
            alien_shoot((WAVE/2 + 1) * max(1,10 * WAVE - aliens_left));
            if(gameclock % (1 + NEO_MODE) == 0) animate_bullets();
            if(maxYY > 22) GAMEOVER = 1;
            if(GAMEOVER)    break;
            if(gameclock == 0)    move_aliens();
            if(gameclock % (2 + 2* NEO_MODE) == 0) animate_bomb(1);

            gameclock++;
            gameclock %= max(1,(aliens_left - WAVE )  + 1) * (1 + NEO_MODE);
            // PORTE = combo;
            print_screen();
        }
        WAVE++;
        bmb_clear();
        bomba.stage = 0;
        // bombactive = 1;

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
    bombactive = 0;
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
        scoremult = 1;
        LOADING_TIME = 5;
        NEO_MODE = 0;
        scorenow = 0;
        combo = 0;
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
