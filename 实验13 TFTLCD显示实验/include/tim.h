#ifndef __TIM_H
#define __TIM_H
#include "stm32f10x.h"
//最大计数1ms
#define   TIME_TIM_PERIOD                                (1000-1)    //ARR
#define   TIM_CK_CNT                                      (72-1)      //PSC

#define   TIM_RCC_APB1Periph_TIMX                        RCC_APB1Periph_TIM6    
#define   TIM_RCC_APB1PeriphClockCmd                     RCC_APB1PeriphClockCmd
#define   TIMX                                           TIM6
#define   TIM_IRQ                                        TIM6_IRQn
#define   BASE_TIMX_IRQHandle                            TIM6_IRQHandler


//Y轴
#define   YTIME_TIM_PERIOD                                (1000-1)    //ARR
#define   YTIM_CK_CNT                                      (72-1)      //PSC
#define   YTIM_RCC_APB1Periph_TIMX                        RCC_APB1Periph_TIM7    
#define   YTIM_RCC_APB1PeriphClockCmd                     RCC_APB1PeriphClockCmd
#define   YTIMX                                           TIM7
#define   YTIM_IRQ                                        TIM7_IRQn
#define   YBASE_TIMX_IRQHandle                            TIM7_IRQHandler



void BASIC_TIM_Init(void);


#endif /*__TIM_H*/








