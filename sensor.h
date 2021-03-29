#ifndef __SENSOR_H
#define __SENSOR_H
#include "ge.h"

#define SENSOR_POWER_1        PORTCbits.RC3
#define SENSOR_POWER_2        PORTEbits.RE0
#define SENSOR_SIG_1          PORTCbits.RC4
#define SENSOR_SIG_2          PORTCbits.RC5

#define SENSOR_SIG_3        PORTEbits.RE1 
#define SENSOR_SIG_4        PORTEbits.RE2


void SENSOR_Init(void);




#endif 