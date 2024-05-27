
/**
 * @file Mcu.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of Microcontroller Component
 * @version    1.0.0
 * @date       2024-02-22
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "Mcu.h"


/*__________________ -Macros- _________________*/


/*__________________ -Public- _________________*/
PUBLIC void Error_Handler(void);
/*__________________ -Privates- _________________*/
PRIVATE u8_t u8InitDoneFlag = 0;
PRIVATE u8_t u8ClockSelectDoneFlag = 0;
/*__________________ -Prototypes- _________________*/

enumRetMcu_e enum_McuEnablePeripherals(void)
{
    enumRetMcu_e LOC_enumRet = NOT_VALID_MCU ; 
    
    if(u8ClockSelectDoneFlag == 1)
    {
      /*____ Enable Unused Peripherals : 
      1- SRAM
      2- WWDG
      3- AFIO
      4- PWR
      5- REMAP_AFIO
      6- GPIOA,B,C,D 
      7- ADC1
      8- CAN
      9- I2C1
      10- USART1,2,3
      */
     #if(MCU_UT==OFF)
      __HAL_RCC_SRAM_CLK_ENABLE();
      __HAL_RCC_WWDG_CLK_ENABLE();


      __HAL_RCC_AFIO_CLK_ENABLE();
      __HAL_RCC_PWR_CLK_ENABLE();
      __HAL_AFIO_REMAP_SWJ_NOJTAG();

      __HAL_RCC_GPIOA_CLK_ENABLE();
      __HAL_RCC_GPIOB_CLK_ENABLE();
      __HAL_RCC_GPIOC_CLK_ENABLE();
      __HAL_RCC_GPIOD_CLK_ENABLE();
      __HAL_RCC_ADC1_CLK_ENABLE();
      __HAL_RCC_CAN1_CLK_ENABLE();
      __HAL_RCC_I2C1_CLK_ENABLE();

      __HAL_RCC_USART1_CLK_ENABLE();
      __HAL_RCC_USART2_CLK_ENABLE();
      __HAL_RCC_USART3_CLK_ENABLE();
    #endif

    
      LOC_enumRet = VALID_MCU;
      u8InitDoneFlag = 1;
    }
    else
    {
        LOC_enumRet = NOT_VALID_MCU ; 
    }
    
    return    LOC_enumRet ;
}

enumRetMcu_e  enum_McuDisablePeripherals(void)
{
   enumRetMcu_e LOC_enumRet = NOT_VALID_MCU ; 
    
    if(u8InitDoneFlag == 1)
    {
      /*____ disable Unused Peripherals : 
      1- SPI1,SPI2
      2- USB
      4- ADC2
      5- DMA
      6- CRC 
      7- FLITF
      8- BKP
      9- I2C2
      */
     #if(MCU_UT==OFF)
        __HAL_RCC_DMA1_CLK_DISABLE();
        __HAL_RCC_CRC_CLK_DISABLE();
        __HAL_RCC_FLITF_CLK_DISABLE();
        __HAL_RCC_BKP_CLK_DISABLE();
        __HAL_RCC_I2C2_CLK_DISABLE();
        __HAL_RCC_SPI1_CLK_DISABLE();
        __HAL_RCC_SPI2_CLK_DISABLE();
        __HAL_RCC_USB_CLK_DISABLE();
        __HAL_RCC_TIM4_CLK_DISABLE();
        __HAL_RCC_ADC2_CLK_DISABLE();
        __HAL_RCC_TIM1_CLK_DISABLE();
        __HAL_RCC_TIM2_CLK_DISABLE();
        __HAL_RCC_TIM3_CLK_DISABLE();
    #endif
    LOC_enumRet = VALID_MCU;
    }
    else
    {
        LOC_enumRet = NOT_VALID_MCU ; 
    }
    
    return    LOC_enumRet ;   
}

enumRetMcu_e enum_McuSetClockSource(void)
{
    /*---- LOCALs ---*/
    enumRetMcu_e LOC_enumRet = NOT_VALID_MCU ; 
    
    HAL_Init();
    SystemClock_Config();

    LOC_enumRet = VALID_MCU;
    u8ClockSelectDoneFlag = 1;

    return    LOC_enumRet ;     
}

enumPLLstability_e  enum_McuGetPllStatus(void)
{
    enumPLLstability_e enumPllStability =PLL_UNSTABLE;
    u32_t LOC_u32PllFlag = SET;

    if(u8InitDoneFlag == 1)
    {
        /*__Implementation here !!__*/

      /* Check the PLL ready flag */
      #if(MCU_UT==OFF)
         LOC_u32PllFlag = __HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY);
      #endif
      enumPllStability = (enumPLLstability_e) LOC_u32PllFlag;
   
    }
    else 
    {
        enumPllStability = PLL_UNSTABLE;
    }
    return enumPllStability ;
}






