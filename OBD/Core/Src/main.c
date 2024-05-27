/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "BitMath.h"
#include "MQTTSim800.h"
#include "Mcu.h"
#include "GPIO.h"
#include "ADC.h"
#include "WDT.h"
#include "UART.h"
#include "I2C.h"
#include "Timer.h"
#include "Can.h"

#include "TPS.h"
#include "Battery.h"
#include "CRS.h"
#include "ExtI2cEeprom.h"
#include "MemManager.h"
#include "BitsManager.h"
#include "PwmCommander.h"
#include "CAN_ISO_15765.h"
#include "LEDDriverCnfg.h"
#include "LEDDriver.h"
#include "BuzzerDriverCnfg.h"
#include "BuzzerDriver.h"
#include "Vehicle_App.h"
#include "Wireless_App.h"
#include "LowPowerApp.h"
#include "MonitoringApp.h"
#include "QueueInterface.h"
#include "UDSHandler.h"
#include "CANTp.h"
#include "OBDIIHandler.h"

#include "FreeRTOS.h"
#include "task.h"

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


CAN_HandleTypeDef hcan;


RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
 void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_CAN_Init(void);
 void MX_WWDG_Init(void);
 void MX_ADC1_Init(void);
 void MX_I2C1_Init(void);
 void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

/* USER CODE BEGIN PFP */
void PeriodicAPIs_10ms( void * pvParameters )
{

    for( ;; )
    {
      

        vid_ComM_Manage();
        vid_TpManage();
        vid_GpioManage();

        vTaskDelay(2);
    }
}

void PeriodicAPIs_100ms( void * pvParameters )
{

    for( ;; )
    {

        enum_MonitorAppManage();
        enum_LedDrvManage();
        enum_BuzzerDrvManage();

        vTaskDelay(1000);
    }
}

void PeriodicAPIs_150ms( void * pvParameters )
{

    for( ;; )
    {

        vid_TPSManage();
        vid_CRSManage();
        enum_LowPowerAppManage();

        vTaskDelay(150);
    }
}

void PeriodicAPIs_15ms( void * pvParameters )
{

    for( ;; )
    {

        vid_BattManage();
        vid_WdtRefresh();
        vTaskDelay(15);
    }
}

void PeriodicAPIs_50ms( void * pvParameters )
{

    for( ;; )
    {
        HAL_GPIO_TogglePin(Unused1_GPIO_Port, Unused1_Pin);

        vid_Mqtt_Manage();

        vTaskDelay(50);
    }
}


