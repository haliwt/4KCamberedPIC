#ifndef __BIPOLAR_H
#define __BIPOLAR_H
#include "ge.h"
#include  <stdbool.h>

#define SRN             PORTAbits.RA0
#define RESETn          PORTAbits.RA1
#define USM0            PORTAbits.RA2
#define USM1            PORTAbits.RA3
#define DIR             PORTAbits.RA4
#define HOME            PORTAbits.RA5
#define SLEEP_UNI       PORTAbits.RA6
#define STEP_DRV        PORTBbits.RB0
#define ENABLE_DRV      PORTCbits.RC0


void DRV8818_Motor_Init(void);
void DRV8818_MotorDriver(void);

void PWM2_Initialize(void);
void PWM2_LoadDutyValue(uint16_t dutyValue);
bool PWM2_OutputStatusGet(void);
void DRV8818_Stop(void);

#endif 