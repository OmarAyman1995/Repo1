#include "Breakpoint.h"
#include "string.h"
#include "UserInterface.h"
#include "Services.h"

/* Current Size of Parameters Added from a Service to be Sent to Tool */
extern uint8_t SizeOfParams;

/* Array of Parameters that will be Received from Tool */
extern uint8_t ServiceParamtersInRequest[USER_MAX_PARAMETERS];

/* Array of Parameters that will be sent to Tool */
extern uint8_t ServiceParametersInResponse[USER_MAX_PARAMETERS];

/* Current Response Type from a Service to be Sent to Tool */
extern volatile enumRespType_t ServiceResponseType;

uint8_t break_flag = 0;

uint8_t BrkNameBuff[BRKNAME_SIZE] = {0};


void Service_BrkInfo(void){
    /* Set name in response */
    SizeOfParams = (uint8_t)strlen((char*)BrkNameBuff);
    strcpy((char*)ServiceParametersInResponse+1, (char*)BrkNameBuff);
    ServiceParametersInResponse[0] = SizeOfParams;
    ++SizeOfParams;

    ServiceResponseType = POSITIVE_RESPONSE;
}


void Service_BrkContinue(void){
    break_flag = BREAK_SET;
    ServiceResponseType = POSITIVE_RESPONSE;
}


void BrkSetName(uint8_t* name){
    if(name != NULLPTR){
        strcpy((char*)BrkNameBuff, (char*)name);
    }
}

void BrkClearName(void){
    clear_array(BrkNameBuff, BRKNAME_SIZE);
}


void BrkPointMain(void){

    while(break_flag == BREAK_NOTSET){
        CREWSPY_RUN();
    }

    break_flag = BREAK_NOTSET;
    BrkClearName();
}
