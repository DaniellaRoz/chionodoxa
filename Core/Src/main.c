/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	volatile uint32_t timer_val;

	// Using the same struct as in the traffic light, I prefer this over the macros
	typedef struct {
		GPIO_TypeDef* port;
		uint16_t pin;
	} Pin;

	// SS stands for Seven Segment, seven segment display values

	/* Guide:
	 *  -    A
	 * | |  F|B
	 *  -    G
	 * | |  E|C
	 *  -    D
	 */

	const Pin LED =  {GPIOB, GPIO_PIN_2};
	const Pin BTN =  {GPIOB, GPIO_PIN_1};
	const Pin SSA = {GPIOB, GPIO_PIN_12};
	const Pin SSB = {GPIOB, GPIO_PIN_13};
	const Pin SSC =  {GPIOC, GPIO_PIN_9};
	const Pin SSD = {GPIOB, GPIO_PIN_15};
	const Pin SSE =  {GPIOC, GPIO_PIN_6};
	const Pin SSF =  {GPIOB, GPIO_PIN_5};
	const Pin SSG =  {GPIOC, GPIO_PIN_8};

	// Pre-defining the numbers to be displayed in arrays

	Pin zero[] = {SSA, SSB, SSC, SSD, SSE, SSF};
	Pin one[] = {SSB, SSC};
	Pin two[] = {SSA, SSB, SSG, SSE, SSD};
	Pin three[] = {SSA, SSB, SSG, SSC, SSD};
	Pin four[] = {SSF, SSB, SSG, SSC};
	Pin five[] = {SSA, SSF, SSG, SSC, SSD};
	Pin six[] = {SSA, SSF, SSC, SSD, SSE, SSG};
	Pin seven[] = {SSA, SSB, SSC};
	Pin eight[] = {SSA, SSB, SSC, SSD, SSE, SSF, SSG};
	Pin nine[] = {SSA, SSB, SSF, SSG, SSC, SSD};

	// Defining the function in main as it's an impure function with side effects and will access the pins directly, which have only been defined in main.
	// When passing in, arrays decay to pointers, so I need to pass the size as an argument with `sizeof(arr) / sizeof(arr[0])`
	void display_num(Pin *number, int size) {
		HAL_GPIO_WritePin(SSA.port, SSA.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSB.port, SSB.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSC.port, SSC.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSD.port, SSD.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSE.port, SSE.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSF.port, SSF.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SSG.port, SSG.pin, GPIO_PIN_RESET);

		for (int i = 0; i < size; i++) {
			HAL_GPIO_WritePin(number[i].port, number[i].pin, GPIO_PIN_SET);
		}
	}

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  // Start timer
  HAL_TIM_Base_Start(&htim2);
  timer_val = __HAL_TIM_GET_COUNTER(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	uint32_t now = __HAL_TIM_GET_COUNTER(&htim2);
	uint32_t elapsed = now - timer_val;

	if (elapsed < 10001) {
		display_num(zero, sizeof(zero) / sizeof(zero[0]));
	} else if (elapsed < 20001) {
		display_num(one, sizeof(one) / sizeof(one[0]));
	} else if (elapsed < 30001) {
		display_num(two, sizeof(two) / sizeof(two[0]));
	} else if (elapsed < 40001) {
		display_num(three, sizeof(three) / sizeof(three[0]));
	} else if (elapsed < 50001) {
		display_num(four, sizeof(four) / sizeof(four[0]));
	} else if (elapsed < 60001) {
		display_num(five, sizeof(five) / sizeof(five[0]));
	} else if (elapsed < 70001) {
		display_num(six, sizeof(six) / sizeof(six[0]));
	} else if (elapsed < 80001) {
		display_num(seven, sizeof(seven) / sizeof(seven[0]));
	} else if (elapsed < 90001) {
		display_num(eight, sizeof(eight) / sizeof(eight[0]));
	} else if (elapsed < 100001) {
		display_num(nine, sizeof(nine) / sizeof(nine[0]));
	} else {
		timer_val = now;
	}

	// Test for if button works, light on if button pressed
	GPIO_PinState button_state = HAL_GPIO_ReadPin(BTN.port, BTN.pin);
	HAL_GPIO_WritePin(LED.port, LED.pin, button_state);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 108;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 10800 - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Pin|SSA_Pin|SSB_Pin|SSD_Pin
                          |SSF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SSE_Pin|SSG_Pin|SSC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BTN_Pin */
  GPIO_InitStruct.Pin = BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin SSA_Pin SSB_Pin SSD_Pin
                           SSF_Pin */
  GPIO_InitStruct.Pin = LED_Pin|SSA_Pin|SSB_Pin|SSD_Pin
                          |SSF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SSE_Pin SSG_Pin SSC_Pin */
  GPIO_InitStruct.Pin = SSE_Pin|SSG_Pin|SSC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
