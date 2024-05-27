#include "HandlingMqtt.h"

#define MAX_MQTT_MESSAGE 20



void vid_HandlingMqtt_Callback(u8_t *message, u32_t size){
    
    if(size < MAX_MQTT_MESSAGE){
        u8_QueueIF_Push(WIRELESS_RECV_HANDLER, message+1);
    }
}



u8_t u8_HandlingMqtt_Send(u8_t *pData, u32_t size){
    return u8_MQTT_Publish(PUBLISH_TOPIC, pData, size);
}
