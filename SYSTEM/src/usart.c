/*
 * usart.c
 *
 *  Created on: 2017��9��22��
 *      Author: Administrator
 */

#include "main.h"

#if EN_USART1_RX
char USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
int USART1_RX_STA = 0;            //bit15��������ɱ�־,bit13~0��	���յ�����Ч�ֽ���Ŀ
#endif
char USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
int USART2_RX_STA = 0;            //bit15��������ɱ�־��bit13~0�����յ�����Ч�ֽ���Ŀ
char USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
int USART3_RX_STA = 0;            //bit15��������ɱ�־��bit13~0��	���յ�����Ч�ֽ���Ŀ
char USART4_RX_BUF[USART4_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
int USART4_RX_STA = 0;            //bit15��������ɱ�־��bit13~0�����յ�����Ч�ֽ���Ŀ

/**
  * @brief  �������´���,֧��printf����,������Ҫѡ��use MicroLIB
  */
#if 1
#pragma import(__use_no_semihosting)

struct __FILE //��׼����Ҫ��֧�ֺ���
{
    int handle;
};
FILE __stdout;
/**
  * @brief  ����_sys_exit()�Ա���ʹ�ð�����ģʽ
  * @param  x: 
  * @retval None.
  */
_sys_exit(int x)
{
    x = x;
}
/**
  * @brief  �ض���fputc����,ʹ�ô���1 printf
  * @param  x: 
  * @retval None.
  */
int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;
    USART_SendData(USART1, (uint8_t)ch);
    return ch;
}
#endif
/**
  * @brief  Transmits single data through the USART1 peripheral.
  * @param  data: the data to transmit.
  * @retval None.
  */
void uart1_putchar(char data)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;
    USART_SendData(USART1, data);
}
/**
  * @brief  Transmits string through the USART1 peripheral.
  * @param  str: string pointer
  * @retval None.
  */
void uart1_sendstring(char *str)
{
    while (*str != '\0')
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
            ;
        USART_SendData(USART1, *(str++));
    }
}
/**
  * @brief  printf through the USART1 peripheral.
  * @param  format, ...
  * @retval None.
  */
void uart1_printf(char *format, ...)
{
    va_list ap;
    char string[512];

    va_start(ap, format);
    vsprintf(string, format, ap);
    va_end(ap);

    uart1_sendstring((char *)string);
}
/**
  * @brief  ����1��ʼ��
  * @param  bound��������
  * @retval None.
  */
void usart1_configuration(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //ʹ��USART1��GPIOAʱ��
    USART_DeInit(USART1);                                                         //��λ����1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //��ʼ��PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                //��ʼ��PA10

    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                     //һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
#if EN_USART1_RX                              //���ʹ���˽���
    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //���������ж�
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //��������֡�ж�
#endif
    USART_Cmd(USART1, ENABLE); //ʹ�ܴ���
}
/**
  * @brief  ����1�жϷ�����
  * @param  
  * @retval None.
  */
#if EN_USART1_RX             //���ʹ���˽���
void USART1_IRQHandler(void) //����1�жϷ������
{
    char Res;
    BaseType_t YieldRequired;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART1);   //(USART1->DR);	//��ȡ���յ�������
        if ((USART1_RX_STA & 0x8000) == 0) //����δ���
        {
            if ((Res == 0x0A) || (Res == 0x0D)) //�س����н���
            {
                USART1_RX_STA |= 0x8000;                                        //���յ�������
                YieldRequired = xTaskResumeFromISR(Uart1Analysis_Task_Handler); //�ָ����ڽ�������
                if (YieldRequired == pdTRUE)
                {
                    /*�������xTaskResumeFromISR()����ֵΪpdTRUE����ô˵��Ҫ�ָ������
                    ������������ȼ����ڻ��߸����������е�����(���жϴ�ϵ�����),������
                    �˳��жϵ�ʱ��һ��Ҫ�����������л���*/
                    portYIELD_FROM_ISR(YieldRequired);
                }
            }
            else if (Res == 0x08) //֧���˸��
            {
                USART1_RX_STA--;
                if (USART1_RX_STA < 1) //buf����
                    USART1_RX_STA = 0;
            }
            else
            {
                USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = Res;
                USART1_RX_STA++;
                if (USART1_RX_STA > (USART1_REC_LEN - 1))
                {
                    USART1_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) //֡�ж�
    {
        USART_ReceiveData(USART1);
    }
    if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET) //����ж�
    {
        USART_ReceiveData(USART1);
    }
}
#endif
/**
  * @brief  Transmits single data through the USART1 peripheral.
  * @param  data: the data to transmit.
  * @retval None.
  */
void uart2_putchar(char data)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
        ;
    USART_SendData(USART2, data);
}
/**
  * @brief  Transmits string through the USART2 peripheral.
  * @param  str: string pointer
  * @retval None.
  */
void uart2_sendstring(char *str)
{
    while (*str != '\0')
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
            ;
        USART_SendData(USART2, *(str++));
    }
}
/**
  * @brief  printf through the USART1 peripheral.
  * @param  format, ...
  * @retval None.
  */
void uart2_printf(char *format, ...)
{
    va_list ap;
    char string[512];

    va_start(ap, format);
    vsprintf(string, format, ap);
    va_end(ap);

    uart2_sendstring((char *)string);
}
/**
  * @brief  ����2��ʼ��
  * @param  bound��������
  * @retval None.
  */
