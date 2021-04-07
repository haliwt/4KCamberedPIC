#include "usart.h"

/****************************************************************************
    * 
    * Function Name:void SerialPORT_Init(void)
    * Function:serial uusart printf TX2
    * Input Ref:NO
    * Return Ref:NO
    * 
 * *************************************************************************/
void SerialPORT_Init(void)
{
    
    ANSELCbits.ANSELC1 = 0 ; //I/O is digital RC1 TX
    ANSELCbits.ANSELC2 = 0 ; // RXD is digital RC2
    TRISCbits.TRISC1 = 0; // output IO
    TRISCbits.TRISC2 =1; // input IO
    RC1PPS = TX1REG;//0x0B;  // RC1 as EUSART2 TX/CK output 
    RC2PPS= 0x0B;//RC2 as input
    
    //Data be send TXD
    SYNC1 =0; //Asynchronous 
    TX2STAbits.CSRC =1 ; // clock source select bit 
    TX2STAbits.TX9 = 0;  //selects 8-bit transmission
    TX2STAbits.TXEN = 1;  //Transmit Enable bit
    TX2STAbits.SYNC = 0;  //Asynchronous mode 
    TX2STAbits.SENDB = 0;  //Send break character bit 
    TX2STAbits.TRMT = 0;  //Transmit shift register(TSR)status bit
    TX2STAbits.TX9D = 0;  //can be address/data bit or a parity bit 
    
    TX2STAbits.BRGH=1 ; // high baud rate select bit
    BAUD2CONbits.BRG16=0;  //16 bit baud rate generator select bit 0 is 8 bit
  
    SPBRG = 0x17;  //baud rate is 9600bps
    
    //Data receive RXD
    RC2STAbits.SPEN =1 ;  //Open serial port,Serial Port Enable
    RC2STAbits.RX9 = 0 ; //8 bit reception enable
    RC2STAbits.SREN =1;   //Single Receive Enable bit 
    RC2STAbits.CREN =1;   //continuous Receive Enable bit
   
    RC2STAbits.ADDEN =1;   //Address Detect Enable bit 
    RC2STAbits.FERR =1;   // Framing Error bit-??? ,unread RCxREG - receive data register 
    RC2STAbits.OERR =0;   //nothing overflow error 
    RC2STAbits.RX9D=0;   //ninth bit received data
    TX2REG = 0x00;

}
/****************************************************************************
    * 
    * Function Name:void USART_BlueToothInit(void)
    * Function:bluetooth uusart communication TX1 
    * Input Ref:NO
    * Return Ref:NO
    * 
 * *************************************************************************/
void USART_BlueToothInit(void)
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

/****************************************************************************
    * 
    * Function Name:void USART_BlueToothInit(void)
    * Function:bluetooth uusart communication TX1 
    * Input Ref:NO
    * Return Ref:NO
    * 
 * *************************************************************************/
void send232byte(uint8_t bytebuf)
{
    TX1REG = bytebuf;
    while (TX1STAbits.TRMT == 0);
}