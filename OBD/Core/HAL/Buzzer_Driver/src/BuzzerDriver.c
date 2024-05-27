#include "BuzzerDriver.h"
#include "BuzzerDriverCnfg.h"
#include "CmsisAbstract.h"
#include "GPIO.h"

#define FLAG_SET   1
#define FLAG_CLEAR 0

/*__________________________________Data__________________________*/

#if BUZZER_DRV_UT == OFF

/**
 * @brief variable to hold operrating configurations of Buzzer
 * @note Covers Requirement CCO-CDD-1024
 */
PRIVATE BuzzerConfig_t GLOB_buzzerConfig    = {0};         

/**
 * @brief variable to store the counted run time of the buzzer with the enumState mentioned in the configuration structure
 * @note Covers Requirement CCO-CDD-1034
 */
PRIVATE u16_t GLOB_BuzzerStateTimeCounter=0;  

/**
 * @brief variable to store the counted run time of the Buzzer with the enumState mentioned in the configuration structure
 * @note Covers Requirement CCO-CDD-1035
 */
PRIVATE u16_t GLOB_BuzzerToggleTimeCount=0;

#else

BuzzerConfig_t GLOB_buzzerConfig    = {0};         
u16_t GLOB_BuzzerStateTimeCounter=0;  
u16_t GLOB_BuzzerToggleTimeCount=0; 

#endif

/*__________________________Private functions Prototypes_____________________*/
#if BUZZER_DRV_UT == OFF

/// @brief Handles the refreshing of the buzzer enumState based on a given desired enumState
/// @param strDesiredConfig desired configuration to operate Buzzer
/// @return API Error State
/// @note Covers Requirement CCO-CDD-1036
PRIVATE BuzzerDrvErrorState_e enum_RefreshBuzzerState(const BuzzerConfig_t *strDesiredConfig);


/// @brief handles the enumState refreshing and operatin time for Buzzer
/// @param strBuzzerConfig Configuration to handle
/// @return API error type
/// @note Covers Requirement CCO-CDD-1037
PRIVATE BuzzerDrvErrorState_e enum_BuzzerHandle(const BuzzerConfig_t *strBuzzerConfig);
#else

 BuzzerDrvErrorState_e enum_RefreshBuzzerState(const BuzzerConfig_t *strDesiredConfig);
 BuzzerDrvErrorState_e enum_BuzzerHandle(const BuzzerConfig_t *strBuzzerConfig);

 #endif

/*__________________________Public functions Prototypes_____________________*/
/*_________________________________________________________________________________________________*/

