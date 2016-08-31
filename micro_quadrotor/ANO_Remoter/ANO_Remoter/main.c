/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sysconfig.h"
#include "ANO_Param.h"
#include "ANO_Drv_Flash.h"
uint8_t 	NRF_ENABLE = 0;
uint8_t 	UART1_ENABLE = 0;

int main(void)
{
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//初始化USB
	USB_HID_Init();
	
	//初始化LED
	ANO_LED_Init();
	ANO_LED_0_FLASH();
	
	//初始化系统滴答定时器
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	
	
	//初始化NRF所用SPI
	ANO_SPI_Init();
	//检查NRF连接是否正常
	NRF_ENABLE = ANO_NRF_Check();
	//如果连接正常，则将NRF初始化为RX2模式（高级接收）
	if(NRF_ENABLE)
		ANO_NRF_Init(MODEL_RX2,80);

	//初始化ADC采样
	ADC1_Init();
	
	//摇杆值初始化
	ANO_Stick_Init();
	
	//OLED液晶初始化
	OLED_Init();
	
	//参数初始化
	ANO_Param_READ();
	
	while (1)
	{			 
		ANO_Loop();
	}
}
