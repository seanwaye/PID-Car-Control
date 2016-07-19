#ifndef __ANO_PARAM_H
#define __ANO_PARAM_H

#include "stm32f10x.h"
#include "ANO_Drv_Flash.h"

struct param{
	uint16_t FirstInitFlag;
	uint16_t StickCal_Rol;
	uint16_t StickCal_Pit;    
	uint16_t StickCal_Thr;    // смце
	uint16_t StickCal_Yaw;
};
extern struct param ANO_Param;

void ANO_Param_READ(void);
void ANO_Param_SAVE(void);

#endif

