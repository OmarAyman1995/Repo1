/**
 * @file LowPowerApp.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief This header file is for the LowPower Feature for the CrewCopilot Project

 * @version 
 * @date 2024-2-25
 * 
 * @copyright Copyright (crewteq) 2024 
 */

#ifndef LOW_POWER_APP
#define LOW_POWER_APP

#include "typedefs.h"

/*________________________________Data types_______________________________*/

/*enum for Component APIs Error Handling*/
/**
 * @brief enum for Component APIs Error Handling
 * @note Covers Requirement CCO-CDD-1090
 * 
 */
typedef enum 
{
    LOW_POWER_SUCCESS,
    LOW_POWER_FAILED,
    TRANSITION_TO_LOW_POWER,
    LOW_POWER_STATE,
    NORMAL_STATE
}LowPowerApiReturn_e;

/**
 * @brief enum for Device operating States
 * @note Covers Requirement CCO-CDD-1092
 * 
 */
typedef enum 
{
    DEVICE_MODE_NORMAL,
    DEVICE_MODE_LOW_POWER
}DeviceState_e;



/**
 * @brief Structure for the factors that affect the transition to Low Power State
 * @note Covers Requirement CCO-CDD-1091
 * 
 */
typedef struct  
{
  bool u8VehicleBatteryCondition;               
  bool u8IgnitionCondition;
  bool u8BluetoothPairingCondition;
  bool u8MQTTPairingCondition;
  bool u8WirelessRequestCondition;
}LowPowerFactors_t;


/*________________________________Public Functions prototypes_______________________________*/

/// @note Covers Requirement CCO-CDD-1095
/// @brief  Initalization Function for the LowPower App Component, it Does the following 
///         - initalize Global Variables of LowPowerApp 
///         - sets a callback function to be called from CAN Driver upon receiving a WakeUp Frame from vehicle
///@return API Error State
LowPowerApiReturn_e enum_LowPowerAppInit (void);


/// @note Covers Requirement CCO-CDD-1096
/// @brief main function for the Component called periodically by OS, Component does the following
///        - get Low Power data from other components
///        - check if all Low Power Conditions Are True
///        - take actions for low power mode and normal mode
///        - checks for wakeUp event to take actions of normal mode
LowPowerApiReturn_e enum_LowPowerAppManage (void);














#endif