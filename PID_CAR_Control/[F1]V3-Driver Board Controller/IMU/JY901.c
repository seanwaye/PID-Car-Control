/**
  ******************************************************************************
  * JY-901代码
  ******************************************************************************
  */
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
		sum+=temp_Angle[j];
		if (max < temp_Angle[j])
			max = temp_Angle[j];
		if (min > temp_Angle[j])
			min = temp_Angle[j];
	}
	return ((sum - max - min)*60/32768);
}

void ParseSerialData(unsigned char ucData)
{
	static unsigned char ucRxCnt = 0;	
	static unsigned char ucRxBuffer[12];
	
	ucRxBuffer[ucRxCnt++]=ucData;
	
	if (ucRxBuffer[0]!=0x55)  //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	
	if (ucRxCnt<11) {return;} //数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])
		{
			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
			case 0x50:	memcpy(&stcTime, &ucRxBuffer[2], 8); break;			//时间
			case 0x51:	memcpy(&stcAcc, &ucRxBuffer[2], 8); break;			//加速度
			case 0x52:	memcpy(&stcGyro, &ucRxBuffer[2], 8); break;			//角速度								
			case 0x53:	memcpy(&stcAngle, &ucRxBuffer[2], 8);						//角度
									sAngle = Calculate_Angle(); break;
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
	}
}

int16_t Inertia_Get_Angle_Yaw(void)
{
	return (int16_t)sAngle;
}
