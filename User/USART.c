#include "include.h"
//#include "USART.h"
/*********************************************************************************
version 1.0
ģ����    :<��>
�ļ���    :<��>
����ļ�  :<��>
�ļ�ʵ�ֹ���:<ADC1��ʼ��\��ȡADֵ>
����      :<DHY>
�汾      :<1.0>

----------------------------------------------------------------------------------------------------------------------
��ע      :<��>
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼ ��
����    �汾    �޸���        �޸�����
YYYY/MM/DD X.Y  <���߻��޸���>  <�޸�����>
YYYY/MM/DD X.Y  <���߻��޸���>  <�޸�����>
====================================================================
����˵��:
*******************************************************************************/ 

 /**
  * @brief  USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

    /* ʹ�� UART ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* ���� PXx �� USARTx_Tx*/
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1);

    /*  ���� PXx �� USARTx__Rx*/
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);

    /* ����Tx����Ϊ���ù���  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9  ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ����Rx����Ϊ���ù��� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ���ô�USART ģʽ */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure); 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  USART1 TX DMA ���ã��ڴ浽����(USART1->DR)
  * @param  ��
  * @retval ��
  */
void USART_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*����DMAʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* ��λ��ʼ��DMA������ */
    DMA_DeInit(DMA2_Stream7);

    /* ȷ��DMA��������λ��� */
    while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)  {
    }

    /*usart1 tx��Ӧdma2��ͨ��4��������7*/	
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    /*����DMAԴ���������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = DEBUG_USART_DR_BASE;	 
    /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    //DMA_InitStructure.DMA_Memory0BaseAddr = (u32)SendBuff;
    /*���򣺴��ڴ浽����*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;	
    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    //DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    /*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    /*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    /*DMAģʽ��һ��ģʽ*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 
    /*���ȼ�����*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    /*����FIFO*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
    /*�洢��ͻ������ 16������*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    /*����ͻ������ 1������*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
    /*����DMA2��������7*/		   
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);

    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
        
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    /*ʹ��DMA*/
    DMA_Cmd(DMA2_Stream7, DISABLE);

}
/**
  * @brief  DMA���η����������·���
  * @param  uint32_t SEND_SIZE	�����ַ������ȣ�uint8_t* SEND_buffҪ���͵�����
  * @retval ��
  */
void USART_DMA_SENDMORE(uint32_t send_size,uint8_t* send_buff)
{
    uint16_t i;
    Print ("DMA��ʼ����\n");
    for(i=0;i<send_size;i++)
    {
        Print ("%02x ",send_buff[i]);
        if(i%20 == 19)
        {
            Print ("\n");
        }
    }
    Print ("\n");

    DMA2_Stream7->M0AR = (u32)send_buff;
    DMA2_Stream7->NDTR = send_size;

    /* ʧ��DMAͨ�� */
    DMA_Cmd(DMA2_Stream7, DISABLE);

    /* �����־ */
    DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
        
    /* ʹ��DMAͨ�� */
    DMA_Cmd(DMA2_Stream7, ENABLE);

}
/**
  * @brief  �жϿ���������
  * @param  ��
  * @retval ��
  */
void NVIC_Configuration(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	/* ����USART1Ϊ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	/* �������ȼ�Ϊ1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* �����ȼ�Ϊ1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* ��ʼ������NVIC */
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the DMA Stream IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

}

