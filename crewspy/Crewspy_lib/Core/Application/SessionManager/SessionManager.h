#ifndef __SESSIONMANAGER_H
#define __SESSIONMANAGER_H

#include "GlobalCnfg.h"
#include "SessionManager_Cnfg.h"
#include "UserInterface.h"
#include "Services.h"
#include "Parser.h"
#include "Responder.h"
#include "ServiceHandler.h"
#include "COM_Adapter.h"
#include <string.h>

/*implements state machine*/
/*  Define the states   */
typedef enum {
    LISTEN_STATE,
    PROCESS_STATE,
    RESPOND_STATE,
    ACKWAIT_STATE,
    STARTCOM_STATE
} state_t;


/*  Define the events   */
typedef enum {
    BUFFER_RECEIVED_EVENT,
    SERVICE_FINISH_EVENT,
    RESPONSE_SENT_EVENT,
    ACK_RECEIVED_EVENT,
    START_COM_EVENT,
    END_COM_EVENT,
    PRIVILEGE_SERVICE_RESPOND,
    PRIVILEGE_SERVICE_EXECUTE,
    NULL_EVENT
} event_t;

#define VALUE_OF_ONE                          1
#define PRIVILEGE_FLAGE_ONE                   1
#define MAX_PARAM_IN_ONE_FRAME                10
#define MAX_PARAM_IN_TWO_FRAMES               20
#define MAX_PARAM_IN_THREE_FRAMES             30
#define MAX_PARAM_IN_FOUR_FRAMES              40
#define MAX_PARAM_IN_FIVE_FRAMES              50


void StartComActions(void);
void ListenStateActions(void);
void ProcessStateActions(void);
void ResponseStateActions(void);

void state_machine(void);

#endif
