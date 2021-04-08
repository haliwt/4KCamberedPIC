#include "usart.h"

/****************************************************************************
    * 
    * Function Name:void SerialPORT_Init(void)
    * Function:serial uusart printf TX2
    * Input Ref:NO
    * Return Ref:NO
    * 
 * *************************************************************************/
void USART1_Init(void)
{

    ANSELCbits.ANSELC6 = 0;
    ANSELCbits.ANSELC7 = 0;
    TRISCbits.TRISC6 = 1;//0; //
    TRISCbits.TRISC7 = 1; //RX1

    //RX1PPSbits.RXPPS  = PORTCbits.RC7;
    //TX1PPSbits.TXPPS  = PORTCbits.RC6;
  // RX1PPSbits.RXPPS = RC7PPS;
  // TX1PPSbits.TXPPS=RC6PPS;
    RC7PPS = RX1PPSbits.RXPPS ;//RX1PPSbits.RXPPS = PORTCbits.RC7 ;
    RC6PPS = 0x09;

    /*串口初始化*/
   // SPBRGH=0;
   // SPBRGL = 51; //9600
    
    TX1STAbits.TX9 = 0;  //selects 8-bit transmission
  

    TX1STAbits.SYNC = 0;
    

    TX1STAbits.TXEN = 1;

     //Data receive RXD
    RC1STAbits.SPEN = 1; //Total switch Enable
    RC1STAbits.RX9 = 0;  //0;  //The receive buffer is loaded and interrupt
    RC1STAbits.SREN = 1; //Single Receive Enable bit
    RC1STAbits.CREN = 1; //continuous Receive Enable bit
    RC1STAbits.ADDEN = 1;//0; //1
    /*串口初始化结束*/

  
    TX1STAbits.BRGH =   1;// 0;
    BAUD1CONbits.BRG16 = 0;//1; //??8??????
      SP1BRG =51;
    
 //   PIR3bits.TX1IF=0;
    PIR3bits.RC1IF=0;
    
   // PIE3bits.TX1IE =1;
    PIE3bits.RC1IE = 1; // 使能接收中断
    PEIE = 0X1; // 使能外部中断
    GIE = 0X1; // 开放全局中断

}

void send232byte(uint8_t bytebuf)
{
    TX1REG = bytebuf;
    while (TX1STAbits.TRMT == 0);
}