#ifndef __ANO_RC_H
#define __ANO_RC_H

#include "stm32f10x.h"
#include "include.h"

extern u8 fly_ready,NS;
extern u16 RX_CH[CH_NUM];  // 全局接收数组
extern s16 CH_N[];                 // 全局执行数组

void RC_duty(float dT);
void fail_safe_check(void);
	
#endif

