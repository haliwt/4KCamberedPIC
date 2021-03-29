#include "bipolar.h"
#include <xc.h>
#define PWM2_INITIALIZE_DUTY_VALUE    511
/****************************************************************************
    *
    * Function Name: void DRV8818_Motor_Init(void)
    * Function :Initial motor for GPIO 
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void DRV8818_Motor_Init(void)
{
   ANSELA = 0x00; //digital I/O 
   TRISA = 0x00;  //GPIO input 
   
   ANSELBbits.ANSELB0 = 0;
   TRISBbits.TRISB0 = 0;
   
   ANSELCbits.ANSELC0 = 0;
   TRISCbits.TRISC0 = 0;

}
/****************************************************************************
    *
    * Function Name: DRV8818_MotorDriver(void)
    * Function :bipolar motor be drive
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void DRV8818_MotorDriver(void)
{
    

}
/****************************************************************************
    *
    * Function Name: void PWM2_Initialize(void)
    * Function :PWM2
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void PWM2_Initialize(void)
{
    
    // Set the PWM2 to the options selected in the User Interface
    RB0PPS = CCP2;
	ANSELBbits.ANSELB0 = 0;
    TRISBbits.TRISB0 = 0;
    
    //period Timer of T2PR = PWM of period
    T2PR = 0xF9; //period = 0.002s (500Hz)
    
	// MODE PWM; EN enabled; FMT right_aligned; 
	CCP2CON = 0x8C; //0b1000 1100
    
    //CCPR2bits.CCPR2H 0f 8,9bit PWM duty cycle ,FMT=0; 
     // RH 1; 
	CCPR2H = 0x01;    
	
	// RL 255; 
	CCPR2L = 0xFF; 
     
    //clear TMR2IF = 0
    PIR4bits.TMR2IF =0;
    
    //Select source frequency 
    T2CLKCON = 0x02 ; //Select Fosc = 8MHZ
    
    //Select prescaler value CKPS = 16
    T2CON = 0xC0; 
  //  T2CONbits.ON = 1; //Timer is ON
	// Selecting Timer 2
	CCPTMRSbits.C2TSEL = 0x1;
    
}

void PWM2_LoadDutyValue(uint16_t dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP2CONbits.FMT)
    {
        dutyValue <<= 6;
        CCPR2H = dutyValue >> 8;
        CCPR2L =(uint8_t)dutyValue;
    }
    else
    {
        CCPR2H = dutyValue >> 8;
        CCPR2L =(uint8_t) dutyValue;
    }
}

bool PWM2_OutputStatusGet(void)
{
   
    // Returns the output status
    return(CCP2CONbits.OUT);
}
/****************************************************************************
    *
    * Function Name: void DRV8818_Stop(void)
    * Function :PWM2
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void DRV8818_Stop(void)
{
    ENABLE_DRV =1; //disable output PWM
    T2CONbits.ON = 0; //Timer is OFF
}