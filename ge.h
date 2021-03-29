#ifndef __GE_H
#define __GE_H
#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ  8000000


#define	Set(x,y)	((x) |= (1 << (y)))				//??1
#define	Clr(x,y)	((x) &= ~ (1 << (y)))			//??0

#define	bit0(x,y)		(((x) & (1 << (y))) == 0)		//?0?? if(b0(x,y)) ?????0
#define	bit1(x,y)		((x) & (1 << (y)))				//?1?? if(b1(x,y)) ?????1

#define uchar	unsigned char
#define uint	unsigned int
#define ulong	unsigned long


typedef signed char int8_t;
typedef signed short int16_t;






#endif 