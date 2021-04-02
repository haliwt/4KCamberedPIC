#include "unipolar.h"


const float Step_angle = 0.08822   ;  //step angle =15 ,reduction rate 1:85 -> stepAngle =7.5/85=0.0882
const uint16_t RPM =500;//500 RPM
int16_t Step_Count = 4080; //360/7.5/85 ; revoulation one circle 
int16_t Delay = 1;//10; //0.0294ms;//  //delay(ms)=(Step_angle) /(6 * RPM)= 0.0882*1000/(6*500);  


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
    * Input Ref:revcnt -motor revolution number,revdir =0 CCW revdir =1 CW
    *            Delay(T)= Step_angle/(6*RPM),RPM revolution per minute
    *            Subdiv= 8;
    * Return Ref:NO
    * 
 ****************************************************************************/
void Stepper_UnipolarMotor(int revcnt, uint8_t revdir)
{
    uint16_t k,p;
    
    UNIPOLAR_ON = 0;
    ONE_PHASE=0;   //PIN9 - half phase 
    HALF_PHASE =1;  //PIN10 =0 8 step 
  
    if(revcnt <0){
        DIRECTION  = revdir;
        while(1){
            STEP =1;
            __delay_ms(Delay);
            STEP = 0;
            __delay_ms(Delay);
        }
    }
    else{
        p=(uint16_t)(revcnt* Step_Count) ; //Step_Count = 360/Step_angle 
        DIRECTION  = revdir;
        for(k=0;k<p;k++){
            STEP =1;
            __delay_ms(Delay);
            STEP =0;
            __delay_ms(Delay);
            stop_uni =1;
        }
        for(k=0;k<variate.gSpeedcnt;k++)
            __delay_ms(1);
        if(stop_uni == 1){
             stop_uni = 0;
             UNIPOLAR_ON = 1;
             HALF_PHASE = 1;
             ONE_PHASE =1;

        }
    }

}
/****************************************************************************
    *
    * Function Name: void Unipolar_StopMotor()
    * Function :unipolar run function
    * Input Ref:NO           
    * Return Ref:NO
    * 
 ****************************************************************************/
 void Unipolar_StopMotor(void)
 {
     UNIPOLAR_ON = 1;
     HALF_PHASE = 1;
     ONE_PHASE =1;
 
 }