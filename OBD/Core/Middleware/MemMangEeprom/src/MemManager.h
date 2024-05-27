#ifndef __MEM_MANAGER_H
#define __MEM_MANAGER_H

/**
 * @file MemManager.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Header file of Memory Manager of External EEPROM
 * @version    1.0.0
 * @date       2024-03-13
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "typedefs.h"
#include "ExtI2cEeprom.h"
#include "string.h"
/*____________________Macros________________________________________*/
#define         MEM_MANAGER_DEVICE_INFO_BLOCK               0U
#define         MEM_MANAGER_STATIC_FIRST_BLOCK              1U

#define         MEM_MANAGER_STATIC_LAST_BLOCK               460U
#define         MEM_MANAGER_BLUETOOTH_BLOCK                 461U
#define         MEM_MANAGER_FAILURES_FIRST_BLOCK            462U
#define         MEM_MANAGER_FAILURES_LAST_BLOCK             511U

#define         MEM_MANAGER_BLUETOOTH_NOT_INITIALIZED       "NOT INIT"
#define         MEM_MANAGER_BLUETOOTH_SUCCESS               "SUCCESS"
#define         MEM_MANAGER_BLUETOOTH_FAIL                  "FAIL    "

/*____________________UserDatatypes___________________________________*/

/// @brief this is the mapping of the static PID and their Data.
typedef struct
{
    /// @brief the ascii code (the string) of static PID + space
    u8_t u8StaticPid[4]; 
    
    /// @brief the ascii code (the string) of MODE + space
    u8_t u8Mode[3];
    
    /// @brief the ascii code (the string) of Data  ( A,B,C,D ) + space
    u8_t u8StaticData [17];

}strPIDstatic_t;

/// @brief this enumeration will be used as a return types to indicate if the function
///        returns successfully or Not !.
typedef enum
{
    VALID_MEM_MANG  = 0,
    NOT_VALID_MEM_MANG= 1,
    UNKOWN_MEM_MANG = 2
}enumRetMemMang_e;

/// @brief this enumeration will be used as a declaration of the 31 static PIDs
typedef enum
{
    PIDs_PID_SUPPORTED0                                                  = 0,
    PIDs_OXYGEN_SENSOR_PRESENT0                                          = 1,                                                            
    PIDs_OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO                          = 2,
    PIDs_OXYGEN_SENSOR_PRESENT1                                          = 3,
    PIDs_PID_SUPPORTED1                                                  = 4,                                                           
    PIDs_PID_SUPPORTED2                                                  = 5,                                                             
    PIDs_FUEL_TYPE                                                       = 6,                                                            
    PIDs_EMISSION_REQUIREMENTS                                           = 7,
    PIDs_PID_SUPPORTED3                                                  = 8,                                                          
    PIDs_ENGINE_REFERENCE_TORQUE                                         = 9,
    PIDs_AUXILIARY_INPUT_OUTPUT_SUPPORTED                                = 10,
    PIDs_PID_SUPPORTED4                                                  = 11,
    PIDs_WWH_OBD_VEHICLE_OBD_SYS_INFO                                    = 12,
    PIDs_WWH_OBD_VEHICLE_OBD_COUNTER_SUPPORT0                            = 13,
    PIDs_WWH_OBD_VEHICLE_OBD_COUNTER_SUPPORT1                            = 14,      
    PIDs_PID_SUPPORTED5                                                  = 15,                                                            
    PIDs_BS_DISABLE_SWITCH_STATE                                         = 16,
    PIDs_PID_SUPPORTED6                                                  = 17,                                                          
    PIDs_OBD_MONITOR_IDS_SUPPORTED                                       = 18,
    PIDs_MODE_9_SUPPORTED_PIDS                                           = 19,
    PIDs_VIN_MESSAGE_COUNT                                               = 20,
    PIDs_VIN                                                             = 21,
    PIDs_CALIBRATION_ID_MESSAGE_COUNT_FOR_PID04                          = 22,
    PIDs_CALIBRATION_ID                                                  = 23,
    PIDs_CALIBRATION_VERIFICATION_NUMBERS_FOR_PID_06                     = 24,
    PIDs_CALIBRATION_VERIFICATION_NUMBERS                                = 25,
    PIDs_IN_USE_PERFORMANCE_TRACKING_FOR_PID_08_0B                       = 26,   
    PIDs_IN_USE_PERFORMANCE_TRACKING_FOR_SPARK_IGNITION_VEHICLE          = 27,
    PIDs_ECU_NAME_MESSAGE_COUNT_FOR_PID_0A                               = 28,
    PIDs_ECU_NAME                                                        = 29,
    PIDs_IN_USE_PERFORMANCE_TRACKING_FOR_COMPRESSION_IGNITION_VEHICLE    = 30,
    PIDs_NUMBERS                                                         = 31                                                                                                                                                                                                                                                                                                                                    
}enumStaticPIDs_e;

