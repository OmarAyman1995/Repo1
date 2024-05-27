#ifndef __HANDLINGMQTT_H
#define __HANDLINGMQTT_H



#include "typedefs.h"
#include "MQTTSim800.h"
#include "QueueInterface.h"


#define PUBLISH_TOPIC   "pubtopic"
#define SUBSCRIBE_TOPIC "subtopic"


/**
 * @brief used to send data on Mqtt
 * 
 * @param pData data that will be sent on Mqtt
 * @param size size of the data
 * @return u8_t 1 if success, 0 if fail
 */
u8_t u8_HandlingMqtt_Send(u8_t *pData, u32_t size);


/**
 * @brief callback function will be called whenever new message has been recieved
 * 
 * @param message message array
 * @param size size of the message
 */
void vid_HandlingMqtt_Callback(u8_t *message, u32_t size);






#endif
