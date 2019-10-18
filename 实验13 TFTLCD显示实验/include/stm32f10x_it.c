/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
#include "csbcj.h"
//#include "lcd12864.h"
#include "tim.h"
#include "Systick.h"

extern   uint16_t  TIME_X_Y;
extern  float time; 
extern  float  UltrasonicWave_Distance;


extern   uint16_t  YTIME_X_Y;
extern  float  Ytime; 
extern  float  YUltrasonicWave_Distance;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
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


//X��
//�жϷ���������������Ϣ�Ĵ���
void EXTIX_IRQHandler(void)
{
    SysTick_Delay_us(10);		                                                      //��ʱ10us
   if(EXTI_GetITStatus(EXTI_Linex) != RESET)                              //�жϷ���
	   {
			 TIM_SetCounter(TIMX,0);                                            //����������
			 TIME_X_Y=0;                                                        //�����������
			 
			 TIM_Cmd(TIMX, ENABLE);                                             //����ʱ��
			 while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                //�ȴ��͵�ƽ
			 TIM_Cmd(TIMX, DISABLE);			                                      //��ʱ��2ʧ��
			 time=TIM_GetCounter(TIMX);					                                //ȡ��ʱ��
	     EXTI_ClearITPendingBit(EXTI_Linex);                                //���EXTI7��·����λ
     }
}



//TIMx���жϷ�����   
// TIME_x_yΪ�жϴ���
void BASE_TIMX_IRQHandle(void )
{
  if (TIM_GetITStatus(TIMX,TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		  {
			  TIME_X_Y++;  //��¼�����˶��ٴ��жϣ�һ���ж�Ϊ60000us
			  TIM_ClearITPendingBit(TIMX,TIM_FLAG_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
			}
}




//Y��
//�жϷ���������������Ϣ�Ĵ���
void YEXTIX_IRQHandler(void)  
{
    SysTick_Delay_us(10);		                                                      //��ʱ10us
   if(EXTI_GetITStatus(YEXTI_Linex) != RESET)                              //�жϷ���
	   {
			 TIM_SetCounter(YTIMX,0);                                            //����������
			 YTIME_X_Y=0;                                                        //�����������
			 TIM_Cmd(YTIMX, ENABLE);                                             //����ʱ��
			 while(GPIO_ReadInputDataBit(YECHO_PORT,YECHO_PIN));	                //�ȴ��͵�ƽ
			 TIM_Cmd(YTIMX, DISABLE);			                                      //��ʱ��2ʧ��
			 Ytime=TIM_GetCounter(YTIMX);					                                //ȡ��ʱ��
	     EXTI_ClearITPendingBit(YEXTI_Linex);                                //���EXTI7��·����λ
     }
}

//TIMx���жϷ�����   
// TIME_x_yΪ�жϴ���
void YBASE_TIMX_IRQHandle(void )
{
  if (TIM_GetITStatus(YTIMX,TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		  {
			  YTIME_X_Y++;  //��¼�����˶��ٴ��жϣ�һ���ж�Ϊ60000us
			  TIM_ClearITPendingBit(YTIMX,TIM_FLAG_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
			}
}





/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
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


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
