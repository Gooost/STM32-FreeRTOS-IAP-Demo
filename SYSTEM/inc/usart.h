/*
 * usart.h
 *
 *  Created on: 2017年9月22日
 *      Author: Administrator
 */
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
	
#define USART1_REC_LEN  		256  		//定义最大接收字节数 64
#define USART2_REC_LEN  		256  		//定义最大接收字节数 64
#define USART3_REC_LEN  		256  		//定义最大接收字节数 64
#define USART4_REC_LEN  		256  		//定义最大接收字节数 64

#define EN_USART1_RX 			1			//使能（1）/禁止（0）串口1接收
	  	

extern char USART1_RX_BUF[USART1_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern int USART1_RX_STA;         			//接收状态标记	

extern char  USART2_RX_BUF[USART2_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern int USART2_RX_STA;         			//接收状态标记
  	
extern char  USART3_RX_BUF[USART3_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern int USART3_RX_STA;         			//接收状态标记
	  	
extern char  USART4_RX_BUF[USART4_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern int USART4_RX_STA;         			//接收状态标记

void usart1_configuration(u32 bound);
void uart1_putchar(char data);
void uart1_sendstring(char * str);
void uart1_printf(char *format, ...);

void usart2_configuration(u32 bound);
void uart2_putchar(char data);
void uart2_sendstring(char * str);
void uart2_printf(char *format, ...);

void usart3_configuration(u32 bound);
void uart3_putchar(char data);
void uart3_sendstring(char * str);
void uart3_printf(char *format, ...);

void usart4_configuration(u32 bound);
void uart4_putchar(char data);
void uart4_sendstring(char * str);
void uart4_printf(char *format, ...);


#endif


