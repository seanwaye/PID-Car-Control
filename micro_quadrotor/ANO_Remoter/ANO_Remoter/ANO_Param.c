/**************************  (C) COPYRIGHT 2016  ******************************
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
**************************************************************************************/
#include "ANO_Param.h"
#include "ANO_Stick.h"
#include "ANO_Drv_MPU6050.h"

#define FIRSTINITFLAH  			0x44

struct param ANO_Param;

void ANO_Param_Init(void)//恢复默认参数
{
	ANO_Param.FirstInitFlag = FIRSTINITFLAH;
	ANO_Param.StickCal_Rol = 0;
	ANO_Param.StickCal_Pit = 0;
	ANO_Param.StickCal_Yaw = 0;
	ANO_Param.StickCal_Thr = 0;
	
	ANO_Flash_Write((u8 *)(&ANO_Param),sizeof(ANO_Param));
}

void ANO_Param_SAVE(void)
{
	ANO_Param.FirstInitFlag = FIRSTINITFLAH;
	ANO_Param.StickCal_Rol = (s16)ANO_STICK_ROL_CAL;
	ANO_Param.StickCal_Pit = (s16)ANO_STICK_PIT_CAL;
	ANO_Param.StickCal_Yaw = (s16)ANO_STICK_YAW_CAL;
	ANO_Param.StickCal_Thr = (s16)ANO_STICK_THR_CAL;
	
	ANO_Flash_Write((u8 *)(&ANO_Param),sizeof(ANO_Param));
}

void ANO_Param_READ(void)
{
	ANO_Flash_Read((u8 *)(&ANO_Param),sizeof(ANO_Param));
	if(ANO_Param.FirstInitFlag != FIRSTINITFLAH)//板子从未初始化
	{
		ANO_Param_Init();
	}
	if(ANO_Param.FirstInitFlag != FIRSTINITFLAH)//板子从未初始化
	{
		while(1);
	}
	ANO_STICK_ROL_CAL = (s16)ANO_Param.StickCal_Rol;
	ANO_STICK_PIT_CAL = (s16)ANO_Param.StickCal_Pit;
	ANO_STICK_YAW_CAL = (s16)ANO_Param.StickCal_Yaw;
	ANO_STICK_THR_CAL = (s16)ANO_Param.StickCal_Thr;
}
