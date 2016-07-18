#ifndef _include_H_
#define _include_H_

#include "ANO_Data.h"

#include "stm32f10x.h"
#include "mymath.h"

#include "ANO_Drv_Uart.h"
#include "ANO_Drv_Uart3.h"
#include "ANO_Drv_SPI.h"
#include "ANO_Drv_Nrf24l01.h"
#include "ANO_Drv_LED.h"
#include "ANO_Drv_hid.h"
#include "ANO_Drv_ADC.h"

#include "bsp_SysTick.h"

//#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */

#define HW_TYPE	1
#define HW_VER	3
#define BL_VER	100
#define PT_VER	400

/***************LED GPIO定义******************/
#define ANO_RCC_LED_0				RCC_APB2Periph_GPIOB
#define ANO_GPIO_LED_0				GPIOB
#define ANO_Pin_LED_0				GPIO_Pin_8
/*********************************************/

/***************UART1 GPIO定义******************/
#define ANO_RCC_UART1		RCC_APB2Periph_GPIOA
#define ANO_GPIO_UART1		GPIOA
#define ANO_UART1_Pin_TX	GPIO_Pin_9
#define ANO_UART1_Pin_RX	GPIO_Pin_10
/*********************************************/
/***************SPI GPIO定义******************/
#define ANO_GPIO_SPI		GPIOB
#define ANO_GPIO_CE			GPIOA
#define RCC_GPIO_SPI		RCC_APB2Periph_GPIOB
#define SPI_Pin_CSN			GPIO_Pin_12
#define SPI_Pin_SCK			GPIO_Pin_13
#define SPI_Pin_MISO		GPIO_Pin_14
#define SPI_Pin_MOSI		GPIO_Pin_15
/*********************************************/
/***************硬件中断优先级******************/
#define NVIC_UART_P	3
#define NVIC_UART_S	1
/***********************************************/

// 6轴枚举类型
enum
{
 A_X = 0,  // 加速度
 A_Y ,
 A_Z ,
 G_Y ,      // 速度
 G_X ,
 G_Z ,
 TEM ,
 ITEMS ,
};

// CH_filter[],0横滚，1俯仰，2油门，3航向		
enum
{
 ROL= 0,
 PIT ,
 THR ,
 YAW ,
 AUX1 ,
 AUX2 ,
 AUX3 ,
 AUX4 ,
// AUX5 ,
// AUX6 ,
// AUX7 ,
// AUX8 ,
// AUX9 ,
// AUX10 ,
// AUX11 ,
// AUX12 ,
 CH_NUM,
};

enum
{
	m1=0,
	m2,
	m3,
	m4,
	m5,
	m6,
	m7,
	m8,
};

enum
{
	MPU_6050_0 = 0,
	MPU_6050_1,
};
#endif


