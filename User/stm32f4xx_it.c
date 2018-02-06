/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <includes.h>
#include "include.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
u16 Rx_BuffLen;
uint8_t Rx_Buff[SENDBUFF_SIZE];
uint8_t Achieve_Flg;
uint8_t Starting_Identifier[10];
void Judgement_Frame_Format(void)
{
	uint8_t i=0,j=0,k=1,n=0;
	uint32_t l=0,m;
    Print ("S1-----TYPE---------address------S2--len--SEQ-C---Fn--CS-END--Data...\n");
	for(i=0;i<Rx_BuffLen;i++)
	{
		if(Rx_Buff[i] == 0x97)
		{
			Starting_Identifier[k] = i;
			Print ("��%u����ʼ����λ���ڵ�%uλ\n",k,Starting_Identifier[k]);
			k++;
		}
	}
	for(i=1;i<k-1;i++)
	{
		for(j=i+1;j<k;j++)
		{
			if((Starting_Identifier[j] - Starting_Identifier[i]) == 11)//�ж�������ʼλ�Ƿ����11λ
			{
				Print ("��%u���͵�%u���������11λ������\n",i,j);
				if(((Rx_Buff[Starting_Identifier[j]+4]) & 0xC0) == 0x40)//�жϿ������Ƿ���ȷ
				{
                    Print ("��������ȷ\n");
					l = (Rx_Buff[Starting_Identifier[j]+2]<<8) + (Rx_Buff[Starting_Identifier[j]+1]);
					if((l + 19) == (Rx_BuffLen-Starting_Identifier[i]))//�ж�һ֡���ݵĳ����Ƿ���ȷ
					{
						Print ("����֡������ȷ\n");
						for(m=Starting_Identifier[i];m<(l + 18);m++)
						{
							n+=Rx_Buff[m];
						}
						if(n == (Rx_Buff[Starting_Identifier[i]+18]))//�ж��ж�У����Ƿ���ȷ
						{
                            Achieve_Flg=1;
							Print ("У�����ȷ\n");
						}
						else
						{
							Print ("У��Ͳ���ȷ\n");
						}
					}
					else
					{
						Print ("����֡���Ȳ���ȷ\n");
					}
				}
				else
				{
					Print ("�����벻��ȷ\n");
				}
			}	
		}
	}
}

/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */

void USART1_IRQHandler(void)
{
    uint8_t ucTemp;
    uint8_t i;
    CPU_SR_ALLOC();

    CPU_CRITICAL_ENTER();
    OSIntNestingCtr++;                                      /* Tell uC/OS-III that we are starting an ISR             */
    CPU_CRITICAL_EXIT();
			
	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		ucTemp = USART_ReceiveData( USART1 );
		if (ucTemp == 0xE9) 
		{
			Achieve_Flg=0;
			Rx_Buff[Rx_BuffLen] = ucTemp;
			Print ("%02x ",ucTemp);
            if(Rx_BuffLen%20 == 19)
		    {
				Print ("\n");
			}
            if(Rx_BuffLen>=19)
            {
                Judgement_Frame_Format();
                if(!Achieve_Flg)
                {
                    for(i=0;i<Rx_BuffLen+1;i++)
                    {
                        Rx_Buff[i] = 0;
                    }
                    Rx_BuffLen=0;
                    Print ("�������ݲ���ȷ\n");
                }
                else
                {
                    Print ("����������ɲ���ȷ\n");
                }
            }
            else
            {
                Rx_BuffLen++;
                if (Rx_BuffLen >= (SENDBUFF_SIZE-1))
                {
                    Rx_BuffLen = SENDBUFF_SIZE-1;
                }	
            }	
		}
		else
		{
			Rx_Buff[Rx_BuffLen]=ucTemp;
			Print ("%02x ",ucTemp);
			if(Rx_BuffLen%20 == 19)
		    {
				Print ("\n");
			}
			Rx_BuffLen++;
			if (Rx_BuffLen >= (SENDBUFF_SIZE-1))
            {
                Rx_BuffLen = SENDBUFF_SIZE-1;
            }				
		}
	}
	OSIntExit(); 
}


u8 Dma_Complete;
void DMA2_Stream7_IRQHandler(void)
{

    CPU_SR_ALLOC();

    CPU_CRITICAL_ENTER();
    OSIntNestingCtr++;                                      /* Tell uC/OS-III that we are starting an ISR             */
    CPU_CRITICAL_EXIT();

    if (DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7)!=RESET)
    {		
        DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);
        
        DMA_Cmd(DMA2_Stream7, DISABLE);		
        Print ("DMA���ͽ���\n\n");
        Dma_Complete = 1;
    }
    OSIntExit(); 
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
