#ifndef _Uart_Mode1_H_
#define	_Uart_Mode1_H_

void UART_Init();	// khoi tao UART_MODE1
void UART_Write(char c);   // gui 1 ky tu ra UART 
void UART_Write_Text(char *str);  // gui 1 chuoi ky tu
char UART_DATA_Ready();  // KT xem da nhan duoc 1 byte du lieu hay chua, tra ve 1 la da nhan duoc, 0 la chua nhan duoc
char UART_Read();	  // doc byte nhan duoc tu UART

#endif