/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "port.h"
#include "motor_pcb_interface.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
static u8 encoderCounter = 0;
static u16 motorControlCounter = 0;
void SysTick_Handler(void)
{
	motorControlCounter++;
	encoderCounter++;
	
	// get the encoder number
	if(encoderCounter == 30) //Sampling speed in each 30 ms.
	{
		encoderCounter = 0;
		Sampling_Tick_Speed();
	}
	
	// set the motor speed
	if(motorControlCounter == 70)
	{
		motorControlCounter = 0;
		// after get current speed, we can calculate the PID parameters and control the motor
		MotorSpeedPID(returnSpeed());
	}
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles USART1 Handler. For PID
	*             Get current speed from the encoder
  * @param  None
  * @retval None
  */
static int uartCounter = 0;
static u8 pointer = 0;
void USART1_IRQHandler(void)
{
	static int16_t motorDifference = 0;
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
			uint16_t temp;
		  // inilazition of the data to be snet ending
			sendDataPID[2] = 0x0d;
			sendDataPID[3] = 0x0a;
			uartCounter++;
			if(uartCounter == 500)
			{
				// the speed differnece between two wheel
				// left - right
				//motorDifference = Get_Speed(0) - Get_Speed(1);
				
				// send the difference	of  angle
				/***************************************************************************************************************************/
				
				/*motorDifference = Inertia_Get_Angle_Yaw();
				
					if(motorDifference > 0)
							motorDifference = motorDifference % 360;
					else
							motorDifference = (360 + motorDifference) % 360;
				*/
				motorDifference = returnAngle();
				
				/****************************************************************************************************************************/
	
				uartCounter = 0;
				temp = motorDifference;
				sendDataPID[0] = ((motorDifference) >> 8) & 0xFF;
				sendDataPID[1] = temp & 0xFF;
				
				// sned a 5 length messgae
				if(pointer == 4)
					pointer = 0;
				USART_SendData(USART1, sendDataPID[pointer]);
				pointer++;
			}
	}
}

/**
  * @brief  This function handles USART1 Handler. For JY901.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{	
		u8 tmp = USART_ReceiveData(USART2);
		ParseSerialData(tmp);
	}
}	

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
