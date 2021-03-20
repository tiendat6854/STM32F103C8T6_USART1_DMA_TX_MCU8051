#include"uart.h"

uint16_t u16Buffer[] = {'D', 'A', 'T'};

void uart_dma_Init(void)
{
	// GPIOA, USART1 clock enable
  RCC->APB2ENR |= (1 << 2) | (1 << 14);

  // PA9- TX : AF output PP, 50Hz
  GPIOA->CRH &= ~(15 << 4) ;
	GPIOA->CRH |= (11 << 4);
	
  // PA10- RX : Floating input , 50Hz
	GPIOB->CRH &= ~(15 << 8) ;
	GPIOB->CRH |= (4 << 8);

  // f = 72MHZ on APB2 bus
  USART1->BRR = 0x1D4C; // baud 9600
	
  USART1->CR1 &= ~(1 << 12); //  Start bit, 8 Data bits
	USART1->CR2 &= ~(3 << 12); //  1 Stop bit
	USART1->CR1 &= ~(1 << 10); //  Parity control disabled
	
  USART1->CR1 |= (3 << 2);   //  Receiver, Transmitter enable
	USART1->CR1 |= (1 << 13);  //  USART enable
	
		// DMA1 Channel 4 - USART1_TX
  RCC->AHBENR |= (1 << 0);
	
	DMA1_Channel4->CCR &= ~(3 << 10);
	DMA1_Channel4->CCR |= (1 << 10); // Memory size 16 bit
	
	DMA1_Channel4->CCR &= ~(3 << 8);
	DMA1_Channel4->CCR |= (1 << 8); //  Peripheral size 16 bit
	
	DMA1_Channel4->CCR |= (3 << 12) | (1 << 7) | (1 << 4) | (1 << 5);
	
	DMA1_Channel4->CMAR = (uint32_t)u16Buffer;
	
	DMA1_Channel4->CPAR = (uint32_t)(&(USART1->DR));
	
	DMA1_Channel4 ->CNDTR = sizeof(u16Buffer);
	
	USART1->CR3 |= (3 << 6);
	
	DMA1_Channel4->CCR |= (1 << 0);
	
	TIM2->DIER |= (1 << 9);
}
