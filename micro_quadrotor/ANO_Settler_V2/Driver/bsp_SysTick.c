/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：bsp_SysTick.c
 * 描述    ：滴答时钟
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
*****************************************************************************/
#include "include.h"
#include "time.h"
#include "loop.h"
// 	//初始化系统滴答定时器
// 	cycleCounterInit();
// 	SysTick_Config(SystemCoreClock / 1000);	
	
// cycles per microsecond
volatile uint32_t usTicks = 0;
// 滴答定时器计数变量 ,49天后溢出
volatile uint32_t sysTickUptime = 0;

void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

void SysTick_IRQ(void)
{
	sysTickUptime++;
	Loop_check();
	sys_time();
}

uint32_t GetSysTime_us(void) //两次获取若大于u32/1000(us),则两次差值溢出，不可取
{
    register uint32_t ms, cycle_cnt;
    do {
        ms = sysTickUptime;
        cycle_cnt = SysTick->VAL;
    } while (ms != sysTickUptime);
    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void Delay_us(__IO u32 nTime)
{ 
	u32 now;
	now = GetSysTime_us();
	while(GetSysTime_us()-now<nTime);
}

void Delay_ms(__IO u32 nTime)
{ 
  u16 i ;
	for(i=0;i<nTime;i++)
	{
		Delay_us(1000);
	}
}

void Delay(vu32 nCount)
{
  for(; nCount!= 0;nCount--);
}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/


