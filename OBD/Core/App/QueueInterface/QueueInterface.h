#ifndef __VEHICLEQUEUEINTERFACE_H
#define __VEHICLEQUEUEINTERFACE_H



#include "typedefs.h"



#define VEHICLE_QUEUE_SIZE 3
#define WIRLESS_SEND_QUEUE_SIZE 3
#define WIRLESS_RECV_QUEUE_SIZE 3



typedef enum
{
    VEHICLE_HANDLER,
    WIRELESS_SEND_HANDLER,
    WIRELESS_RECV_HANDLER
}QHandler;



/**
 * @brief initialize vehicle queues
 * 
 * @return u8_t 1 in success, 0 if failed
 * @note CCO-CDD-200
 */
u8_t u8_QueueIF_Init(void);


/**
 * @brief push new request in queue
 * 
 * @param new_request the new request information
 * @return u8_t 1 in success, 0 if queue full
 * @note CCO-CDD-200
 */
u8_t u8_QueueIF_Push(QHandler handler,void* new_request);


/**
 * @brief pop a saved request
 * 
 * @param request if there any request saved, its information will be copied into that pointer
 * @return u8_t 1 if there there any, 0 if queue is empty
 * @note CCO-CDD-207
 */
u8_t u8_QueueIF_Pop(QHandler handler, void* request);


void vid_TaskDelay(u16_t delay);



#endif
