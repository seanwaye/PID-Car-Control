/************************ (C) COPYRIGHT 2016 *******************************
 * 文件名  ：ANO_Drv_LED.cpp
 * 描述    ：LED驱动函数
**********************************************************************************/
#include "ANO_Drv_LED.h"
#include "ANO_RC.h"

// LED_0 初始化
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

void ANO_LED_0_OFF(void)
{
	//GPIO_ResetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);	
	ANO_GPIO_LED_0->BRR = ANO_Pin_LED_0;
}

void ANO_LED_0_ON(void)
{
	//GPIO_SetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);	
	ANO_GPIO_LED_0->BSRR = ANO_Pin_LED_0;	
}

u16 led_accuracy = 20;//该时间应与LED_Duty()调用周期相同
float on_time;

void LED_1ms_DRV()
{
	static u16 led_cnt;
	
	if(led_cnt < on_time)
		ANO_LED_0_ON();
	else
		ANO_LED_0_OFF();
	
	if(++led_cnt >= led_accuracy)
		led_cnt = 0;
}

//亮-灭 为一组
void LED_Dyty(float dT)
{
	if(!fly_ready)
		led_breath(dT,1500); // 呼吸灯
	else
		led_flash(dT,2,100,100,500);//调用周期（s），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
}

void led_breath(float dT,u16 T)// 一次半程的时间，单位ms
{
	static u8 dir;
	switch(dir)
	{
		case 0: on_time += safe_div(led_accuracy,(T/(dT*1000)));
								if(on_time>20)
								{
										dir = 1;
								}
								break;
		case 1: on_time -= safe_div(led_accuracy,(T/(dT*1000)));
						    if(on_time<0)
								{
										dir = 0;
								}
								break;
			
		default: dir = 0;
								break;
	}
}

//亮-灭 为一组
//调用周期（s），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
void led_flash(float dT,u16 group_n,u16 on_ms,u16 off_ms,u16 group_dT_ms)
{
	static u16 ms_cnt;
	static u16 group_n_cnt;
	
	if(group_n_cnt < group_n)   //组数没到
	{
		if(ms_cnt<on_ms)
		{
			on_time = 20;
		}
		else if(ms_cnt<(on_ms+off_ms))
		{
			on_time = 0;
		}
		if(ms_cnt>=(on_ms+off_ms))
		{
			group_n_cnt ++;
			ms_cnt = 0;
		}
	}
	else						//进入组间隔
	{
		if(ms_cnt<group_dT_ms)
		{
			on_time = 0;
		}
		else
		{
			group_n_cnt = 0;
			ms_cnt = 0;
		}
	}
	
	ms_cnt += (dT*1000);        //计时

}
/******** *****END OF FILE************/

