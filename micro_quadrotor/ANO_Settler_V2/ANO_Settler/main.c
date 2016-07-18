/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_main.c
 * 描述    ：主函数
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
*****************************************************************************/
#include "include.h"
#include "ANO_Init.h"
#include "loop.h"
int main(void)
{
	sys_init();

 while(1)
 {
	 main_loop();
 }
}

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/

