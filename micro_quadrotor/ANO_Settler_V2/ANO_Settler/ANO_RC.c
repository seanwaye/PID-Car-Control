/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/

#include "ANO_RC.h"
#include "ANO_Data_Transfer.h"
#include "ANO_Data.h"

#define UN_YAW_VALUE  350
#define UN_THR_VALUE -400

u8 fly_ready = 0;
u16 fly_ready_cnt = 0;

u16 RX_CH[CH_NUM];
s16 CH_N[CH_NUM];

void unlock()
{
	//解锁检测
	if(CH_N[THR] < UN_THR_VALUE)
	{
		if(CH_N[YAW]>UN_YAW_VALUE)
		{
			if(fly_ready_cnt<10000)
			{
				fly_ready_cnt++;
			}
			if(fly_ready_cnt>200) //200*dT秒
			{
				fly_ready = 1;
			}
		}
		else
		{
			if(CH_N[YAW]>-UN_YAW_VALUE)
			{
				fly_ready_cnt = 0;
			}
		}
	}
	else
	{
		fly_ready_cnt = 0;
	}
	
	//上锁检测
	if(CH_N[THR] < UN_THR_VALUE)
	{
		if(CH_N[YAW]<-UN_YAW_VALUE)
		{
			if(fly_ready_cnt<10000)
			{
				fly_ready_cnt++;
			}
			if(fly_ready_cnt>200) //200*dT秒
			{
				fly_ready = 0;
			}
		}
		else
		{
			if(CH_N[YAW]<UN_YAW_VALUE)
			{
				fly_ready_cnt = 0;
			}
		}
	}
	else
	{
		fly_ready_cnt = 0;
	}
	
	if(CH_N[THR]>-350)
	{
		flag.thr_low = 0;//油门非低
	}
	else
	{
		flag.thr_low = 1;//油门拉低
	}
		
}

void RC_duty(float dT) //建议2ms调用一次
{
	u8 i ;
	for(i=0;i<CH_NUM;i++)
	{
		CH_N[i] = ((s16)RX_CH[i] - 1500);
	}
	
	unlock();
	
//失控保护检查
	fail_safe_check();
}

void fail_safe()
{
  if(CH_N[THR]>-100)
	{
		CH_N[THR] = -100;
	}

	CH_N[ROL] = 0;
	CH_N[PIT] = 0;
	CH_N[YAW] = 0;
}


void fail_safe_check() //dT秒调用一次
{
	static u16 cnt;
	
	if(flag.NS == 0)
	{
		cnt++;
	}
	else
	{
		cnt = 0;
	}

	if(cnt >= 500) //500*dT 秒
	{
		fail_safe();
	}
	
	flag.NS = 0;
}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/

