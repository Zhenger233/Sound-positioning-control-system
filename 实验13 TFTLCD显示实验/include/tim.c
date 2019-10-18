#include "tim.h"
#include  "stm32f10x.h"
#include "Systick.h"



static void BASIC_TIM_NVIC_Config(void)
{
	
	//X��
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
	//Y��
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = YTIM_IRQ ;	  
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}




static void BASIC_TIM_Config(void)
{
	
	//X��
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    	TIM_RCC_APB1PeriphClockCmd(TIM_RCC_APB1Periph_TIMX,ENABLE);
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = TIME_TIM_PERIOD;
	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_CK_CNT;//��Ƶϵ��71+1
		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		// �ظ���������ֵ��������ʱ��û�У����ù�
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
		// ����������жϱ�־λ
    TIM_ClearFlag(TIMX, TIM_FLAG_Update);
		// �����������ж�
    TIM_ITConfig(TIMX,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
		// ʹ�ܼ�����
    TIM_Cmd(TIMX, ENABLE);
		
		
	//Y��	
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    	TIM_RCC_APB1PeriphClockCmd(YTIM_RCC_APB1Periph_TIMX,ENABLE);
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = YTIME_TIM_PERIOD;
	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= YTIM_CK_CNT;//��Ƶϵ��71+1
		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		// �ظ���������ֵ��������ʱ��û�У����ù�
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(YTIMX, &TIM_TimeBaseStructure);
		// ����������жϱ�־λ
    TIM_ClearFlag(YTIMX, TIM_FLAG_Update);
		// �����������ж�
    TIM_ITConfig(YTIMX,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
		// ʹ�ܼ�����
    TIM_Cmd(YTIMX, ENABLE);	
		
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Config();
}



