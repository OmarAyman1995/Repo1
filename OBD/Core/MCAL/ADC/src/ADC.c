
/**
 * @file ADC.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of Analoug / digtal converter (ADC) Component
 * @version    1.0.0
 * @date       2024-03-04
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "ADC.h"
#include "QueueInterface.h"

/*__________________ -Macros- _________________*/

/*_________________ - Privates _______________*/


/*__________________ -Public- _________________*/
ADC_HandleTypeDef hadc1;
PUBLIC void vid_WdtRefresh(void);
/*__________________ -Privates- _________________*/

#if(ADC_UT==OFF)
PRIVATE u8_t u8InitDoneFlag = 0;
#endif

#if(ADC_UT==ON)
 u8_t u8InitDoneFlag = 0 ;
#endif

/*__________________ -Implementations- _________________*/

enumRetAdc_e enum_AdcInit(void)
{   
  /*------- Locals ------*/
  enumRetAdc_e LOC_enumRet = UNKOWN_ADC;

  /*------- Action -----*/
  if(u8InitDoneFlag==0){MX_ADC1_Init();}
  else 
  {
    /* -- do nothing --*/
  }
  
  u8InitDoneFlag = 1 ;
  LOC_enumRet  = VALID_ADC;

  return LOC_enumRet;
}

enumRetAdc_e enum_AdcReadFromChannel(u8_t u8Channel, u32_t *u32ReadValue)
{
  /*__Locals*/
  PRIVATE u8_t  LOC_u8prevChannel = 100 ;
  enumRetAdc_e  LOC_enumRet = UNKOWN_ADC;
  
  /*------ check if initialization is Done -----*/

  if((u8InitDoneFlag == 1) && (u32ReadValue!=NULL) && ((u8Channel==0) || (u8Channel==1) || (u8Channel==4) || (u8Channel==6)) )
  {
    /*_ Select Channel To read _*/
    hadc1.Init.NbrOfConversion = u8Channel+1;
    
    /*---do NOT initialize the same channel if you have already initialized it! */
    if(LOC_u8prevChannel != u8Channel)
    {
      LOC_u8prevChannel = u8Channel;
      HAL_ADC_Init(&hadc1);
    }
    else {/*Do nothing*/}
    
    /*----- wait until ADC conversion complete --- */
    vid_TaskDelay(1);

    /*____Start*/
    HAL_ADC_Start(&hadc1);

    /*____wait*/
    HAL_ADC_PollForConversion(&hadc1,500);
      
    /*____Read*/
    *u32ReadValue = 4000;

    /*__Stop*/
    HAL_ADC_Stop(&hadc1);

    LOC_enumRet  = VALID_ADC;
  }

  else 
  {
    LOC_enumRet  = NOT_VALID_ADC;
  }

   /*__Return*/
   return LOC_enumRet;

}
