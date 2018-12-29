/*
 * usart.c
 *
 *  Created on: 2017年9月22日
 *      Author: Administrator
 */

#include "main.h"

#if EN_USART1_RX
char USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
int USART1_RX_STA = 0;            //bit15：接收完成标志,bit13~0：	接收到的有效字节数目
#endif
char USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
int USART2_RX_STA = 0;            //bit15：接收完成标志，bit13~0：接收到的有效字节数目
char USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
int USART3_RX_STA = 0;            //bit15：接收完成标志，bit13~0，	接收到的有效字节数目
char USART4_RX_BUF[USART4_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
int USART4_RX_STA = 0;            //bit15：接收完成标志，bit13~0，接收到的有效字节数目

/**
  * @brief  加入以下代码,支持printf函数,而不需要选择use MicroLIB
  */
#if 1
#pragma import(__use_no_semihosting)

struct __FILE //标准库需要的支持函数
{
    int handle;
};
FILE __stdout;
/**
  * @brief  定义_sys_exit()以避免使用半主机模式
  * @param  x: 
  * @retval None.
  */
_sys_exit(int x)
{
    x = x;
}
/**
  * @brief  重定义fputc函数,使用串口1 printf
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
  * @brief  串口1初始化
  * @param  bound：波特率
  * @retval None.
  */
void usart1_configuration(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟
    USART_DeInit(USART1);                                                         //复位串口1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化PA10

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
#if EN_USART1_RX                              //如果使能了接收
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启接收中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //开启接受帧中断
#endif
    USART_Cmd(USART1, ENABLE); //使能串口
}
/**
  * @brief  串口1中断服务函数
  * @param  
  * @retval None.
  */
#if EN_USART1_RX             //如果使能了接收
void USART1_IRQHandler(void) //串口1中断服务程序
{
    char Res;
    BaseType_t YieldRequired;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART1);   //(USART1->DR);	//读取接收到的数据
        if ((USART1_RX_STA & 0x8000) == 0) //接收未完成
        {
            if ((Res == 0x0A) || (Res == 0x0D)) //回车换行结束
            {
                USART1_RX_STA |= 0x8000;                                        //接收到结束符
                YieldRequired = xTaskResumeFromISR(Uart1Analysis_Task_Handler); //恢复串口解析函数
                if (YieldRequired == pdTRUE)
                {
                    /*如果函数xTaskResumeFromISR()返回值为pdTRUE，那么说明要恢复的这个
                    任务的任务优先级等于或者高于正在运行的任务(被中断打断的任务),所以在
                    退出中断的时候一定要进行上下文切换！*/
                    portYIELD_FROM_ISR(YieldRequired);
                }
            }
            else if (Res == 0x08) //支持退格符
            {
                USART1_RX_STA--;
                if (USART1_RX_STA < 1) //buf限制
                    USART1_RX_STA = 0;
            }
            else
            {
                USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = Res;
                USART1_RX_STA++;
                if (USART1_RX_STA > (USART1_REC_LEN - 1))
                {
                    USART1_RX_STA = 0; //接收数据错误,重新开始接收
                }
            }
        }
    }
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) //帧中断
    {
        USART_ReceiveData(USART1);
    }
    if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET) //溢出中断
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
  * @brief  串口2初始化
  * @param  bound：波特率
  * @retval None.
  */
void usart2_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    USART_DeInit(USART2); //复位串口2

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //USART2_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //USART2_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启中断
    USART_Cmd(USART2, ENABLE);                     //使能串口
}
/**
  * @brief  串口2中断服务函数
  * @param  
  * @retval None.
  */
void USART2_IRQHandler(void)
{
    char Res;

    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(USART2);
        if ((USART2_RX_STA & 0x8000) == 0) //接收未完成
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
                    USART2_RX_STA = 0; //接收数据错误,重新开始接收
                }
            }
        }
    }
    if (USART_GetITStatus(USART2, USART_IT_ORE) != RESET) //溢出中断
    {
        USART_ReceiveData(USART2);
        USART_ClearITPendingBit(USART2, USART_IT_ORE);
    }
}
/**
  * @brief  串口3初始化
  * @param  bound：波特率
  * @retval None.
  */
void usart3_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    USART_DeInit(USART3); //复位串口3

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //USART3_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //USART3_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口
    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //开启中断
    USART_Cmd(USART3, ENABLE);                     //使能串口
}
/**
  * @brief  串口3中断服务函数
  * @param  
  * @retval None.
  */
void USART3_IRQHandler(void)
{
    char last_res;
    static char Res;

    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        last_res = Res; //保存上次接收到的数据
        Res = USART_ReceiveData(USART3);
        if ((USART3_RX_STA & 0x8000) == 0) //接收未完成
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
                    USART3_RX_STA = 0; //接收数据错误,重新开始接收
                }
            }
        }
    }

    if (USART_GetITStatus(USART3, USART_IT_ORE) != RESET) //溢出中断
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
  * @brief  串口4初始化
  * @param  bound：波特率
  * @retval None.
  */
void usart4_configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    USART_DeInit(UART4); //复位串口4

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

    USART_Init(UART4, &USART_InitStructure); //初始化串口
    //Usart4 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); //开启中断
    USART_Cmd(UART4, ENABLE);                     //使能串口
}
/**
  * @brief  串口4中断服务函数
  * @param  
  * @retval None.
  */
void UART4_IRQHandler(void)
{
    char Res;

    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(UART4);
        if ((USART4_RX_STA & 0x8000) == 0) //接收未完成
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
                    USART4_RX_STA = 0; //接收数据错误,重新开始接收
                }
            }
        }
    }

    if (USART_GetITStatus(UART4, USART_IT_ORE) != RESET) //溢出中断
    {
        USART_ReceiveData(UART4);
        USART_ClearITPendingBit(UART4, USART_IT_ORE);
    }
}
