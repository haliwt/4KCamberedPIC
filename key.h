#ifndef _KEY_H_
#define _KEY_H_
#include "ge.h"


#define CW_KEY          PORTBbits.RB1
#define CCW_KEY         PORTBbits.RB2
#define SPEED_KEY       PORTBbits.RB3
#define DOWN_KEY        PORTBbits.RB4
#define UP_KEY          PORTBbits.RB5

#define _KEY_ALL_OFF    0x1F 

//definition KEY of value
#define _KEY_TRG_1_CW       0x01  // clockwise
#define _KEY_TRG_2_CCW      0x02  // anti-clockwise
#define _KEY_TRG_3_SPEED    0x04  // SPEED
#define _KEY_TRG_4_UP       0x08  //UP
#define _KEY_TRG_5_DOWN     0x09  //Down

//definition KEY of long press key value
#define _KEY_CONT_1_CW          0x81    //long press key of value clockwise
#define _KEY_CONT_2_CCW         0x82
#define _KEY_CONT_3_SPEED       0x84
#define _KEY_CONT_4_UP          0x88
#define _KEY_CONT_5_DOWN        0x89




typedef struct _state_
{
    uint8_t state;
    uint8_t read;
    uint8_t buffer;
    uint8_t value;
    uint16_t on_time;
    uint16_t off_time;
    
}key_types;


key_types key;
enum keystate{start = 0,first =1,second =2,cont =3,end = 4,finish =5  };


void KEY_Init(void);
uint8_t KEY_Scan(void);




#endif