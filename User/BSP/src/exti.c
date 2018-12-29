/*
 * exit.c
 *
 *  Created on: 2017年9月21日
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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能复用功能时钟

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); //
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			 //使能PB1所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		 //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief   外部中断1服务程序
  * @param  
  * @retval None.
  */
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
	}
	EXTI_ClearITPendingBit(EXTI_Line1); //清除EXTI_Line1上的中断标志位
}
/**
  * @brief   外部中断4服务程序
  * @param  
  * @retval None.
  */
void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
	}
	EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位
}
