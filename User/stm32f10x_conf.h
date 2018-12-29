/*******************************************************************************
** �ļ���: 		stm32f10x_.conf.h
** ����:		������������ļ�
** ����ļ�:	ST������ͷ�ļ� 
*******************************************************************************/

/* ��ֹ�ض��� ----------------------------------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* ����Ҫʹ�����¹���ʱ����Ҫȥ�����ע�ͣ�����Ӧ��ͷ�ļ� �������ڹ����м�����Ӧ��CԴ�ļ�*/
#include "stm32f10x_adc.h"  
#include "stm32f10x_bkp.h" 
#include "stm32f10x_can.h" 
#include "stm32f10x_cec.h" 
#include "stm32f10x_crc.h" 
#include "stm32f10x_dac.h" 
#include "stm32f10x_dbgmcu.h" 
#include "stm32f10x_dma.h" 
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h" 
#include "stm32f10x_fsmc.h" 
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h" 
#include "stm32f10x_iwdg.h" 
#include "stm32f10x_pwr.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h" 
#include "stm32f10x_sdio.h" 
#include "stm32f10x_spi.h" 
#include "stm32f10x_tim.h" 
#include "stm32f10x_usart.h"
#include "stm32f10x_wwdg.h" 
#include "misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#ifdef  USE_FULL_ASSERT

/******************************************************************************
  * @˵��   assert_param ���ڲ������.
  * @����   expr: ����expr��flase, ������� assert_param
  *         ������������ڵ�Դ�ļ��������ڵ�����
  *         ����expr �� true, ��������ֵ.
  * @����ֵ ��
*******************************************************************************/
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* ��������------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/***************************END OF FILE****************************************/
