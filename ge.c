#include "ge.h"
#include "unipolar.h"
#include "bipolar.h"
#include "key.h"
#include "led.h"
#include "sensor.h"
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
            __asm("nop");
        }
    }
    
}

void SysMode(uint8_t val)
{

    
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
       
        variate.gPositionUp =0;
        variate.gPositionDown =0;

        break;

    case unibolar_CW:

        StepUnibolar_Driver();

        break;

    case unibolar_CCW: //SW1

        StepUnibolar_Driver();
         break;

    case bibolar_UP: //SW3
        if( variate.gPositionUp==1){
            DRV8818_Stop();
            variate.gPositionDown=0; 
            variate.gCountUp=0;
        }
        else  DRV8818_MotorDriver(1, 1);
        if(variate.gCountDown >1)variate.gPositionDown =0;

        break;

    case bibolar_DOWN:
        if( variate.gPositionDown==1){
             DRV8818_Stop();
             variate.gPositionUp=0;
             variate.gCountDown =0;
        }  //
        else
            DRV8818_MotorDriver(1, 0);
        if(variate.gCountUp >1)variate.gPositionUp =0;

        break;

    case motorStop:
        HALF_PHASE = 1;
        ONE_PHASE = 1;
        Unipolar_StopMotor();
        DRV8818_Stop();
        RunMode = Nothing;
        variate.gMotorDir=0;
        variate.gPositionUp =0;
        variate.gPositionDown =0;
        break;

    default:

        break;
        
    }
   
}
