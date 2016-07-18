/************************************************************************************************/
// 数据发送函数
/************************************************************************************************/
#include "ANO_DT.h"

// 最多可以将一个4字节的变量拆分
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
	
// buffer
u8 data_to_send[50];
int16_t PLANE_YAW, PLANE_ROL, PLANE_PIT;

void ANO_DT_Send_Data(u8 *dataToSend , u8 length)
{
	ANO_NRF_TxPacket_AP(dataToSend,length);
}

void ANO_DT_Send_RCData(void)
{
	u8 _cnt=0;
	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xAF;
	data_to_send[_cnt++] = 0x03;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = BYTE1(ANO_STICK_THR);
	data_to_send[_cnt++] = BYTE0(ANO_STICK_THR);
	data_to_send[_cnt++] = BYTE1(ANO_STICK_YAW);
	data_to_send[_cnt++] = BYTE0(ANO_STICK_YAW);
	data_to_send[_cnt++] = BYTE1(ANO_STICK_ROL);
	data_to_send[_cnt++] = BYTE0(ANO_STICK_ROL);
	data_to_send[_cnt++] = BYTE1(ANO_STICK_PIT);
	data_to_send[_cnt++] = BYTE0(ANO_STICK_PIT);
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	
	data_to_send[3] = _cnt-4;
	
	u8 sum = 0;
	for(u8 i = 0;i < _cnt; i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++] = sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}

void ANO_DT_NrfData_Anl(u8 *data_buf , u8 num)
{
	u8 sum = 0;
	
	for(u8 i = 0;i < (num-1);i++)
		sum += *(data_buf+i);
	if(!(sum == *(data_buf+num-1)))		return;		//判断sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAA))		return;		//判断帧头
	
	if(*(data_buf+2)==0X01)
	{
		PLANE_ROL = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		PLANE_PIT = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		PLANE_YAW = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
	}
}

