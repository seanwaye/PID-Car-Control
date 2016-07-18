#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"


void Encoder_Init(void);

extern int Car_Speed;
extern float Car_Angle; 
extern uint8_t Start_Due;
extern int32_t zero ;   

#endif