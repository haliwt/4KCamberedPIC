#ifndef __SENSOR_H
#define __SENSOR_H
#include "ge.h"



#define SENSOR_POWER_DOWN       PORTEbits.RE0 //PORTCbits.RC3  //J11
#define SENSOR_POWER_UP         PORTCbits.RC3   //J8

//#define SENSOR_SIG_1           PORTCbits.RC4   //J11
//#define SENSOR_SIG_2           PORTCbits.RC5   //J8

#define SENSOR_SIG_UP         PORTCbits.RC4  // PORTEbits.RE1  //J11
#define SENSOR_SIG_DWON       PORTCbits.RC5 // PORTEbits.RE2  //J8


typedef uint16_t adc_result_t;

typedef enum
{
    POT_CHANNEL =  0x0,
    channel_ANC4 = 0x14,
    channel_ANC5=  0x15,
    channel_VSS =  0x3C,
    channel_Temp =  0x3D,
    channel_DAC1 =  0x3E,
    channel_FVR_buf1 =  0x3F
} adcc_channel_t;


void SENSOR_Init(void);
void ADCC_Initialize(void);
void ADCC_SelectChannel(adcc_channel_t channel, uint8_t acquisitionDelay);
adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel, uint8_t acquisitionDelay);

#endif 