/*******************************************************************************
** 文件名: 		stm32f10x_.conf.h
** 功能:		函数库的配置文件
** 相关文件:	ST函数库头文件 
*******************************************************************************/

/* 防止重定义 ----------------------------------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* 当需要使用以下功能时，需要去掉相关注释，打开相应的头文件 ，并且在工程中加入相应的C源文件*/
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
  * @说明   assert_param 用于参数检查.
  * @参数   expr: 假如expr是flase, 将会调用 assert_param
  *         报告错误发生所在的源文件名和所在的行数
  *         假如expr 是 true, 将步返回值.
  * @返回值 无
*******************************************************************************/
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* 函数定义------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/***************************END OF FILE****************************************/
