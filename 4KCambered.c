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

void main(void) {
    uint8_t TKey ;
    TMR0_Initialize();
     SerialPORT_Init();
     UNIPOLAR_MOTOR_Init();
     DRV8818_Motor_Init();
     PWM2_Initialize();
     KEY_Init();
     TX1REG=RC1REG; //
     
     while(1)
     {
         TKey = KEY_Scan();
         switch(TKey){
             case _KEY_TRG_1_CW :
                 
                 break;
             case _KEY_TRG_2_CCW:
                 
                 break;
             case _KEY_TRG_3_SPEED:
                 break;
             case _KEY_TRG_4_UP:
                 break;
                 
             case _KEY_TRG_5_DOWN:
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
    //TIMER0 overflow interrupter 
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
         PIE0bits.TMR0IE =0;
         PIR0bits.TMR0IF =0;
         TMR0=0x06;  // load intial value 0x06
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
    if(IOCCFbits.IOCCF4==1 ){
         Unipolar_StopMotor() ;
    
    }
    //Sensor GPIO interrupter Bipolar 
    if(IOCCFbits.IOCCF5 ==1){
        DRV8818_Stop();
    
    }



}
