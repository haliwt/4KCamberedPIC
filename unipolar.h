#ifndef __UNIPOLAR_H
#define __UNIPOLAR_H
#include "ge.h"

#define UNIPOLAR_ON     PORTDbits.RD0
#define STEP            PORTDbits.RD2
#define DIRECTION       PORTDbits.RD1
#define HALF_PHASE      PORTDbits.RD3   //UCN5804LB 10PIN=1
#define ONE_PHASE       PORTDbits.RD4   //UCN5804LB 9PIN =0

void UNIPOLAR_MOTOR_Init(void);
void Stepper_UnipolarMotor(int revcnt, uint8_t revdir);
void Unipolar_StopMotor(void);






#endif 