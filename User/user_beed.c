#include "include.h" 


 /**
  * @brief  ��ʼ������BEED��IO
  * @param  ��
  * @retval ��
  */
void BEED_GPIO_Config(void)
{		
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*����LED��ص�GPIO����ʱ��*/
    RCC_AHB1PeriphClockCmd ( BEED_GPIO_CLK, ENABLE); 

    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStructure.GPIO_Pin = BEED_PIN;	

    /*��������ģʽΪ���ģʽ*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    /*������������Ϊ2MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

    /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
    GPIO_Init(BEED_GPIO_PORT, &GPIO_InitStructure);	

    /*�ر�BEED*/
    BEED_OFF;		
}
