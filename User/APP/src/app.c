/*
 * app.c
 *
 *  Created on: 2017��9��11��
 *      Author: Administrator
 */
#include "main.h"


//������
TaskHandle_t StartTask_Handler;
TaskHandle_t Task1Task_Handler;
TaskHandle_t Uart1Analysis_Task_Handler;
TaskHandle_t KeyTask_Handler;

//������
void task1_task(void *pvParameters);
void uart1_analysis_task(void *pvParameters);
void key_task(void *pvParameters);


/**
  * @brief  ����������
  * @param  pvParameters���ò�������Ϊ����������뵽Ҫ�����������У�void����ָ��(void*), pvParameters��ֵ�����ݵ��������Ĵ��Ρ�
  * @retval None.
  */
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); //�����ٽ���
	//����KEY����
	xTaskCreate((TaskFunction_t)key_task,
				(const char *)"key_task",
				(uint16_t)KEY_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)KEY_TASK_PRIO,
				(TaskHandle_t *)&KeyTask_Handler);
	//����TASK1����
	xTaskCreate((TaskFunction_t)task1_task,
				(const char *)"task1_task",
				(uint16_t)TASK1_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)TASK1_TASK_PRIO,
				(TaskHandle_t *)&Task1Task_Handler);
	//�������ڽ�������
	xTaskCreate((TaskFunction_t)uart1_analysis_task,
				(const char *)"uart1_analysis",
				(uint16_t)UARTANALYSIS_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)UARTANALYSIS_TASK_PRIO,
				(TaskHandle_t *)&Uart1Analysis_Task_Handler);
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL();			//�˳��ٽ���
}
/**
  * @brief  ������
  * @param  pvParameters���ò�������Ϊ����������뵽Ҫ�����������У�void����ָ��(void*), pvParameters��ֵ�����ݵ��������Ĵ��Ρ�
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
  * @brief  ����1���ݽ�������
  * @param  pvParameters���ò�������Ϊ����������뵽Ҫ�����������У�void����ָ��(void*), pvParameters��ֵ�����ݵ��������Ĵ��Ρ�
  * @retval None.
  */
void uart1_analysis_task(void *pvParameters)
{
	while (1)
	{
		sys_cmd_exe();		//��������
		vTaskSuspend(NULL); //�����Լ�
	}
}
/**
  * @brief  ������
  * @param  pvParameters���ò�������Ϊ����������뵽Ҫ�����������У�void����ָ��(void*), pvParameters��ֵ�����ݵ��������Ĵ��Ρ�
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


