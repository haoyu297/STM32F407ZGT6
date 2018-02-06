/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>   
#include "include.h"





/*
*********************************************************************************************************
*                                                 TCBandSTACKS
*********************************************************************************************************
*/

static  OS_TCB   AppTaskLed1TCB;
static  CPU_STK  AppTaskLed1Stk [ APP_TASK_LED1_STK_SIZE ];

static  OS_TCB   AppTaskDMA2TCB;
static  CPU_STK  AppTaskDMA2Stk [ APP_TASK_DMA2_STK_SIZE ]; 

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskLed1  ( void * p_arg );

static  void  AppTaskDMA2 ( void * p_arg );

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;                               /* Init uC/OS-III.                                      */

	CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;


    OSInit(&err);
    CPU_Init();
    BSP_Init();                                                 /* Initialize BSP functions                             */

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

		
		OSTaskCreate((OS_TCB     *)&AppTaskDMA2TCB,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"",
                 (OS_TASK_PTR ) AppTaskDMA2,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_DMA2_PRIO, 
                 (CPU_STK    *)&AppTaskDMA2Stk[0],
                 (CPU_STK_SIZE) APP_TASK_DMA2_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_DMA2_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
		OSTaskCreate((OS_TCB     *)&AppTaskLed1TCB,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"",
                 (OS_TASK_PTR ) AppTaskLed1,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED1_PRIO,
                 (CPU_STK    *)&AppTaskLed1Stk[0],
                 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
		
		
}
uint16_t ddd[20];
/*
*********************************************************************************************************
*                                          LED1 TASK
*********************************************************************************************************
*/
static  void  AppTaskLed1 ( void * p_arg )
{
		OS_ERR      err;
//97 FF FF FF FF AA AA AA AA AA AA 97 00 01 30 80 01 01 00 59 E9 
		(void)p_arg;
    
		while (DEF_TRUE) 
		{  
			if(Dma_Complete) 
			{
				Dma_Complete = 0; 
				BEED_ON;
				OSTimeDly ( 50, OS_OPT_TIME_DLY, & err );
				BEED_OFF;
			}
			
			LED1_TOGGLE;
			OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );
		}		
}

/*
*********************************************************************************************************
*                                          DMA2 TASK
*********************************************************************************************************
*/
u8 suiji;
static  void  AppTaskDMA2 ( void * p_arg )
{
		OS_ERR      err;
//97 FF FF FF FF AA AA AA AA AA AA 97 00 00 30 40 01 02 99 E9
		(void)p_arg;
		while (DEF_TRUE) 
		{                                          /* Task body, always written as an infinite loop.       */
			suiji++;
			if(suiji>8)
				suiji=3;
			
			Hand_Rx_Buff(); 
			OSTimeDly ( 2, OS_OPT_TIME_DLY, & err );
		}		
}




