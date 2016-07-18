#ifndef __ANO_DRV_LED_H__
#define __ANO_DRV_LED_H__

#include "include.h"

void ANO_LED_Init(void);
void ANO_LED_0_ON(void);
void ANO_LED_0_OFF(void);

void LED_1ms_DRV(void);
void LED_Dyty(float );
void led_breath(float,u16 T);
void led_flash(float dT,u16 group_n,u16 on_ms,u16 off_ms,u16 group_dT_ms);
#endif

