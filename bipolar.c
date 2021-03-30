#include "bipolar.h"
#include "ge.h"

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
    
    RESETn =1; //
    ENABLE_DRV =0;
    SLEEP_UNI = 1;
    PWM2_LoadDutyValue(variate.getDutyCycle);

}
/****************************************************************************
    *
    * Function Name: void PWM2_Initialize(void)
    * Function :PWM Period =[(T2PR+1)]*4*Tosc*(TMR2PS) //Tosc =1/8MHZ=0.125us
    *            PWM period = 0.002s (500Hz) ,TMR2PS =16
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
    T2PR = 0xF9; //249 period = 0.002s (500Hz)
    
	// MODE PWM; EN enabled; FMT=0 right_aligned; 
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
    
    //Select prescaler value CK2PS = 16
    T2CON = 0xC0; 
  //  T2CONbits.ON = 1; //Timer is ON
	// Selecting Timer 2
	CCPTMRSbits.C2TSEL = 0x1;
    
}
/****************************************************************************
    *
    * Function Name: void PWM2_LoadDutyValue(uint16_t dutyValue)
    * Function :PWM2 duty value = (CCPRxH :CCPRxL)/?4*(T2PR +1)?
    *                             (CCPRxH :CCPRxL)/1000       
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
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
        CCPR2H = dutyValue >> 8; //High MSB 2bit 
        CCPR2L =(uint8_t) dutyValue; //Low LSB 8bit 
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
    RESETn = 0; // low power disaple output
    ENABLE_DRV =1; //disable output PWM
    T2CONbits.ON = 0; //Timer is OFF
   
}