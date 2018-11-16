/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "iwdg.h"
#include "main.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
static void update_led();
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void)
{
	/* USER CODE BEGIN Init */
	HAL_IWDG_Init(&hiwdg);
	#define led_default_state 1
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,led_default_state);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,led_default_state);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,led_default_state);
	HAL_GPIO_WritePin(led4_GPIO_Port,led4_Pin,led_default_state);
	HAL_GPIO_WritePin(led5_GPIO_Port,led5_Pin,led_default_state);
	HAL_GPIO_WritePin(led6_GPIO_Port,led6_Pin,led_default_state);
	HAL_GPIO_WritePin(led7_GPIO_Port,led7_Pin,led_default_state);

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */
	(void) argument;
	/* Infinite loop */
	for (;;)
	{
		//HAL_IWDG_Refresh(&hiwdg);
		update_led();
		osThreadYield();
		//osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
static void toggle_led(uint8_t bit)
{
	switch (bit)
	{
	case 1:
		HAL_GPIO_TogglePin(led7_GPIO_Port, led7_Pin);

		break;
	case 1 << 1:
		HAL_GPIO_TogglePin(led6_GPIO_Port, led6_Pin);

		break;
	case 1 << 2:
		HAL_GPIO_TogglePin(led5_GPIO_Port, led5_Pin);

		break;
	case 1 << 3:
		HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);

		break;
	case 1 << 4:
		HAL_GPIO_TogglePin(led3_GPIO_Port, led3_Pin);

		break;
	case 1 << 5:
		HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);

		break;
	case 1 << 6:
		HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);

		break;
	}

}

static void update_led()
{
	static uint8_t count = 0;
	static uint8_t last_grey = 0;
	static uint8_t last_transition_bit = 0;
	uint8_t grey = (count ^ (count >> 1)) & 0x7f;
	uint8_t transition_bit = grey ^ last_grey;
	toggle_led(transition_bit);
	toggle_led(last_transition_bit);
	last_grey = grey;
	last_transition_bit = transition_bit;
	count++;
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
