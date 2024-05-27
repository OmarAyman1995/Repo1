#ifndef __VEHICLEDATATYPES_H
#define __VEHICLEDATATYPES_H


#include "typedefs.h"


/**
 * @brief the type of data that will be used in Vehicle Request API
 * 
 */
typedef struct 
{
    u8_t service;
    u8_t obd_mode;
    u8_t obd_pid;
    u8_t uds_can_id;
    u8_t uds_sid;
    u8_t uds_did1;
    u8_t uds_did2;
    ResponseCallback callback;
}Vehicle_RequestTypedef;


/**
 * @brief Request State
 * 
 */
typedef enum
{
    VEDIAPP_IDLE = 0,
    VEDIAPP_GIVEN_WRONG_ARGS,
    VEDIHANDLER_TRANSMIT_ERROR,
    VEDIHANDLER_RESPONSE_ERROR,
    VEDIAPP_IS_WAITING,
    VEDIAPP_TRANSMIT_CPLT,
    VEDIAPP_SUCCESS
}VehicleAppState;


/**
 * @brief the return of Vehicle Request API
 * 
 */
typedef enum{
    VEHICLE_APP_OK,
    VEHICLE_APP_ERROR,
    VEHICLE_APP_BUSY,
}VehicleApp_StatusTypeDef;


#endif
