#include "csbcj.h"
#include "tim.h"
#include "delay.h"
#include "Systick.h"

extern float time;                         //X����ʱ��
extern float UltrasonicWave_Distance;      //X����     

extern float Ytime;                         //Y����ʱ��
extern float YUltrasonicWave_Distance;      //Y����

static void BASIC_CSBC_NVIC_Config(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure; 

 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOX,GPIO_PinSourcex);    //GPIOC.7	  �ж����Լ��жϳ�ʼ������
    EXTI_InitStructure.EXTI_Line=EXTI_Linex;                      //�ⲿ�ж���7
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //���� EXTI ��·Ϊ�ж����� 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        //����������· ������Ϊ�ж�����
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
  	EXTI_Init(&EXTI_InitStructure);		                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	              // �����ж���Ϊ2	
    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn ;		          // �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;			// ���������ȼ�Ϊ 2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	 	        // ������ռ���ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);
	
	
	  //Y��
	 	GPIO_EXTILineConfig(YGPIO_PortSourceGPIOX,YGPIO_PinSourcex);    //GPIOC.7	  �ж����Լ��жϳ�ʼ������
    EXTI_InitStructure.EXTI_Line=YEXTI_Linex;                      //�ⲿ�ж���7
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //���� EXTI ��·Ϊ�ж����� 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        //����������· ������Ϊ�ж�����
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
  	EXTI_Init(&EXTI_InitStructure);		                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = YEXTIx_IRQn ;		          // �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;			// ���������ȼ�Ϊ 2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	 	        // ������ռ���ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);
	
}


/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef       GPIO_InitStructure;	
	
  RCC_APBxPeriphClockCmd(RCC_GPIO_Clock, ENABLE);
   //X 
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					        //PC8��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	           //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				        //PC7��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		      //��Ϊ����
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						  //��ʼ��GPIOA
	BASIC_CSBC_NVIC_Config();
	
	
	//Y
	GPIO_InitStructure.GPIO_Pin = YTRIG_PIN;					        //PC9��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(YTRIG_PORT, &GPIO_InitStructure);	           //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = YECHO_PIN;				        //PC4��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		      //��Ϊ����
  GPIO_Init(YECHO_PORT,&GPIO_InitStructure);						  //��ʼ��GPIOA
	BASIC_CSBC_NVIC_Config();
	
}



/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
	//X
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  SysTick_Delay_us(20); 		                        //��ʱ20US�ߵ�ƽ����ģ�鹤��
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);     //��ʼ�����رոߵ�ƽ�õ͵�ƽ
	
	//Y
	GPIO_SetBits(YTRIG_PORT,YTRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  SysTick_Delay_us(20); 		                        //��ʱ20US�ߵ�ƽ����ģ�鹤��
  GPIO_ResetBits(YTRIG_PORT,YTRIG_PIN);     //��ʼ�����رոߵ�ƽ�õ͵�ƽ
}

