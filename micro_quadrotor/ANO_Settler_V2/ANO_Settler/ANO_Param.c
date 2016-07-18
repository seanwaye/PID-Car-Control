/***************************** (C) COPYRIGHT 2016 *****************************
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
**************************************************************************************/
#include "ANO_Param.h"
#include "ANO_Drv_MPU6050.h"
#include "ANO_CTRL.h"

struct _save_param_st_pk ANO_Param;

void ANO_Param_Init()
{
	ANO_Param.firstintiflag = FIRST_INIT_FLAG;
	ANO_Param.hardware = 200;
	ANO_Param.software = 100;
	
	ANO_Param.PID_rol.kp = 1000;
	ANO_Param.PID_rol.ki = 1000;
	ANO_Param.PID_rol.kd = 1000;

	ANO_Param.PID_pit.kp = 1000;
	ANO_Param.PID_pit.ki = 1000;
	ANO_Param.PID_pit.kd = 1000;
	
	ANO_Param.PID_yaw.kp = 1000;
	ANO_Param.PID_yaw.ki = 1000;
	ANO_Param.PID_yaw.kd = 1000;
	
	ANO_Param.PID_rol_s.kp = 1000;
	ANO_Param.PID_rol_s.ki = 1000;
	ANO_Param.PID_rol_s.kd = 1000;
	
	ANO_Param.PID_pit_s.kp = 1000;
	ANO_Param.PID_pit_s.ki = 1000;
	ANO_Param.PID_pit_s.kd = 1000;
	
	ANO_Param.PID_yaw_s.kp = 1000;
	ANO_Param.PID_yaw_s.ki = 1000;
	ANO_Param.PID_yaw_s.kd = 1000;
	
	ANO_Param.PID_hs.kp = 1000;
	ANO_Param.PID_hs.ki = 1000;
	ANO_Param.PID_hs.kd = 1000;

	ANO_Param_Save();
}

void ANO_Param_Read(void)
{
	ANO_Flash_Read((u8 *)(&ANO_Param),sizeof(ANO_Param));
	if(ANO_Param.firstintiflag != FIRST_INIT_FLAG)//板子从未初始化
	{
		ANO_Param_Init();
	}
//	if(ANO_Param.firstintiflag != FIRST_INIT_FLAG)//板子从未初始化
//	{
//		while(1);
//	}
}

void ANO_Param_Save(void)
{
	ANO_Flash_Write((u8 *)(&ANO_Param),sizeof(ANO_Param));
	pid_init();
}

u16 save_pid_en = 0;
void PID_Save_Overtime(u16 ms,u16 dTms)
{
	if(save_pid_en!=0)
	{
		save_pid_en++;
	}
	
	if(save_pid_en>=(ms/dTms))
	{
		ANO_Param_Save();
		save_pid_en = 0;
	}

}






