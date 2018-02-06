#ifndef __USART_H
#define __USART_H	

//DMA
#define DEBUG_USART_DR_BASE               ((uint32_t)&USART1->DR)		
#define SENDBUFF_SIZE                     1000				//发送的数据量
#define DEBUG_USART_DMA_CLK               RCC_AHB1Periph_DMA2	
#define DEBUG_USART_DMA_CHANNEL           DMA_Channel_4
#define DEBUG_USART_DMA_STREAM            DMA2_Stream7

typedef unsigned	int uint32_t;
typedef unsigned	char uint8_t;

void USART_Config(void);
void USART_DMA_Config(void);
void USART_DMA_SENDMORE(uint32_t send_size,uint8_t *send_buff);
void NVIC_Configuration(void);
#endif 
