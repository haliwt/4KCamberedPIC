#include "unipolar.h"
#include <xc.h>
#include "ge.h"

const float Step_angle = 0.0882     ;  //step angle 
const uint16_t RPM =500;
int16_t Step_Count = 4082; //360/0.0882 ; revoulation one circle 
int16_t Delay = 29;//us   // Step_angle /(6 * RPM)= 0.0882/;  


/****************************************************************************
    *
    * Function Name: void UNIPOLAR_MOTOR_Init(void)
    * Function :Initial motor for GPIO 
    * Input Ref:NO
    * Return Ref:NO
    * 
 ****************************************************************************/
void UNIPOLAR_MOTOR_Init(void)
{
   ANSELDbits.ANSELD0 = 0; //digital GPIO don't analog
   TRISDbits.TRISD0 = 0;   //output 
   ANSELDbits.ANSELD1 = 0;
   TRISDbits.TRISD1 = 0;
   
   ANSELDbits.ANSELD2 = 0; //SETP_INPUT_PWM
   TRISDbits.TRISD2 = 0;
   ANSELDbits.ANSELD3 = 0;
   TRISDbits.TRISD3 = 0;
   ANSELDbits.ANSELD4 = 0;
   TRISDbits.TRISD4 = 0;
}
/****************************************************************************
    *
    * Function Name: void Stepper_Motor(int8_t revcnt, uint8_t revdir,uint8_t gapdly)
    * Function :unipolar run function
    * Input Ref:revcnt -motor revolution number
    *            Delay(T)= Step_angle/(6*RPM),RPM revolution per minute
    * Return Ref:NO
    * 
 ****************************************************************************/
void Stepper_Motor(int revcnt, uint8_t revdir,uint8_t gapdly)
{
    int k,p;
    if(revcnt <0){
        DIRECTION  = revdir;
        while(1){
            STEP =1;
            STEP = 0;
            __delay_ms(Delay);
        }
    }
    else{
        p=revcnt* Step_Count; //Step_Count = 360/Step_angle 
        DIRECTION  = revdir;
        for(k=0;k<gapdly;k++){
            STEP =1;
            STEP =0;
            __delay_ms(Delay);
        }
        for(k=0;k<gapdly;k++)
            __delay_ms(1);
    }

}