#ifndef __PORT_H
#define __PORT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//For Systick
#ifdef CLOCKS_PER_SEC
	#undef CLOCKS_PER_SEC
#endif
#define CLOCKS_PER_SEC					1000

/* Exported functions ------------------------------------------------------- */
void Our_Sys_Init(void);

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif
