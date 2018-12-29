/*
 * sys.c
 *
 *  Created on: 2017��9��22��
 *      Author: Administrator
 */

#include "sys.h"

/**
  * @brief  THUMBָ�֧�ֻ���������������·���ʵ��ִ�л��ָ��WFI
  * @param  
  * @param  
  * @retval None.
  */
void WFI_SET(void)
{
	__ASM volatile("wfi");
}
/**
  * @brief  �ر������ж� 
  * @param  
  * @retval None.
  */
void INTX_DISABLE(void)
{
	__ASM volatile("cpsid i");
}
/**
  * @brief  ���������ж�
  * @param  
  * @retval None.
  */
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");
}
/**
  * @brief  ����ջ����ַ
  * @param  addr:ջ����ַ
  * @param  
  * @retval None.
  */
__asm void MSR_MSP(u32 addr)
{
	MSR MSP, r0 //set Main Stack value
	BX r14
}
