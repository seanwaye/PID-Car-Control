/* Includes ------------------------------------------------------------------*/
#include "JY901.h"
#include "motor_pcb_interface.h"
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct STime		   stcTime;
struct SAcc 		   stcAcc;
struct SGyro 		 stcGyro;
struct SAngle 	   stcAngle;
struct SMag 		   stcMag;
struct SDStatus  stcDStatus;
struct SPress 	   stcPress;
struct SLonLat 	 stcLonLat;
struct SGPSV 	 stcGPSV;
struct SQuat		   stcQuat;
float sAngle        = 0;
short temp_Angle[5] = {0}, i = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
float Calculate_Angle()
{
	float sum = 0;
	short max = 0x8000, min = 0x7fff, j;
	temp_Angle[i++] = stcAngle.Angle[2];
//	short temp_angle = 0;
//	temp_angle = stcAngle.Angle[2] * 1.0 / 1.0;
//	sum += temp_angle;
	i %= 5;
	for (j = 0; j < 5; j++)
	{
		sum += temp_Angle[j];
		if (max < temp_Angle[j])
			max = temp_Angle[j];
		if (min > temp_Angle[j])
			min = temp_Angle[j];
	}
	return ((sum - max - min)*60/32768);
}

float Calculate_Angle_2()
{
	float sum_sin = 0;
	float sum_cos = 0;
	float angle = 0;
	short j=0;
	temp_Angle[i++] = stcAngle.Angle[2];
	i %= 5;
	if(temp_Angle[4] == 0)
	{
		return 0;
	}
	for(j=0; j<5; j++)
	{
		angle =  (float)temp_Angle[j]*3.1415926/32768;
	//	angle = temp_Angle[j]*3.1415926/32768;
		sum_sin += sin(angle);
		sum_cos += cos(angle);
	}
	return atan2(sum_sin/5, sum_cos/5) * 180/3.1415926;
}

void ParseSerialData(unsigned char ucData)
{
	static unsigned char ucRxCnt = 0;	
	static unsigned char ucRxBuffer[12];
	int16_t temp;
	int16_t temp2;
	sendDataPID[2] = 0x0d;
	sendDataPID[3] = 0x0a;
	
	ucRxBuffer[ucRxCnt++] = ucData;
	
	if (ucRxBuffer[0] != 0x55)  //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	
	if (ucRxCnt < 11) {return;} //数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])
		{
			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
			case 0x50:	memcpy(&stcTime, &ucRxBuffer[2], 8); break;			//时间
			case 0x51:	memcpy(&stcAcc, &ucRxBuffer[2], 8); break;			//加速度
			case 0x52:	memcpy(&stcGyro, &ucRxBuffer[2], 8); break;			//角速度								
			case 0x53:	memcpy(&stcAngle, &ucRxBuffer[2], 8);						//角度
									sAngle = Calculate_Angle_2(); break;
									//sAngle = (float)(stcAngle.Angle[2] * 2.0 / 2.0); break;
			case 0x54:	memcpy(&stcMag, &ucRxBuffer[2], 8); break;			//磁场
			case 0x55:	memcpy(&stcDStatus, &ucRxBuffer[2], 8); break;	//端口状态数据
			case 0x56:	memcpy(&stcPress, &ucRxBuffer[2], 8); break;		//气压
			case 0x57:	memcpy(&stcLonLat, &ucRxBuffer[2], 8); break;		//经纬度
			case 0x58:	memcpy(&stcGPSV, &ucRxBuffer[2], 8); break;			//地速
			case 0x59:	memcpy(&stcQuat, &ucRxBuffer[2], 8); break;			//四元数
			default:	break;
		}
		ucRxCnt=0;
		temp = sAngle;
		temp2 = sAngle;
    sendDataPID[0] = ((temp2) >> 8) & 0xFF;
    sendDataPID[1] = temp & 0xFF;
	  My_Send_Data(USART1, sendDataPID, 4);
	}
}

void My_Send_Data(USART_TypeDef* USARTx, u8 *data, u16 length)
{
	static u8 i;
	
	for(i = 0; i < length; i++)
	{
		USART_SendData(USARTx, data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	}
}

int16_t Inertia_Get_Angle_Yaw(void)
{
	return (int16_t)sAngle;
}
