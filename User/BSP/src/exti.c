/*
 * exit.c
 *
 *  Created on: 2017��9��21��
 *      Author: Administrator
 */
#include "main.h"

/**
  * @brief   led port initialization 
  * @param  
  * @retval None.
  */
void exti_configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //ʹ�ܸ��ù���ʱ��

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); //
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			 //ʹ��PB1���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		 //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief   �ⲿ�ж�1�������
  * @param  
  * @retval None.
  */
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
	}
	EXTI_ClearITPendingBit(EXTI_Line1); //���EXTI_Line1�ϵ��жϱ�־λ
}
/**
  * @brief   �ⲿ�ж�4�������
  * @param  
  * @retval None.
  */
void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
	}
	EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ
}
