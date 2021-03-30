/*
 * File:   4KCambered.c
 * Author: Administrator
 *
 * Created on March 26, 2021, 9:49 AM
 */
// CONFIG1
#pragma config NOSC = SOSC       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)

// CONFIG2~4
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


#include <xc.h>
#include "key.h"
#include "tmr0.h"
#include "usart.h"
#include "unipolar.h"
#include "bipolar.h"
#include "TM1650.h"

void main(void) {
    uint8_t TKey;
     Init_Tm1650();
     Digital_NumberInit();
     TMR0_Initialize();
     SerialPORT_Init();
     UNIPOLAR_MOTOR_Init();
     DRV8818_Motor_Init();
     PWM2_Initialize();
     KEY_Init();
    
     
     while(1)
     {
         TM1650_Set(0x68,1) ;
         TM1650_Set(0x6A,2) ;
         TM1650_Set(0x6C,3) ;
         TKey = KEY_Scan();
         switch(TKey){
             case _KEY_TRG_1_CW :
                 variate.gstep_to_index = 0x1;//print message 
                 variate.gunipolar_en =1;
                 if(variate.gSpeed_Keyflag == 1){
                     variate.gSpeedcnt = 1;
                 }
                 else{
                      variate.gSpeedcnt = 5;
                 }
                 Stepper_UnipolarMotor(200,0);
                  
                 break;
             case _KEY_TRG_2_CCW:
                 variate.gstep_to_index = 0x2;//print message 
                 variate.gunipolar_en=2;
                   if(variate.gSpeed_Keyflag == 1){
                       variate.gSpeedcnt = 1;
                 }
                 else{
                      variate.gSpeedcnt = 5;
                 }
                  Stepper_UnipolarMotor(200,1);
                
                 break;
             case _KEY_TRG_3_SPEED:
                  variate.gstep_to_index = 0x3;//print message 
                  variate.gSpeed_Keyflag =1; //flag bit 
                  if(variate.gunipolar_en ==1){
                      variate.gSpeedcnt = 1; //
                      TKey =  _KEY_TRG_1_CW;
                  }
                  else if(variate.gunipolar_en ==2){
                      variate.gSpeedcnt = 1;
                      TKey =  _KEY_TRG_2_CCW;
                   }
                  
                  if(variate.gbipolar_en ==1){
                      variate.getDutyCycle = 600;
                      TKey =  _KEY_TRG_4_UP; //Duty cycle 
                   }
                  else  if(variate.gbipolar_en ==2){
                      variate.getDutyCycle = 600;
                      TKey =  _KEY_TRG_5_DOWN; //Duty cycle 
                   }
                 
                 break;
             case _KEY_TRG_4_UP:
                 variate.gstep_to_index = 0x4;//print message 
                 variate.gbipolar_en =1;
                 if(variate.gSpeed_Keyflag ==1)
                     variate.getDutyCycle =500;
                 else 
                      variate.getDutyCycle =300;
                
                 DIR =1;
                 DRV8818_MotorDriver();
                 break;
                 
             case _KEY_TRG_5_DOWN:
                 variate.gstep_to_index = 0x5;//print message 
                 variate.gbipolar_en =2;
                if(variate.gSpeed_Keyflag ==1)
                     variate.getDutyCycle =500;
                 else 
                      variate.getDutyCycle =300;
                 DIR = 0;
                 DRV8818_MotorDriver();
                 break;
             default:
                 variate.gSpeed_Keyflag =0;
                 break;
        }
    }
}
/**********************************************************
 * 
 * TMR0 Overflow 1.0ms interrupter function,
 * 
 * ********************************************************/
void interrupter()
{
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
            TX2REG=variate.gstep_to_index ;
         }
         
    }
    //usart interrupter 
    if(PIR3bits.RC1IF==1 && PIE3bits.RC1IE ==1) //???????????
    {
        PIR3bits.RC1IF = 0;
        TX1REG=RC1REG; //???????????
    }
    //PWM
    if(TMR2IF == 1){
        TMR2IF = 0;
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
