#ifndef __ANO_STICK_H__
#define __ANO_STICK_H__

#include "sysconfig.h"

extern uint8_t 	ANO_Stick_Mode;
extern uint8_t 	ANO_Stick_Check;
extern uint16_t ANO_STICK_YAW, ANO_STICK_THR, ANO_STICK_ROL, ANO_STICK_PIT;
extern int16_t  ANO_STICK_YAW_CAL, ANO_STICK_THR_CAL, ANO_STICK_ROL_CAL, ANO_STICK_PIT_CAL;
extern uint8_t 	ANO_KEY_VALUE;

void ANO_Stick_Init(void);
void ANO_Stick_Scan(void);

#endif
