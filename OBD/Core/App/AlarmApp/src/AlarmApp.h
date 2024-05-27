/**
 * @file AlarmApp.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 *
 
 * @brief This header file is for the Alarming Feature for the CrewCopilot Project

 * @version 
 * @date 2024-2-29
 * 
 * @copyright Copyright (crewteq) 2024 
 */

#ifndef ALARM_APP
#define ALARM_APP

#include "typedefs.h"
#include "Battery.h"
/*___________________________________________________User Data Types______________________________________________________________*/


/**
 * @brief SWC API error state
 * @note Covers Requirement CCO-CDD-1701 
*/
typedef enum
{
    ALARM_APP_FAILED,
    ALARM_APP_SUCCESS

}AlarmAppErrorState_e;


/**
 * @brief Structure for the elemnts to monitor for alarming
 * @note Covers Requirement CCO-CDD-1702
 * 
 */
typedef struct
{

  /// @brief State of the battery connection
  enumBatteryState_e enumVehicleBatteryConnection;

  /// @brief State of the Bluetooth pairing 
  bool u8BluetoothPairingState; 

  /// @brief State of the MQTT pairing
  bool u8MQTTPairingState;          
}AlarmData_t;


/*___________________________________________________Public Function Prototypes______________________________________________________________*/
/// @note Covers Requirement CCO-CDD-1703
/// @brief Function that runs periodically, called by Os
/// @return API error state
AlarmAppErrorState_e enum_AlarmAppManage (void);






#endif
