#include "SessionManager.h"


/* Array of Parameters that will be Received from Tool */
uint8_t ServiceParamtersInRequest[USER_MAX_PARAMETERS ]= {0};

/* Array of Parameters that will be sent to Tool */
uint8_t ServiceParametersInResponse[USER_MAX_PARAMETERS] = {0};

/* Current Response Type from a Service to be Sent to Tool */
volatile enumRespType_t ServiceResponseType = 0;

/* initialize the state machine with Listen state */
state_t current_state = STARTCOM_STATE;
event_t current_event = NULL_EVENT;

static uint8_t Shared_Service_ID   = 0;

/* Current Size of Parameters Added from a Service to be Sent to Tool*/
uint8_t SizeOfParams = 0;


/*Define States*/
/**
 * @brief stay here as long as start com request not received
 * if start com has been requested, switch to ListenState
 */
void StartComActions(void)
{
    uint8_t buffer[FRAME_MAX_SIZE] = {0};
    uint8_t service_id = 0;
    uint8_t IsBufferReady = 0;
    uint8_t numberOfFrames = 0;
    IsBufferReady = ComBufferIsReady();
    if(1 == IsBufferReady)
    {
        ComAdapterGetBuffer(buffer, &numberOfFrames);
        service_id = Parse_ServiceID(buffer);
        if(STARTCOM_SERVICE == service_id)
        {
            Responder_SendTargetConfigs();
            current_event = START_COM_EVENT;
        }else{
            /*stay in this state*/
        }
    }else{
        /*stay in this state*/
    }
}


/**
 * @brief stay here as long as buffer from Uart is not ready
 * if buffer is came, send ack, store the data came, make the switch logic
 */
void ListenStateActions(void){

    uint8_t DataInRequest[FRAME_MAX_SIZE] = {0};
    uint8_t service_id = 0;
    uint8_t IsBufferReady = 0;
    uint8_t numberOfFrames = 0;
    uint8_t privilege_flag = 0;
    uint8_t u8counter = 0;

    /* Check if New Buffer Received in UART*/
    IsBufferReady = ComBufferIsReady();
    if(1 == IsBufferReady)
    {
        /* Get The Buffer */
        ComAdapterGetBuffer(DataInRequest, &numberOfFrames);

        /* Get Service ID */
        service_id = Parse_ServiceID(DataInRequest);
        Shared_Service_ID = service_id;

        /* Check if the frame is ENDCOM Frame */
        if(ENDCOM_SERVICE == service_id)
        {
            /* Trigger End Com Event to switch to Start Com State*/
            current_event = END_COM_EVENT;
        }else{
            /* Otherwise it is a Normal Service Request Frame */

            /* Put the Data came in request to the ServiceParamtersInRequest array to make Services Use Them */
            for((u8counter=0) ; u8counter < ((numberOfFrames*NUM_OF_PARMS)+VALUE_OF_ONE); (u8counter++))
            {
                ServiceParamtersInRequest[u8counter]= DataInRequest[u8counter+VALUE_OF_ONE];
            }

            /* Switching Logic, Check the Privilege Flag of the Requested Service*/
            privilege_flag = ServHndl_getPrivilege(service_id);
            if( PRIVILEGE_FLAGE_ONE == privilege_flag){
                current_event = PRIVILEGE_SERVICE_RESPOND;

            }else{
                current_event = BUFFER_RECEIVED_EVENT;

            }
        }

    }else{
        /*stay in this state*/
    }
}


/**
 * @brief Execute the Service based on The Service ID that is obtained from ListenState
 */
void ProcessStateActions(void){

    ServHndl_ExecuteService(Shared_Service_ID);
    Shared_Service_ID = 0;

    /* Switching Logic */
    current_event = SERVICE_FINISH_EVENT;
}


/**
 * @brief  Create Response frame based on Service parameters and Service ID
 * then send it to UartTp Layer
 */

void ResponseStateActions(void){

    uint8_t buffer[FRAME_MAX_SIZE] = {0};
    uint8_t current_service = 0;
    uint8_t size_to_send = 0;


    /* Get the Executed Service ID*/
    current_service = ServHndl_GetCurrentService();
    if(current_event == PRIVILEGE_SERVICE_RESPOND){
        current_service = SOFTWARERESET_SERIVCE;
    }

    /* Create Response Buffer[Service ID, Parameters] to be sent to UartTp */
    Responder_PutServiceIDAndParams(buffer,
                  current_service,
                  ServiceParametersInResponse,
                  USER_MAX_PARAMETERS);

    /* Calculate Size of the Response Buffer for UartTp */
    if(SizeOfParams <= MAX_PARAM_IN_ONE_FRAME)
    {
        size_to_send = MAX_PARAM_IN_ONE_FRAME + VALUE_OF_ONE;
    }
    else if( SizeOfParams <= MAX_PARAM_IN_TWO_FRAMES)
    {
        size_to_send = MAX_PARAM_IN_TWO_FRAMES + VALUE_OF_ONE;
    }
    else if( SizeOfParams <= MAX_PARAM_IN_THREE_FRAMES)
    {
        size_to_send = MAX_PARAM_IN_THREE_FRAMES + VALUE_OF_ONE;
    }
    else if( SizeOfParams <= MAX_PARAM_IN_FOUR_FRAMES)
    {
        size_to_send = MAX_PARAM_IN_FOUR_FRAMES + VALUE_OF_ONE;
    }
    else if( SizeOfParams <= MAX_PARAM_IN_FIVE_FRAMES)
    {
        size_to_send = MAX_PARAM_IN_FIVE_FRAMES + VALUE_OF_ONE;
    }else{
        /*misra c*/
    }

    /* Send the Response Buffer to UartTp to add Frame Constants then Send it to Tool */
    ComAdapterSendBuffer(buffer, ServiceResponseType, size_to_send);

    /* Reset for Next Request from Tool */
    clear_array(ServiceParametersInResponse, USER_MAX_PARAMETERS);
    clear_array(ServiceParamtersInRequest, USER_MAX_PARAMETERS);
    SizeOfParams = 0;

    /* Switching Logic */
    current_event = RESPONSE_SENT_EVENT;
}



/**
 * @brief State Machine of the Library
 *
 */
void state_machine(void) {

    switch(current_state)
    {
    case STARTCOM_STATE:
        StartComActions();
        if (current_event == START_COM_EVENT) {
            current_state = LISTEN_STATE;
        }
        break;
    case LISTEN_STATE:
        ListenStateActions();
        if(current_event == BUFFER_RECEIVED_EVENT){
            ProcessStateActions();
            ResponseStateActions();
        }else if(current_event == PRIVILEGE_SERVICE_RESPOND){
            ResponseStateActions();
            ProcessStateActions();
        }else if (current_event == END_COM_EVENT)
        {
            current_state = STARTCOM_STATE;
        }else{
            /* misra c */
        }
        break;
    default:
        break;
    }
}
