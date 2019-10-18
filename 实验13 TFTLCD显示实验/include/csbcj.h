#ifndef __CSBCJ_H
#define __CSBCJ_H
#include "tim.h"


#define  RCC_APBxPeriphClockCmd   RCC_APB2PeriphClockCmd
#define  RCC_GPIO_Clock           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)


//X��
//���������������10us
#define	 TRIG_PORT      GPIOC		     //TRIG    
#define	 TRIG_PIN       GPIO_Pin_8   //TRIG 
//���ܵ��ز��ź�����
#define	 ECHO_PORT      GPIOC		      //ECHO
#define	 ECHO_PIN       GPIO_Pin_7	  //ECHO
//�����жϽ��ճ������ز��ź�
#define  GPIO_PortSourceGPIOX    GPIO_PortSourceGPIOC
#define  GPIO_PinSourcex         GPIO_PinSource7
#define  EXTI_Linex              EXTI_Line7
#define  EXTIx_IRQn              EXTI9_5_IRQn
#define  EXTIX_IRQHandler        EXTI9_5_IRQHandler


//Y��
//���������������10us
#define	 YTRIG_PORT      GPIOC		      //TRIG    
#define	 YTRIG_PIN       GPIO_Pin_9     //TRIG 
//���ܵ��ز��ź�����
#define	 YECHO_PORT      GPIOC		      //ECHO
#define	 YECHO_PIN       GPIO_Pin_4	    //ECHO
//�����жϽ��ճ������ز��ź�
#define  YGPIO_PortSourceGPIOX    GPIO_PortSourceGPIOC
#define  YGPIO_PinSourcex         GPIO_PinSource4
#define  YEXTI_Linex              EXTI_Line4
#define  YEXTIx_IRQn              EXTI4_IRQn
#define  YEXTIX_IRQHandler        EXTI4_IRQHandler






static void BASIC_CSBC_NVIC_Config(void);
void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��



#endif  /*__CSBCJ_H*/


