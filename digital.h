#ifndef __DIGITAL_H
#define __DIGITAL_H
#include "ge.h"


/**************************************************
	*XinTong LED Display Data Data:2020.07.23

	    //                a
        //            ---------
        //           |         |
        //         f |         | b
        //           |    g    |
        //            ---------
        //           |         |
        //         e |         | c
        //           |    d    |
        //            ---------   O <- h
**************************************************/
//偶数地址，SEG1~SEG8
#define   seg_a  0x01       //seg_a   //seg_e = 0x10  
#define   seg_b  0x02      //seg_b , //seg_f = 0x20
#define   seg_c  0x04      //seg_c , //seg_g = 0x40
#define   seg_d  0x08      //seg_d , //seg_d = 0x08
#define   seg_e  0x10      //seg_e , //seg_c = 0x04
#define   seg_f  0x20      //seg_f   //seg_a = 0x01
#define   seg_g  0x40      //seg_g   //seg_b = 0x02 
#define   seg_h  0x80      //Dot 

/*************High byte*******************/
//奇数地址，SEG9~SEG12
#define   seg_i 0x01       //地址不一样 奇数地址
#define   seg_j 0x02
#define   seg_k 0x04
#define   seg_l 0x08 

#define char_H     seg_b+seg_c+seg_e+seg_f+seg_g      //char "H"	

#define PM_DISP    seg_h    //PM_disp
#define PM_M       seg_i


#define	Set(x,y)	((x) |= (1 << (y)))				//位置1

extern uint8_t pmlog ;

void Digital_Init(void);
//const unsigned char GreeNumber[];

//const unsigned char BlueNumber[];


//extern const unsigned char segNumber[];
        

  


#endif 