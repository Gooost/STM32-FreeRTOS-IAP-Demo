/*
 * key.h
 *
 *  Created on: 2017Äê9ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"

#define KEY1		PEin(14)	//PE14
#define KEY2		PCin(6)		//PC6
#define KEY3		PBin(7)		//PB6
#define KEY4		PBin(6)		//PB7
#define KEY5		PGin(6)		//PG5
#define KEY6		PGin(5)		//PG6


void key_configuration(void);
void key_scan(void);
char key_command_test(char *argv[]);

#endif /* __KEY_H_ */
