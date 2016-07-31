/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_H
#define __ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "motor_pcb_interface.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//Encoder
#define ENCODER_LEFT_A											 GPIO_Pin_0
#define ENCODER_LEFT_A_Source					 GPIO_PinSource0
#define ENCODER_LEFT_A_Line							 EXTI_Line0
#define ENCODER_LEFT_A_IRQn						 EXTI0_IRQn

#define ENCODER_LEFT_B											 GPIO_Pin_1

#define ENCODER_RIGHT_A										 GPIO_Pin_2
#define ENCODER_RIGHT_A_Source				 GPIO_PinSource2
#define ENCODER_RIGHT_A_Line						 EXTI_Line2
#define ENCODER_RIGHT_A_IRQn					 EXTI2_IRQn

#define ENCODER_RIGHT_B										 GPIO_Pin_3

#define ENCODER_GPIO												   GPIOB
#define ENCODER_PORT_SOURCE					 GPIO_PortSourceGPIOB

/* Exported functions ------------------------------------------------------- */

#endif /* __ENCODER_H */
