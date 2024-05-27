/**
 * @file LowPowerApp.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief This header file is for the Monitoring Feature for the CrewCopilot Project

 * @version 
 * @date 2024-2-26
 * 
 * @copyright Copyright (crewteq) 2024 
 */

#ifndef MONITOR_APP
#define MONITOR_APP


#include "typedefs.h"
#include "Battery.h"
#include "Wireless_App.h"
#include "TPS.h"
#include "CRS.h"
#include "string.h"
#include "Can.h"
#include "Vehicle_App.h"

/*________________________________Data types_______________________________*/

/**
 * @brief enum for Component APIs return values for error handling
 * @note Covers Requirement CCO-CDD-1040
 * 
 */
typedef enum 
{
    MONITORING_APP_FAILED,
    MONITORING_APP_SUCCESS,
    MONITORING_APP_BLOCKED
}MonitroingAppApiReturn_e;


/**
 * @brief Data to Monitor
 * @note Covers Requirement CCO-CDD-1045
 */
typedef struct 
{
    enumBatteryState_e u8VehicleBatteryState;
    enumBatteryState_e u8OnBoardBatteryState;
    enumTemperatureStates_e enumTemperatureState;
    enumCurrentStates_e  enumCurrentState;
    u8_t u8IgnitionState;
    bool enumCanNetworkState;
    double s64VehicleBatteryValue;
    double s64CurrentValue;
    double s64TemperatureValue;
    double s64OnBoardBatteryValue;
}DataToMonitor_t;


/*________________________________Public Functions prototypes_______________________________*/

/// @note Covers Requirement CCO-CDD-1042
/// @brief Init function for component, initalize global Variables
/// @return API return State
MonitroingAppApiReturn_e enum_MonitorAppInit (void);


/// @note Covers Requirement CCO-CDD-1043
/// @brief main function for the Component called periodically by OS, Component does the following
///          - Collects all the monitoring data from other SWC
///          - constructs the Monitor Msg-
///          - communicates the Monitor Msg to the “WirelessApp“ Component   
/// @return API return State
MonitroingAppApiReturn_e enum_MonitorAppManage (void);





#endif