/*
 * KEY1.c
 *
 *  Created on: 2017年9月11日
 *      Author: Administrator
 */
#include "main.h"

/**
  * @brief  KEY1 port initialization 
  * @param  
  * @retval None.
  */
void key_configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Enable led pin RCC*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //KEY4 == 0 & KEY3 == 0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //KEY2 == 0
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //key1
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //KEY6 == 0 & KEY5 == 0
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //power control pin
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
/**
  * @brief  KEY1 1 short press
  * @param  
  * @retval None.
  */
void key1_short_press(void)
{
	printf("## KEY1 1 short pass\r\n");
}
/**
  * @brief  KEY1 1 long press 
  * @param  
  * @retval None.
  */
void key1_long_press(void)
{
	printf("## KEY1 1 long pass\r\n");
}
/**
  * @brief  KEY1 2 short press 
  * @param  
  * @retval None.
  */
void key2_short_press(void)
{
	printf("## KEY1 2 short pass\r\n");
}
/**
  * @brief  KEY1 2 long press 
  * @param  
  * @retval None.
  */
void key2_long_press(void)
{
	printf("## KEY1 2 long pass\r\n");
}
/**
  * @brief  KEY1 3 short press 
  * @param  
  * @retval None.
  */
void key3_short_press(void)
{
	printf("## KEY1 3 short pass\r\n");
}
/**
  * @brief  KEY1 3 long press 
  * @param  
  * @retval None.
  */
void key3_long_press(void)
{
	printf("## KEY1 3 long pass\r\n");
}
/**
  * @brief  KEY1 4 short press 
  * @param  
  * @retval None.
  */
void key4_short_press(void)
{
	printf("## KEY1 4 short pass\r\n");
}
/**
  * @brief  KEY1 4 long press 
  * @param  
  * @retval None.
  */
void key4_long_press(void)
{
	printf("## KEY1 4 long pass\r\n");
}
/**
  * @brief  KEY1 5 short press  
  * @param  
  * @retval None.
  */
void key5_short_press(void)
{
	printf("## KEY1 5 short pass\r\n");
}
/**
  * @brief  KEY1 5 long press 
  * @param  
  * @retval None.
  */
void key5_long_press(void) //按键 5G/E切换
{
	printf("## KEY1 5 long pass\r\n");
}
/**
  * @brief  KEY1 6 short press  
  * @param  
  * @retval None.
  */
void key6_short_press(void)
{
	printf("## KEY1 6 short pass\r\n");
}
/**
  * @brief   KEY1 6 long press
  * @param  
  * @retval None.
  */
void key6_long_press(void) //按键 5G/E切换
{
	printf("## KEY1 6 long pass\r\n");
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key1_scan(void) //调用周期
{
	u16 timer_key = 0;

	if (KEY1)
	{
		while (KEY1)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key1_long_press();
			while (KEY1) //等待松开按键
			{
				delay_ms(20);
			}
		}
		else
		{
			key1_short_press();
		}
	}
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key2_scan(void) //调用周期
{
	u16 timer_key = 0;

	if (KEY2 == 0)
	{
		while (KEY2 == 0)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key2_long_press();
			while (KEY2 == 0) //等待按键抬起
			{
				delay_ms(20);
			}
		}
		else
		{
			key2_short_press();
		}
	}
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key3_scan(void) //调用周期
{
	u16 timer_key = 0;

	if (KEY3 == 0)
	{
		while (KEY3 == 0)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key3_long_press();
			while (KEY3 == 0) //等待按键抬起
			{
				delay_ms(20);
			}
		}
		else
		{
			key3_short_press();
		}
	}
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key4_scan(void) //调用周期
{
	u16 timer_key = 0;

	if (KEY4 == 0)
	{
		while (KEY4 == 0)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key4_long_press();
			while (KEY4 == 0) //等待按键抬起
			{
				delay_ms(20);
			}
		}
		else
		{
			key4_short_press();
		}
	}
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key5_scan(void)
{
	u16 timer_key = 0;

	if (KEY5 == 0)
	{
		while (KEY5 == 0)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key5_long_press();
			while (KEY5 == 0) //等待按键抬起
			{
				delay_ms(20);
			}
		}
		else
		{
			key5_short_press();
		}
	}
}
/**
  * @brief  按键检测函数 
  * @param  
  * @retval None.
  */
void key6_scan(void)
{
	u16 timer_key = 0;

	if (KEY6 == 0)
	{
		while (KEY6 == 0)
		{
			timer_key++;
			if (timer_key > 50)
			{
				break;
			}
			delay_ms(20);
		}
		if (timer_key > 50)
		{
			key6_long_press();
			while (KEY6 == 0) //等待抬起
			{
				delay_ms(20);
			}
		}
		else
		{
			key6_short_press();
		}
	}
}

/**
  * @brief  按键检测函数，支持长按
  * @param  
  * @retval None.
  */
void key_scan(void) //调用周期20ms
{
	//	key1_scan();
	key2_scan();
	key3_scan();
	key4_scan();
	key5_scan();
	key6_scan();
}
/**
  * @brief  按键检测函数，支持长按
  * @param  
  * @retval None.
  */
char key_command_test(char *argv[])
{
	char value = 0;
	int key_val = 0;

	key_val = atoi(argv[1]);
	switch (key_val)
	{
	case 1:
		key1_short_press();
		break;
	case 11:
		key1_long_press();
		break;
	case 2:
		key2_short_press();
		break;
	case 22:
		key2_long_press();
		break;
	case 3:
		key3_short_press();
		break;
	case 33:
		key3_long_press();
		break;
	case 4:
		key4_short_press();
		break;
	case 44:
		key4_long_press();
		break;
	case 5:
		key5_short_press();
		break;
	case 55:
		key5_long_press();
		break;
	case 6:
		key6_short_press();
		break;
	case 66:
		key6_long_press();
		break;
	default:
		value = 2;
		break;
	}
	return value;
}
