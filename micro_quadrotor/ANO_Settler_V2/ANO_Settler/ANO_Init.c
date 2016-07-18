/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Init.c
 * 描述    ：初始化函数
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
*****************************************************************************/
#include "ANO_Init.h"
#include "ANO_Drv_MPU6050.h"
#include "i2c_soft.h"
#include "ANO_Drv_Hid.h"
#include "ANO_Param.h"
#include "ANO_Motor.h"
#include "ANO_CTRL.h"

u8 NRF_ENABLE;
void sys_init()
{
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//初始化USB
	USB_HID_Init();
	
	//初始化系统滴答定时器
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	
	
	//i2c初始化
	I2c_Soft_Init();
	
	//初始化SPI
	ANO_SPI_Init();
	//检查NRF连接是否正常
	NRF_ENABLE = ANO_NRF_Check();
	//如果连接正常，则将NRF初始化为TX2模式（高级发送）
	if(NRF_ENABLE)
	{
		ANO_NRF_Init(MODEL_TX2,80);
	}
	
	#ifdef ANO_DT_USE_WIFI
	ANO_UART3_Init(500000);
	#endif
	
	Delay_ms(100);
	
	MPU6050_Init(20);
	
	Delay_ms(200);
	
	//参数初始化
	ANO_Param_Read();
	
	//电机输出初始化
	pwm_out_init();
	
	//pid参数初始化
	pid_init();
	
	//led初始化
	ANO_LED_Init();
}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/


