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

uint8_t redata;

void main(void) {
 
     
     unsigned long mV,vim;
     static uint8_t power_on=0;
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
    USART_BlueToothInit();
   //  USART1_Init();
     ADCC_Initialize();
     LED_Init();

     SENSOR_POWER_UP=1;
     SENSOR_POWER_DOWN=1; 

     while(1)
     {
         
     
         TX1REG = 0xcd;
       if(power_on ==0 ){
           power_on ++;
           variate.gPositionUp =0;
           variate.gPositionDown =0;
           variate.gMotorDir=0;
           RunMode = 0;
       }
       else {
                if(variate.gMotorDir==1)
                    vim= ADCC_GetSingleConversion(channel_ANC4, 10);   //J8 UP
                else if(variate.gMotorDir==2)
                        vim= ADCC_GetSingleConversion(channel_ANC5, 10); //J11 DOWN
                if(variate.gMotorDir==1 ||variate.gMotorDir==2){
                    mV=(vim * 5000)>>10; //mv =(vin *5000)/1024;
                    if(mV < 600){
                        LED1=0;
                        LED2 =0;
                    }
                    else if(mV >600){
                        LED2=1;
                        LED1=1;
                     if(variate.gMotorDir==1){ //UP J9
                             DRV8818_Stop();
                            variate.gPositionUp=1;
                            variate.gPositionDown =0;
                            
                        }
                        else if(variate.gMotorDir==2){ //DWON J11
                             DRV8818_Stop();
                            variate.gPositionDown=1;
                            variate.gPositionUp =0;
                        }
                    }
                }
       }

             // TKey =KEY_Scan();
        SysMode(TKey);
        CheckRun();
        //TX1REG = 0xAB;
        

    }
}

/**********************************************************
 * 
 * TMR0 Overflow 1.0ms interrupter function,
 * 
 * ********************************************************/
void __interrupt() Hallsensor(void)
{

     uint8_t recdata;
     static uint8_t blink = 0, blink2 = 0, speedValueCCW,speedValueCW;
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
        //100ms
        if(variate.getTime_100ms>9){
             variate.getTime_100ms =0;
             variate.getTime_1s ++ ;
         }
         //1s
         if(variate.getTime_1s >9){
            variate.getTime_1s =0;
            variate.gCountUp++;
            variate.gCountDown++;
            blink =blink ^ 0x01;
            if(blink==1)LED1=1;
            else LED1=0;
            
         }
         
    }
  
 
    if(PIR0bits.INT2IF ==1){ //CCW 
        PIR0bits.INT2IF= 0;
        Unipolar_StopMotor();
        TKey = 2;
        LED1=1;
        LED2=0;
        DIRECTION=0;
        UNIPOLAR_ON = 0;  //run start 
        variate.gMotorDir=0;
        speedValueCCW++;
        if(speedValueCCW ==1){
            
            DelayStepUnibolar = 100;  //max -slowly
        }
       
        else {
            DelayStepUnibolar = 10; //max  -fast
            speedValueCCW =0;
        }
    }
    if(PIR0bits.INT1IF ==1){  //CW
        PIR0bits.INT1IF = 0;
        Unipolar_StopMotor();
        TKey = 1;
        LED2=1;
        LED1=0;
        UNIPOLAR_ON = 0; //run start
        DIRECTION=1;
         variate.gMotorDir=0;
        speedValueCW++;
        if (speedValueCW == 1){

            DelayStepUnibolar = 100; //max -slowly
        }
        else {
            DelayStepUnibolar = 10; //max  -fast
            speedValueCW = 0;
        }
    }

    if (IOCBFbits.IOCBF3 == 1) //STOP 
    { 
        IOCBFbits.IOCBF3 = 0;
        variate.gMotorDir=0;
         TKey = 4;
         HALF_PHASE = 1;
         ONE_PHASE =1;
        Unipolar_StopMotor();
        DRV8818_Stop();
        variate.gPositionUp =0;
        variate.gPositionDown =0;
    }
    if (IOCBFbits.IOCBF4 == 1)//SW4 J8-TO motor 
    { //UP
        //LED2 = 0;
        IOCBFbits.IOCBF4 = 0;
        TKey = 8;
        SENSOR_POWER_UP =0;  //J8
        variate.gMotorDir=1;
        if(variate.gPositionUp ==1){
            DRV8818_Stop();
            variate.gPositionDown =0;
            variate.gCountUp=0;
        }
    }
    if (IOCBFbits.IOCBF5 == 1) //SW3 -J11--T0 -BACK mtor DOWN
    {   //DOWN
        //LED1 =0;
        // LED2 =0 ;
        IOCBFbits.IOCBF5 = 0;
        TKey = 9;
        SENSOR_POWER_DOWN =0;  //POWER RE0 J11  PORTC = RC4
         variate.gMotorDir=2;
        if(variate.gPositionDown ==1){
            DRV8818_Stop();
            variate.gPositionUp=0;
            variate.gCountDown =0;
        }
    }
    
    if(PIR3bits.RC1IF ==1)//） // 判断是否为串口接收中断
    {
         PIR3bits.RC1IF = 0;
         redata = RC1REG;
          TX1REG = redata;
         

       // 收到的数据发送回去
    }
    
   // if(PIR3bits.TX1IF ==1){
      //  PIR3bits.TX1IF =0;
       // TX1REG = redata;
   // }
}
