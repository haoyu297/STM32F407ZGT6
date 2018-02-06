#ifndef __USER_BEED_H
#define	__USER_BEED_H
#include "stm32f4xx.h"


#define BEED_PIN                  GPIO_Pin_7                 
#define BEED_GPIO_PORT            GPIOG                      
#define BEED_GPIO_CLK             RCC_AHB1Periph_GPIOG

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	     {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define BEED_TOGGLE		    digitalToggle(BEED_GPIO_PORT,BEED_PIN)
#define BEED_ON			    digitalHi(BEED_GPIO_PORT,BEED_PIN)
#define BEED_OFF			digitalLo(BEED_GPIO_PORT,BEED_PIN)

void BEED_GPIO_Config(void);

#endif


