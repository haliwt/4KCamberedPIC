#include <xc.h>
#include "key.h"

/****************************************************************************
    *
    * Function Name: void KEY_Init(void)
    * Function :KEY inital
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void KEY_Init(void)
{
    ANSELBbits.ANSELB1=0;  //digital IO
    ANSELBbits.ANSELB2=0; 
    ANSELBbits.ANSELB3=0; 
    ANSELBbits.ANSELB4=0; 
    ANSELBbits.ANSELB5=0; 
    
    TRISBbits.TRISB1 = 1;    //input GPIO 
    TRISBbits.TRISB2 = 1;    //input GPIO 
    TRISBbits.TRISB3 = 1;    //input GPIO 
    TRISBbits.TRISB4 = 1;    //input GPIO 
    TRISBbits.TRISB5 = 1;    //input GPIO  
    

}
/****************************************************************************
    *
    * Function Name: void UNIPOLAR_MOTOR_Init(void)
    * Function :Initial motor for GPIO 
    * Input Ref:NO
    * Return Ref: key value
    * 
 ****************************************************************************/
uint8_t KEY_Scan(void)
{
    uint8_t reval =0;
    key.read = _KEY_ALL_OFF; //0x1f
    
    if(CW_KEY ==1){
        key.read &= ~0x01; // 0x1E
    }
    if(CCW_KEY ==1){
        key.read &= ~0x02 ; // 0x1D
    }
    if(SPEED_KEY ==1){
        key.read &= ~0x04; // 0x1B
    }
    if(UP_KEY ==1){
        key.read &= ~0x08 ; //0x17
    }
    if(DOWN_KEY==1){
        key.read &= ~0x09; //0x0F
    }
    switch(key.state){
        
        case start:
           if(key.read !=_KEY_ALL_OFF){
                key.buffer  =key.read;
                key.state = first;
                key.on_time = 0;
                key.off_time =0;
            
            }
            break;
        
        case first:
            if(key.read == key.buffer){
                if(++key.on_time >10) //??
                {
                    key.value = key.buffer ^ _KEY_ALL_OFF;//???????
                    key.on_time =0;
                    key.state= second;
                }
            }
            else{
                key.state = start;
            
            }
        break;
        
        case second:
            if(key.read == key.buffer) //??????????
            {
                if(++key.on_time >300) //???
                {
                  key.value  = key.value | 0x80;
                  key.on_time =0;
                  key.state = finish;
                }
            
            }
            else if(key.read == _KEY_ALL_OFF)//????
            {
                if(++key.off_time>5)
                {
                    key.value = key.buffer ^_KEY_ALL_OFF;
                    key.state = finish;
                }
            }
        break;
        
        case finish:
            reval = key.value ;//??? ?1.????  2. ??????????
            key.state = end;
        break;
        
        case end:
            if(key.read == _KEY_ALL_OFF){
                if(++key.off_time >10){
                    key.state = start;
                }
            }
        break;
        default :
            key.state = start;
            break;
    
   }
  return reval ;

}

