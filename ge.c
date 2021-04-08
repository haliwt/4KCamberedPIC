#include "ge.h"
#include "unipolar.h"
#include "bipolar.h"
#include "key.h"
#include "led.h"
#include "sensor.h"
#include "usart.h"
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times T= 1/8mhz = 0.125uS
    *Input Ref:  8MHz  one cycle = 0.5us
    *Return Ref:
    *
*******************************************************************/
void  delay_10us(uint16_t n)
{
    uint16_t i,j=0;
    for(j=0;j<n;j++){
        for(i=0;i<5;i++){
            __asm("nop");  //1 one cycle
            __asm("nop");  //1 one cycle 
        }                  //2 one cycle
    }
    
}
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times T= 1/8mhz = 0.125uS
    *Input Ref:  8MHz  one cycle = 0.5us
    *Return Ref:
    *
*******************************************************************/
void SysModeRail(uint8_t val)
{

    if (!val)
    {
        return;
    }
    
    switch (val)
    {
   

    case _KEY_TRG_4_UP:

        RunMode_Rail = 4;

        break;

    case _KEY_TRG_5_DOWN:

        RunMode_Rail = 5;

        break;
    }


    
}
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times T= 1/8mhz = 0.125uS
    *Input Ref:  8MHz  one cycle = 0.5us
    *Return Ref:
    *
*******************************************************************/
void SysModeDisk(uint8_t val)
{

    
    if (!val)
    {
        return;
    }
    
    switch (val)
    {
    case _KEY_TRG_1_CW:

        RunMode_Disk = 1;
        break;

    case _KEY_TRG_2_CCW: //SW1

        RunMode_Disk = 2;
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
void CheckRunRail(uint8_t bval)
{
    if(!bval) return ;
    
    
    switch (bval)
    {

        
        case Nothing:
            DRV8818_Stop();
            variate.gPositionUp =0;
            variate.gPositionDown =0;
            
            break;

        case bibolar_UP: //SW3
            TX1REG = 0xb1;

            if( variate.gPositionUp==1){
                DRV8818_Stop();
                variate.gPositionDown=0; 
                variate.gCountUp=0;
                StepUnibolar_Driver();
            }
            else {
                 DRV8818_MotorDriver();
                 StepUnibolar_Driver();
            }
            if(variate.gCountDown >1)variate.gPositionDown =0;
           

        break;

        case bibolar_DOWN:
            TX1REG =0xb2;
            if( variate.gPositionDown==1){
                DRV8818_Stop();
                variate.gPositionUp=0;
                variate.gCountDown =0;
                StepUnibolar_Driver();
            }  //
            else{
                DRV8818_MotorDriver();
                StepUnibolar_Driver();
            }
            if(variate.gCountUp >1)variate.gPositionUp =0;
            
                
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
void CheckRunDisk(uint8_t uval)
{
     if(!uval) return ;

    switch (uval)
    {

    case Nothing:
         HALF_PHASE = 1;
         ONE_PHASE = 1;
        Unipolar_StopMotor();
        
        break;

    case unibolar_CW:
    {
         TX1REG = 0xa1;
         StepUnibolar_Driver();
         
        if(TKeyBibolar == 3){
            if( variate.gPositionUp==1){
                DRV8818_Stop();
                variate.gPositionDown=0; 
                variate.gCountUp=0;
            }
            else  DRV8818_MotorDriver();
            if(variate.gCountDown >1)variate.gPositionDown =0;
        }
        if(TKeyBibolar ==4){ //Down
            if( variate.gPositionDown==1){
                        DRV8818_Stop();
                        variate.gPositionUp=0;
                        variate.gCountDown =0;
            }  //
            else  DRV8818_MotorDriver();
            if(variate.gCountUp >1)variate.gPositionUp =0;
        }

            

        
    }
    break;

    case unibolar_CCW: //SW1
    {
         TX1REG = 0xa2;
        StepUnibolar_Driver();
        if(TKeyBibolar == 3){
            if( variate.gPositionUp==1){
                DRV8818_Stop();
                variate.gPositionDown=0; 
                variate.gCountUp=0;
            }
            else  DRV8818_MotorDriver();
            if(variate.gCountDown >1)variate.gPositionDown =0;
        }
        if(TKeyBibolar ==4){ //Down
            if( variate.gPositionDown==1){
                        DRV8818_Stop();
                        variate.gPositionUp=0;
                        variate.gCountDown =0;
            }  //
            else  DRV8818_MotorDriver();
            if(variate.gCountUp >1)variate.gPositionUp =0;
        }

        

    }
    break;

        
    }
   
   
}
