#ifndef __CANCOMMNGR_H
#define __CANCOMMNGR_H


#include "ComMCommonDataTypes.h"
#include "Com_SM.h"


#define REQUESTS_MAXSIZE 5
#define REQUEST_TIMEOUT (250)



/**
 * @brief Status of Com Mananger
 * 
 */
typedef enum
{
    CAN_DRIVER_INIT_FAIL = 0,
    SYSTEM_CORE_CLOCK_ARG_INVALID,
    NOTIFY_FUNC_ARG_INVALID,
    CAN_TRANSMIT_ARG_INVALID,
    CAN_RECEIVE_ARG_INVALID,
    COM_INIT_OK,
    COM_SUBSCRIBE_OK,
    COM_SETREQUEST_OK,
    COM_EXPECTRECEIVE_OK,
}ComM_StatusTypeDef;




/**
 * @brief Initialize ComM
 * 
 * @note CCO-CDD-201
 */
void vid_ComM_init(void);


/**
 * @brief periodic function of ComM
 * 
 * @note CCO-CDD-202 CCO-CDD-203 CCO-CDD-204 CCO-CDD-205 CCO-CDD-206 CCO-CDD-222 CCO-CDD-223
 */
void vid_ComM_Manage(void);



/**
 * @brief set request order
 * 
 * @param can_transmit request information
 * @return ComM_StatusTypeDef set request status
 * @note CCO-CDD-202 CCO-CDD-203 CCO-CDD-204 CCO-CDD-205 CCO-CDD-206 CCO-CDD-222 CCO-CDD-223
 */
void enum_Comm_StartTimeForRequest(void);


/**
 * @brief set response order
 * 
 * @param can_receive response information
 * @return ComM_StatusTypeDef set response status
 * @note CCO-CDD-202 CCO-CDD-203 CCO-CDD-204 CCO-CDD-205 CCO-CDD-206 CCO-CDD-222 CCO-CDD-223
 */
void enum_Comm_StartTimeForResponse(void);


/**
 * @brief the receive callback function that lower layer communication should call whenever recieve happen
 * 
 */
void vid_Comm_ReceiveCallback(void);

/**
 * @brief the transmit callback function that lower layer communication should call whenever transmit happen
 * 
 */
void vid_Comm_TransmitCallback(void);


#endif
