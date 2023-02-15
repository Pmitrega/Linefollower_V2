/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "motors.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B_IN2_Pin GPIO_PIN_13
#define B_IN2_GPIO_Port GPIOC
#define A_IN1_Pin GPIO_PIN_14
#define A_IN1_GPIO_Port GPIOC
#define A_IN2_Pin GPIO_PIN_15
#define A_IN2_GPIO_Port GPIOC
#define BUT1_Pin GPIO_PIN_12
#define BUT1_GPIO_Port GPIOB
#define BUT2_Pin GPIO_PIN_13
#define BUT2_GPIO_Port GPIOB
#define STBY_Pin GPIO_PIN_8
#define STBY_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOA
#define B_IN1_Pin GPIO_PIN_15
#define B_IN1_GPIO_Port GPIOA
#define ENCA_1_Pin GPIO_PIN_4
#define ENCA_1_GPIO_Port GPIOB
#define ENCA_2_Pin GPIO_PIN_5
#define ENCA_2_GPIO_Port GPIOB
#define ENCB_1_Pin GPIO_PIN_6
#define ENCB_1_GPIO_Port GPIOB
#define ENCB_2_Pin GPIO_PIN_7
#define ENCB_2_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_8
#define PWMB_GPIO_Port GPIOB
#define PWMA_Pin GPIO_PIN_9
#define PWMA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
