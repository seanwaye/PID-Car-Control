#ifndef __ANO_Data_H
#define __ANO_Data_H

#include "stm32f10x.h"
#include "include.h"

// float格式的XYZ坐标
typedef struct
{
	float x;
	float y;
	float z;
} _xyz_f_st;

// s16格式的XYZ坐标
typedef struct
{
	s16 x;
	s16 y;
	s16 z;
} _xyz_s16_st;

// 无对齐优化的float格式XYZ坐标
typedef struct
{
	float x;
	float y;
	float z;
}
__attribute__((packed)) _xyz_f_st_pk;

// 无对齐优化的s16格式的XYZ坐标
typedef struct
{
	s16 x;
	s16 y;
	s16 z;
}__attribute__((packed)) _xyz_s16_st_pk;


typedef struct
{
	u8 thr_low;
	u8 NS;
	u8 landed;
}_flag_st;


typedef struct
{
	float out_weight;
	float out_weight_slow;
} _global_f_st;
 
extern _flag_st flag;
extern _global_f_st gf;
#endif

