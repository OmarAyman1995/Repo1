#ifndef __BATTERY_H
#define __BATTERY_H

/**
 * @file Battery.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of Battery Driver
 * @version    1.0.0
 * @date       2024-03-10
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "typedefs.h"
#include "ADC.h"






/*____________________Macros________________________________________*/
#define BATTERY_UT  UT

#define ADC_CHANNEL_ONBOARD_BATTERY 6
#define ADC_CHANNEL_VEHICLE_BATTERY 0

#define VCC_MCU                     3.3f
#define ADC_TOTAL_LEVELS_NUMBER     4096.0f
#define ON_BOARD_BATTERY_MIN         2.8f
#define ON_BOARD_BATTERY_MAX         3.1f


#define VEHICLE_BATTERY_LEVEL1      9.0f
#define VEHICLE_BATTERY_LEVEL2      14.0f
#define VEHICLE_BATTERY_LEVEL3      16.0f

#define VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS 4.0f
/*____________________UserDatatypes___________________________________*/
/// @brief this enumeration will be used as a return type to indicate if the functionreturns successfully or Not !.
typedef enum
{
    VALID_BAT_RETURN = 0 ,
    NOT_VALID_BAT_RETURN = 1 ,
    UNKOWN_BAT_RETURN = 2
}enumRetBat_e;

/// @brief this enumeration defines the different states of two types of batteries
/// @note   for Vehicle battery
/// @note   High (above 14 Volt)
/// @note   Low (below 9 Volt)
/// @note   Normal (between 9 and 14 Volt)
/// @note   Battery Malfunction (above 16 )
/// @note   Device Disconnected (Equal Zero)
/// @brief 
typedef enum
{
    HIGH_VOLT_BATTERY               = 0, 
    LOW_VOLT_BATTERY                = 1,
    NORMAL_VOLT_BATTERY             = 2,
    MALFUNCTION_VOLT_BATTERY        = 3,
    DISCONNECTED_VOLT_BATTERY       = 4
}enumBatteryState_e;

/// @brief this structure contains two batteries in the system and their states and voltages.
typedef struct
{
    /// @brief HIGH_VOLT_BATTERY or LOW_VOLT_BATTERY or NORMAL_VOLT_BATTERY or MALFUNCTION_VOLT_BATTERY or DISCONNECTED_VOLT_BATTERY
    enumBatteryState_e  enumVehicleBatteyState;
    
    /*the volts reading of the VEHICLE_BATTERY*/
    float32_t              floatVehicleBatteyVoltage;

    /// @brief HIGH_VOLT_BATTERY or LOW_VOLT_BATTERY or NORMAL_VOLT_BATTERY or MALFUNCTION_VOLT_BATTERY or DISCONNECTED_VOLT_BATTERY
    enumBatteryState_e  enumOnBoardBatteryState;
    
    /// @brief the volts reading of the ON_BOARD_BATTERY
    float32_t              floatOnBoardBatteryVoltage;

}strBatteriesInfo_t;

/*_____________________Prototypes______________________________________*/

/// @brief this fuction initialize Battery Driver to use the readings of batteries with montoring tasks.
/// @param  NAN
/// @return the validity of function execution of  Battery driver
///         VALID_BAT_RETURN  or NOT_VALID_BAT_RETURN or UNKNOWN_BAT_RETURN  

/// @note Req ID :CCO-CDD-2016
enumRetBat_e enum_BatInit(void);

/// @brief this function calculate the voltage of the batteries and assign states to them
/// @param NAN 
/// @return NAN

/// @note Req ID :CCO-CDD-2017, CCO-CDD-2019

void vid_BattManage(void);


/// @brief this function is used from monitoring layers to get the voltages and states of the batteries in the system.
/// @param strBatteriesInfoArg (out) : the volt of each battery and its state as well.
/// @return the validity of function execution of  Battery driver
///         VALID_BAT_RETURN  or NOT_VALID_BAT_RETURN or UNKNOWN_BAT_RETURN  

/// @note Req ID  Req ID :CCO-CDD-2018
enumRetBat_e enum_BattGet(strBatteriesInfo_t* strBatteriesInfoArg);

/*end __BATTERY_H*/
#endif
