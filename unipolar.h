#ifndef __UNIPOLAR_H
#define __UNIPOLAR_H
#include <xc.h>
#include "ge.h"

#define STEP        PORTDbits.RD2
#define DIRECTION   PORTDbits.RD1
#define HAL_STEP    PORTDbits.RD3
#define ONE_PHASE   PORTDbits.RD4

void UNIPOLAR_MOTOR_Init(void);
void Stepper_Motor(int revcnt, uint8_t revdir,uint8_t gapdly);






#endif 