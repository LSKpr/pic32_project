// //#include <stdlib.h>
// //#include <stdio.h>
// //#include <time.h>

// #include <stdint.h>
// #include <pic32mx.h>
// #include "mipslab.h"

// #define col       128
// #define rows       32
// #define pipeCount   3

// int gameOver = 0;
// char ch;

// // void Draw();
// // void Pipes();
// // void HitTest();


// typedef struct
// {
//     int x;
//     int y;
// }PIX;

// PIX bird;
// PIX pipes[3];

// void Initializeboard()
// {
//     int x, y;
//     for ( x = 0; x < rows; x++)
//     {
//         for ( y = 0; y < col; y++)
//         {
//             board[x][y] = ' ';
//         }
//     }
// }

// void Draw() {
//     int x, y;
//     for ( y = 0; y <= col; y++)  {
//         board[0][y] = '#';
//     }

//     for (x = 1; x < rows - 1; x++)   {
//         board[x][0] = '#';

//         for ( y = 1; y < col - 1; y++)     {
//             if (bird.x == x && bird.y == y)
//             {
//                 board[x][y] = 'B';
//             }
//             else{
//                 board[x][y] = ' ';        //here it will set everything to ' ', even the pipes so depending on
//             }                               //what you choose for the pipes u should change it
//         }                                   //ex if pipes are '|' change condition to <else if (board[x][y] != '|')>

//         board[x][col - 1] = '#';
//     }

//     for (y = 0; y <= col; y++){
//         board[rows - 1][y] = '#';
//     }

//     toTable(board);
//     display_image(0,screen2);
// }

// void Pipes()
// {
//     int i;
//     for (i = 0; i < pipeCount; i++){
//         if (pipes[i].x == -1) {
//           if (i == 0) {
//             pipes[i].x = pipes[2].x + 15;
//           }else {
//            pipes[i].x = pipes[i - 1].x + 15;
//            }
//           pipes[i].y = (rrand(1) % 7) + 5;
//         }

//     }
// }

// void HitTest()
// {
//     if (bird.y == 15){
//         gameOver=1;
//     }
//     int i;
//     for (i = 0; i < pipeCount; i++){
//         if ((bird.x -2 < pipes[i].x +2) && (bird.x > pipes[i].x -2) &&((bird.y < pipes[i].y -2) ||(bird.y > pipes[i].y +1)))
//         {
//             gameOver = 1;
//         }
//     }
// }

// void getch2(void) {
//     if(getbtns()&0x8)   
//       ch = 'w';   //only use 1 btn
//     else  
//      ch = ' ';
//     PORTE = getbtns();
// }
// void clear_brd()
// {
//     int i, j;
//     for ( i = 0; i < 128; i++)
//     {
//         for ( j = 0; j < 32; j++)
//         {
//             board[i][j] = 0;
//         }
        
//     }
    
// }
// void bird_game(){
//     srrand(TMR2);
//     //function above is to change the game aspect each time it is played
//     //basically makes it random everytime
//     //it is not a must in our code

//     bird.x = 10;
//     bird.y = 10;
//     int i;
//     for (i = 0; i < pipeCount; i++){
//         pipes[i].x = 25 + 15 * i;
//         pipes[i].y = (rrand(1)%7) +5;
//     }

//     int frame = 0;

//     // printf("Press the button to jump.\n");

//     // for (i = 0; i <= rows; i++){
//     //     printf("\n");
//     // }
//     clear_brd();
//     Draw();

//     //here u can use interrupts to check if a button is pressed
//     //if u don t add interrupts the game will start immediately
//     //
//     //add interrupts:
//     //

//     while(getbtns() == 0){}

//     while (!gameOver){
//         getch2();
//         if (ch == 'w'){
//             bird.y -= 2;
//         }
//         if (frame == 2){
//             bird.y++;
//             for (i = 0; i < 3; i++){
//                 pipes[i].x--;
//             }
//             frame = 0;
//         }
//         HitTest();
//         Draw();
//         Pipes();
//         // delay(1);
//         frame++;
//         quicksleep(100 * 1000);                //this is for delay, use interrupts or delays here instead of this one
//     }
// }
