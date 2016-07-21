/***********************************  (C) COPYRIGHT 2016  *********************************
 * 文件名  ：main.c
 * 描述    ：主函数
*************************************************************************************************/
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

/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE ****************/

