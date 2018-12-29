/*
 * main.c
 *
 *  Created on: 2017��9��21��
 *      Author: Administrator
 *    Function: ���Գ���LED��˸
 */
#include "main.h"

/**
  * @brief   ������ 
  * @param  
  * @retval None.
  */
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //����ϵͳ�ж����ȼ�����4
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000); //���������ж��������λ���� 0x3000
		led_configuration();							//��ʼ��LED	
		delay_configuration();						//��ʱ������ʼ��
		command_init(115200); 						//��ʼ��USMART
		key_configuration();							//��ʼ������
		exti_configuration();							//��ʼ���ⲿ�ж�	
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000); //���������ж��������λ���� 0x3000
		uart1_printf("\n\rboard_support_package_configuration\r\n");
    while (1)
    {
			//������ʼ����
			xTaskCreate((TaskFunction_t)start_task,			 //������
						(const char *)"start_task",			 //��������
						(uint16_t)START_STK_SIZE,			 //�����ջ��С
						(void *)NULL,						 //���ݸ��������Ĳ���
						(UBaseType_t)START_TASK_PRIO,		 //�������ȼ�
						(TaskHandle_t *)&StartTask_Handler); //������
			vTaskStartScheduler();			
    }
}
