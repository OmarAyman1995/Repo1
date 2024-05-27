#ifndef BUZZER_DRV
#define BUZZER_DRV

#include "typedefs.h"

/**
 * @brief this enumeration defines the Buzzer operating states
 *  @note Covers Requirement CCO-CDD-1020
 * 
 */
typedef enum
{ 
    BUZZER_ON,BUZZER_OFF,BUZZER_TOGGLE

}BuzzerState_e;


/**
 * @brief this enumeration defines the Buzzer API error states
 * @note Covers Requirement CCO-CDD-1021
 */
typedef enum
{ 
    BUZZER_DRV_OK,BUZZER_DRV_NOK

}BuzzerDrvErrorState_e;


/**
 * @brief Contains description of the operating configuration of the buzzer
 * @note Covers Requirement CCO-CDD-1022
 * 
 */
typedef struct
{ 
    /// @brief enumState of Buzzer
    BuzzerState_e  enumState; 

    /// @brief Time to operate with the choosen enumState
    u16_t       u16StateTime;       

    /// @brief Toggle period if enumState is "Toggle"
    u16_t       u16TogglePeriod;   

}BuzzerConfig_t;


/**
 * @brief This function initializes the Buzzer driver by doing the following: 
          - initialize the private data container that contains buzzer configurations with the given arguments by user
          - initializes any global variables in the component to zero
 * 
 * @param strBuzzerInitState structure containing configuration of buzzer
 * @return BuzzerDrvErrorState_e the enumState of function execution.
 * @note Covers Requirement CCO-CDD-1025
 */
BuzzerDrvErrorState_e enum_BuzzerDrvInit (const BuzzerConfig_t *strBuzzerInitState);

/**
 * @brief This function manages the driver internal behavior as follows: Updates the status of theBuzzer
 * 
 * @return BuzzerDrvErrorState_e the enumState of function execution.
 * @note Covers Requirement CCO-CDD-1026
 */
BuzzerDrvErrorState_e enum_BuzzerDrvManage (void);

/**
 * @brief This function sets a certain configuration for a Buzzer
 * 
 * @param strDesiredState Structure containing the Buzzer configuration
 * @return BuzzerDrvErrorState_e the enumState of function execution.
 * @note Covers Requirement CCO-CDD-1027
 */
BuzzerDrvErrorState_e enum_SetBuzzerState (const BuzzerConfig_t *strDesiredState);















#endif
