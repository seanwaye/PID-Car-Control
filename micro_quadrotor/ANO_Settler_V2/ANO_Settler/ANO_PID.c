/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_PID.c
 * 描述    ：PID函数
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
*****************************************************************************/
#include "ANO_PID.h"

void PID_calculate( float T,            //周期（单位：秒）
					float in_ff,			      	//前馈值
					float expect,		    	//期望值（设定值）
					float feedback,		   	//反馈值（）
					PID_arg_t *pid_arg, //PID参数结构体
					PID_val_t *pid_val,	//PID数据结构体
					float inte_lim,		      	//integration limit，积分限幅
					float *out  )				     //输出
{
	pid_val->err = pid_arg->kp *(expect - feedback);
	pid_val->err_d = pid_arg->kd *(pid_val->err - pid_val->err_old) *safe_div(1.0f,T);
	pid_val->feedback_d = - ( pid_arg->k_pre_d ) *(feedback - pid_val->feedback_old) *safe_div(1.0f,T);
	pid_val->err_i += (pid_arg->ki *pid_val->err + INNER_INTEGRAL *pid_val->feedback_d)*T;
	
	if(INTEGRAL_LIMIT_EN)
	{
		pid_val->err_i = LIMIT(pid_val->err_i,-inte_lim,inte_lim);
	}
	
	*out = pid_arg->k_ff *in_ff + pid_val->err + pid_val->err_d + pid_val->feedback_d + pid_val->err_i;
	
	pid_val->feedback_old = feedback;
	pid_val->err_old = pid_val->err;
}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/


