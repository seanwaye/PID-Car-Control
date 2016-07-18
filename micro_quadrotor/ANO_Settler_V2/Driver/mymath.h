/***
*mymath.h
*
*       
*
*Purpose:
*       This file defined the functions and variables used by users
*       to fast computation the result of trigonometric functions and
*       the square root.
****/
//#include "SN32F700.h"
#include "stm32f10x.h"

#ifndef __MYMATH_H__
#define __MYMATH_H__

#define REAL   float
#define TAN_MAP_RES     0.003921569f     /* (smallest non-zero value in table) */
#define DEG_PER_RAD			57.29578f
#define RAD_PER_DEG     0.017453293f
#define TAN_MAP_SIZE    256
#define MY_PPPIII   3.14159f
#define MY_PPPIII_HALF   1.570796f

////计算浮点数平方
//float my_pow(float a)
#define my_pow(x) ((x)*(x))
#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

float my_abs(float f);
REAL fast_atan2(REAL y, REAL x);
//float my_pow(float a);
float my_sqrt(float number);
double mx_sin(double rad);
double my_sin(double rad);
float my_cos(double rad);
float my_deadzone(float x,float ,float zoom);
float my_deadzone_2(float x,float ,float zoom);

float To_180_degrees(float x);
double To_180_degrees_db(double x);
float my_pow_2_curve(float in,float a,float max);
float safe_div(float numerator ,float denominator);
float my_HLP(float T,float hz,float x,float zoom,float,float *zoom_adj);

double my_norm_2(double x,double y);

double my_norm_3(double x,double y,double z);

float second_degree(float in ,float max,float first_p);

#endif

