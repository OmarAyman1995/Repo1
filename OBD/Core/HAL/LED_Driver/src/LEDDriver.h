#ifndef LED_DRV
#define LED_DRV

#include "typedefs.h"


/// @brief LED Operating State
///  @note Covers Requirement  CCO-CDD-1006
typedef enum
{ 
    LED_ON,LED_OFF,LED_TOGGLE

}LedState_e;


/// @brief API Error State
///  @note Covers Requirement CCO-CDD-1007
typedef enum
{ 
    LED_DRV_OK,LED_DRV_NOK

}LedDrvErrorState_e;

/**
 * @brief Configuration for Operating Led
 * @note  Covers Requirement CCO-CDD-1008
 * 
 */
typedef struct
{ 
    /// @brief enumState of led
    LedState_e  enumState;           

    /// @brief Time to operate with the choosen enumState
    u16_t       u16StateTime;       

    /// @brief Toggle period if enumState is "Toggle"
    u16_t       u16TogglePeriod;   

}LedConfig_t;


/// @brief Init Function for component
/// @param strPowerLedInitState Desired configuration to set the power led to in init
/// @param strIndicatorLedInitState Desired configuration to set the indicator led to in init
/// @return API return Value
/// @note  Covers Requirement CCO-CDD-1001
LedDrvErrorState_e enum_LedDrvInit (const LedConfig_t *strPowerLedInitState,const LedConfig_t *strIndicatorLedInitState );

/**
 * @brief This function manages the driver internal behavior as follows:
            - Updates the status of the power LED based on it’s current desired configuration 
            - Updates the status of the Indicator LED based on it’s current desired configuration
            - monitors the sub scheduling time for both leds and if time is reached, led are turned off
 * 
 * @return LedDrvErrorState_e API return Value
 * @note  Covers Requirement CCO-CDD-1002
 */
LedDrvErrorState_e enum_LedDrvManage (void);

/**
 * @brief  	This function updates the power led State
 * 
 * @param strDesiredState Structure containing the led configuration
 * @return LedDrvErrorState_e api RETURN VALUE
 * @note  Covers Requirement CCO-CDD-1004
 */
LedDrvErrorState_e enum_SetPowerLedState (const LedConfig_t *strDesiredState);


/**
 * @brief This function updates Indicator led enumState
 * 
 * @param strDesiredState Structure containing the led configuration
 * @return LedDrvErrorState_e API return Value
 * @note  Covers Requirement CCO-CDD-1005
 */
LedDrvErrorState_e enum_SetIndicatorLedState(const LedConfig_t *strDesiredState);














#endif
