/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define BUTTON_CREDIT_Pin GPIO_PIN_13
#define BUTTON_CREDIT_GPIO_Port GPIOC
#define BUTTON_SERVICE_Pin GPIO_PIN_0
#define BUTTON_SERVICE_GPIO_Port GPIOC
#define BUTTON_TEST_Pin GPIO_PIN_1
#define BUTTON_TEST_GPIO_Port GPIOC
#define BUTTON_9_Pin GPIO_PIN_4
#define BUTTON_9_GPIO_Port GPIOC
#define BUTTON_10_Pin GPIO_PIN_5
#define BUTTON_10_GPIO_Port GPIOC
#define BUTTON_11_Pin GPIO_PIN_0
#define BUTTON_11_GPIO_Port GPIOB
#define BUTTON_12_Pin GPIO_PIN_1
#define BUTTON_12_GPIO_Port GPIOB
#define BUTTON_13_Pin GPIO_PIN_2
#define BUTTON_13_GPIO_Port GPIOB
#define BUTTON_14_Pin GPIO_PIN_10
#define BUTTON_14_GPIO_Port GPIOB
#define BUTTON_15_Pin GPIO_PIN_12
#define BUTTON_15_GPIO_Port GPIOB
#define BUTTON_16_Pin GPIO_PIN_13
#define BUTTON_16_GPIO_Port GPIOB
#define BUTTON_1_Pin GPIO_PIN_15
#define BUTTON_1_GPIO_Port GPIOA
#define BUTTON_2_Pin GPIO_PIN_10
#define BUTTON_2_GPIO_Port GPIOC
#define BUTTON_3_Pin GPIO_PIN_11
#define BUTTON_3_GPIO_Port GPIOC
#define BUTTON_4_Pin GPIO_PIN_12
#define BUTTON_4_GPIO_Port GPIOC
#define BUTTON_5_Pin GPIO_PIN_2
#define BUTTON_5_GPIO_Port GPIOD
#define BUTTON_6_Pin GPIO_PIN_3
#define BUTTON_6_GPIO_Port GPIOB
#define BUTTON_7_Pin GPIO_PIN_4
#define BUTTON_7_GPIO_Port GPIOB
#define BUTTON_8_Pin GPIO_PIN_5
#define BUTTON_8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
