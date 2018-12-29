/*
 * led.c
 *
 *  Created on: 2017Äê9ÔÂ11ÈÕ
 *      Author: Administrator
 */
#include "main.h"

/**
  * @brief  led port initialization 
  * @param  
  * @retval None.
  */
void led_configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Enable led pin RCC*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; //LED1 RED and GREEN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_SetBits(GPIOF, GPIO_Pin_4 | GPIO_Pin_5); //output high,led off

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //LED2 RED and GREEN
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9); //output high,led off

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //LED3 RED and GREEN
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG, GPIO_Pin_2 | GPIO_Pin_3); //output high,led off
}
