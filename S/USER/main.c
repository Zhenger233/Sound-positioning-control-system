#include "delay.h"
#include "key.h"
#include "sys.h" 
#include "24l01.h" 	 
#include "car.h"
#include "timer.h"
/************************************************
B13---SPI-SCK
B14---SPI-MISO
B15---SPI-MOSI
B6----NRF-IRQ
B7----NRF-CSN
B8----NRF-CE
B5----CAR-PWMA
A9----CAR-PWMB
A1----CSB-TRIG
A12---CAR-AIN1
B11---CAR-AIN2
A11---CAR-BIN1
A10---CAR-BIN2
************************************************/
u8 key,mode;
u16 t=0,speed=10;			 
u8 tmp_buf[33];	
u8* str=0;

 int main(void)
 {	 
	SystemInit();
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
 	//LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
 	NRF24L01_Init();    		//初始化NRF24L01 
	TIM3_PWM_Init(899,0);
	TIM_SetCompare2(TIM2,speed);
	TIM_SetCompare2(TIM3,speed);
	TIM_SetCompare4(TIM4,speed);
	car_init();
	while(NRF24L01_Check())
	{
 		delay_ms(200);
	} 	
	
	NRF24L01_RX_Mode();		  
	while(1)
	{	  		    		    				 
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
		{
			STBY=~STBY;
			key=tmp_buf[0];
			switch(key)
			{
				case 0:str="ERROR";break;	//0		   
				case 162:str="POWER";stop();break;	    //a2-45
				case 98:str="UP";up();break;	    //62-46
				case 2:str="PLAY";STBY=1;break;		 //2-40
				case 226:str="ALIENTEK";break;		// e2-47
				case 194:str="RIGHT";right();break;	   //c2-43
				case 34:str="LEFT";left();break;		 // 22-44
				case 224:str="VOL-";speed-=10;break;		  //e0-07
				case 168:str="DOWN";down();break;		   //a8-15
				case 144:str="VOL+";speed+=10;break;		    //90-09
				case 104:str="1";break;		  //68-16
				case 152:str="2";break;	   //98-19
				case 176:str="3";break;	    //b0-0d
				case 48:str="4";break;		    //30-0c
				case 24:str="5";break;		    //18-18
				case 122:str="6";break;		  //7a-5e
				case 16:str="7";break;			  //10-08					
				case 56:str="8";break;	 //38-1c
				case 90:str="9";break;//5a-5a
				case 66:str="0";break;//42-42
				case 82:str="DELETE";break;		 //52-4a
			}
			if(speed<=0)speed=0;
			if(speed>899)speed=899;
			TIM_SetCompare4(TIM4,speed);
			TIM_SetCompare2(TIM3,speed);
		}else delay_us(100);	   				    
	}	
}


