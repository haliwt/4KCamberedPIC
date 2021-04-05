#include "ge.h"
#include "unipolar.h"
#include "bipolar.h"
#include "key.h"
#include "led.h"
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times T= 1/8mhz = 0.125uS
    *Input Ref:
    *Return Ref:
    *
*******************************************************************/
void  delay_us(uint16_t n)
{
    uint16_t i,j=0;
    for(j=0;j<n;j++){
        for(i=0;i<8;i++){
            asm("nop");
        }
    }
    
}

void SysMode(uint8_t val)
{

    static uint8_t key_cw;
    static uint8_t key_ccw;
    static uint8_t key_up;
    static uint8_t key_down;
    static uint8_t key_speed;
    if (!val)
    {
        return;
    }
    
    switch (val)
    {
    case _KEY_TRG_1_CW:

        RunMode = 1;
        break;

    case _KEY_TRG_2_CCW: //SW1

        RunMode = 2;
        break;

    case _KEY_TRG_3_SPEED:

        RunMode = 3;
        break;

    case _KEY_TRG_4_UP:

        RunMode = 4;

        break;

    case _KEY_TRG_5_DOWN:

        RunMode = 5;

        break;
    }


    
}

/******************************************************************
    *
    *Function Name:void CheckRun(void)
    *Function :run mode hold process
    *Input Ref:NO
    *Return Ref:NO
    *
*******************************************************************/
void CheckRun(void)
{
    static uint8_t blink = 0;
    switch (RunMode)
    {

    case Nothing:
        // Unipolar_StopMotor();
        // DRV8818_Stop();

        break;

    case unibolar_CW:

        StepUnibolar_Driver();

        break;

    case unibolar_CCW: //SW1

        StepUnibolar_Driver();
         break;

    case bibolar_UP: //SW3
        DRV8818_MotorDriver(1, 1);

        break;

    case bibolar_DOWN:
        DRV8818_MotorDriver(1, 0);

        break;

    case motorStop:
        blink = blink ^ 0x01;
        if (blink == 1)
            LED2 = 1;
        else
            LED2 = 0;
        break;

    default:

        break;
        
    }
   
}
