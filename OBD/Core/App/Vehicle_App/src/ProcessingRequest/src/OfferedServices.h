#ifndef __OFFEREDSERVICES_H
#define __OFFEREDSERVICES_H



#include "typedefs.h"
#include "ProcessingRequest.h"
#include "Vehicle_App.h"
#include "PIDsDatabase.h"


#define NOTIFICATION_COLLET_BUFFER  0
#define NOTIFICATION_SEND           1
#define NOTIFICATION_ERROR          2
#define NOTIFICATION_NOT_SUPPORTED  3
#define NOTIFICATION_COLLECT_VIN    4



/**
 * @brief Manual UDS Request Types
 * 
 */
typedef enum
{
    READ_BY_LOCAL_IDENTIFIER = 0,
    ECU_RESET,
    TESTER_PRESENT,
    UDS_MESSAGES_SIZE
}UDSList_e;

/**
 * @brief manual obd request service
 * 
 * @param mode OBD mode
 * @param pid OBD pid
 * @return uint8_t 1 if success, 0 if fail
 */
u8_t u8_MakeManualOBDRequest(u8_t mode, u8_t pid);



/**
 * @brief requests all dynamic pids
 * 
 * @param type_of_data decide if request is static or dynamic
 * @param receiveCallback function will be called after each request of each PID
 */
void vid_dynamicRequest(pToFuncCallbackStaticService receiveCallback);


/**
 * @brief requests all static pids
 * 
 * @param receiveCallback function will be called after each request of each PID
 */
void vid_staticRequest(pToFuncCallbackStaticService receiveCallback);



/**
 * @brief update pids database supported or not supported
 * 
 * @return uint8_t 1 if success, 0 if fail (no response from vehicle)
 */
u8_t u8_update_pids_database(void);



/**
 * @brief manual uds request service
 * 
 * @param uds_request 
 * @param did1 
 * @param did2 
 * @return uint8_t uint8_t 1 if success, 0 if fail
 */
u8_t u8_make_manual_uds_request(UDSList_e uds_request, u8_t did1, u8_t did2);




/**
 * @brief ComM should call this function to know the state of the request order or state of the response order
 * 
 * @param data 
 * @param notification 
 */
void vid_notificationFunction(TypeOfNotification_t notification);



#endif
