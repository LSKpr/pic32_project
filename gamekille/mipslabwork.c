/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog
   This file modified 2023-01-23 by Kacper Lisik

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
// #include <stdio.h>
// #include <string.h>
#define NoG 8 // number of games
int selectGame = 1;
char games[NoG][16] = {"GAME", "SNAKE", "SPC_INV", "FLPBRD_not_wrkng", "Gameslot 0", "Gameslot 1", "Gameslot 2 ", " "};
int mytime = 0x5957;
int prime = 1234567;
int timeoutcount = 0;
char textstring[] = "text, more text, and even more text!";
char ammo = 0;
char ammo2 = 0;
/* Interrupt Service Routine */
void user_isr(void)
{

    if (IFS(0) & (1 << 8))
    {
        gametick++;
        ammo++;
        ammo = in_range(ammo,0,250);
        ammo2++;
        ammo2 = in_range(ammo2,0,250);
        IFS(0) &= !(1 << 8);
    }
    // if(IFS(0) & (1<<19))
    // {
    //   PORTE++;
    IFS(0) &= !(1 << 19);
    // }

    // if(timeoutcount >= 10)
    // {
    //   timeoutcount = 0;
    //   time2string( textstring, mytime );
    //   display_string( 3, textstring );
    //   display_update();
    //   tick( &mytime );
    // }
    // IFS(0)=0;
}
/* Lab-specific initialization goes here */
void labinit(void)
{

    // 1/80.000.000 -> 256/80.000.000 -> 100ms = 31.250
    T2CON = 0x8070; // 256 prescaling
    PR2 = 31250;
    TMR2 = 0;
    PORTE = 0;
    IEC(0) |= (1 << 8); // enable Interrupt 0xbf881060
    IEC(0) |= (1 << 19);
    IPC(2) |= 30;
    IPC(4) |= 31 << 24;
    // buttons and switches
    TRISE = 0;
    TRISD |= 0x0FF0;
    enable_interrupt();
    IFS(0) = 0;
    display_image(0, screen2);
    // delay(10000);
    srrand(TMR2);
    return;
}
/* This function is called repetitively from the main program */
void labwork(void)
{
    // menu
    selectGame = min(NoG - 2, max(selectGame, 1));
    display_string(0, "GAME`KILLE`````");
    display_string(1, *games + 16 * (selectGame - 1));
    display_string(2, *games + 16 * (selectGame));
    display_string(3, *games + 16 * (selectGame + 1));
    display_update(0x5); // 0x5 = 0101 - highlight 1st and 3rd line
    if (getbtns() & (1 << 2))
    {
        selectGame++;
        while (getbtns() & (1 << 2))
        {
        }
    }
    if (getbtns() & (1 << 1))
    {
        selectGame--;
        while (getbtns() & (1 << 1))
        {
        }
    }
    PORTE = getbtns();
    if (getbtns() & (1 << 3))
    {

        while (getbtns() & (1 << 3))
        {
        }
        display_clear();
        if (selectGame == 1)
        {
            // display_image(0,snakescreen);
            // delay(3);
            snake_game();
        }
        else    if(selectGame == 2) spcinvmenu();
        // else    if(selectGame ==3)  bird_game();
    }
    // display_image(0, screen2);
}
