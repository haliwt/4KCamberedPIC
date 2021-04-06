#ifndef _USART_H
#define _USART_H
#include "ge.h"

void SerialPORT_Init(void);
void USART_BlueToothInit(void);

void USART1_Init(void);
void send232byte(uint8_t bytebuf);

#endif 