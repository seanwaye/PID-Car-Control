#include "encoder_timer.h"
#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_it.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "delay.h"



//Omron Encoder counts for 4000 per spin
#define Startup
//#define angle_CNT   10000  //???????

int Car_Speed = 0;
float Car_Angle = 0; 
uint8_t Start_Due = 0;
int32_t zero = 0;   //?????,???????????
uint8_t Angle_Target_Interrupt = 100;   //??????????

void TIM3_Init()    //????
{

	//u16 CCR1_Val = 2500;
	//u16 CCR2_Val = 1000;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;

	/*----------------------------------------------------------------*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	GPIO_StructInit(&GPIO_InitStructure);
	/* Configure PA.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*----------------------------------------------------------------*/	


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //??TIM3
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period =8000;       //???????????????????
	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //?????:
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//????????:???
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //??????
	//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*???TIM3??? */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/*-----------------------------------------------------------------*/
	//????                        ????
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
	                         TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising?????
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 1;         //?????
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //????
	//Reset counter
	TIM3->CNT =0;


	TIM_Cmd(TIM3, ENABLE);   //?????3



}

void TIM2_Init()   //????
{
	

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure; 

	/*----------------------------------------------------------------*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	GPIO_StructInit(&GPIO_InitStructure);
	/* Configure PA.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*----------------------------------------------------------------*/	


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //??TIM3
	TIM_DeInit(TIM2);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period =4000;       
	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //?????:
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//????????:???
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //??????
	//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*???TIM3??? */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/*-----------------------------------------------------------------*/
	//????                        ????
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, 
	                         TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising?????
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 1;         //?????
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
   
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; 
	TIM_OCInitStructure.TIM_Pulse = Angle_Target_Interrupt;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);//?? TIM_CCR1 ?????????
	TIM_ITConfig(TIM2, TIM_IT_CC3, DISABLE);//???? TIM_Cmd(TIM2, ENABLE); //?????(??? CEN ?)




	// TIM_OCStructInit(&TIM_OCInitStructure);       //?????????????
	// TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	// TIM_OCInitStructure.TIM_Pulse = Angle_Target_Interrupt;
	// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	// TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
	// TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);

	TIM_ClearFlag(TIM2, TIM_FLAG_CC3);
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);   //????
	//Reset counter
	TIM2->CNT = 0;   


	TIM_Cmd(TIM2, ENABLE);   //?????3

	/* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   
}

void EXTI4_Encoder_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef exti;  
    NVIC_InitTypeDef NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);            //??IO????   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //????IO???????                                                   
    //GPIO??????  A
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;  
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;      //????????  
    GPIO_Init(GPIOA,&GPIO_InitStructure);  
              
    //GPIO???????????  
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);  
      
    //exti??  
    exti.EXTI_Line = EXTI_Line4;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;            //????????????  
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC??????  
    NVIC_exti.NVIC_IRQChannel = EXTI4_IRQn;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;         //??????2  
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;            //?????2  
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI4_IRQHandler(void)
{
	//USART1_printf(USART2, "%d\r\n",TIM2->CNT);
	//?????????????  (?????????????,?????????)
	#ifdef Startup
	if (!Start_Due)
	{
		zero = TIM2->CNT; 
		Car_Turn(0); 
		SysTick_Init(72); 
		Start_Due = 1;
		Delay(0xF);
		Car_Turn_Angle(0);   //???
	}
	else
	{
		TIM2 -> CNT = zero;   //???0,?????????
	}
	#endif 

	#ifndef Startup
	//TIM2 -> CNT = zero;    //????
	#endif

	EXTI_ClearITPendingBit(EXTI_Line4);
}



void Encoder_Init(void){
	TIM3_Init();
	TIM2_Init();
	EXTI4_Encoder_Init();
}