#include "board.h"

static volatile uint32_t usTicks = 0;
// 滴答定时器计数变量 ,49天后溢出
static volatile uint32_t sysTickUptime = 0;

void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

void Delay(vu32 nCount)
{
	for(; nCount!= 0;nCount--);
}

// SysTick 调用，任务调度计时全部加1ms
void SysTick_IRQ(void)
{
	sysTickUptime++;
	S_cnt_1ms++;
	S_cnt_2ms++;
	S_cnt_5ms++;
	S_cnt_10ms++;
	S_cnt_20ms++;
	S_cnt_30ms++;
	S_cnt_1000ms++;
}

