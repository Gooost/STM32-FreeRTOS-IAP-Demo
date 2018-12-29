/*
 * main.c
 *
 *  Created on: 2017年9月21日
 *      Author: Administrator
 *    Function: 测试程序，LED闪烁
 */
#include "main.h"

/**
  * @brief   主函数 
  * @param  
  * @retval None.
  */
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //设置系统中断优先级分组4
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000); //重新设置中断向量表的位置在 0x3000
		led_configuration();							//初始化LED	
		delay_configuration();						//延时函数初始化
		command_init(115200); 						//初始化USMART
		key_configuration();							//初始化按键
		exti_configuration();							//初始化外部中断	
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000); //重新设置中断向量表的位置在 0x3000
		uart1_printf("\n\rboard_support_package_configuration\r\n");
    while (1)
    {
			//创建开始任务
			xTaskCreate((TaskFunction_t)start_task,			 //任务函数
						(const char *)"start_task",			 //任务名称
						(uint16_t)START_STK_SIZE,			 //任务堆栈大小
						(void *)NULL,						 //传递给任务函数的参数
						(UBaseType_t)START_TASK_PRIO,		 //任务优先级
						(TaskHandle_t *)&StartTask_Handler); //任务句柄
			vTaskStartScheduler();			
    }
}
