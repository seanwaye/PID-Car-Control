#ifndef _ANO_MOTOR_H
#define	_ANO_MOTOR_H

#include "stm32f10x.h"
#include "ANO_Config.h"
void pwm_out_init(void);
void motor_out(s16 pwm[]);

#endif



