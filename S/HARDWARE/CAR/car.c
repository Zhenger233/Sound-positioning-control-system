#include "car.h"
#include "stm32f10x.h"
#include "timer.h"

void car_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_ResetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_10);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_ResetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_0|GPIO_Pin_1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}

void up(void)
{
//	TIM_SetCompare1(TIM3,speed);
//	TIM_SetCompare2(TIM3,speed);
	AIN1=BIN1=1;
	AIN2=BIN2=0;
}
void down(void)
{
//	TIM_SetCompare1(TIM3,speed);
//	TIM_SetCompare2(TIM3,speed);
	AIN1=BIN1=0;
	AIN2=BIN2=1;
}
void left(void)
{
//	TIM_SetCompare1(TIM3,speed);
//	TIM_SetCompare2(TIM3,speed);
	AIN1=BIN2=1;
	AIN2=BIN1=0;
}
void right(void)
{
//	TIM_SetCompare1(TIM3,speed);
//	TIM_SetCompare2(TIM3,speed);
	AIN1=BIN2=0;
	AIN2=BIN1=1;
}
void stop(void)
{
	AIN1=AIN2=BIN1=BIN2=0;
	STBY=0;
}


