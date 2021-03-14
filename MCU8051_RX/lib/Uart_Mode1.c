#include"main.h"
#include"Uart_Mode1.h"

#if(FREQ_OSC != 11059200)
    #error "Thu vien Uart_Mode1 chi ho tro tan so hoat dong la 11.0592 Mhz"
#endif

void UART_Init()
{
   // khoi tao UART Mode 1 , 9600 baud
   SM0 = 0; SM1 = 1; // UART mode1
   TMOD &= 0x0F;  // giu nguyen 4 bit sau
   TMOD |= 0x20;  // 0010xxxx - timer 1 hoat dong o che do 8 bit tu dong nap lai
   #if(BAUD_RATE == 9600)
   TH1 = 0xFD;   // toc do baud 9600
   #elif(BAUD_RATE == 2400)
   TH1 = 0xF4;	 // toc do baud 2400
   #elif(BAUD_RATE == 1200)
   TH1 = 0xE8;	 // toc do baud 1200
   #elif(BAUD_RATE == 19200)
      {  TH1 = 0xFD;	 // toc do baud 19200
	     PCON |= 0x80;
	  }
   #else
      #error "BAUD_RATE chi co the la 1 trong 4 so: 19200, 9600, 2400, 1200"
   #endif
   TR1 = 1;      // timer 1 bat dau chay
   TI  = 1;      // san sang gui du lieu
   REN = 1;      // cho phep nhan du lieu
}
void UART_Write(char c)
{
   while(TI == 0);
   TI = 0;
   SBUF = c;
}
void UART_Write_Text(char *str)
{
   unsigned char i=0;
   while(str[i]!=0)
   {
       UART_Write(str[i]);
	   i++;
   }
}
char UART_DATA_Ready()
{
   return RI;
}
char UART_Read()
{
   RI = 0;
   return SBUF;
}