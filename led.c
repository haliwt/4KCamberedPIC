#include "led.h"

void LED_Init(void)
{
    ANSELCbits.ANSELC4 = 0;
    ANSELCbits.ANSELC5 = 0;

    TRISCbits.TRISC4=0;
    TRISCbits.TRISC5 = 0 ;

}