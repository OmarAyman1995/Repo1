#include "ComM.h"
#include <stdbool.h>
#include "OBDIIHandler.h"
#include "UDSHandler.h"
#include "string.h"


u32_t GLOB_u32ReceiveTimeout = 0;
u32_t GLOB_u32TransmitTimeout = 0;

volatile u8_t GLOB_u8ReceiveCplt = 0;
volatile u8_t GLOB_u8TransmitCplt = 0;

u8_t isThereOngoingRequest = 0;
u8_t isThereOngoingResponse = 0;



void vid_ComM_init(void){

    // initialize all global variables
    GLOB_u32ReceiveTimeout = 0;
    GLOB_u32TransmitTimeout = 0;
    GLOB_u8ReceiveCplt = 0;
    GLOB_u8TransmitCplt = 0;

    OBDII_SetTxCallback(vid_Comm_TransmitCallback);
    OBDII_SetRxCallback(vid_Comm_ReceiveCallback);
}


void vid_ComM_Manage(void){


    ComStatus_e LOC_enum_determinedState = IDLE;

    // retreive information of CanComm events
    bool isReceiveQueueEmpty  = (isThereOngoingResponse  == FALSE);
    bool isTransmitQueueEmpty = (isThereOngoingRequest == FALSE);
    bool isReceiveTimeout     = (GLOB_u32ReceiveTimeout > REQUEST_TIMEOUT);
    bool isReceiveCplt        = (GLOB_u8ReceiveCplt == 1);
    bool isTransmitTimeout    = (GLOB_u32TransmitTimeout > REQUEST_TIMEOUT);
    bool isTransmitCplt       = (GLOB_u8TransmitCplt == 1);

    LOC_enum_determinedState = enum_determineState(isReceiveQueueEmpty,
                           isTransmitQueueEmpty,
                           isReceiveTimeout,
                           isReceiveCplt,
                           isTransmitTimeout,
                           isTransmitCplt);

    // execute the state behavior that is delegated to the state machine component
    vid_state_machine_switchto(LOC_enum_determinedState);
    vid_state_machine_run();
}



void enum_Comm_StartTimeForRequest(void){
    isThereOngoingRequest = 1;

}

void enum_Comm_StartTimeForResponse(void){
    isThereOngoingResponse = 1;
}



void vid_Comm_ReceiveCallback(void){
    GLOB_u8ReceiveCplt = 1;
}

void vid_Comm_TransmitCallback(void){
    GLOB_u8TransmitCplt = 1;
}
