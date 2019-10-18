#include "tim.h"
#include  "stm32f10x.h"
#include "Systick.h"



static void BASIC_TIM_NVIC_Config(void)
{
	
	//X轴
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
	//Y轴
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = YTIM_IRQ ;	  
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}




static void BASIC_TIM_Config(void)
{
	
	//X轴
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// 开启定时器时钟,即内部时钟CK_INT=72M
    	TIM_RCC_APB1PeriphClockCmd(TIM_RCC_APB1Periph_TIMX,ENABLE);
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = TIME_TIM_PERIOD;
	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_CK_CNT;//分频系数71+1
		// 时钟分频因子 ，基本定时器没有，不用管
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		// 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		// 重复计数器的值，基本定时器没有，不用管
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	  // 初始化定时器
    TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
		// 清除计数器中断标志位
    TIM_ClearFlag(TIMX, TIM_FLAG_Update);
		// 开启计数器中断
    TIM_ITConfig(TIMX,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
		// 使能计数器
    TIM_Cmd(TIMX, ENABLE);
		
		
	//Y轴	
		// 开启定时器时钟,即内部时钟CK_INT=72M
    	TIM_RCC_APB1PeriphClockCmd(YTIM_RCC_APB1Periph_TIMX,ENABLE);
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = YTIME_TIM_PERIOD;
	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= YTIM_CK_CNT;//分频系数71+1
		// 时钟分频因子 ，基本定时器没有，不用管
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		// 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		// 重复计数器的值，基本定时器没有，不用管
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	  // 初始化定时器
    TIM_TimeBaseInit(YTIMX, &TIM_TimeBaseStructure);
		// 清除计数器中断标志位
    TIM_ClearFlag(YTIMX, TIM_FLAG_Update);
		// 开启计数器中断
    TIM_ITConfig(YTIMX,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
		// 使能计数器
    TIM_Cmd(YTIMX, ENABLE);	
		
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Config();
}



