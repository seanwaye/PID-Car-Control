/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Drv_LED.cpp
 * 描述    ：LED
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Drv_LED.h"

void ANO_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*使能SWD 禁用JTAG*/
	RCC_APB2PeriphClockCmd(ANO_RCC_LED_0,ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED_0;
	GPIO_Init(ANO_GPIO_LED_0, &GPIO_InitStructure);
}

void ANO_LED_0_ON(void)
{
	GPIO_ResetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);	
}

void ANO_LED_0_OFF(void)
{
	GPIO_SetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);			
}

void ANO_LED_0_FLASH(void)
{
	ANO_LED_0_ON();
	Delay(300000);
	ANO_LED_0_OFF();
	Delay(300000);
	ANO_LED_0_ON();
	Delay(300000);
	ANO_LED_0_OFF();
	Delay(300000);
	ANO_LED_0_ON();
	Delay(300000);
	ANO_LED_0_OFF();
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

