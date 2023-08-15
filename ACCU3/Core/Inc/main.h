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
#include "stm32f1xx_hal.h"

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
#define Yellow_Pin GPIO_PIN_13
#define Yellow_GPIO_Port GPIOC
#define Blue_LED_Pin GPIO_PIN_14
#define Blue_LED_GPIO_Port GPIOC
#define Green_LED_Pin GPIO_PIN_15
#define Green_LED_GPIO_Port GPIOC
#define Analog_Input_Pin GPIO_PIN_0
#define Analog_Input_GPIO_Port GPIOA
#define Red_2_LED_Pin GPIO_PIN_1
#define Red_2_LED_GPIO_Port GPIOA
#define Red_1_LED_Pin GPIO_PIN_2
#define Red_1_LED_GPIO_Port GPIOA
#define Relay_2_Pin GPIO_PIN_3
#define Relay_2_GPIO_Port GPIOA
#define Row_1_Pin GPIO_PIN_4
#define Row_1_GPIO_Port GPIOA
#define Row_2_Pin GPIO_PIN_5
#define Row_2_GPIO_Port GPIOA
#define Row_3_Pin GPIO_PIN_6
#define Row_3_GPIO_Port GPIOA
#define Row_4_Pin GPIO_PIN_7
#define Row_4_GPIO_Port GPIOA
#define Col_4_Pin GPIO_PIN_0
#define Col_4_GPIO_Port GPIOB
#define Col_3_Pin GPIO_PIN_1
#define Col_3_GPIO_Port GPIOB
#define Col_2_Pin GPIO_PIN_10
#define Col_2_GPIO_Port GPIOB
#define Col_1_Pin GPIO_PIN_11
#define Col_1_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_12
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_13
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_14
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_15
#define LCD_D4_GPIO_Port GPIOB
#define LCD_EN_Pin GPIO_PIN_8
#define LCD_EN_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_11
#define LCD_RS_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOB
#define Relay_1_Pin GPIO_PIN_5
#define Relay_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
