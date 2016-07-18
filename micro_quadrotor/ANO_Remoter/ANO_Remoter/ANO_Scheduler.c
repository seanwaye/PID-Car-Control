/***********************   (C) COPYRIGHT 2016   ****************************
 * 文件名  ：ANO_Scheduler.cpp
 * 描述    ：任务处理
**********************************************************************************/
#include "ANO_Scheduler.h"
#include "sysconfig.h"

uint16_t S_cnt_1ms=0,S_cnt_2ms=0,S_cnt_5ms=0,S_cnt_10ms=0,S_cnt_20ms=0,S_cnt_30ms=0,S_cnt_1000ms=0;

static void ANO_Loop_1000Hz(void)	//1ms执行一次
{
	ANO_NRF_Check_Event();
	Usb_Hid_Send();
}

static void ANO_Loop_500Hz(void)	//2ms执行一次
{	
	
}

static void ANO_Loop_200Hz(void)	//5ms执行一次
{

}

static void ANO_Loop_100Hz(void)	//10ms执行一次
{

}

static void ANO_Loop_50Hz(void)	//20ms执行一次
{
	ANO_Stick_Scan();
	ANO_DT_Send_RCData();
}

static void ANO_Loop_33Hz(void)	//30ms执行一次
{
	ANO_Display_30ms();
}

static void ANO_Loop_1Hz(void)	  //1000ms执行一次
{
	NRF_SSI = NRF_SSI_CNT;
	NRF_SSI_CNT = 0;
}

void ANO_Loop(void)
{
		if (USB_ReceiveFlg == TRUE)
		{
			if(Hid_RxData[0] < 33)
				ANO_NRF_TxPacket_AP(&(Hid_RxData[1]),Hid_RxData[0]);
			USB_ReceiveFlg = 0x00;	
		}
		
		if(S_cnt_1ms >= 1)
		{
			ANO_Loop_1000Hz();	
			S_cnt_1ms = 0;
		}
		if(S_cnt_2ms >= 2)
		{
			ANO_Loop_500Hz();
			S_cnt_2ms = 0;
		}		
		if(S_cnt_5ms >= 5)
		{	
			ANO_Loop_200Hz();
			S_cnt_5ms = 0;
		}
		if(S_cnt_10ms >= 10)
		{		
			ANO_Loop_100Hz();
			S_cnt_10ms = 0;
		}
		if(S_cnt_20ms >= 20)
		{		
			ANO_Loop_50Hz();
			S_cnt_20ms = 0;
		}	
		if(S_cnt_30ms >= 30)
		{		
			ANO_Loop_33Hz();
			S_cnt_30ms = 0;
		}	
		if(S_cnt_1000ms >= 1000)
		{		
			ANO_Loop_1Hz();
			S_cnt_1000ms = 0;
		}	
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
