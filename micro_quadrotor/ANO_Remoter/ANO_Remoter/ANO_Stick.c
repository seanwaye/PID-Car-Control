#include "ANO_Stick.h"

#define PRESS_LONG		60
#define ADC_MAX_STICK 2048

uint8_t ANO_Stick_Mode = 0;//=0,摇杆模式，=1，姿态控制模式
uint8_t ANO_Stick_Check = 0;//=0,不校准，=1，minmax校准，=2，middle校准。
uint16_t ANO_STICK_YAW, ANO_STICK_THR, ANO_STICK_ROL, ANO_STICK_PIT;
int16_t  ANO_STICK_YAW_CAL, ANO_STICK_THR_CAL, ANO_STICK_ROL_CAL, ANO_STICK_PIT_CAL;
uint8_t ANO_KEY_VALUE;//=0,未按键，=1，短按button，=2，短按stick——button，=11，长按button，=12，长按stick——button

struct S_stick
{
	uint16_t min;
	uint16_t max;
};
struct S_stick stick_yaw,stick_thr,stick_rol,stick_pit;

void ANO_Stick_Init(void)
{
	stick_yaw.min = 0;
	stick_yaw.max = 2048;
	stick_thr.min = 0;
	stick_thr.max = 2048;
	stick_rol.min = 0;
	stick_rol.max = 2048;
	stick_pit.min = 0;
	stick_pit.max = 2048;
}
void ANO_Stick_Scan(void)
{
	static u16 down_cnt = 0;	//按键按下时间计时
	static u8 key_state = 0;  //=0,没有按下按键，=1，按下button，=2，按下stick——button
	
	if(ANO_Stick_Check ==0)//正常扫描，输出结果进行校准
	{
		ANO_STICK_THR =   (ADC_ConvertedValue[0] - stick_thr.min) * 1000 / (stick_thr.max - stick_thr.min) + 1000 + ANO_STICK_THR_CAL;
		ANO_STICK_YAW = - (ADC_ConvertedValue[1] - stick_yaw.min) * 1000 / (stick_yaw.max - stick_yaw.min) + 2000 + ANO_STICK_YAW_CAL;
		ANO_STICK_PIT =   (ADC_ConvertedValue[2] - stick_pit.min) * 1000 / (stick_pit.max - stick_pit.min) + 1000 + ANO_STICK_PIT_CAL;
		ANO_STICK_ROL = - (ADC_ConvertedValue[3] - stick_rol.min) * 1000 / (stick_rol.max - stick_rol.min) + 2000 + ANO_STICK_ROL_CAL;
	}
	else     //校准状态，输出摇杆采样原始值
	{
		ANO_STICK_THR =   (ADC_ConvertedValue[0] - stick_thr.min) * 1000 / (stick_thr.max - stick_thr.min) + 1000 ;
		ANO_STICK_YAW = - (ADC_ConvertedValue[1] - stick_yaw.min) * 1000 / (stick_yaw.max - stick_yaw.min) + 2000 ;
		ANO_STICK_PIT =   (ADC_ConvertedValue[2] - stick_pit.min) * 1000 / (stick_pit.max - stick_pit.min) + 1000 ;
		ANO_STICK_ROL = - (ADC_ConvertedValue[3] - stick_rol.min) * 1000 / (stick_rol.max - stick_rol.min) + 2000 ;
	}
	
	if(ANO_Stick_Check ==1)
	{
		ANO_STICK_THR_CAL = 0;
		ANO_STICK_YAW_CAL = 0;
		ANO_STICK_PIT_CAL = 0;
		ANO_STICK_ROL_CAL = 0;
	}
	if(ANO_Stick_Check ==2)
	{
		ANO_STICK_THR_CAL = 0;
		ANO_STICK_YAW_CAL = 1500 - ANO_STICK_YAW;
		ANO_STICK_PIT_CAL = 1500 - ANO_STICK_PIT;
		ANO_STICK_ROL_CAL = 1500 - ANO_STICK_ROL;
	}
	
	if(ADC_ConvertedValue[5] > 3800)//未按下
	{
		if(key_state == 1)
		{
			if(down_cnt > PRESS_LONG)
				ANO_KEY_VALUE = 11;
			else
				ANO_KEY_VALUE = 1;
		}
		if(key_state == 2)
		{
			if(down_cnt > PRESS_LONG)
				ANO_KEY_VALUE = 12;
			else
				ANO_KEY_VALUE = 2;
		}
		key_state = 0;
		down_cnt = 0;
	}
	else if(ADC_ConvertedValue[5] > 1800)//stick_button被按下
	{
		key_state = 2;
		if(down_cnt < 250)
			down_cnt++;
	}
	else//button被按下
	{
		key_state = 1;
		if(down_cnt < 250)
			down_cnt++;
	}
}

