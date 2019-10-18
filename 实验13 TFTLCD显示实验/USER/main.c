#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"

#include "csbcj.h"
#include "tim.h"
 
/************************************************
 ALIENTEK ս��STM32F103������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
 	
	
//X��
uint16_t   TIME_X_Y=0;                 //�����ж��������
float      time=0;                     //���յ��ź����õ�ʱ��
float      UltrasonicWave_Distance=0;  //����
float      testCNT1=0;                 //û������ת��֮ǰ�ľ���    
unsigned char       dispBuff1[100];             //����ת����ľ���

//Y��
uint16_t   YTIME_X_Y=0;
float      Ytime=0; 
float      YUltrasonicWave_Distance=0;
float      testCNT2=0;
unsigned char       dispBuff2[100];
u8 x=0;
void dingwei_distance(void)
 {
	 
	 //X��
	 time=time+((TIME_X_Y)*1000); //��ʱ��3�жϼ���ֵһ��������Ϊ1000us���������ʱ��
	 time=time*0.000001;                         //ת����λΪs
	 UltrasonicWave_Distance=((340*time)*100)/2;  //��λ��cm		 
	 testCNT1=UltrasonicWave_Distance;
	 sprintf((char*)dispBuff1,"%0.3f cm",testCNT1);	//ʹ��c��׼��ѱ���ת�����ַ���
	 //display_string_5x8_1(1,60,dispBuff1);             //dispBuffΪת������ַ���
	 LCD_ShowString(30,150,200,16,16,dispBuff1);
	 
	 //Y��
	 Ytime=Ytime+((YTIME_X_Y)*1000); //��ʱ��3�жϼ���ֵһ��������Ϊ1000us���������ʱ��
	 Ytime=Ytime*0.000001;                         //ת����λΪs
	 YUltrasonicWave_Distance=((340*time)*100)/2;  //��λ��cm		 
	 testCNT2=YUltrasonicWave_Distance;
	 sprintf((char*)dispBuff1,"%0.3f cm",testCNT2);	//ʹ��c��׼��ѱ���ת�����ַ���
	 //display_string_5x8_1(3,60,dispBuff2);             //dispBuffΪת������ַ���
	 LCD_ShowString(30,170,200,16,16,dispBuff2);
	 
 }


 
 

 
 
 int main(void)
 {	 
	 UltrasonicWave_Configuration();   //������ģ���ʼ��
	 BASIC_TIM_Init();                 //��ʱ����ʼ��

//	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	POINT_COLOR=RED;
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣				 	
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
 		//LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID
		LCD_ShowString(30,130,200,12,12,"2014/5/4");
		
	    x++;
//		if(x==12)x=0;
//		LED0=!LED0;				   		 
		delay_ms(1000);	
		
		
		 UltrasonicWave_StartMeasure();                    //����������ģ��
		 dingwei_distance();
		delay_ms(60);

	} 

}
