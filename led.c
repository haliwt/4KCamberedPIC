#include "led.h"

void LED_Init(void)
{
    ANSELEbits.ANSELE1 = 0;
    ANSELEbits.ANSELE2 = 0;

    TRISEbits.TRISE1=0;
    TRISEbits.TRISE2 = 0 ;

}