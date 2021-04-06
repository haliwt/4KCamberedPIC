#include "sensor.h"
#include <xc.h>

/***********************************************************
    *
    *Function Name:void SENSOR_Init(void)
    *Function :sensor gpio initial 
    *Input Ref:NO
    *Return Ref:NO
    *
***********************************************************/
void SENSOR_Init(void)
{
  ANSELCbits.ANSELC3 = 0 ; //digital IO   
  TRISCbits.TRISC3 = 0;  //output  POWER EN_2 FOR J8 
  
  ANSELEbits.ANSELE0 = 0; //POWER 
  TRISEbits.TRISE0 = 0 ;  //control power EN_1 FOR J11

  //io input signal 
  
  //ANSELEbits.ANSELE1 = 0;
  //TRISEbits.TRISE1 = 1 ; //INPUT IO J11 

  ///ANSELEbits.ANSELE2 = 0;
  //TRISEbits.TRISE2 = 1;  //input signal J8

  ANSELCbits.ANSELC4 = 1;  //J11 --Analog
  TRISCbits.TRISC4 = 1 ; //INPUT IO J11 

  ANSELCbits.ANSELC5 = 1;  //J8
  TRISCbits.TRISC5 = 1 ; //INPUT IO J11 

  IOCCPbits.IOCCP5 = 0; //Position  Edge interrupt on changed
  IOCCPbits.IOCCP4 = 0; //Position  Edge


   //GPIO PORTE don't interrupt function PIN
}
/***********************************************************
    *
    *Function Name:void ADCC_Initialize(void)
    *Function :
    *Input Ref:NO
    *Return Ref:NO
    *
***********************************************************/
void ADCC_Initialize(void)
{
    // set the ADCC to the options selected in the User Interface
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL VSS; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS ADFLTR; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADAOV ACC or ADERR not Overflowed; 
    ADSTAT = 0x00;
    // ADCS FOSC/8; 
    ADCLK = 0x03;
    // ADNREF VSS; ADPREF VDD; 
    ADREF = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPRE = 0x00;
    // ADACQ 0; 
    ADACQ = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADLTHL 0; 
    ADLTHL = 0x00;
    // ADLTHH 0; 
    ADLTHH = 0x00;
    // ADUTHL 0; 
    ADUTHL = 0x00;
    // ADUTHH 0; 
    ADUTHH = 0x00;
    // ADSTPTL 0; 
    ADSTPTL = 0x00;
    // ADSTPTH 0; 
    ADSTPTH = 0x00;
    
    // ADGO stop; ADFM right; ADON enabled; ADCONT disabled; ADCS FOSC/ADCLK; 
    ADCON0 = 0x84;
    

}
/***********************************************************
    *
    *Function Name:void ADCC_Initialize(void)
    *Function :
    *Input Ref:NO
    *Return Ref:NO
    *
***********************************************************/
uint16_t ADCC_GetConversion(adcc_channel_t channel){
    return ADCC_GetSingleConversion(channel, 0);
}

void ADCC_SelectChannel(adcc_channel_t channel, uint8_t acquisitionDelay)
{
    // select the A/D channel
    ADPCH = channel;  
    //Set the Acquisition Delay
    ADACQ = acquisitionDelay;
  
    // Turn on the ADC module
    ADCON0bits.ADON = 1;
}

void ADCC_StartConversion()
{
    // Start the conversion
    ADCON0bits.ADGO = 1;
}

uint8_t ADCC_IsConversionDone()
{
    // Start the conversion
    return (!ADCON0bits.ADGO);
}

adc_result_t ADCC_GetConversionResult(void)
{
    // Return the result
    return ((ADRESH << 8) + ADRESL);
}
/*********************************************************************************************
    *
    *Function Name:adc_result_t 
               ADCC_GetSingleConversion(adcc_channel_t channel, uint8_t acquisitionDelay)
    *Function :ADC changed 
    *Input Ref:input ADC channel 
    *Return Ref: ADC be changed value
    *
***********************************************************************************************/
adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel, uint8_t acquisitionDelay)
{
    // select the A/D channel
    ADPCH = channel;  

    //Set the Acquisition Delay
    ADACQ = acquisitionDelay;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
	
    //Disable the continuous mode.
    ADCON0bits.ADCONT = 0;    

    // Start the conversion
    ADCON0bits.ADGO = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.ADGO)
    {
    }

    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}