/// @brief this enumeration will be used as a declaration of the four blocks of EEPROM memory regions
typedef enum 
{
    MEM_MNG_DEVICE_INFO_BLOCK                   = 0,
    MEM_MNG_STATIC_DATA_BLOCK                   = 1,
    MEM_MNG_BLUETOOTH_CONFIGURATION_BLOCK       = 2, 
    MEM_MNG_FAILURES_BLOCK                      = 3
} enumEepromBlocks_e;

/*_____________________Prototypes______________________________________*/


/// @brief this function updates value of blue-tooth configuration status information into the EEPROM ,
/// in a specific location in EEPROM (at page 461th) (“NOT INIT”, “SUCCESS”, “FAIL”)
/// @param u8BluetoothConfigStatus one of the three Macros : 
///        MEM_MANAGER_BLUETOOTH_NOT_INITIALIZED MEM_MANAGER_BLUETOOTH_SUCCESS MEM_MANAGER_BLUETOOTH_FAIL
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID : CCO-CDD-2000
enumRetMemMang_e enum_MemMngUpdateBlueTooth(u8_t* u8BluetoothConfigStatus);

/// @brief this function returns value of blue-tooth configuration status information
/// @param u8BluetoothConfigStatus (out) one of the three Macros :
///        MEM_MANAGER_BLUETOOTH_NOT_INITIALIZED MEM_MANAGER_BLUETOOTH_SUCCESS MEM_MANAGER_BLUETOOTH_FAIL
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID : CCO-CDD-2000
enumRetMemMang_e enum_MemMngReadBlueTooth(u8_t* u8BluetoothConfigStatus);


/// @brief this function in responsible for reading a Device info block.
/// @param  u8DeviceInfo   the data stored in the Device info block
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID : CCO-CDD-2001
enumRetMemMang_e enum_MemMngReadDevInfo(u8_t* u8DeviceInfo);

/// @brief this function in responsible for writing on the Device info block.
/// @param u8DataToWrite the new device information.
/// @param  u8DeviceInfoSize the size of device information text passed as an argument.
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID :CCO-CDD-2002
enumRetMemMang_e enum_MemMngUpdateDevInfo(u8_t* u8DeviceInfo,u8_t u8DeviceInfoSize);


/// @brief this function in responsible for reading a specific PID response from Static Date block.
/// @param strPIDdataStored the data stored in a specific PID static response.
/// @param enumStaticPID the static PID we want to read its response Data.
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID : CCO-CDD-2001
enumRetMemMang_e enum_MemMngReadStatic(strPIDstatic_t *strPIDdataStored ,enumStaticPIDs_e enumStaticPID);


/// @brief this function in responsible for updating the data (response) of a specific static PID
/// @param strDataToWrite the data of a specific PID the user want to update it .
/// @param enumStaticPID the static PID we want to update/write its response Data.
/// @return the validity of initialization of function Execution
///         VALID_MEM_MANG Or NOT_VALID_MEM_MANG Or UNKOWN_MEM_MANG
/// @note covers Req ID : CCO-CDD-2002
enumRetMemMang_e enum_MemMngUpdateStatic(strPIDstatic_t *strDataToWrite, enumStaticPIDs_e enumStaticPID);


/*end __MEM_MANAGER_H*/
#endif