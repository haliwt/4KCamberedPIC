#ifndef __LED_H
#define __LED_H
#include "ge.h"

#define LED1    PORTEbits.RE1//PORTCbits.RC4
#define LED2    PORTEbits.RE2//PORTCbits.RC5

void LED_Init(void);



#endif 