void VehicleWireless( void * pvParameters ){


    for(;;){
        HAL_GPIO_TogglePin(Unused10_GPIO_Port, Unused10_Pin);

        vid_WirelessApp_Manage();
        vid_VehicleApp_Manage();
        vTaskDelay(30);
    }
}

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
  asm("NOP");
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t InitSequenceDoneFlag = 0;
SIM800_t SIM800 = {0};
TaskHandle_t  PeriodicAPIs_10ms_h  = NULL;
TaskHandle_t  PeriodicAPIs_100ms_h = NULL;
TaskHandle_t  PeriodicAPIs_150ms_h = NULL;
TaskHandle_t  PeriodicAPIs_50ms_h  = NULL;
TaskHandle_t  PeriodicAPIs_15ms_h  = NULL;
TaskHandle_t  VehicleWireless_h    = NULL;
extern uint32_t SystemCoreClock;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  // HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  // SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  __disable_irq();
  enumRetMcu_e checkMcuInit = 0;
  enumRetGpio_e checkGpioInit = 0;
  enumRetAdc_e checkAdcInit = 0;
  enumRetI2C_e  checkI2cInit = 0;
  enumRetUart_e checkUartInit = 0;
  enumRetEeprom_e checkEepromInit = 0;
  EnumCanDrvApiError checkCanDrv = 0;
  enumRetTps_e checkTemperatureSensorInit = 0;
  enumRetCrs_e checkCurrentSensorInit = 0;
  enumRetBat_e checkBatteryInit = 0;
  BuzzerDrvErrorState_e checkBuzzerInit = 0;
  LedDrvErrorState_e  checkLedInit = 0;
  enum_CanIsoErrorState checkCanIsoInit = 0;
  uint8_t checkQueuesInit = 0;
  LowPowerApiReturn_e checkLowPowerInit = 0;
  enumRetWdt_e checkWdgSettingTime = 0;

  checkMcuInit = enum_McuSetClockSource();
  if(checkMcuInit != VALID_MCU){
      Error_Handler();
  }

  checkMcuInit = enum_McuEnablePeripherals();
  if(checkMcuInit != VALID_MCU){
      Error_Handler();
  }
  checkGpioInit = enum_GpioInit();
  if(checkGpioInit != VALID_GPIO){
      Error_Handler();
  }
  checkAdcInit = enum_AdcInit();
  if(checkAdcInit != VALID_ADC){
      Error_Handler();
  }
  checkI2cInit = enum_I2C1Init();
  if(checkI2cInit != VALID_I2C){
      Error_Handler();
  }
  checkUartInit = enum_uartInit(UART_CHANNEL_1,BAUD_RATE_115200);
  if(checkUartInit != VALID_UART){
      Error_Handler();
  }
  checkUartInit = enum_uartInit(UART_CHANNEL_2,BAUD_RATE_38400);
  if(checkUartInit != VALID_UART){
      Error_Handler();
  }
  checkUartInit = enum_uartInit(UART_CHANNEL_3,BAUD_RATE_115200);
  if(checkUartInit != VALID_UART){
      Error_Handler();
  }
  checkEepromInit = enum_EepromInit();
  if(checkEepromInit != VALID_Eeprom){
      Error_Handler();
  }

  vid_CanDrvInit();

  checkCanDrv = enum_CanDrvSetBitTiming(500000, SystemCoreClock);
  if (checkCanDrv != CAN_API_OK){
      Error_Handler();
  }
  checkCanDrv = enum_SetAcceptenceFilter(0x7e8, STANDARD_FORMAT, 0);
  if (checkCanDrv != CAN_API_OK){
      Error_Handler();
  }
  checkCanDrv = enum_SetAcceptenceFilter(0x18DB33F1, EXTENDED_FORMAT, 1);
  if (checkCanDrv != CAN_API_OK){
      Error_Handler();
  }

  vid_CanDrvStart();

  checkTemperatureSensorInit = enum_TPSInit();
  if(checkTemperatureSensorInit != VALID_TPS){
      Error_Handler();
  }
  checkCurrentSensorInit = enum_CRSInit();
  if(checkCurrentSensorInit != VALID_CRS){
      Error_Handler();
  }
  checkBatteryInit = enum_BatInit();
  if(checkBatteryInit != VALID_BAT_RETURN){
      Error_Handler();
  }

  BuzzerConfig_t buzzerCfg = {.enumState = BUZZER_OFF, .u16StateTime = BUZZER_MAX_TIME, .u16TogglePeriod = 0};
  checkBuzzerInit = enum_BuzzerDrvInit(&buzzerCfg);
  if(checkBuzzerInit != BUZZER_DRV_OK){
      Error_Handler();
  }

  LedConfig_t ledCfg = {.enumState = LED_OFF, .u16StateTime = LED_MAX_TIME, .u16TogglePeriod = 0};
  checkLedInit = enum_LedDrvInit(&ledCfg, &ledCfg);
  if(checkLedInit != LED_DRV_OK){
      Error_Handler();
  }

  // vid_UDSHandlerInit();
  OBDII_Initialize();
  vid_TpInit();

  checkCanIsoInit = enum_CanIsoinit();
  if(checkCanIsoInit != CAN_ISO_OK){
      Error_Handler();
  }

  vid_setVariant(BLUEOOTH_VARIANT);

  checkQueuesInit = u8_QueueIF_Init();
  if(checkQueuesInit != 1){
      Error_Handler();
  }

  vid_ComM_init();
  vid_WirelessApp_Init();
  vid_VehicleApp_Init();

  checkLowPowerInit = enum_LowPowerAppInit();
  if(checkLowPowerInit != LOW_POWER_SUCCESS){
      Error_Handler();
  }

  // tasks
  BaseType_t xReturned = pdFAIL;
  xReturned = xTaskCreate(
                    PeriodicAPIs_10ms,       /* Function that implements the task. */
                    "PeriodicAPIs_10ms",          /* Text name for the task. */
                    300,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    4,/* Priority at which the task is created. */
                    &PeriodicAPIs_10ms_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

  xReturned = xTaskCreate(
                    VehicleWireless,       /* Function that implements the task. */
                    "VehicleWireless",          /* Text name for the task. */
                    300,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    3,/* Priority at which the task is created. */
                    &VehicleWireless_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

    xReturned = xTaskCreate(
                    PeriodicAPIs_150ms,       /* Function that implements the task. */
                    "PeriodicAPIs_150ms",          /* Text name for the task. */
                    150,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &PeriodicAPIs_150ms_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

      xReturned = xTaskCreate(
                    PeriodicAPIs_15ms,       /* Function that implements the task. */
                    "PeriodicAPIs_15ms",          /* Text name for the task. */
                    150,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &PeriodicAPIs_15ms_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

        xReturned = xTaskCreate(
                    PeriodicAPIs_50ms,       /* Function that implements the task. */
                    "PeriodicAPIs_50ms",          /* Text name for the task. */
                    150,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &PeriodicAPIs_50ms_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

        xReturned = xTaskCreate(
                    PeriodicAPIs_100ms,       /* Function that implements the task. */
                    "PeriodicAPIs_100ms",          /* Text name for the task. */
                    300,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                    &PeriodicAPIs_100ms_h );      /* Used to pass out the created task's handle. */
  if(xReturned != pdPASS){
      Error_Handler();
  }

  checkWdgSettingTime = enum_WdtSetResetTime(50);
  if(checkWdgSettingTime != VALID_WDT){
      Error_Handler();
  }

  InitSequenceDoneFlag = 1;
  __enable_irq();

  HAL_GPIO_WritePin(Unused1_GPIO_Port,Unused1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Unused10_GPIO_Port,Unused10_Pin,GPIO_PIN_RESET);
  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
  void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc1.Init.ContinuousConvMode =  DISABLE ;
    hadc1.Init.DiscontinuousConvMode = ENABLE ;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      Error_Handler();
    }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  GLOB_strHi2c1.Instance = I2C1;
  GLOB_strHi2c1.Init.ClockSpeed = 100000;
  GLOB_strHi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  GLOB_strHi2c1.Init.OwnAddress1 = 0;
  GLOB_strHi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  GLOB_strHi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  GLOB_strHi2c1.Init.OwnAddress2 = 0;
  GLOB_strHi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  GLOB_strHi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&GLOB_strHi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
 void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1536;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
 
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
 void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 64;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  if (HAL_HalfDuplex_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief WWDG Initialization Function
  * @param None
  * @retval None
  */
void MX_WWDG_Init(void)
{

  /* USER CODE BEGIN WWDG_Init 0 */

  /* USER CODE END WWDG_Init 0 */

  /* USER CODE BEGIN WWDG_Init 1 */

  /* USER CODE END WWDG_Init 1 */
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_8;
  hwwdg.Init.Window = 127;
  hwwdg.Init.Counter = 105;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN WWDG_Init 2 */

  /* USER CODE END WWDG_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PANDA_GREEN_LED_GPIO_Port, PANDA_GREEN_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SIM800_RST_Pin|BLUT_SIM_Connected_Indicator_Pin|BuzzerPin_Pin|Bluetooth_module_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PowerLED_GPIO_Port, PowerLED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Unused10_Pin Unused11_Pin */
  GPIO_InitStruct.Pin = Unused10_Pin|Unused11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PANDA_GREEN_LED_Pin */
  GPIO_InitStruct.Pin = PANDA_GREEN_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(PANDA_GREEN_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Unused12_Pin Unused13_Pin */
  GPIO_InitStruct.Pin = Unused12_Pin|Unused13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : Unused1_Pin */
  GPIO_InitStruct.Pin = Unused1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Unused1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FALLING_EDGE_Pin_Pin */
  GPIO_InitStruct.Pin = FALLING_EDGE_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  // HAL_GPIO_Init(FALLING_EDGE_Pin_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RISING_Edge_Pin_Pin */
  GPIO_InitStruct.Pin = RISING_Edge_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  // HAL_GPIO_Init(RISING_Edge_Pin_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BluetoothState_Pin Unused5_Pin Unused2_Pin */
  GPIO_InitStruct.Pin = BluetoothState_Pin|Unused5_Pin|Unused2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Unused7_Pin Unused8_Pin Unused9_Pin Unused4_Pin
                           Unused6_Pin */
  GPIO_InitStruct.Pin = Unused7_Pin|Unused8_Pin|Unused9_Pin|Unused4_Pin
                          |Unused6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SIM800_RST_Pin BLUT_SIM_Connected_Indicator_Pin BuzzerPin_Pin Bluetooth_module_Pin */
  GPIO_InitStruct.Pin = SIM800_RST_Pin|BLUT_SIM_Connected_Indicator_Pin|BuzzerPin_Pin|Bluetooth_module_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PowerLED_Pin */
  GPIO_InitStruct.Pin = PowerLED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(PowerLED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Unused3_Pin */
  GPIO_InitStruct.Pin = Unused3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Unused3_GPIO_Port, &GPIO_InitStruct);

  /*Configure peripheral I/O remapping */
  __HAL_AFIO_REMAP_PD01_ENABLE();

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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

#ifdef  USE_FULL_ASSERT
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
