
/**
 * @file WDT.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of Watch-Dog Timer (WDT) Component
 * @version    1.0.0
 * @date       2024-03-05
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "WDT.h"


/*__________________ -Macros- _________________*/

/*_________________ - Privates _______________*/


/*__________________ -Public- _________________*/

PUBLIC HAL_StatusTypeDef HAL_WWDG_Refresh(WWDG_HandleTypeDef *hwwdg);
WWDG_HandleTypeDef hwwdg;
/*__________________ -Privates- _________________*/
PRIVATE u8_t u8InitDoneFlag = 0;

/*__________________ -Implementations- _________________*/

enumRetWdt_e enum_WdtSetResetTime(u8_t u8TimeInMilliSec)
{
  /*----- Locals -----*/
  enumRetWdt_e LOC_enumRetVal = UNKOWN_WDT;
  double LOC_doubleTempDownCounter = 0.0;
  u32_t LOC_u32DownCounter = 0;
  /*------ calculations --------*/
 
  LOC_doubleTempDownCounter = (double)u8TimeInMilliSec/((1.0/(double)CPU_SPEED_IN_WWDG_DRIVER) * 4096.0 * 8.0);
  LOC_u32DownCounter = (u32_t)LOC_doubleTempDownCounter | 0b01000000;
  if((LOC_u32DownCounter>80) && (LOC_u32DownCounter<127))
  {
    LOC_enumRetVal = VALID_WDT;
  }
  else 
  {
    /*--- set it to the default value to make the reset time of WWDG = ~(50ms) */
    LOC_u32DownCounter = 112;
    LOC_enumRetVal = NOT_VALID_WDT;
  }
  /*-------initialization -----*/
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_8;
  hwwdg.Init.Window = 127;
  hwwdg.Init.Counter = LOC_u32DownCounter;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
    LOC_enumRetVal = NOT_VALID_WDT;
  }
  u8InitDoneFlag  = 1 ;
  return LOC_enumRetVal;
}

void vid_WdtRefresh(void)
{
  if(u8InitDoneFlag == 1)
  {
    /* ---- Refreshing ----*/
    HAL_WWDG_Refresh(&hwwdg);
  }
  else 
  {
    /*---- do nothing -----*/
  }
}
