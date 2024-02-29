#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw()
{
    return (PORTD & (0x0F00))>>8;
}

int getbtns()
{
    return ((PORTD & (0x0E0)) >> 4) | ((PORTF >> 1) & 0x1);       // buttons: 432 - portd; 1 - portf
}
// int getbtns(void){
//     int buttons234=PORTD;  //read from the buttons
//     buttons234=buttons234 >> 5;//shift 5 digits so that btn2 corresponds to LSB
//     buttons234=buttons234 & 0x7; //keep only the last 3 LSB
//     int button1=PORTF;
//     button1=button1>>1;
//     button1=button1 & 0x1;
//     int buttons;
//     buttons=(buttons234<<1) | button1;
//     return buttons;

// }