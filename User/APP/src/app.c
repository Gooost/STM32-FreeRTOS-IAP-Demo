/*
 * app.c
 *
 *  Created on: 2017年9月11日
 *      Author: Administrator
 */
#include "main.h"


//任务句柄
TaskHandle_t StartTask_Handler;
TaskHandle_t Task1Task_Handler;
TaskHandle_t Uart1Analysis_Task_Handler;
TaskHandle_t KeyTask_Handler;

//任务函数
void task1_task(void *pvParameters);
void uart1_analysis_task(void *pvParameters);
void key_task(void *pvParameters);


/**
  * @brief  创建任务函数
  * @param  pvParameters：该参数会作为任务参数传入到要创建的任务中，void类型指针(void*), pvParameters的值将传递到任务函数的传参。
  * @retval None.
  */
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); //进入临界区
	//创建KEY任务
	xTaskCreate((TaskFunction_t)key_task,
				(const char *)"key_task",
				(uint16_t)KEY_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)KEY_TASK_PRIO,
				(TaskHandle_t *)&KeyTask_Handler);
	//创建TASK1任务
	xTaskCreate((TaskFunction_t)task1_task,
				(const char *)"task1_task",
				(uint16_t)TASK1_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK1_TASK_PRIO,
				(TaskHandle_t *)&Task1Task_Handler);
	//创建串口解析任务
	xTaskCreate((TaskFunction_t)uart1_analysis_task,
				(const char *)"uart1_analysis",
				(uint16_t)UARTANALYSIS_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)UARTANALYSIS_TASK_PRIO,
				(TaskHandle_t *)&Uart1Analysis_Task_Handler);
	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();			//退出临界区
}
/**
  * @brief  任务函数
  * @param  pvParameters：该参数会作为任务参数传入到要创建的任务中，void类型指针(void*), pvParameters的值将传递到任务函数的传参。
  * @retval None.
  */
void task1_task(void *pvParameters)
{
	while (1)
	{
		GREEN_D3 = ~GREEN_D3;
		vTaskDelay(50);
	}
}
/**
  * @brief  串口1数据解析任务
  * @param  pvParameters：该参数会作为任务参数传入到要创建的任务中，void类型指针(void*), pvParameters的值将传递到任务函数的传参。
  * @retval None.
  */
void uart1_analysis_task(void *pvParameters)
{
	while (1)
	{
		sys_cmd_exe();		//处理命令
		vTaskSuspend(NULL); //挂起自己
	}
}
/**
  * @brief  任务函数
  * @param  pvParameters：该参数会作为任务参数传入到要创建的任务中，void类型指针(void*), pvParameters的值将传递到任务函数的传参。
  * @retval None.
  */
void key_task(void *pvParameters)
{
	while (1)
	{
		key_scan();
		vTaskDelay(20);
		RED_D3 = ~RED_D3;
	}
}


