#ifndef __USER_BEED_H
#define	__USER_BEED_H
#include "stm32f4xx.h"


#define BEED_PIN                  GPIO_Pin_7                 
#define BEED_GPIO_PORT            GPIOG                      
#define BEED_GPIO_CLK             RCC_AHB1Periph_GPIOG

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	     {p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define BEED_TOGGLE		    digitalToggle(BEED_GPIO_PORT,BEED_PIN)
#define BEED_ON			    digitalHi(BEED_GPIO_PORT,BEED_PIN)
#define BEED_OFF			digitalLo(BEED_GPIO_PORT,BEED_PIN)

void BEED_GPIO_Config(void);

#endif


