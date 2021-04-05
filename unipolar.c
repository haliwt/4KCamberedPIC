#include "unipolar.h"
#include "ge.h"
#include "key.h"


const float Step_angle = 0.08822   ;  //step angle =15 ,reduction rate 1:85 -> stepAngle =7.5/85=0.0882
const uint16_t RPM =500;//500 RPM
int16_t Step_Count = 4080; //360/7.5/85 ; revoulation one circle 
//10; //0.0294ms;//  //delay(ms)=(Step_angle) /(6 * RPM)= 0.0882*1000/(6*500);  


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
    uint16_t k,p,subdiv=8;
    
    UNIPOLAR_ON = 0;
    ONE_PHASE=0;   //PIN9 - half phase 
    HALF_PHASE =1;  //PIN10 =0 8 step

    TKey = KEY_Scan();
    if(revcnt <0){
        DIRECTION  = revdir;
        while(1){
            STEP =1;
            delay_us(DelayStepUnibolar);
            STEP = 0;
            delay_us(DelayStepUnibolar);
           
        }
    }
    else{
        p=(uint16_t)(revcnt* Step_Count) ; //Step_Count = 360/Step_angle 
        DIRECTION  = revdir;
        for(k=0;k<p;k++){
             STEP =1;
           delay_us(DelayStepUnibolar);
            STEP =0;
            delay_us(DelayStepUnibolar);
           
        }
        
    }

}
/****************************************************************************
    *
    * Function Name: void Unipolar_StopMotor(void)
    * Function :unipolar run function  10us-max 1ms-mid 100us - slowly
    * Input Ref:NO           
    * Return Ref:NO
    * 
 ****************************************************************************/
 void Unipolar_StopMotor(void)
 {
     UNIPOLAR_ON = 1;
    // HALF_PHASE = 1;
    // ONE_PHASE =1;
 
 }
 /****************************************************************************
    *
    * Function Name: void StepUnibolar_Driver(void)
    * Function :unipolar run function  10us-fast-max 100us-mid 500us - slowly
    * Input Ref:NO           
    * Return Ref:NO
    * 
 ****************************************************************************/
 void StepUnibolar_Driver(void)
 {

     UNIPOLAR_ON = 0;
     ONE_PHASE = 0;  //PIN9 - half phase
     HALF_PHASE = 1; //PIN10 =0 8 step
     STEP = 1;
     delay_us(DelayStepUnibolar);//delay_us(500); //delay_us(10)//delay_us(100);//__delay_ms(Delay);
     STEP = 0;
     delay_us(DelayStepUnibolar); //delay_us(500) ;//delay_us(10)//delay_us(100);//__delay_ms(Delay);
 }