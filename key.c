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
    TRISBbits.TRISB3 = 1;    //input GPIO  SPPEED 
    TRISBbits.TRISB4 = 1;    //input GPIO 
    TRISBbits.TRISB5 = 1;    //input GPIO 

    //GPIO IOC = interrupter on changed 
   // IOCBPbits.IOCBP3 = 1; //Position  Edge 
    
    PIE0bits.IOCIE =1 ;//interrupt-on-change enable
   // PIR0bits.IOCIF =0 ;
  //  IOCBFbits.IOCBF3=0;
   
     INT2IE=1; 
     INT2EDG =0;
     INT2IF = 0;
    
    
    //INTEDG0=0;               //设置下降沿触发中断	                
  	INT2IE=1;  	            //使能外部中断
  	GIE=1;                  //开放全局中断
   
    
    

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
    static uint16_t  k1=0 ;
    static uint16_t  k2=0 ;
    static uint16_t  k3=0 ;
    static uint16_t  k4=0 ;
    static uint16_t  k5=0 ;
    uint8_t cnt;
    
    
    if(CW_KEY ==1 ){
        if(k1<200)
        k1++;   
    }
    else {  
      k1=0;  
    }
    
    if(CCW_KEY ==1){
       if(k2<200)
        k2++; 
       
    }
    else{
        
        k2=0; 
    }  
    
    if(SPEED_KEY ==1){
       if(k3<200)
        k3++; 
       
    }
    else{
        
        k3=0; 
    } 
    
    if(UP_KEY ==1){
       if(k4<200)
        k4++; 
       
    }
    else{
        
        k4=0; 
    }  
    
    if(DOWN_KEY ==1){
       if(k5<200)
        k5++; 
       
    }
    else{
        
        k5=0; 
    } 
    
    cnt =0;
    if(k1>190){
       cnt= 0x1  ;  
    } 
    if(k2>190){
        cnt= 0x2  ;  
    }
    if(k3>190){
        cnt= 0x4  ;  
    }
    if(k4>190){
        cnt= 0x8  ;  
    }
    if(k5>190){
        cnt= 0x9  ;  
    }
    return cnt ;
    
}
   
    



