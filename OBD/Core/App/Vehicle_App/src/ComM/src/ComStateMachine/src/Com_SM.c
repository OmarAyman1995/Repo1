#include "Com_SM.h"
#include "string.h"
/* state machine pointers */

static ComStatus_e GLOB_enum_currentState = IDLE;
static u8_t GLOB_u8_isRequestTransmitted = 0;

extern void vid_notificationFunction(TypeOfNotification_t notification);


extern u32_t GLOB_u32ReceiveTimeout;
extern u32_t GLOB_u32TransmitTimeout;

extern volatile u8_t GLOB_u8ReceiveCplt;
extern volatile u8_t GLOB_u8TransmitCplt;

extern u8_t isThereOngoingRequest;
extern u8_t isThereOngoingResponse;



void vid_state_machine_switchto(ComStatus_e new_state){
    GLOB_enum_currentState = new_state;
}


/* States Actions */

void vid_make_transmit_actions(void){

    GLOB_u8_isRequestTransmitted = 1;
}

void transmit_done_actions(void){

    vid_notificationFunction(TRANSMIT_CPLT);

    isThereOngoingRequest = 0;
    GLOB_u8TransmitCplt = 0;
    GLOB_u8_isRequestTransmitted = 0;
    
}

void vid_make_receive_actions(void){

    vid_notificationFunction(RECEIVE_CPLT);  
    GLOB_u32ReceiveTimeout = 0;

    isThereOngoingResponse = 0;
    GLOB_u8ReceiveCplt = 0;
}

void vid_idle_actions(void){
    /* Do Nothing */
}

void vid_waiting_receive_actions(void){

    ++GLOB_u32ReceiveTimeout;
}

void vid_receive_timeout_actions(void){

    vid_notificationFunction(RECEIVE_TIMEOUT);
    
    GLOB_u32ReceiveTimeout = 0;
    isThereOngoingResponse = 0;
}

void vid_transmit_timeout_actions(void){

    vid_notificationFunction(TRANSMIT_TIMEOUT);

    GLOB_u32TransmitTimeout = 0;
    isThereOngoingRequest = 0;
}

void vid_waiting_transmit_actions(void){
    ++GLOB_u32TransmitTimeout;
}

// delegates the switching logic between states according to the passed arguments
ComStatus_e enum_determineState( bool isReceiveQueueEmpty,
                            bool isTransmitQueueEmpty,
                            bool isReceiveTimeout,
                            bool isReceiveCplt,
                            bool isTransmitTimeout,
                            bool isTransmitCplt) {

    ComStatus_e LOC_enum_retvalue = 0;

    // determine the state according the switching logic information
    if (isReceiveQueueEmpty && isTransmitQueueEmpty) {
        LOC_enum_retvalue = IDLE;

    } else if (isReceiveQueueEmpty && (!isTransmitQueueEmpty)) {

        if(isTransmitTimeout){
            LOC_enum_retvalue = TRANSMIT_TIMEOUT_STATE;
        }else if(!isTransmitCplt){
            LOC_enum_retvalue = WAITING_TRANSMIT_STATE;
        }else{
            LOC_enum_retvalue = TRANSMIT_DONE;
        }

    } else if ((!isReceiveQueueEmpty) && isReceiveTimeout) {
        LOC_enum_retvalue = RECEIVE_TIMEOUT_STATE;

    } else if ((!isReceiveQueueEmpty) && (!isReceiveTimeout) && isReceiveCplt) {
        LOC_enum_retvalue = RECEIVING_STATE;

    } else if((!isReceiveQueueEmpty) && (!isReceiveTimeout) && (!isReceiveCplt)){
        LOC_enum_retvalue = WAITING_RECEIVE_STATE;

    }else{
        // stay on the same state
        LOC_enum_retvalue = GLOB_enum_currentState;
    }

    return LOC_enum_retvalue;
}

void vid_state_machine_run(void){
    switch (GLOB_enum_currentState)
    {
    case IDLE:
        vid_idle_actions();
        break;
    case TRANSMITTING_STATE:
        vid_make_transmit_actions();
        break;
    case RECEIVING_STATE:
        vid_make_receive_actions();
        break;
    case RECEIVE_TIMEOUT_STATE:
        vid_receive_timeout_actions();
        break;
    case WAITING_RECEIVE_STATE:
        vid_waiting_receive_actions();
        break;
    case WAITING_TRANSMIT_STATE:
        vid_waiting_transmit_actions();
        break;
    case TRANSMIT_TIMEOUT_STATE:
        vid_transmit_timeout_actions();
        break;
    case TRANSMIT_DONE:
        transmit_done_actions();
        break;
    default:
    }
}
