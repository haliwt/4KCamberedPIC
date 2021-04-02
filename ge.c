#include "ge.h"
#include "unipolar.h"
#include "bipolar.h"
#include "key.h"
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times T= 1/8mhz = 0.125uS
    *Input Ref:
    *Return Ref:
    *
*******************************************************************/
void  delay_us(uint16_t n)
{
    uint16_t i,j=0;
    for(j=0;j<n;j++){
        for(i=0;i<8;i++){
            asm("nop");
        }
    }
    
}

void SysMode(uint8_t TKey)
{
    switch(TKey){
            case _KEY_TRG_1_CW :
                
                
                 variate.majorMode = uniboplar_CW;
                  
            break;
                 
            case _KEY_TRG_2_CCW:
               
                 variate.majorMode = uniboplar_CCW;
                
                 break;
            case _KEY_TRG_3_SPEED:
                

                 variate.majorMode = motorStop;
                 
            break;
            
            case _KEY_TRG_4_UP:
                variate.majorMode = biboplar_UP ; 
            break;
                 
            case _KEY_TRG_5_DOWN:
                variate.majorMode = bibolar_DOWN;
               
            break;
            default:
                variate.gSpeed_Keyflag =0;
              
            break;
        }

}

/******************************************************************
    *
    *Function Name:void CheckRun(void)
    *Function :run mode hold process
    *Input Ref:NO
    *Return Ref:NO
    *
*******************************************************************/
void CheckRun(void)
{

    switch(variate.majorMode){

       case Nothing:
            Unipolar_StopMotor();
            DRV8818_Stop();

       break;

       case  uniboplar_CW :
             
            Stepper_UnipolarMotor(1,0);

       break;

       case uniboplar_CCW :
                Stepper_UnipolarMotor(1,1);
       break;

       case motorStop:
           Unipolar_StopMotor();
       break;

       case  biboplar_UP:
            DRV8818_MotorDriver(1);

       case bibolar_DOWN:
           DRV8818_MotorDriver(0);

       break;

       default:
         

       break;



    }


}