/***********************************************************
    *
    *Function Name:void ADCC_Initialize(void)
    *Function :
    *Input Ref:NO
    *Return Ref:NO
    *
***********************************************************/
void ADCC_StopConversion(void)
{
    //Reset the ADGO bit.
    ADCON0bits.ADGO = 0;
}

void ADCC_SetStopOnInterrupt(void)
{
    //Set the ADSOI bit.
    ADCON3bits.ADSOI = 1;
}

void ADCC_DischargeSampleCapacitor(void)
{
    //Set the ADC channel to AVss.
    ADPCH = 0x3C;   
}

void ADCC_LoadAcquisitionRegister(uint8_t acquisitionValue)
{
    //Load the ADACQ register.
    ADACQ = acquisitionValue;   
}

void ADCC_SetPrechargeTime(uint8_t prechargeTime)
{
    //Load the ADPRE register.
    ADPRE = prechargeTime;  
}

void ADCC_SetRepeatCount(uint8_t repeatCount)
{
    //Load the ADRPT register.
    ADRPT = repeatCount;   
}

uint8_t ADCC_GetCurrentCountofConversions(void)
{
    //Return the contents of ADCNT register
    return ADCNT;
}

void ADCC_ClearAccumulator(void)
{
    //Reset the ADCON2bits.ADACLR bit.
    ADCON2bits.ADACLR = 1;
}

uint16_t ADCC_GetAccumulatorValue(void)
{
    //Return the contents of ADACCH and ADACCL registers
    return ((ADACCH << 8) + ADACCL);
}

uint8_t ADCC_HasAccumulatorOverflowed(void)
{
    //Return the status of ADSTATbits.ADAOV
    return ADSTATbits.ADAOV;
}

uint16_t ADCC_GetFilterValue(void)
{
    //Return the contents of ADFLTRH and ADFLTRL registers
    return ((ADFLTRH << 8) + ADFLTRL);
}

uint16_t ADCC_GetPreviousResult(void)
{
    //Return the contents of ADPREVH and ADPREVL registers
    return ((ADPREVH << 8) + ADPREVL);
}

void ADCC_DefineSetPoint(uint16_t setPoint)
{
    //Sets the ADSTPTH and ADSTPTL registers
    ADSTPTH = setPoint >> 8;
    ADSTPTL = setPoint;
}

void ADCC_SetUpperThreshold(uint16_t upperThreshold)
{
    //Sets the ADUTHH and ADUTHL registers
    ADUTHH = upperThreshold >> 8;
    ADUTHL = upperThreshold;
}

void ADCC_SetLowerThreshold(uint16_t lowerThreshold)
{
    //Sets the ADLTHH and ADLTHL registers
    ADLTHH = lowerThreshold >> 8;
    ADLTHL = lowerThreshold;
}

uint16_t ADCC_GetErrorCalculation(void)
{
	//Return the contents of ADERRH and ADERRL registers
	return ((ADERRH << 8) + ADERRL);
}

void ADCC_EnableDoubleSampling(void)
{
    //Sets the ADCON1bits.ADDSEN
    ADCON1bits.ADDSEN = 1;
}

void ADCC_EnableContinuousConversion(void)
{
    //Sets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 1;
}

void ADCC_DisableContinuousConversion(void)
{
    //Resets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 0;
}

//bool ADCC_HasErrorCrossedUpperThreshold(void)
//{
    //Returns the value of ADSTATbits.ADUTHR bit.
  //  return ADSTATbits.ADUTHR;
//}

//bool ADCC_HasErrorCrossedLowerThreshold(void)
//{
    //Returns the value of ADSTATbits.ADLTHR bit.
    //return ADSTATbits.ADLTHR;
//}

uint8_t ADCC_GetConversionStageStatus(void)
{
    //Returns the contents of ADSTATbits.ADSTAT field.
    return ADSTATbits.ADSTAT;
}