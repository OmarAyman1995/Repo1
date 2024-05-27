#include "LEDDriver.h"
#include "LEDDriverCnfg.h"
#include "CmsisAbstract.h"
#include "GPIO.h"

#define FLAG_SET   1
#define FLAG_CLEAR 0

/*__________________________________Data__________________________*/

#if LED_DRIVER_UT == OFF

/// @brief variable to hold operrating configurations of power led
/// @note Covers Requirement  CCO-CDD-1010
PRIVATE LedConfig_t GLOB_StrPowerLedConfig    = {0};


/// @brief variable to hold operating conditions for Indicator led
/// @note Covers Requirement  CCO-CDD-1015
PRIVATE LedConfig_t GLOB_StrIndicatorLedConfig= {0};        

/// @brief variable to store the counted run time of the power led with the enumState mentioned in the configuration structure
/// @note  Covers Requirement  CCO-CDD-1016
PRIVATE u16_t GLOB_u16PowerLedStateTimeCounter=0;           

/// @brief variable to store the counted run time of the Power led with the enumState mentioned in the configuration structure
/// @note  Covers Requirement  CCO-CDD-1017
PRIVATE u16_t GLOB_u16PowerLedToggleTimeCount=0;          

/// @brief variable to store the counted run time of the indicator led with the enumState mentioned in the configuration structure
/// @note  Covers Requirement CCO-CDD-1018
PRIVATE u16_t GLOB_u16IndicatorLedStateTimeCounter=0;     /*variable to store the counted run time of the indicator led with the enumState mentioned in the configuration structure*/


/// @brief variable to store the counted run time of the indicator led, used for toggling
/// @note  Covers Requirement CCO-CDD-1019
PRIVATE u16_t GLOB_u16IndicatorLedToggleTimeCount=0;     

#else
LedConfig_t GLOB_StrPowerLedConfig    = {0};
LedConfig_t GLOB_StrIndicatorLedConfig= {0};        
u16_t GLOB_u16PowerLedStateTimeCounter=0;           
u16_t GLOB_u16PowerLedToggleTimeCount=0;          
u16_t GLOB_u16IndicatorLedStateTimeCounter=0;     
u16_t GLOB_u16IndicatorLedToggleTimeCount=0;  

#endif


/*__________________________Private functions Prototypes_____________________*/

#if LED_DRIVER_UT == OFF

/// @brief Handles the refreshing of the Power led enumState based on a given desired enumState
/// @param strDesiredConfig desired configuration to operate led
/// @return API Error State
/// @note  Covers Requirement CCO-CDD-1007 
PRIVATE LedDrvErrorState_e enum_RefreshPowerLedState(const LedConfig_t *strDesiredConfig);

/// @brief Handles the refreshing of the Indictaor led enumState based on a given desired enumState
/// @param strDesiredConfig desired enumState to operate led
/// @return API Error State
/// @note  Covers Requirement CCO-CDD-1008
PRIVATE LedDrvErrorState_e enum_RefreshIndicatorLedState(const LedConfig_t *strDesiredConfig);

/// @brief handles the enumState refreshing and operatin time for Power LED
/// @param strLedConfig Configuration to handle
/// @return API error type
/// @note  Covers Requirement CCO-CDD-1007
PRIVATE LedDrvErrorState_e enum_PowerLedHandle(const LedConfig_t *strLedConfig);

/// @brief handles the enumState refreshing and operatin time for Indicator LED
/// @param strLedConfig Configuration to handle
/// @return API error type
/// @note  Covers Requirement CCO-CDD-1008
PRIVATE LedDrvErrorState_e enum_IndicatorLedHandle(const LedConfig_t *strLedConfig);

#else
LedDrvErrorState_e enum_RefreshPowerLedState(const LedConfig_t *strDesiredConfig);
LedDrvErrorState_e enum_RefreshIndicatorLedState(const LedConfig_t *strDesiredConfig);
LedDrvErrorState_e enum_PowerLedHandle(const LedConfig_t *strLedConfig);
LedDrvErrorState_e enum_IndicatorLedHandle(const LedConfig_t *strLedConfig);

#endif

