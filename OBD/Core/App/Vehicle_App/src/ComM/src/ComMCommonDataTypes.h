#ifndef __CANCOMCOMMONDATATYPES_H
#define __CANCOMCOMMONDATATYPES_H

#include "typedefs.h"


/**
 * @brief Request States
 * 
 */
typedef enum 
{
    TRANSMIT_CPLT = 0,
    TRANSMIT_TIMEOUT,
    RECEIVE_CPLT,
    RECEIVE_TIMEOUT
}TypeOfNotification_t;




/**
 * @brief periodic function status
 * 
 */
typedef enum{
    IDLE = 0,
    TRANSMITTING_STATE,
    WAITING_TRANSMIT_STATE,
    TRANSMIT_TIMEOUT_STATE,
    TRANSMIT_DONE,
    RECEIVING_STATE,
    RECEIVE_TIMEOUT_STATE,
    WAITING_RECEIVE_STATE,
    MUTEX_GUARD
}ComStatus_e;


#endif
