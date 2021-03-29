#include "usart.h"
#include <xc.h>
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
    
    ANSELCbits.ANSELC1 = 0 ; //I/O is digital RC1
    ANSELCbits.ANSELC2 = 0 ; // RXD is digital RC2
    TRISCbits.TRISC1 = 0; // output IO
    TRISCbits.TRISC2 =1; // input IO
    RC1PPS = 0x0B;  // RC1 as EUSART2 TX/CK
    RC2PPS=0x0A;//RC2 as EUSART2 RD
    
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
    ANSELCbits.ANSELC6 =0;
    ANSELCbits.ANSELC7 =0;
    TRISCbits.TRISC6= 1; //??C???????
    TRISCbits.TRISC7 =0; //
    
    TX2STAbits.BRGH=1 ; // high baud rate select bit
    BAUD2CONbits.BRG16=0;  //16 bit baud rate generator select bit 0 is 8 bit
  
    SPBRG = 0x17;  //baud rate is 9600bps
    
    TX1STA=0X24; //??????????????
    RC1STA=0X90; //???????????
    PIE3bits.RC1IE=1; //EUSARTx receive interrupt enable bit 
    INTCONbits.GIE=1; //global interrupt enable bit
    INTCONbits.PEIE = 1; //

}