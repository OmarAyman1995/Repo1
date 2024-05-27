
/**
 * @file GPIO.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of General Purpose Input Output (GPIO) Component
 * @version    1.0.0
 * @date       2024-02-27
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "GPIO.h"


/*__________________ -Macros- _________________*/

/*_________________ - Privates _______________*/


/*__________________ -Public- _________________*/

/*__________________ -Privates- _________________*/

#if (GPIO_UT==OFF)
PRIVATE u8_t u8InitDoneFlag = 0;
#endif

#if (GPIO_UT==ON)
u8_t u8InitDoneFlag = 0;
#endif
/*__________________ -Implementations- _________________*/

enumRetGpio_e enum_GpioInit(void)
{
  /*---- LOCALs ----*/
  enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
  
  /* ---- Implementation ---- */
  MX_GPIO_Init();

  LOC_enumRet = VALID_GPIO;
  u8InitDoneFlag = 1 ;
  
  return LOC_enumRet;
}

enumRetGpio_e enum_GpioReadPin(GPIO_TypeDef* GPIOx,u16_t u16Pinx,GPIO_PinState* enumPinState)
{
  /*---- LOCALs ----*/
  enumRetGpio_e LOC_enumRet  = NOT_VALID_GPIO;
  if((u8InitDoneFlag == 1) && (GPIOx!=NULL) && (u16Pinx<=0x8000) && (enumPinState!=NULL))
  {
    *enumPinState = HAL_GPIO_ReadPin(GPIOx,u16Pinx);
    LOC_enumRet = VALID_GPIO;
  }
  else 
  {
    LOC_enumRet  = NOT_VALID_GPIO;
  }
  return LOC_enumRet;
}
enumRetGpio_e enum_GpioWritePin(GPIO_TypeDef* GPIOx,u16_t u16Pinx,GPIO_PinState enumPinState)
{
  /*---- LOCALs ----*/
  enumRetGpio_e LOC_enumRet  = NOT_VALID_GPIO;
  if((u8InitDoneFlag == 1) && (GPIOx!=NULL) && (u16Pinx<=0x8000))
  {
    HAL_GPIO_WritePin(GPIOx,u16Pinx,enumPinState);
    LOC_enumRet = VALID_GPIO;
  }
  else 
  {
    LOC_enumRet  = NOT_VALID_GPIO;
  }
  return LOC_enumRet;

}
enumRetGpio_e enum_GpioTogglePin(GPIO_TypeDef* GPIOx,u16_t u16Pinx)
{
  /*---- LOCALs ----*/
  enumRetGpio_e LOC_enumRet  = NOT_VALID_GPIO;
  if((u8InitDoneFlag == 1) && (GPIOx!=NULL) && (u16Pinx<=0x8000))
  {
    HAL_GPIO_TogglePin(GPIOx,u16Pinx);
    LOC_enumRet = VALID_GPIO;
  }
  else 
  {
    LOC_enumRet  = NOT_VALID_GPIO;
  }
  return LOC_enumRet;

}
void vid_GpioInitUnusedPins(void)
{
  /* ---- Implementation ---- */
  if(u8InitDoneFlag == 1)
  {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pins : Unused10_Pin Unused11_Pin */
  GPIO_InitStruct.Pin = Unused10_Pin|Unused11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

   /*Configure GPIO pins : Unused12_Pin Unused13_Pin */
  GPIO_InitStruct.Pin = Unused12_Pin|Unused13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : Unused1_Pin Unused3_Pin */
  GPIO_InitStruct.Pin = Unused1_Pin|Unused3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins :  Unused5_Pin Unused2_Pin */
  GPIO_InitStruct.Pin = Unused5_Pin|Unused2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Unused5_Pin Unused7_Pin Unused8_Pin Unused9_Pin
                           Unused4_Pin Unused2_Pin Unused6_Pin */
  GPIO_InitStruct.Pin = Unused5_Pin|Unused7_Pin|Unused8_Pin|Unused9_Pin
                          |Unused4_Pin|Unused2_Pin|Unused6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  }
  else 
  {
    /*---- Do nothing ----*/
  }
}

void vid_GpioInitUsedPins(void)
{
  /* ---- Implementation ---- */
  if(u8InitDoneFlag == 1)
  {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

      /*Configure GPIO pin : PANDA_GREEN_LED_Pin */
    GPIO_InitStruct.Pin = PANDA_GREEN_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PANDA_GREEN_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FALLING_EDGE_Pin_Pin */
  GPIO_InitStruct.Pin = FALLING_EDGE_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  //HAL_GPIO_Init(FALLING_EDGE_Pin_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RISING_Edge_Pin_Pin */
  GPIO_InitStruct.Pin = RISING_Edge_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  //HAL_GPIO_Init(RISING_Edge_Pin_GPIO_Port, &GPIO_InitStruct);
    
  /*Configure GPIO pin : BluetoothState_Pin */
  GPIO_InitStruct.Pin = BluetoothState_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BluetoothState_GPIO_Port, &GPIO_InitStruct);

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

  /*Configure peripheral I/O remapping */
  #if(GPIO_UT==OFF)  
    __HAL_AFIO_REMAP_PD01_ENABLE();
  #endif
  }
  else 
  {
    /*---- Do nothing ----*/
  }
}

void vid_GpioManage(void)
{
  /* ---- Implementation ---- */
  if(u8InitDoneFlag == 1)
  {
    vid_GpioInitUsedPins();
    vid_GpioInitUnusedPins();
  }
  else 
  {
    /*---- Do nothing ----*/
  }
}