/*__________________________Public functions Prototypes_____________________*/
/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_LedDrvInit (const LedConfig_t *strPowerLedInitState,const LedConfig_t *strIndicatorLedInitState )
{
  LedDrvErrorState_e LOC_enumApiReturnValue = LED_DRV_OK;
  if(strPowerLedInitState==NULL || strIndicatorLedInitState==NULL)
  {
    LOC_enumApiReturnValue=LED_DRV_NOK;
  }

  else
  {
  /*store leds inital enumState in global variables*/
  GLOB_StrPowerLedConfig.enumState=strPowerLedInitState->enumState;
  GLOB_StrPowerLedConfig.u16StateTime=strPowerLedInitState->u16StateTime;
  GLOB_StrPowerLedConfig.u16TogglePeriod=strPowerLedInitState->u16TogglePeriod;

  GLOB_StrIndicatorLedConfig.enumState=strPowerLedInitState->enumState;
  GLOB_StrIndicatorLedConfig.u16StateTime=strPowerLedInitState->u16StateTime;
  GLOB_StrIndicatorLedConfig.u16TogglePeriod=strPowerLedInitState->u16TogglePeriod;
  }
  
  return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_LedDrvManage (void)
{
    LedDrvErrorState_e        LOC_enumApiReturnValue=LED_DRV_OK;
    LedDrvErrorState_e        LOC_enumReturnValue1=0;
    LedDrvErrorState_e        LOC_enumReturnValue2=0;


    /*Handle Leds*/
    LOC_enumReturnValue1=enum_PowerLedHandle(&GLOB_StrPowerLedConfig);
    LOC_enumReturnValue2=enum_IndicatorLedHandle(&GLOB_StrIndicatorLedConfig);


    /*error Handling*/

    if(LOC_enumReturnValue1==LED_DRV_NOK || LOC_enumReturnValue2==LED_DRV_NOK)
    {
        LOC_enumApiReturnValue=LED_DRV_NOK;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
    
   
}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_SetPowerLedState(const LedConfig_t *strDesiredState)
{
    LedDrvErrorState_e LOC_enumApiRetrurnValue=LED_DRV_OK;
    if(strDesiredState==NULL)
    {
      LOC_enumApiRetrurnValue=LED_DRV_NOK;
    }
    else
    {
      /*set values of the global structure to the desired values*/
      vid_DisableIrq();
      GLOB_StrPowerLedConfig.enumState=strDesiredState->enumState;
      GLOB_StrPowerLedConfig.u16StateTime=strDesiredState->u16StateTime;
      GLOB_StrPowerLedConfig.u16TogglePeriod=strDesiredState->u16TogglePeriod;

      /*reset operting time count*/
       GLOB_u16PowerLedStateTimeCounter=0;
      vid_EnableIrq();
    }
    
    return LOC_enumApiRetrurnValue;
}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_SetIndicatorLedState(const LedConfig_t *strDesiredState)
{
   LedDrvErrorState_e LOC_enumApiRetrurnValue=LED_DRV_OK;
    if(strDesiredState==NULL)
    {
      LOC_enumApiRetrurnValue=LED_DRV_NOK;
    }

    else
    {
       /*set values of the global structure to the desired values*/
       vid_DisableIrq();
       GLOB_StrIndicatorLedConfig.enumState=strDesiredState->enumState;
       GLOB_StrIndicatorLedConfig.u16StateTime=strDesiredState->u16StateTime;
       GLOB_StrIndicatorLedConfig.u16TogglePeriod=strDesiredState->u16TogglePeriod;

       /*reset operting time count*/
       GLOB_u16IndicatorLedStateTimeCounter=0;
       vid_EnableIrq();
    }

  return LOC_enumApiRetrurnValue;
}


/*__________________________Private functions Implementation_____________________*/
/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_PowerLedHandle(const LedConfig_t *strLedConfig)
{
    LedDrvErrorState_e LOC_enumApiReturnValue=LED_DRV_OK;
    LedDrvErrorState_e LOC_enumReturnValue1=0;
    LedConfig_t      LOC_strLedResetConfig={
        .enumState=LED_OFF,
        .u16StateTime=LED_MAX_TIME,
    };


    /*check for power led operating time*/
    if(GLOB_u16PowerLedStateTimeCounter >= strLedConfig->u16StateTime)
    {
        /*turn led off*/
        LOC_enumReturnValue1=enum_SetPowerLedState(&LOC_strLedResetConfig);

        /*reset counter*/
        GLOB_u16PowerLedStateTimeCounter=0;

    }
    
    /*if time is not exceeded*/
    else
    {
        /*refresh the enumState*/
        LOC_enumReturnValue1=enum_RefreshPowerLedState(strLedConfig);
        
        /*increment counter*/
        GLOB_u16PowerLedStateTimeCounter=GLOB_u16PowerLedStateTimeCounter+LED_MANAGE_PERIODICITY;
    }



    /*error Handling*/
    if(LOC_enumReturnValue1==LED_DRV_NOK)
    {
        LOC_enumApiReturnValue=LED_DRV_NOK;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_IndicatorLedHandle(const LedConfig_t *strLedConfig)
{
    LedDrvErrorState_e LOC_enumApiReturnValue=LED_DRV_OK;
    LedDrvErrorState_e LOC_enumReturnValue1=0;
    LedConfig_t      LOC_strLedResetConfig={
        .enumState=LED_OFF,
        .u16StateTime=LED_MAX_TIME,
    };

    /*check for power led operating time*/
    if(GLOB_u16IndicatorLedStateTimeCounter >= strLedConfig->u16StateTime)
    {
        /*refresh the enumState back to reset enumState*/
        LOC_enumReturnValue1=enum_SetIndicatorLedState(&LOC_strLedResetConfig);

        /*reset counter*/
        GLOB_u16IndicatorLedStateTimeCounter=0;

    }
    
    /*if time is not exceeded*/
    else
    {
        /*refresh the enumState*/
        LOC_enumReturnValue1=enum_RefreshIndicatorLedState(strLedConfig);
        
        /*increment counter*/
        GLOB_u16IndicatorLedStateTimeCounter=GLOB_u16IndicatorLedStateTimeCounter+LED_MANAGE_PERIODICITY;
    }



    /*error Handling*/
    if(LOC_enumReturnValue1==LED_DRV_NOK)
    {
        LOC_enumApiReturnValue=LED_DRV_NOK;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_RefreshPowerLedState(const LedConfig_t *strDesiredConfig)
{
    LedDrvErrorState_e LOC_enumApiReturnValue=LED_DRV_OK;
     enumRetGpio_e LOC_enumReturnValue1=VALID_GPIO;
     
    
    switch (strDesiredConfig->enumState)
    {
         case LED_ON:
         LOC_enumReturnValue1=enum_GpioWritePin(POWER_LED_PORT,POWER_LED_PIN,GPIO_PIN_SET);
         break;

         case LED_OFF:
         LOC_enumReturnValue1=enum_GpioWritePin(POWER_LED_PORT,POWER_LED_PIN,GPIO_PIN_RESET);
         break;

         case LED_TOGGLE:
         /*check if the counter for toggling equals or exceeds toggle time in the global configuration*/
         if(GLOB_u16PowerLedToggleTimeCount>=strDesiredConfig->u16TogglePeriod)
         {
            /*toggle led*/
            LOC_enumReturnValue1=enum_GpioTogglePin(POWER_LED_PORT,POWER_LED_PIN);

            /*reset counter*/
            GLOB_u16PowerLedToggleTimeCount=0;
         }

         else
         {
            /*increment counter*/
            GLOB_u16PowerLedToggleTimeCount=GLOB_u16PowerLedToggleTimeCount+LED_MANAGE_PERIODICITY;
         }
         break;

         default:
         LOC_enumReturnValue1=NOT_VALID_GPIO;

    }


     /*errorHandling*/
     if(LOC_enumReturnValue1==NOT_VALID_GPIO)
     {
        LOC_enumApiReturnValue=LED_DRV_NOK;
     }
     else
     {
        /*do nothing*/
     }

     return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

LedDrvErrorState_e enum_RefreshIndicatorLedState(const LedConfig_t *strDesiredConfig)
{
    LedDrvErrorState_e LOC_enumApiReturnValue=LED_DRV_OK;
    enumRetGpio_e LOC_enumReturnValue1=VALID_GPIO;

      switch (strDesiredConfig->enumState)
      {
         case LED_ON:
         LOC_enumReturnValue1=enum_GpioWritePin(INDICATOR_LED_PORT,INDICATOR_LED_PIN,GPIO_PIN_SET);
         break;

         case LED_OFF:
         LOC_enumReturnValue1=enum_GpioWritePin(INDICATOR_LED_PORT,INDICATOR_LED_PIN,GPIO_PIN_RESET);
         break;

         case LED_TOGGLE:
         if(GLOB_u16IndicatorLedToggleTimeCount>= strDesiredConfig->u16TogglePeriod)
         {
            /*toggle led*/
            LOC_enumReturnValue1=enum_GpioTogglePin(INDICATOR_LED_PORT,INDICATOR_LED_PIN);

            /*reset counter*/
            GLOB_u16IndicatorLedToggleTimeCount=0;
         }

         else
         {
            /*increment counter*/
            GLOB_u16IndicatorLedToggleTimeCount=GLOB_u16IndicatorLedToggleTimeCount+LED_MANAGE_PERIODICITY;
         }
         break;

         default:
         LOC_enumReturnValue1=NOT_VALID_GPIO;

      }

      /*errorHandling*/
      if(LOC_enumReturnValue1==NOT_VALID_GPIO)
      {
        LOC_enumApiReturnValue=LED_DRV_NOK;
      }
      else
      {
        /*do nothing*/
      }


     return LOC_enumApiReturnValue;

}

