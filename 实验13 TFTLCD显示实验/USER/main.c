#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"

#include "csbcj.h"
#include "tim.h"
 
/************************************************
 ALIENTEK 战舰STM32F103开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 	
	
//X轴
uint16_t   TIME_X_Y=0;                 //发生中断溢出次数
float      time=0;                     //接收到信号所用的时间
float      UltrasonicWave_Distance=0;  //距离
float      testCNT1=0;                 //没有类型转换之前的距离    
unsigned char       dispBuff1[100];             //类型转换后的距离

//Y轴
uint16_t   YTIME_X_Y=0;
float      Ytime=0; 
float      YUltrasonicWave_Distance=0;
float      testCNT2=0;
unsigned char       dispBuff2[100];
u8 x=0;
void dingwei_distance(void)
 {
	 
	 //X轴
	 time=time+((TIME_X_Y)*1000); //定时器3中断计数值一次最大计数为1000us，计算出总时间
	 time=time*0.000001;                         //转换单位为s
	 UltrasonicWave_Distance=((340*time)*100)/2;  //单位是cm		 
	 testCNT1=UltrasonicWave_Distance;
	 sprintf((char*)dispBuff1,"%0.3f cm",testCNT1);	//使用c标准库把变量转化成字符串
	 //display_string_5x8_1(1,60,dispBuff1);             //dispBuff为转换后的字符串
	 LCD_ShowString(30,150,200,16,16,dispBuff1);
	 
	 //Y轴
	 Ytime=Ytime+((YTIME_X_Y)*1000); //定时器3中断计数值一次最大计数为1000us，计算出总时间
	 Ytime=Ytime*0.000001;                         //转换单位为s
	 YUltrasonicWave_Distance=((340*time)*100)/2;  //单位是cm		 
	 testCNT2=YUltrasonicWave_Distance;
	 sprintf((char*)dispBuff1,"%0.3f cm",testCNT2);	//使用c标准库把变量转化成字符串
	 //display_string_5x8_1(3,60,dispBuff2);             //dispBuff为转换后的字符串
	 LCD_ShowString(30,170,200,16,16,dispBuff2);
	 
 }


 
 

 
 
 int main(void)
 {	 
	 UltrasonicWave_Configuration();   //超声波模块初始化
	 BASIC_TIM_Init();                 //定时器初始化

//	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();
	POINT_COLOR=RED;
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。				 	
  	while(1) 
	{		 
switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break;

			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		LCD_Clear(WHITE);

		POINT_COLOR=RED;	  
		LCD_ShowString(30,40,210,24,24,"WarShip STM32 ^_^"); 
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 		//LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID
		LCD_ShowString(30,130,200,12,12,"2014/5/4");
		
	    x++;
//		if(x==12)x=0;
//		LED0=!LED0;				   		 
		delay_ms(1000);	
		
		
		 UltrasonicWave_StartMeasure();                    //启动超声波模块
		 dingwei_distance();
		delay_ms(60);

	} 

}
