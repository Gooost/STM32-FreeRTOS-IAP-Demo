/*
 * usart.h
 *
 *  Created on: 2017��9��22��
 *      Author: Administrator
 */
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
	
#define USART1_REC_LEN  		256  		//�����������ֽ��� 64
#define USART2_REC_LEN  		256  		//�����������ֽ��� 64
#define USART3_REC_LEN  		256  		//�����������ֽ��� 64
#define USART4_REC_LEN  		256  		//�����������ֽ��� 64

#define EN_USART1_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
	  	

extern char USART1_RX_BUF[USART1_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern int USART1_RX_STA;         			//����״̬���	

extern char  USART2_RX_BUF[USART2_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern int USART2_RX_STA;         			//����״̬���
  	
extern char  USART3_RX_BUF[USART3_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern int USART3_RX_STA;         			//����״̬���
	  	
extern char  USART4_RX_BUF[USART4_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern int USART4_RX_STA;         			//����״̬���

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


