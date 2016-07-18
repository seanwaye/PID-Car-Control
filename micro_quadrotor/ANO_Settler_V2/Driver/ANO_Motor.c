/********************** (C) COPYRIGHT 2016  *****************************
 * 文件名  ：ANO_Motor.c
 * 描述    ：电机pwm输出
*****************************************************************************/
#include "ANO_Motor.h"
#include "mymath.h"

#define ACCURACY 1000 //0.001

void pwm_out_init()
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  				TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_OCStructInit(&TIM_OCInitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	uint16_t PrescalerValue = 0;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / (24000*ACCURACY)) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;		//
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//pwm时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

}

void motor_out(s16 pwm[MOTOR_NUM])
{
	u8 i;
	for(i=0;i<MOTOR_NUM;i++)
	{
		pwm[i] = LIMIT(pwm[i],0,1000);
	}
	
	TIM2->CCR1 = (u16)pwm[0] ; 
	TIM2->CCR2 = (u16)pwm[1] ;	
	TIM2->CCR3 = (u16)pwm[2] ; 
	TIM2->CCR4 = (u16)pwm[3] ;

}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/



