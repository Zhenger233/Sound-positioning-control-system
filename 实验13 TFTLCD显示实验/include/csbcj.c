#include "csbcj.h"
#include "tim.h"
#include "delay.h"
#include "Systick.h"

extern float time;                         //X接收时间
extern float UltrasonicWave_Distance;      //X距离     

extern float Ytime;                         //Y接收时间
extern float YUltrasonicWave_Distance;      //Y距离

static void BASIC_CSBC_NVIC_Config(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure; 

 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOX,GPIO_PinSourcex);    //GPIOC.7	  中断线以及中断初始化配置
    EXTI_InitStructure.EXTI_Line=EXTI_Linex;                      //外部中断线7
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //设置 EXTI 线路为中断请求 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        //设置输入线路 上升沿为中断请求
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //使能
  	EXTI_Init(&EXTI_InitStructure);		                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	              // 设置中断组为2	
    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn ;		          // 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;			// 设置主优先级为 2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	 	        // 设置抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //使能中断
    NVIC_Init(&NVIC_InitStructure);
	
	
	  //Y轴
	 	GPIO_EXTILineConfig(YGPIO_PortSourceGPIOX,YGPIO_PinSourcex);    //GPIOC.7	  中断线以及中断初始化配置
    EXTI_InitStructure.EXTI_Line=YEXTI_Linex;                      //外部中断线7
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //设置 EXTI 线路为中断请求 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        //设置输入线路 上升沿为中断请求
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //使能
  	EXTI_Init(&EXTI_InitStructure);		                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = YEXTIx_IRQn ;		          // 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;			// 设置主优先级为 2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	 	        // 设置抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //使能中断
    NVIC_Init(&NVIC_InitStructure);
	
}


/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef       GPIO_InitStructure;	
	
  RCC_APBxPeriphClockCmd(RCC_GPIO_Clock, ENABLE);
   //X 
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					        //PC8接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	           //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				        //PC7接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		      //设为输入
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						  //初始化GPIOA
	BASIC_CSBC_NVIC_Config();
	
	
	//Y
	GPIO_InitStructure.GPIO_Pin = YTRIG_PIN;					        //PC9接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(YTRIG_PORT, &GPIO_InitStructure);	           //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin = YECHO_PIN;				        //PC4接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		      //设为输入
  GPIO_Init(YECHO_PORT,&GPIO_InitStructure);						  //初始化GPIOA
	BASIC_CSBC_NVIC_Config();
	
}



/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_StartMeasure(void)
{
	//X
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //送>10US的高电平
  SysTick_Delay_us(20); 		                        //延时20US高电平触发模块工作
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);     //开始工作关闭高电平置低电平
	
	//Y
	GPIO_SetBits(YTRIG_PORT,YTRIG_PIN); 		  //送>10US的高电平
  SysTick_Delay_us(20); 		                        //延时20US高电平触发模块工作
  GPIO_ResetBits(YTRIG_PORT,YTRIG_PIN);     //开始工作关闭高电平置低电平
}

