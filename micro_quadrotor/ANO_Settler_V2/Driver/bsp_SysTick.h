#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void cycleCounterInit(void);
void SysTick_IRQ(void);

void Delay(vu32);
void Delay_us(__IO u32 nTime);
void Delay_ms(__IO u32 nTime);	 //单位ms

uint32_t GetSysTime_us(void);

extern volatile uint32_t sysTickUptime;
#endif /* __SYSTICK_H */
