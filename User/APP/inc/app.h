/*
 * app.h
 *
 *  Created on: 2017年9月11日
 *      Author: Administrator
 */

#ifndef __APP_H_
#define __APP_H_

//任务优先级
#define START_TASK_PRIO 1
#define KEY_TASK_PRIO 2
#define TASK1_TASK_PRIO 3
#define UARTANALYSIS_TASK_PRIO 4

//任务堆栈大小
#define START_STK_SIZE 512
#define KEY_STK_SIZE 512
#define TASK1_STK_SIZE 512
#define UARTANALYSIS_STK_SIZE 512

extern TaskHandle_t StartTask_Handler;
extern TaskHandle_t Task1Task_Handler;
extern TaskHandle_t Uart1Analysis_Task_Handler;
extern TaskHandle_t KeyTask_Handler;

void start_task(void *pvParameters);

#endif /* __APP_H_ */
