/**
  ******************************************************************************
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "motor_pcb_interface.h"

/* Private typedef-----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static u8 LEFT_DIREC = 0;
static u8 RIGHT_DIREC = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Motor_If_Forward(u8 left_or_right, u8 if_forward)
{
	if(left_or_right == 0) //select left motor
	{
		if(if_forward) //forward
		{
			GPIO_SetBits(SIGNAL_GPIO, PHASE_PIN_LEFT);
			GPIO_ResetBits(SIGNAL_GPIO, PHASE_PIN_LEFT_2);
			LEFT_DIREC = 1;
		}
		else //backward
		{
			GPIO_ResetBits(SIGNAL_GPIO, PHASE_PIN_LEFT);
			GPIO_SetBits(SIGNAL_GPIO, PHASE_PIN_LEFT_2);
			LEFT_DIREC = 0;
		}
	}
	
	else //select right motor
	{
		if(if_forward) //forward
		{
			GPIO_SetBits(SIGNAL_GPIO, PHASE_PIN_RIGHT);
			GPIO_ResetBits(SIGNAL_GPIO, PHASE_PIN_RIGHT_2);
			RIGHT_DIREC = 1;
		}
		else //backward
		{
			GPIO_ResetBits(SIGNAL_GPIO, PHASE_PIN_RIGHT);
			GPIO_SetBits(SIGNAL_GPIO, PHASE_PIN_RIGHT_2);
			RIGHT_DIREC = 0;
		}
	}
}

u8 Motor_Get_Direc(u8 left_or_right)
{
	return (left_or_right == 0) ? LEFT_DIREC : RIGHT_DIREC;
}

void Motor_Toggle_Direc(u8 left_or_right)
{
	static u8 temp = 0;
	temp = Motor_Get_Direc(left_or_right);
	temp = (temp == 0) ? 1 : 0;
	Motor_If_Forward(left_or_right, temp);
}

void Motor_Set_Speed(u8 left_or_right, u16 speed)
{
	static TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	speed = speed > 1000 ? 1000 : speed;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			
		
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		
	TIM_OCInitStructure.TIM_Pulse = speed;	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;		
	
	if(left_or_right == 0) //select left motor
		TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);
	
	else //select right motor
		TIM_OC2Init(PWM_TIM, &TIM_OCInitStructure);
}
