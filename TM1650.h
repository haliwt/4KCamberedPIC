#ifndef __TM1650_H
#define __TM1650_H
#include "ge.h"
#include "digital.h"


#define SCL 	PORTDbits.RD5
#define SDA     PORTDbits.RD6
#define SET_SDA_OUT_TM1650()       (ANSELDbits.ANSELD6=0,TRISDbits.TRISD6=0)
#define SET_SDA_IN_TM1650() 	   (ANSELDbits.ANSELD6=0,TRISDbits.TRISD6=1)
/*---向TM1650显示 写指令*/
#define  TM1650_ORDER      0x48        //数字指令 写数据




void IIC_Init_TM1650(void);
void IIC_Start_TM1650(void);
void IIC_Stop_TM1650(void);
void IIC_Ack_TM1650(void);
void IIC_NAck_TM1650(void);
uint8_t IIC_Wait_Ack_TM1650(void);
void IIC_WrByte_TM1650(uint8_t number);
void TM1650_Set(uint8_t add,uint8_t dat) ;
void Init_Tm1650(void);
void  delay_us(uint16_t n);

void Digital_NumberInit(void);




#endif 