BuzzerDrvErrorState_e enum_BuzzerDrvInit (const BuzzerConfig_t *StrBuzzerInitState)
{
  BuzzerDrvErrorState_e LOC_enumApiReturnValue=BUZZER_DRV_OK;
  if(StrBuzzerInitState==NULL)
  {
    LOC_enumApiReturnValue=BUZZER_DRV_NOK;
  }

  else
  {
  /*store Buzzer inital enumState in global variables*/
  GLOB_buzzerConfig.enumState=StrBuzzerInitState->enumState;
  GLOB_buzzerConfig.u16StateTime=StrBuzzerInitState->u16StateTime;
  GLOB_buzzerConfig.u16TogglePeriod=StrBuzzerInitState->u16TogglePeriod;
  }
  
  return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

BuzzerDrvErrorState_e enum_BuzzerDrvManage (void)
{
    BuzzerDrvErrorState_e        LOC_enumApiReturnValue=BUZZER_DRV_OK;
    BuzzerDrvErrorState_e        LOC_enumReturnValue1=0;

    /*Handle Buzzer*/
    LOC_enumReturnValue1=enum_BuzzerHandle(&GLOB_buzzerConfig);


    /*error Handling*/

    if(LOC_enumReturnValue1==BUZZER_DRV_NOK )
    {
        LOC_enumApiReturnValue=BUZZER_DRV_NOK;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
    
   
}


/*_________________________________________________________________________________________________*/

BuzzerDrvErrorState_e enum_SetBuzzerState(const BuzzerConfig_t *strDesiredState)
{
    BuzzerDrvErrorState_e LOC_enumApiRetrurnValue=BUZZER_DRV_OK;
    if(strDesiredState==NULL)
    {
      LOC_enumApiRetrurnValue=BUZZER_DRV_NOK;
    }
    else
    {
      /*set values of the global structure to the desired values*/
      vid_DisableIrq();
      GLOB_buzzerConfig.enumState=strDesiredState->enumState;
      GLOB_buzzerConfig.u16StateTime=strDesiredState->u16StateTime;
      GLOB_buzzerConfig.u16TogglePeriod=strDesiredState->u16TogglePeriod;
      vid_EnableIrq();
    }
    
    return LOC_enumApiRetrurnValue;
}


/*__________________________Private functions Implementation_____________________*/
/*_________________________________________________________________________________________________*/

BuzzerDrvErrorState_e enum_BuzzerHandle(const BuzzerConfig_t *strBuzzerConfig)
{
    BuzzerDrvErrorState_e LOC_enumApiReturnValue=BUZZER_DRV_OK;
    BuzzerDrvErrorState_e LOC_enumReturnValue1=0;
    BuzzerConfig_t      LOC_strBuzzerResetConfig={
        .enumState=BUZZER_OFF,
        .u16StateTime=BUZZER_MAX_TIME,
    };


    /*check for Buzzer operating time*/
    if(GLOB_BuzzerStateTimeCounter >= strBuzzerConfig->u16StateTime)
    {
        /*turn buzzer off*/
        LOC_enumReturnValue1=enum_SetBuzzerState(&LOC_strBuzzerResetConfig);

        /*reset counter*/
        GLOB_BuzzerStateTimeCounter=0;

    }
    
    /*if time is not exceeded*/
    else
    {
        /*refresh the enumState*/
        LOC_enumReturnValue1=enum_RefreshBuzzerState(strBuzzerConfig);
        
        /*increment counter*/
        GLOB_BuzzerStateTimeCounter=GLOB_BuzzerStateTimeCounter+BUZZER_MANAGE_PERIODICITY;
    }



    /*error Handling*/
    if(LOC_enumReturnValue1==BUZZER_DRV_NOK)
    {
        LOC_enumApiReturnValue=BUZZER_DRV_NOK;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;

}


/*_________________________________________________________________________________________________*/

BuzzerDrvErrorState_e enum_RefreshBuzzerState(const BuzzerConfig_t *strDesiredConfig)
{
    BuzzerDrvErrorState_e LOC_enumApiReturnValue=BUZZER_DRV_OK;
     enumRetGpio_e LOC_enumReturnValue1=VALID_GPIO;
    
    switch (strDesiredConfig->enumState)
    {
         case BUZZER_ON:
         LOC_enumReturnValue1=enum_GpioWritePin(BUZZER_PORT,BUZZER_PIN,GPIO_PIN_SET);
         break;

         case BUZZER_OFF:
         LOC_enumReturnValue1=enum_GpioWritePin(BUZZER_PORT,BUZZER_PIN,GPIO_PIN_RESET);
         break;

         case BUZZER_TOGGLE:
         /*check if the counter for toggling equals or exceeds toggle time in the global configuration*/
         if(GLOB_BuzzerToggleTimeCount>=strDesiredConfig->u16TogglePeriod)
         {
            /*toggle buzzer*/
            LOC_enumReturnValue1=enum_GpioTogglePin(BUZZER_PORT,BUZZER_PIN);

            /*reset counter*/
            GLOB_BuzzerToggleTimeCount=0;
         }

         else
         {
            /*increment counter*/
            GLOB_BuzzerToggleTimeCount=GLOB_BuzzerToggleTimeCount+BUZZER_MANAGE_PERIODICITY;
         }
         break;

         default:
         LOC_enumReturnValue1=NOT_VALID_GPIO;

    }


     /*errorHandling*/
     if(LOC_enumReturnValue1==NOT_VALID_GPIO)
     {
        LOC_enumApiReturnValue=BUZZER_DRV_NOK;
     }
     else
     {
        /*do nothing*/
     }

     return LOC_enumApiReturnValue;

}
