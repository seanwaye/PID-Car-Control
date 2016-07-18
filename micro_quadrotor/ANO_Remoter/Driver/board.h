#ifndef __BOARD_H__
#define __BOARD_H__
#include "stm32f10x.h"
#include "ANO_Drv_Uart.h"
#include "ANO_Drv_Uart3.h"
#include "ANO_Drv_SPI.h"
#include "ANO_Drv_Nrf24l01.h"
#include "ANO_Drv_LED.h"
#include "ANO_Drv_hid.h"
#include "ANO_Drv_ADC.h"
#include "ANO_Drv_Oled.h"
#include "ANO_DT.h"

//#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */

#define HW_TYPE	1
#define HW_VER	3
#define BL_VER	100
#define PT_VER	400
/***************LED GPIO定义******************/
#define ANO_RCC_LED_0					RCC_APB2Periph_GPIOB
#define ANO_GPIO_LED_0				GPIOB
#define ANO_Pin_LED_0					GPIO_Pin_8
/*********************************************/
/***************I2C GPIO定义******************/
#define ANO_GPIO_I2C	GPIOB
#define I2C_Pin_SCL		GPIO_Pin_6
#define I2C_Pin_SDA		GPIO_Pin_7
#define ANO_RCC_I2C		RCC_APB2Periph_GPIOB
/*********************************************/
/***************UART1 GPIO定义******************/
#define ANO_RCC_UART1			RCC_APB2Periph_GPIOA
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
#define NVIC_UART_P	5
#define NVIC_UART_S	1
/***********************************************/

//任务时基计数变量
extern uint16_t S_cnt_1ms,S_cnt_2ms,S_cnt_5ms,S_cnt_10ms,S_cnt_20ms,S_cnt_30ms,S_cnt_1000ms;

void Delay(vu32 nCount);
void cycleCounterInit(void);
void SysTick_IRQ(void);

#endif 
