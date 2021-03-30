#include "sensor.h"
#include <xc.h>

/***********************************************************
*
*
*
*
*
***********************************************************/
void SENSOR_Init(void)
{
  ANSELCbits.ANSELC3 = 0 ; //digital IO   //ANSELBbits.ANSELB0 = 0;
  TRISCbits.TRISC3 = 0;  //output   // TRISBbits.TRISB0 = 0;
  
  ANSELCbits.ANSELC4 = 0;
  ANSELCbits.ANSELC5 =0;
  
  TRISCbits.TRISC4 = 1;  //input IO
  TRISCbits.TRISC5 =1;   //input IO 
  
  ANSELEbits.ANSELE0 = 0;
  TRISEbits.TRISE0 = 0 ;
  
  ANSELEbits.ANSELE1 = 0;
  TRISEbits.TRISE1 = 1 ; //INPUT IO
  INT0PPSbits.INT0PPS =PORTEbits.RE1;
  
  ANSELEbits.ANSELE2 = 0;
  TRISEbits.TRISE2 = 1 ; //INPUT IO
  INT1PPSbits.INT1PPS =PORTEbits.RE2;
  
  
  //GPIO IOC = interrupter on changed 
  IOCCNbits.IOCCN4 = 1; //Negative Edge 
  IOCCNbits.IOCCN5 = 1;
  
  GIE =1;
  
 }