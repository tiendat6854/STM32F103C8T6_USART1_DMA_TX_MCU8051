#include "stm32f10x.h"                  // Device header
#include"timer2.h"
#include"uart.h"

void GPIO_init(void)
{
  RCC->APB2ENR |= (1 << 4);
	// PC13: Output, 50Mhz
	GPIOC->CRH &= ~(15 << 20);
	GPIOC->CRH |= (3 << 20);
	// PC14,15: Input ( button )
	GPIOC->CRH &= ~(15 << 24);
	GPIOC->CRH |= (12 << 24);
	GPIOC->CRH &= ~(15 << 28);
	GPIOC->CRH |= (12 << 28);
}

void delay_ms(uint32_t t)
{
  while(t)
	{
	  TIM2->CNT = 0; 
		while(TIM2->CNT < 1000) {}
	  --t;
	}
}

int main()
{

  GPIO_init();
	timer2_Init();
	uart_dma_Init();
	
//	uint8_t u8data;
	
	while(1)
	{	
    // Nút nhân dieu khien LED tren VDK 8051
		
		if (GPIOC->IDR == ((GPIOC->IDR) | (1 << 14))) 
			{
			   delay_ms(50);
			   if (GPIOC->IDR == ((GPIOC->IDR) | (1 << 14))) 
				 {
				    while (GPIOC->IDR == ((GPIOC->IDR) | (1 << 14)));
					  USART1->DR = 0x01; // <-> DMA1_Channel4->CPAR = (uint32_t)((USART1->DR = 0x01));
		        while( !(USART1->SR & USART_SR_TC) );
	       }
	    }
			
			if (GPIOC->IDR == ((GPIOC->IDR) | (1 << 15)))
			{
			   delay_ms(50);
			   if (GPIOC->IDR == ((GPIOC->IDR) | (1 << 15)))
				 {
				    while (GPIOC->IDR == ((GPIOC->IDR) | (1 << 15)));
					  USART1->DR = 0x00; // <-> DMA1_Channel4->CPAR = (uint32_t)((USART1->DR = 0x00));
		        while( !(USART1->SR & USART_SR_TC) );
	       }
	    }
			
			/* Receive data:
		
		if ((USART1->SR & USART_SR_RXNE)) 
		{
			char u8Data = USART1->DR;
			if(u8data)
		  {
		     GPIOC->ODR &= ~(1 << 13);
		  }
		  else 
		  {
		     GPIOC->ODR |= (1 << 13);
		  }
		}           */
					
    GPIOC->ODR |= (1 << 13);
    delay_ms(100);
   	GPIOC->ODR &= ~(1 << 13);
    delay_ms(100);
  }
}
