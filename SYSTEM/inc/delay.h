/*
 * delay.h
 *
 *  Created on: 2017��9��22��
 *      Author: Administrator
 */
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
	 
void delay_configuration(void);
void delay_ms(u32 nms);
void delay_us(u32 nus);
void delay_xms(u32 nms);

#endif
