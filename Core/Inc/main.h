/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOB
#define BTN_Pin GPIO_PIN_1
#define BTN_GPIO_Port GPIOB
#define SSA_Pin GPIO_PIN_12
#define SSA_GPIO_Port GPIOB
#define SSB_Pin GPIO_PIN_13
#define SSB_GPIO_Port GPIOB
#define SSC_Pin GPIO_PIN_14
#define SSC_GPIO_Port GPIOB
#define SSD_Pin GPIO_PIN_15
#define SSD_GPIO_Port GPIOB
#define SSE_Pin GPIO_PIN_6
#define SSE_GPIO_Port GPIOC
#define SSF_Pin GPIO_PIN_7
#define SSF_GPIO_Port GPIOC
#define SSG_Pin GPIO_PIN_8
#define SSG_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
