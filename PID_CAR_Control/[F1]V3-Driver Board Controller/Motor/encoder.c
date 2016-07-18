/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_SPEED_COUNTER 1000 //When duty cyle = 100%, the encoder's counter value is saved there.

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO u16 leftCounter = 0;
__IO u16 rightCounter = 0;
__IO u16 saveLeftCounter = 0;
__IO u16 saveRightCounter = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
u16 Get_Speed(u8 left_or_right)
{
	u16 speed;
	// the data of encoder id larger than 1000, so we use %1000
	if(left_or_right == 0) //Select left motor.
	{
		speed = saveLeftCounter;
	}
	else //Select right motor.
	{
		speed = saveRightCounter;
	}
	speed = speed > 1000 ? 1000 : speed;
	return speed;
}

void Encoder_EXTI_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// initial the GPIO pin 
	GPIO_InitStructure.GPIO_Pin = ENCODER_LEFT_A | ENCODER_LEFT_B | ENCODER_RIGHT_A | ENCODER_RIGHT_B;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(ENCODER_GPIO, &GPIO_InitStructure);
	
	/* Connect EXTI0 Line to PA.00 pin */
  GPIO_EXTILineConfig(ENCODER_PORT_SOURCE, ENCODER_LEFT_A_Source);
	GPIO_EXTILineConfig(ENCODER_PORT_SOURCE, ENCODER_RIGHT_A_Source);
	
	EXTI_InitStructure.EXTI_Line = ENCODER_LEFT_A_Line;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = ENCODER_RIGHT_A_Line;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_LEFT_A_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_RIGHT_A_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void) //左编码器
{
	//InputSpeedPhase_L = (GPIO_ReadInputData(GPIOA) & 0x03); //0000 0011
  EXTI_ClearFlag(EXTI_Line0);
  EXTI_ClearITPendingBit(EXTI_Line0);
	leftCounter++;
}

void EXTI2_IRQHandler(void) //右编码器
{
	//InputSpeedPhase_R = (GPIO_ReadInputData(GPIOA) & 0x0C); //0000 1100
  EXTI_ClearFlag(EXTI_Line2);
  EXTI_ClearITPendingBit(EXTI_Line2);
	rightCounter++;
}

void Sampling_Tick_Speed(void) //每30ms被调用一次
{
	saveLeftCounter = leftCounter;
	saveRightCounter = rightCounter;
	leftCounter = 0;
	rightCounter = 0;
}
