#ifndef __CSBCJ_H
#define __CSBCJ_H
#include "tim.h"


#define  RCC_APBxPeriphClockCmd   RCC_APB2PeriphClockCmd
#define  RCC_GPIO_Clock           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)


//X轴
//发送启动脉冲大于10us
#define	 TRIG_PORT      GPIOC		     //TRIG    
#define	 TRIG_PIN       GPIO_Pin_8   //TRIG 
//接受到回波信号引脚
#define	 ECHO_PORT      GPIOC		      //ECHO
#define	 ECHO_PIN       GPIO_Pin_7	  //ECHO
//利用中断接收超声波回波信号
#define  GPIO_PortSourceGPIOX    GPIO_PortSourceGPIOC
#define  GPIO_PinSourcex         GPIO_PinSource7
#define  EXTI_Linex              EXTI_Line7
#define  EXTIx_IRQn              EXTI9_5_IRQn
#define  EXTIX_IRQHandler        EXTI9_5_IRQHandler


//Y轴
//发送启动脉冲大于10us
#define	 YTRIG_PORT      GPIOC		      //TRIG    
#define	 YTRIG_PIN       GPIO_Pin_9     //TRIG 
//接受到回波信号引脚
#define	 YECHO_PORT      GPIOC		      //ECHO
#define	 YECHO_PIN       GPIO_Pin_4	    //ECHO
//利用中断接收超声波回波信号
#define  YGPIO_PortSourceGPIOX    GPIO_PortSourceGPIOC
#define  YGPIO_PinSourcex         GPIO_PinSource4
#define  YEXTI_Linex              EXTI_Line4
#define  YEXTIx_IRQn              EXTI4_IRQn
#define  YEXTIX_IRQHandler        EXTI4_IRQHandler






static void BASIC_CSBC_NVIC_Config(void);
void UltrasonicWave_Configuration(void);               //对超声波模块初始化
void UltrasonicWave_StartMeasure(void);                //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间



#endif  /*__CSBCJ_H*/


