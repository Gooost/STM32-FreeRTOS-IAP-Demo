/*
 * led.h
 *
 *  Created on: 2017��9��11��
 *      Author: Administrator
 */
#ifndef __LED_H
#define __LED_H
#include "sys.h"
//Pin�˿ڶ���
#define RED_D1 PFout(4)   // PF4
#define GREEN_D1 PFout(5) // PF5

#define RED_D2 PCout(8)   // PC8
#define GREEN_D2 PCout(9) // PC9

#define RED_D3 PGout(2)   // PG2
#define GREEN_D3 PGout(3) // PG3


void led_configuration(void);


#endif /* __LED_H */
