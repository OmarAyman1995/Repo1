#ifndef __PROCESSINGREQUEST_H
#define __PROCESSINGREQUEST_H


#include "Vehicle_App.h"
#include "ConversionMngr.h"
#include "PIDsDatabase.h"
#include "OfferedServices.h"
#include "VehicleDataTypes.h"


// location and information of each index at the OBD datafield
#define BYTES_INDEX 0
#define MODE_INDEX 1
#define PID_INDEX 2
#define A_INDEX 3
#define B_INDEX 4
#define C_INDEX 5
#define D_INDEX 6
#define UNUSED_INDEX 7

/**
 * @brief OBD protocol modes
 * 
 */
typedef enum 
{
    OBD_MODE_1 = 1,
    OBD_MODE_2,
    OBD_MODE_3,
    OBD_MODE_4,
    OBD_MODE_5,
    OBD_MODE_6,
    OBD_MODE_7,
    OBD_MODE_8,
    OBD_MODE_9,
    OBD_MODE_10,
}OBDRequestType;


/**
 * @brief type of the desired service/request
 * 
 */
typedef enum 
{
    MANUAL_REQUEST = 0xA1,
    DYNAMIC_DATA_REQUEST,
    STATIC_DATA_REQUEST,
    UDS_REQUEST,
    UPDATE_SUPPORT_TYPE_REQUEST,
}RequestType;


/**
 * @brief makes the request
 * 
 * @param service manual obd, manual uds, static, dynamic
 * @param parameters must be an array with following data if request is OBD the function will use these members [mode,pid],
 * if request is UDS the function will use these members [sid, did1, did2]
 * @return u8_t 1 if success, 0 if fail (transmit timeout or receive timeout)
 */
u8_t u8_Process_Request(RequestType service, Vehicle_RequestTypedef *request);


/**
 * @brief Get the Response Message (json)
 * 
 * @return u8_t* pointer to the response message
 */
u8_t* p_getResponseMessage(void);

/**
 * @brief get the response message size
 * 
 * @return u32_t size of the response message
 */
u32_t u32_getResponseSize(void);


/**
 * @brief resets the processing after calling u8_Process_Request, must be called after each call of u8_Process_Request API
 * 
 */
void vid_Processing_Reset(void);






#endif
