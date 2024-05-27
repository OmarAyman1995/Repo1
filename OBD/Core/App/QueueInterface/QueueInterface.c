#include "QueueInterface.h"
#include "Vehicle_App.h"
#include "Wireless_App.h"
#include "FreeRTOS.h"
#include "queue.h"

typedef Vehicle_RequestTypedef VehicleQueueDatatype;
typedef Vehicle_RequestTypedef WirelessQueueDatatype;

static QueueHandle_t Arr_Of_Handlers[3] = {0};

static u8_t GLOB_u8isInitialized = 0;

u8_t u8_QueueIF_Init(void){
    u8_t returnValue = 0;

    Arr_Of_Handlers[0] = xQueueCreate(VEHICLE_QUEUE_SIZE, sizeof(VehicleQueueDatatype));
    Arr_Of_Handlers[1] = xQueueCreate(WIRLESS_SEND_QUEUE_SIZE, sizeof(WirelessQueueDatatype));
    Arr_Of_Handlers[2] = xQueueCreate(WIRLESS_RECV_QUEUE_SIZE, 10);

    if( (Arr_Of_Handlers[0] == NULLPTR) || 
        (Arr_Of_Handlers[1] == NULLPTR) || 
        (Arr_Of_Handlers[2] == NULLPTR)){
        returnValue =  0;
    }else{
        GLOB_u8isInitialized = 1;
        returnValue =  1;
    }

    return returnValue;
}



u8_t u8_QueueIF_Push(QHandler handler, void* new_request){
    BaseType_t queueReturn = pdFAIL; 
    u8_t returnValue = 0;

    if(GLOB_u8isInitialized == 1){
        queueReturn = xQueueSend(Arr_Of_Handlers[handler], new_request, 0);
        if(queueReturn == pdPASS){
            returnValue = 1;
        }else{
            returnValue = 0;
        }
    }else{
            returnValue = 0;
    }

    return returnValue;
}



u8_t u8_QueueIF_Pop(QHandler handler, void* request){
    BaseType_t queueReturn = pdFAIL;
    u8_t returnValue = 0;

    if(GLOB_u8isInitialized == 1){
        queueReturn = xQueueReceive(Arr_Of_Handlers[handler], request, 0);
        if(queueReturn == pdPASS){
            returnValue = 1;
        }else{
            returnValue = 0;
        }
    }else{
        returnValue = 0;
    }

    return returnValue;
    
}


void vid_TaskDelay(u16_t delay){
#if FREERTOS == 1
    vTaskDelay(delay);
#else
    HAL_Delay(delay);
#endif
}