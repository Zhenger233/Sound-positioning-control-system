#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "remote.h"

#define STBY PAout(1)
//#define PWMA PBout(4)																																																																																																																																																																																		
#define AIN1 PCout(9)
#define AIN2 PCout(10)
//#define PWMB PB(5)
#define BIN1 PCout(12)
#define BIN2 PCout(13)
void car_Init(void);
void stop(void);
void up(void);
void down(void);
void left(void);
void right(void);
void TIM3_PWM_Init(u16 arr,u16 psc);

 int main(void)
 {	 
	u8 key;
	u8 t=0;	
 	u8 *str=0;
	u16 pwmVal=0;
	car_Init();

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	KEY_Init();	 	
	Remote_Init();			//红外接收初始化		 
	TIM3_PWM_Init(899,0);
	TIM_SetCompare2(TIM3,455);
	TIM_SetCompare1(TIM3,455);
	TIM_SetCompare3(TIM3,455);
 	POINT_COLOR=RED;		//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");
	LCD_ShowString(30,70,200,16,16,"REMOTE TEST");	
	LCD_ShowString(30,90,200,16,16,"pwmVal");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");

   	LCD_ShowString(30,130,200,16,16,"KEYVAL:");	
   	LCD_ShowString(30,150,200,16,16,"KEYCNT:");	
   	LCD_ShowString(30,170,200,16,16,"SYMBOL:");	  		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
			LCD_ShowNum(86,130,key,3,16);		//显示键值
			LCD_ShowNum(86,150,RmtCnt,3,16);	//显示按键次数		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";stop();break;	    
				case 98:str="UP";up();break;	    
				case 2:str="PLAY";STBY=!STBY;break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:str="RIGHT";right();break;	   
				case 34:str="LEFT";left();break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";down();break;		   
				case 144:str="VOL+";break;		    
				case 104:str="1";pwmVal++;break;		  
				case 152:str="2";pwmVal+=10;break;	   
				case 176:str="3";break;	    
				case 48:str="4";pwmVal--;break;		    
				case 24:str="5";pwmVal-=10;;break;		    
				case 122:str="6";break;		  
				case 16:str="7";pwmVal=899;break;			   					
				case 56:str="8";pwmVal=1;break;	 
				case 90:str="9";break;
				case 66:str="0";break;
				case 82:str="DELETE";break;		 
			}
			if(pwmVal<800)pwmVal=800;
			printf("%d",pwmVal);
//			if(pwmVal<0)pwmVal=0;
			LCD_ShowNum(86,90,pwmVal,3,16);
			TIM_SetCompare2(TIM3,pwmVal);
			TIM_SetCompare1(TIM3,pwmVal);
			TIM_SetCompare3(TIM3,pwmVal);
			LCD_Fill(86,170,116+8*8,170+16,WHITE);	//清楚之前的显示
			LCD_ShowString(86,170,200,16,16,str);	//显示SYMBOL
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}


void car_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //LED0-->PA.1 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	GPIO_SetBits(GPIOC,GPIO_Pin_10);
	GPIO_SetBits(GPIOC,GPIO_Pin_11);
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	STBY=1;
//	PWMA=1;
//	PWMB=1;
	AIN1=0;
	AIN2=0;
	BIN1=0;
	BIN2=0;
}

void stop()
{
	STBY=0;
}



void up()
{
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
}

void down()
{
	AIN1=0;
	AIN2=1;
	BIN1=0;
	BIN2=1;
}

void left()
{
	AIN1=0;
	AIN2=1;
	BIN1=1;
	BIN2=0;
}

void right()
{
	AIN1=1;
	AIN2=0;
	BIN1=0;
	BIN2=1;
}

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM_CH2
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		LED1=!LED1;
		}
}

