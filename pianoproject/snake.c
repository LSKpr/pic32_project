//
//  snakefinal.c
//  
//
//  Created by Emanuel Paraschiv on 24.02.2024.
//  Modified by Kacper Lisik 
//
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#define putch putchar

#define cols 128
#define rows 32
#define SNAKE_MAX_LEN 300

int isGameOver = 0;

char ch;
void getch(void) {
    if(getbtns()&0x8)   ch = 'w';
    else    if(getbtns()&0x4)   ch = 's';
    else    if(getbtns()&0x2)   ch = 'a';
    else    if(getbtns()&0x1)   ch = 'd';
    PORTE = getbtns();
}



void fill_grid() {
    int i,j;
    for(j=0; j<rows; j++) {
        for(i=0; i<cols; i++) {
            if(i==0||j==0||i==cols-1||j==rows-1) {
                board[i][j] = 1;
            }else{
                board[i][j] = 0 ;
            }
        }
    }
}


void clear_screen() {
    // printf("\033[H\033[J");
}


void print_grid() {
    toTable(board);
    display_image(0, screen2);
}

struct Component {
    int x, y;
};
struct Snake {
    int length;
    struct Component part[SNAKE_MAX_LEN];
};
struct Snake snake;

struct Food {
    int x, y;
    int consumed;
};

struct Food food;

void draw_snake() {
    int i;
    
    for(i=snake.length-1; i>0; i--) {
        board[ snake.part[i].x][snake.part[i].y] = 1;
    }
    board[ snake.part[0].x][snake.part[0].y] = 1;
}

void move_snake(int deltaX, int deltaY) {
    int i;

    for(i=snake.length-1; i>0; i--) {
        snake.part[i] = snake.part[i-1];
    }
    
    snake.part[0].x += deltaX;
    snake.part[0].y += deltaY;
}

void read_keyboard() {
    getch();
    switch(ch) {
        case 'w': move_snake( 0,-1); break;
        case 's': move_snake( 0, 1); break;
        case 'a': move_snake(-1, 0); break;
        case 'd': move_snake( 1, 0); break;
    }
}

void draw_food() {
    if( !food.consumed ) {
        board[ food.x][food.y] = 1;
    }
}


void create_food() {
    food.x = 1 + rrand(food.x) % (cols-2);
    food.y = 1 + rrand(food.y) % (rows-2);
    food.consumed = 0;
}


void create_snake() {
    snake.length = 1;
    snake.part[0].x = 1 + rrand(ch + 7) % (cols-8);
    snake.part[0].y = 1 + rrand(ch + 17*3) % (rows-8);
}

void game_rules() {
    int i;
    if( !food.consumed ) {
            if( food.x == snake.part[0].x &&
                food.y == snake.part[0].y ) {
                    food.consumed = 1;
                    snake.length++;
                    create_food(); // generate a new piece of food
            }
        }
    
    if( snake.part[0].x == 0 || snake.part[0].x == cols-1 ||
        snake.part[0].y == 0 || snake.part[0].y == rows-1 ) {
            isGameOver = 1;
    }
    
    for(i=1; i<snake.length; i++) {
        if( snake.part[0].x == snake.part[i].x && snake.part[0].y == snake.part[i].y ) {
                isGameOver = 1;
        }
    }
}

void snake_game()
{
    create_snake();
    create_food();
    isGameOver = 0;
    while(!isGameOver) {
        quicksleep((10000000/(5+snake.length)));
        fill_grid();
        draw_food();
        draw_snake();
        // delay(1);
        game_rules();
        clear_screen();
        // printf("Snake Game, Score: %d\n", snake.length * 10);
        print_grid();
        if( !isGameOver )
            read_keyboard();
    }
    // printf("Game Over, Final score: %d\n", snake.length * 10);
}
