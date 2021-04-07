#ifndef _USART_H
#define _USART_H
#include "ge.h"

#define RXD1 PORTCbits.RC7
#define TXD1 PORTCbits.RC6

void SerialPORT_Init(void);
void USART_BlueToothInit(void);

void USART1_Init(void);
void send232byte(uint8_t bytebuf);

#endif 