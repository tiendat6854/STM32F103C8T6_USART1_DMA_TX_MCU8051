#include"..\..\lib\main.h"
#include"..\..\lib\uart_mode1.h" 
sbit LED = P1^0;

void main()
{
     UART_Init();
   	 LED = 1;
	 while(1)
	 {
	       if(UART_DATA_Ready()==1)	 // neu da nhan duoc du lieu
		   {
		      if(UART_Read() == 0x01)
			    {
			      LED = 0;
			    }
			    else if(UART_Read()==0x00)
			  {
					
			     LED = 1;
			  }
		   }
	 }
}