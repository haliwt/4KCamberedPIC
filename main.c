/*
 * File:   4KCambered.c
 * Author: Administrator
 *
 * Created on March 26, 2021, 9:49 AM
 */

// CONFIG1
#pragma config MCLRE =EXTMCLR
#pragma config FEXTOSC = ECM     // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF
#pragma config CLKOUTEN = OFF
#pragma config CSWEN =ON 
#pragma RSTOSC = ECM

//CONFIG2 
#pragma config XINST = OFF
#pragma config BOREN = OFF
#pragma config LPBOREN = OFF
#pragma config LVP = OFF



#define _XTAL_FREQ 8000000
#include <xc.h>
#include "key.h"
#include "sensor.h"

#include "tmr0.h"
#include "usart.h"
#include "unipolar.h"
#include "bipolar.h"
#include "TM1650.h"
#include "sensor.h"



void main(void) {
     uint8_t TKey;
     OSCCON1 = 0b01110000;
     OSCCON2 = 0b01110000;
     OSCFRQ  = 0b00000010;
     OSCEN = 0b11110000;
    
   
     SENSOR_Init();
     KEY_Init();
     Init_Tm1650();
     Digital_NumberInit();
     TMR0_Initialize();
     SerialPORT_Init();
     UNIPOLAR_MOTOR_Init();
     DRV8818_Motor_Init();
     PWM2_Initialize();
     variate.gSpeedcnt=3;
    
     
     while(1)
     {
         
        TKey =KEY_Scan();
         switch(TKey){
            case _KEY_TRG_1_CW :
                
                 Stepper_UnipolarMotor(-1,0);
                  
            break;
                 
            case _KEY_TRG_2_CCW:
                Stepper_UnipolarMotor(-1,1);
                
                 break;
            case _KEY_TRG_3_SPEED:
                 Unipolar_StopMotor();
                 
            break;
            
            case _KEY_TRG_4_UP:
                
            break;
                 
            case _KEY_TRG_5_DOWN:
               
            break;
            default:
                variate.gSpeed_Keyflag =0;
              
            break;
        }

    }
}
#if 1
/**********************************************************
 * 
 * TMR0 Overflow 1.0ms interrupter function,
 * 
 * ********************************************************/
void interrupter() 
{
    static uint8_t blink=0;
    //TIMER0 overflow interrupter 1.0ms
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        variate.getTime_10ms++;
        PIE0bits.TMR0IE =0;
         PIR0bits.TMR0IF =0;
         TMR0=0x06;  // load intial value 0x06
        //10ms
         if(variate.getTime_10ms > 9){
            variate.getTime_10ms =0;
            variate.getTime_100ms ++;
             
        }
        //100ms
        if(variate.getTime_100ms>99){
             variate.getTime_100ms =0;
             variate.getTime_1s ++ ;
         
         }
         //1s
         if(variate.getTime_1s >9){
            variate.getTime_1s =0;
            
             blink = blink ^ 0x1;
            if(blink==1)
             SENSOR_POWER_UP=1;
            else SENSOR_POWER_UP=0;
            TX2REG=variate.gstep_to_index ;
         }
         
    }
    //usart interrupter 
    if(PIR3bits.RC1IF==1 && PIE3bits.RC1IE ==1) //???????????
    {
        PIR3bits.RC1IF = 0;
        TX1REG=RC1REG; //???????????
    }
    //PWM OF TIMER2
    if(PIR4bits.TMR2IF == 1){
        TMR2IF = 0;
        T2PR = 0xF9; //249 period = 0.002s (500Hz)
    }
    //Sensor GPIO interrupter Unipolar
    if(PIR0bits.IOCIF ==1){
        PIR0bits.INT0IF =0;
        if(IOCCFbits.IOCCF4==1 ){
             IOCCFbits.IOCCF4=0;
             Unipolar_StopMotor() ;
        }
        //Sensor GPIO interrupter Bipolar 
        if(IOCCFbits.IOCCF5 ==1){
            IOCCFbits.IOCCF5=0;
            DRV8818_Stop();
        }
    }

}
#endif 