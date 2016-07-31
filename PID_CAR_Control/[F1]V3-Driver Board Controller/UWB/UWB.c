/* Includes ------------------------------------------------------------------*/
#include "UWB.h"
#include "motor_pcb_interface.h"
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int16_t coordination[2];
static unsigned char RX_count = 0;	
static unsigned char Rx_Buffer[6];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void AnalyzeDataFromUWB(unsigned char ucData)
{
	int16_t temp;
	int16_t temp2;
	sendDataPID[2] = 0x0d;
	sendDataPID[3] = 0x0a;
	
	// save all 8 bits data in a 6*8=48 bits array
	Rx_Buffer[RX_count++] = ucData;
	
	if (Rx_Buffer[0] != 0x0D)  // wring data head, return
	{
		RX_count = 0;
		return;
	}
	
	if (RX_count != 6)  // have not meet 6 char, return  
			return;
	else
	{		
		if(Rx_Buffer[5] == 0x0a)
		{
			// combine the data to get two coordination
			coordination[0] = Rx_Buffer[1] << 8 | Rx_Buffer[2];
			coordination[1] = Rx_Buffer[3] << 8 | Rx_Buffer[4];
			
			/***************************************************  send in UART1  ************************************************/
			temp = coordination[0];
		  temp2 = coordination[0];
      sendDataPID[0] = ((temp2) >> 8) & 0xFF;
      sendDataPID[1] = temp & 0xFF;
	    My_Send_Data(USART1, sendDataPID, 4);
			/***********************************************************************************************************************/
			
			// reset
			RX_count = 0;
		}
		else
			return;
	}
}

int16_t* getCoordination(void)
{
	return coordination;
}
