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
void Error_Handler(void);
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_ADC1_Init(void);
void MX_WWDG_Init(void);

extern WWDG_HandleTypeDef hwwdg;
extern I2C_HandleTypeDef GLOB_strHi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/


/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Unused10_Pin GPIO_PIN_13
#define Unused10_GPIO_Port GPIOC
#define Unused11_Pin GPIO_PIN_14
#define Unused11_GPIO_Port GPIOC
#define PANDA_GREEN_LED_Pin GPIO_PIN_15
#define PANDA_GREEN_LED_GPIO_Port GPIOC
#define Unused12_Pin GPIO_PIN_0
#define Unused12_GPIO_Port GPIOD
#define Unused13_Pin GPIO_PIN_1
#define Unused13_GPIO_Port GPIOD
#define BatteryMonitor_Pin GPIO_PIN_0
#define BatteryMonitor_GPIO_Port GPIOA
#define CurrentMonitor_Pin GPIO_PIN_1
#define CurrentMonitor_GPIO_Port GPIOA
#define BLUETOOTH_Rx_Pin GPIO_PIN_2
#define BLUETOOTH_Rx_GPIO_Port GPIOA
#define BLUETHOOTH_Tx_Pin GPIO_PIN_3
#define BLUETHOOTH_Tx_GPIO_Port GPIOA
#define TemperatureMonitor_Pin GPIO_PIN_4
#define TemperatureMonitor_GPIO_Port GPIOA
#define Unused1_Pin GPIO_PIN_5
#define Unused1_GPIO_Port GPIOA
#define OnBoardBattery_Pin GPIO_PIN_6
#define OnBoardBattery_GPIO_Port GPIOA
#define FALLING_EDGE_Pin_Pin GPIO_PIN_7
#define FALLING_EDGE_Pin_GPIO_Port GPIOA
#define RISING_Edge_Pin_Pin GPIO_PIN_0
#define RISING_Edge_Pin_GPIO_Port GPIOB
#define BluetoothState_Pin GPIO_PIN_1
#define BluetoothState_GPIO_Port GPIOB
#define Unused5_Pin GPIO_PIN_2
#define Unused5_GPIO_Port GPIOB
#define K_line_Pin GPIO_PIN_10
#define K_line_GPIO_Port GPIOB
#define Unused7_Pin GPIO_PIN_11
#define Unused7_GPIO_Port GPIOB
#define SIM800_RST_Pin GPIO_PIN_12
#define SIM800_RST_GPIO_Port GPIOB
#define BLUT_SIM_Connected_Indicator_Pin GPIO_PIN_13
#define BLUT_SIM_Connected_Indicator_GPIO_Port GPIOB
#define Unused8_Pin GPIO_PIN_14
#define Unused8_GPIO_Port GPIOB
#define Unused9_Pin GPIO_PIN_15
#define Unused9_GPIO_Port GPIOB
#define PowerLED_Pin GPIO_PIN_8
#define PowerLED_GPIO_Port GPIOA
#define SIM800_Rx_Pin GPIO_PIN_9
#define SIM800_Rx_GPIO_Port GPIOA
#define SIM800_Tx_Pin GPIO_PIN_10
#define SIM800_Tx_GPIO_Port GPIOA
#define CAN_Transiver_Rx_Pin GPIO_PIN_11
#define CAN_Transiver_Rx_GPIO_Port GPIOA
#define CAN_Transiver_Tx_Pin GPIO_PIN_12
#define CAN_Transiver_Tx_GPIO_Port GPIOA
#define Unused3_Pin GPIO_PIN_15
#define Unused3_GPIO_Port GPIOA
#define BuzzerPin_Pin GPIO_PIN_3
#define BuzzerPin_GPIO_Port GPIOB
#define Unused4_Pin GPIO_PIN_4
#define Unused4_GPIO_Port GPIOB
#define Bluetooth_module_Pin GPIO_PIN_5
#define Bluetooth_module_GPIO_Port GPIOB
#define EEPROM_Clocks_Pin GPIO_PIN_6
#define EEPROM_Clocks_GPIO_Port GPIOB
#define EEPROM_Data_Pin GPIO_PIN_7
#define EEPROM_Data_GPIO_Port GPIOB
#define Unused2_Pin GPIO_PIN_8
#define Unused2_GPIO_Port GPIOB
#define Unused6_Pin GPIO_PIN_9
#define Unused6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
