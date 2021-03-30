#include "TM1650.h"


/******************************************************************************
 ** 
 ** Function Name: void Digital_NumberInit(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void Digital_NumberInit(void)
{
    ANSELDbits.ANSELD5 = 0; //SCL
    TRISDbits.TRISD5= 0;  //OUTPUT
    
    ANSELDbits.ANSELD6 = 0; //SDA
    TRISDbits.TRISD5 =1 ; //INPUT
    SCL =1;
}

const unsigned char segNumber[]={
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f,        // char "0"  0x00
         seg_b+seg_c,                                // char "1"  0x01
         seg_a+seg_b+seg_d+seg_e+seg_g,              // char "2"  0x02
         seg_a+seg_b+seg_c+seg_d+seg_g,              // char "3"  0x03
         seg_b+seg_c+seg_f+seg_g,                    // char "4"  0x04
         seg_a+seg_c+seg_d+seg_f+seg_g,              // char "5"  0x05
         seg_a+seg_c+seg_d+seg_e+seg_f+seg_g,        // char "6"  0x06
         seg_a+seg_b+seg_c+seg_f,                    // char "7"  0x07
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_g,  // char "8"  0x08
         seg_a+seg_b+seg_c+seg_d+seg_f+seg_g,        // char "9"  0x09
         seg_h,                                      // char "."  0x0A
         0                                           // Dont't display
         
};

volatile uint8_t DispData[3];
/******************************************************************
    *
    *Function Name:void delay_us(uint16_t n)
    *Function :delay times
    *Input Ref:
    *Return Ref:
    *
*******************************************************************/
void  delay_us(uint16_t n)
{
  uint16_t i,j=0;
	for(i=0;i<n;i++){
		asm("nop");
	}
    
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_Start_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Start_TM1650(void)
{
	
	  // SDA 1->0 while SCL High
    //SCL??????SDA?????????????
    SET_SDA_OUT_TM1650();
    SDA = 1;      //???????????????????? 
    asm("nop"); 
    SCL = 1;        //???????            
      asm("nop"); ;//?????5us??????????    
      asm("nop"); ;
      asm("nop"); ;
      asm("nop"); ;        
     SDA = 0;        //??????????           
      asm("nop"); ;
      asm("nop"); ;
      asm("nop"); ;      //?? ????????????
      asm("nop"); ;             
    SCL = 0;        //??????????????????    
        
}

/******************************************************************************
 ** 
 ** Function Name: void I2C_Stop_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Stop_TM1650(void)
{

	// SDA 0->1 while SCL High
    //SCL??????SDA??????? ????
    SET_SDA_OUT_TM1650();
  SCL= 0;
    asm("nop"); 
      asm("nop"); 
      asm("nop"); 
      asm("nop"); 
    SDA = 0;    //?????????
   delay_us(2);
    SCL= 1;   //??????????
    delay_us(1);    //?? ????????????            
    SDA = 1;        //????????           
    delay_us(2);    //?? ??????????   
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_Ack_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Ack_TM1650(void)
{
 //????????????????????????
 
  SET_SDA_OUT_TM1650();
  delay_us(1);
    SDA = 0;
    delay_us(1);
    SCL= 0;
    delay_us(2);
  SCL = 1;
  delay_us(2);
    //????? ?????? ??????
    SCL = 0;
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_NAck_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_NAck_TM1650(void)
{
    //?????? ?????????????????
  SET_SDA_OUT_TM1650();
  delay_us(1);
    SDA = 1;
    delay_us(1);
  SCL= 0;
  delay_us(2);
    SCL = 1;
    delay_us(2);
    //????????? ??????
    SCL = 0;
}
/******************************************************************************
 ** 
 ** Function Name: IIC_Wait_Ack_TM1650(void)
 ** Function:   ??????    	
 ** Input Ref:
 ** Return Ref: 0:?? 1????
 **  
 ******************************************************************************/
uint8_t IIC_Wait_Ack_TM1650(void)
{
    //??????
    uint8_t ackTime = 0;
    //??????????????????????????????
  SCL = 0;
  SET_SDA_OUT_TM1650();
   asm("nop");  //delay_us(1);  
  SDA = 1;//
  asm("nop"); //delay_us(2);
  SET_SDA_IN_TM1650();//???????
  
    //?????
    SCL = 1;
    asm("nop"); //delay_us(2);
    asm("nop"); 
    //?????????
    while(SDA){
        //???????????
        ackTime ++;
        if(ackTime > 100)
        {
            //????? ????
            IIC_Stop_TM1650();
            return 1;
        }
    }
    SCL = 0;
    return 0 ;
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_WrByte_TM1650(uint8_t number)
 ** Function:     	
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void IIC_WrByte_TM1650(uint8_t oneByte)
{
    //????????
    uint8_t i;
    SCL =0;
    delay_us(1);
    SET_SDA_OUT_TM1650();
    //????????????
    //    SCL = 0;
    //??????
    for(i = 0;i < 8; i ++)
    {
    
    if((oneByte&0x80))            //????????
        SDA=1;
    else                     //  TM1650_DIO_L;
        SDA= 0;
          asm("nop"); 
        //delay_us(1);
        SCL=1;
        asm("nop"); //delay_us(1);
        SCL=0;//TM1650_CLK_L;
          asm("nop"); // delay_us(1);
        oneByte<<=1;        

    }
   //  delay_us(1);
}
/******************************************************************************
 ** 
 ** Function Name: void TM1650_Set(u8 add,u8 dat)
 ** Function:     ?????	
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void TM1650_Set(uint8_t add,uint8_t dat) 
{
	//????????????
	IIC_Start_TM1650();
    IIC_WrByte_TM1650(add); //???????
	IIC_Ack_TM1650();
	IIC_WrByte_TM1650(dat);
	IIC_Ack_TM1650();
	IIC_Stop_TM1650();
}

/******************************************************************************
 ** 
 ** Function Name: Init_Tm1650(void)
 ** Function:    
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void Init_Tm1650(void)
{
	//IIC_Init_TM1650();
	//delay_10us(10);			//???????????????????
	TM1650_Set(0x48,0x31);//????5???????

  #if 0
	TM1650_Set(0x68,segNumber[7]);//????5???????
   

	TM1650_Set(0x6A,segNumber[8]);//????5???????


  TM1650_Set(0x6C,segNumber[1]);//????5???????

	
   TM1650_Set(0x6E,segNumber[0]);//????5???????
    #endif 
	
}