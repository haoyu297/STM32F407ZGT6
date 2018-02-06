#include "include.h"
//#include "USART.h"
/*********************************************************************************
version 1.0
模块名    :<无>
文件名    :<无>
相关文件  :<无>
文件实现功能:<ADC1初始化\获取AD值>
作者      :<DHY>
版本      :<1.0>

----------------------------------------------------------------------------------------------------------------------
备注      :<无>
---------------------------------------------------------------------------------------------------------------------
修改记录 ：
日期    版本    修改人        修改内容
YYYY/MM/DD X.Y  <作者或修改名>  <修改内容>
YYYY/MM/DD X.Y  <作者或修改名>  <修改内容>
====================================================================
其他说明:
*******************************************************************************/ 

 /**
  * @brief  USART GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

    /* 使能 UART 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* 连接 PXx 到 USARTx_Tx*/
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1);

    /*  连接 PXx 到 USARTx__Rx*/
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);

    /* 配置Tx引脚为复用功能  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9  ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置Rx引脚为复用功能 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置串USART 模式 */
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
  * @brief  USART1 TX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USART_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*开启DMA时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* 复位初始化DMA数据流 */
    DMA_DeInit(DMA2_Stream7);

    /* 确保DMA数据流复位完成 */
    while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)  {
    }

    /*usart1 tx对应dma2，通道4，数据流7*/	
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    /*设置DMA源：串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = DEBUG_USART_DR_BASE;	 
    /*内存地址(要传输的变量的指针)*/
    //DMA_InitStructure.DMA_Memory0BaseAddr = (u32)SendBuff;
    /*方向：从内存到外设*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;	
    /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    //DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    /*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    /*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    /*DMA模式：一次模式*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 
    /*优先级：中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    /*禁用FIFO*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
    /*存储器突发传输 16个节拍*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    /*外设突发传输 1个节拍*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
    /*配置DMA2的数据流7*/		   
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);

    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
        
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    /*使能DMA*/
    DMA_Cmd(DMA2_Stream7, DISABLE);

}
/**
  * @brief  DMA单次发送设置重新发送
  * @param  uint32_t SEND_SIZE	发送字符串长度，uint8_t* SEND_buff要发送的数组
  * @retval 无
  */
void USART_DMA_SENDMORE(uint32_t send_size,uint8_t* send_buff)
{
    uint16_t i;
    Print ("DMA开始发送\n");
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

    /* 失能DMA通道 */
    DMA_Cmd(DMA2_Stream7, DISABLE);

    /* 清除标志 */
    DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
        
    /* 使能DMA通道 */
    DMA_Cmd(DMA2_Stream7, ENABLE);

}
/**
  * @brief  中断控制器配置
  * @param  无
  * @retval 无
  */
void NVIC_Configuration(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 嵌套向量中断控制器组选择 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	/* 配置USART1为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	/* 抢断优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 子优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* 初始化配置NVIC */
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the DMA Stream IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

}