void usart2_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    USART_DeInit(USART2); //��λ����2

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //USART2_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //USART2_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                     //������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //�����ж�
    USART_Cmd(USART2, ENABLE);                     //ʹ�ܴ���
}
/**
  * @brief  ����2�жϷ�����
  * @param  
  * @retval None.
  */
void USART2_IRQHandler(void)
{
    char Res;

    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(USART2);
        if ((USART2_RX_STA & 0x8000) == 0) //����δ���
        {
            if ((Res == 0x0A) || (Res == 0x0D))
            {
                USART2_RX_STA |= 0x8000;
            }
            else
            {
                USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = Res;
                USART2_RX_STA++;
                if (USART2_RX_STA > (USART2_REC_LEN - 1))
                {
                    USART2_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
    if (USART_GetITStatus(USART2, USART_IT_ORE) != RESET) //����ж�
    {
        USART_ReceiveData(USART2);
        USART_ClearITPendingBit(USART2, USART_IT_ORE);
    }
}
/**
  * @brief  ����3��ʼ��
  * @param  bound��������
  * @retval None.
  */
void usart3_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    USART_DeInit(USART3); //��λ����3

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //USART3_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //USART3_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                     //һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //�����ж�
    USART_Cmd(USART3, ENABLE);                     //ʹ�ܴ���
}
/**
  * @brief  ����3�жϷ�����
  * @param  
  * @retval None.
  */
void USART3_IRQHandler(void)
{
    char last_res;
    static char Res;

    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        last_res = Res; //�����ϴν��յ�������
        Res = USART_ReceiveData(USART3);
        if ((USART3_RX_STA & 0x8000) == 0) //����δ���
        {
            if ((last_res == 0x0d) && (Res == 0x0a))
            {
                USART3_RX_STA |= 0x8000;
            }
            else
            {
                USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = Res;
                USART3_RX_STA++;
                if (USART3_RX_STA > (USART3_REC_LEN - 1))
                {
                    USART3_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }

    if (USART_GetITStatus(USART3, USART_IT_ORE) != RESET) //����ж�
    {
        USART_ReceiveData(USART3);
        USART_ClearITPendingBit(USART3, USART_IT_ORE);
    }
}
/**
  * @brief  Transmits single data through the USART3 peripheral.
  * @param  data: the data to transmit.
  * @param  
  * @retval None.
  */
void uart3_putchar(char data)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
        ;
    USART_SendData(USART3, data);
}
/**
  * @brief  Transmits string through the USART1 peripheral.
  * @param  str: string pointer
  * @retval None.
  */
void uart3_sendstring(char *str)
{
    while (*str != '\0')
    {
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
            ;
        USART_SendData(USART3, *(str++));
    }
}
/**
  * @brief  printf through the USART1 peripheral.
  * @param  format, ...
  * @retval None.
  */
void uart3_printf(char *format, ...)
{
    va_list ap;
    char string[1024];

    va_start(ap, format);
    vsprintf(string, format, ap);
    va_end(ap);

    uart3_sendstring((char *)string);
}
/**
  * @brief  Transmits single data through the UART4 peripheral.
  * @param  data: the data to transmit.
  * @param  
  * @retval None.
  */
void uart4_putchar(char data)
{
    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
        ;
    USART_SendData(UART4, data);
}
/**
  * @brief  Transmits string through the USART1 peripheral.
  * @param  str: string pointer
  * @retval None.
  */
void uart4_sendstring(char *str)
{
    while (*str != '\0') //||*str != '\r'||*str != '\n'
    {
        while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
            ;
        USART_SendData(UART4, *(str++));
    }
}
/**
  * @brief  printf through the USART1 peripheral.
  * @param  format, ...
  * @retval None.
  */
void uart4_printf(char *format, ...)
{
    va_list ap;
    char string[512];

    va_start(ap, format);
    vsprintf(string, format, ap);
    va_end(ap);

    uart4_sendstring((char *)string);
}
/**
  * @brief  ����4��ʼ��
  * @param  bound��������
  * @retval None.
  */
void usart4_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    USART_DeInit(UART4); //��λ����4

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                     //һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //�շ�ģʽ

    USART_Init(UART4, &USART_InitStructure); //��ʼ������
    //Usart4 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;        //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); //�����ж�
    USART_Cmd(UART4, ENABLE);                     //ʹ�ܴ���
}
/**
  * @brief  ����4�жϷ�����
  * @param  
  * @retval None.
  */
void UART4_IRQHandler(void)
{
    char Res;

    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(UART4);
        if ((USART4_RX_STA & 0x8000) == 0) //����δ���
        {
            if ((Res == 0x0A) || (Res == 0x0D))
            {
                USART4_RX_STA |= 0x8000;
            }
            else
            {
                USART4_RX_BUF[USART4_RX_STA & 0X3FFF] = Res;
                USART4_RX_STA++;
                if (USART4_RX_STA > (USART4_REC_LEN - 1))
                {
                    USART4_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }

    if (USART_GetITStatus(UART4, USART_IT_ORE) != RESET) //����ж�
    {
        USART_ReceiveData(UART4);
        USART_ClearITPendingBit(UART4, USART_IT_ORE);
    }
}
