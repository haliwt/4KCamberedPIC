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
    ANSELCbits.ANSELC6 =0;
    ANSELCbits.ANSELC7 =0;
    TRISCbits.TRISC6= 1; //
    TRISCbits.TRISC7 =1; //RX1

    PORTCbits.RC7 = RX1PPSbits.PORT;
    PORTCbits.RC6 = TX1PPSbits.PORT;
    //RX1PPS = RC7;
    //TX1PPS = RC6;
    RC1STAbits.SPEN=1;       // 串口使能位
    RC1STAbits.CREN =1;     // 1=允许连续接收 0=禁止连续接收
    TX1STAbits.TXEN =1;    // TXEN = 1;   // 发送允许
    
    TX1STAbits.TX9=0;// TX9 = 0;    // 1：选择9位接收 0：选择8位接收
    RC1STAbits.RX9=0 ; // RX9 = 0;    // 1：选择9位接收 0：选择8位接收
   
    TX1STAbits.TRMT = 0;
    RC1STAbits.FERR =0;   
    RC1STAbits.OERR =0;

    // 波特率 = FOSC/[64 (n + 1)] = 8000000/(64*(0+1)) = 115200
   

    TX1STAbits.SYNC = 0; // SYNC=0 BRGH16=0 BRGH=0 ，FOSC/[64 (n + 1)]
    BAUD1CONbits.BRG16= 0;
    TX1STAbits.BRGH = 0;
    SP1BRG = 51;
}

void USART2_Init(void)
{

    ANSELCbits.ANSELC6 = 0;
    ANSELCbits.ANSELC7 = 0;
    TRISCbits.TRISC6 = 1; //
    TRISCbits.TRISC7 = 1; //RX1

    PORTCbits.RC7 = RX1PPSbits.PORT;
    PORTCbits.RC6 = TX1PPSbits.PORT;

    //Data be send TXD
    TX1STAbits.SYNC = 0;  //Asynchronous Mode
    TX1STAbits.CSRC = 0;  // clock source select bit
    TX1STAbits.TX9 = 0;   //selects 8-bit transmission
    TX1STAbits.TXEN = 1;  //Transmit Enable bit
  
    TX1STAbits.SENDB = 0; //Send break character bit
    TX1STAbits.TRMT = 0;  //Transmit shift register(TSR)status bit
    TX1STAbits.TX9D = 0;  //can be address/data bit or a parity bit

    //Data receive RXD
    RC1STAbits.RX9 = 0;  //8 bit reception enable
    RC1STAbits.SREN = 1; //Single Receive Enable bit
    RC1STAbits.CREN = 1; //continuous Receive Enable bit

    RC1STAbits.ADDEN = 0; //Address Detect Enable bit
    RC1STAbits.FERR = 0;  // Framing Error bit-??? ,unread RCxREG - receive data register
    RC1STAbits.OERR = 0;  //nothing overflow error
    RC1STAbits.RX9D = 0;  //ninth bit received data

    TX1STAbits.BRGH = 1;    // high baud rate select bit
    BAUD1CONbits.BRG16 = 0; //16 bit baud rate generator select bit 0 is 8 bit

    SPBRG = 51; //baud rate is 9600bps
    TX1REG = 0x05;
}

