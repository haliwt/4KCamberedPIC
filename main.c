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
#include "led.h"



void main(void) {
 
     OSCCON1 = 0b01110000;
     OSCCON2 = 0b01110000;
     OSCFRQ  = 0b00000010;
     OSCEN = 0b11110000;
    
   
     SENSOR_Init();
     KEY_Init();
     Init_Tm1650();
     Digital_NumberInit();
     TMR0_Initialize();
     //SerialPORT_Init();
     UNIPOLAR_MOTOR_Init();
     DRV8818_Motor_Init();
     PWM2_Initialize();
    // USART_BlueToothInit();
     USART2_Init();
     LED_Init();

     variate.gSpeedcnt = 1;

     while(1)
     {

       
        TX1REG=0x04;
       // TKey =KEY_Scan();
        SysMode(TKey);
        CheckRun();
        

    }
}
#if 1
/**********************************************************
 * 
 * TMR0 Overflow 1.0ms interrupter function,
 * 
 * ********************************************************/
void __interrupt() Hallsensor(void)
{
    

    static uint8_t blink=0,blink2=0;
    //TIMER0 overflow interrupter 1.0ms
    if(PIR0bits.TMR0IF == 1)
    {
        variate.getTime_10ms++; //1ms
         PIR0bits.TMR0IF =0;
         TMR0=0x06;  // load intial value 0x06
        //10ms
         if(variate.getTime_10ms > 9){
            variate.getTime_10ms =0;
            variate.getTime_100ms ++;
             
        }
        //100ms=1s
        if(variate.getTime_100ms>9){
             variate.getTime_100ms =0;
             variate.getTime_1s ++ ;
             blink2 = blink2 ^ 0x1;
             if (blink2 == 1)
                 LED2 = 1;
             else
                 LED2 = 0;
         }
         //1s
         if(variate.getTime_1s >9){
            variate.getTime_1s =0;
            
             blink = blink ^ 0x1;
            if(blink==1)
             LED1=1;
            else LED1=0;
            TX2REG=variate.gstep_to_index ;
         }
         
    }
    //usart interrupter 
    if(PIR3bits.RC1IF==1 ) //???????????
    {
        PIR3bits.RC1IF = 0;
        TX1REG=0x02; //???????????
    }
    //PWM OF TIMER2
    if(PIR4bits.TMR2IF == 1){
        TMR2IF = 0;
        T2PR = 0xF9; //249 period = 0.002s (500Hz)
    }
   
    if(PIR0bits.INT2IF ==1){ //CCW 
        PIR0bits.INT2IF= 0;
        Unipolar_StopMotor();
        TKey = 2;
        LED1=1;
        LED2=0;
        DIRECTION=0;
        UNIPOLAR_ON = 0;  //run start 
    }
    if(PIR0bits.INT1IF ==1){  //CW
        PIR0bits.INT1IF = 0;
        Unipolar_StopMotor();
        TKey = 1;
        LED2=1;
        LED1=0;
        UNIPOLAR_ON = 0; //run start
        DIRECTION=1;
        
    }

}
#endif 