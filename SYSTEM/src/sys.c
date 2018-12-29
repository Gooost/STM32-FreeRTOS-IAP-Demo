/*
 * sys.c
 *
 *  Created on: 2017年9月22日
 *      Author: Administrator
 */

#include "sys.h"

/**
  * @brief  THUMB指令不支持汇编内联，采用如下方法实现执行汇编指令WFI
  * @param  
  * @param  
  * @retval None.
  */
void WFI_SET(void)
{
	__ASM volatile("wfi");
}
/**
  * @brief  关闭所有中断 
  * @param  
  * @retval None.
  */
void INTX_DISABLE(void)
{
	__ASM volatile("cpsid i");
}
/**
  * @brief  开启所有中断
  * @param  
  * @retval None.
  */
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");
}
/**
  * @brief  设置栈顶地址
  * @param  addr:栈顶地址
  * @param  
  * @retval None.
  */
__asm void MSR_MSP(u32 addr)
{
	MSR MSP, r0 //set Main Stack value
	BX r14
}
