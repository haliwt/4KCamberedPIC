#ifndef __GE_H
#define __GE_H
#include <stdint.h>
#include <xc.h>



#define _XTAL_FREQ  8000000


#define	SetBit(x,y)	((x) |= (1 << (y)))				// set   1
#define	ClrBit(x,y)	((x) &= ~ (1 << (y)))			// clear 0

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
    uint8_t gMotorDir;
    uint8_t gPositionUp;
    uint8_t gPositionDown;
    uint8_t gCountUp;
    uint8_t gCountDown;
    uint8_t gUnibolar_flag;
    
}varref;

varref variate;
enum item
{
    Nothing,
    unibolar_CW,
    unibolar_CCW,
    motorStop,
    bibolar_UP,
    bibolar_DOWN

};
uint8_t RunStep;
uint8_t RunMode_Rail;
uint8_t RunMode_Disk;
uint8_t lastMode;
uint8_t Mode;
uint8_t TKeyUnibolar;
uint8_t TKeyBibolar;

typedef signed char int8_t;
void  delay_10us(uint16_t n);
void SysModeRail(uint8_t vlu);
void SysModeDisk(uint8_t vlu);
void CheckRunDisk(void);
void CheckRunRail();








#endif 