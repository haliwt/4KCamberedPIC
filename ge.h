#ifndef __GE_H
#define __GE_H
#include <stdint.h>
#include <xc.h>



#define _XTAL_FREQ  8000000


#define	Set(x,y)	((x) |= (1 << (y)))				//??1
#define	Clr(x,y)	((x) &= ~ (1 << (y)))			//??0

#define	bit0(x,y)		(((x) & (1 << (y))) == 0)		//?0?? if(b0(x,y)) ?????0
#define	bit1(x,y)		((x) & (1 << (y)))				//?1?? if(b1(x,y)) ?????1

typedef struct _varref_
{
    uint8_t gunipolar_en;
    uint8_t gbipolar_en;
    uint8_t getTime_10ms;
    uint8_t getTime_100ms;
    uint8_t getTime_1s;
    uint8_t gstep_to_index;
    uint8_t gSpeed_Keyflag;
    uint8_t gSpeedcnt;
    uint16_t getDutyCycle;
}varref;

varref variate;

typedef signed char int8_t;








#endif 