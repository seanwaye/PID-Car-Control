#ifndef __ANO_CTRL_H
#define __ANO_CTRL_H

#include "stm32f10x.h"
#include "ANO_PID.h"
#include "filter.h"

/*=====================================================================================================================
						飞机控制参数
=====================================================================================================================*/
#define MAX_ZSPEED_UP 5000  //最大控制上升速度（mm/s）
#define MAX_ZSPEED_DN 3000	//最大控制下降速度（mm/s）

#define MAX_ROL_ANGLE 35		//最大控制横滚角误差（度）
#define MAX_PIT_ANGLE 35		//最大控制俯仰角误差（度）
#define MAX_YAW_ANGLE 180   //最大控制偏航角误差（度）

#define MAX_ROL_SPEED 300		//最大控制横滚角速率（度/s）
#define MAX_PIT_SPEED 300		//最大控制俯仰角速率（度/s）
#define MAX_YAW_SPEED 200		//最大控制偏航角速率（度/s）

#define MAX_THR       80    //最大控制油门（百分比）

#define CTRL_1_INTER_LIMIT 200  //角速度积分幅度限制
#define CTRL_2_INTER_LIMIT 5    //角度积分幅度限制
/*=====================================================================================================================
						
=====================================================================================================================*/
typedef struct
{
	float exp_rol;
	float exp_pit;
	float exp_yaw;
	float exp_yaw_i_comp;
	
	float fb_rol;
	float fb_pit;
	float fb_yaw;
	
	float out_rol;
	float out_pit;
	float out_yaw;
	
}_copter_ctrl_st;

void CTRL_Duty(float ch1,float ch2,float ch3,float ch4);

void CTRL_2_PID_Init(void);
void CTRL_1_PID_Init(void);
void CTRL_0_PID_Init(void);
void pid_init(void);

void motor_ctrl(float dT,s16 ct_val_rol,s16 ct_val_pit,s16 ct_val_yaw,s16 ct_val_thr);

extern s16 motor[];

extern _copter_ctrl_st ctrl_1;
extern _copter_ctrl_st ctrl_2;
#endif
