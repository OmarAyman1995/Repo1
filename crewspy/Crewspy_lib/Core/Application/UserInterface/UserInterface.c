#include "GlobalCnfg.h"
#include "UserInterface.h"
#include "SessionManager.h"
#include "ServiceHandler.h"
#include "Responder.h"
#include "Parser.h"
#include "COM_Adapter.h"
#include "HWDepServices.h"
#include "HWIndepServices.h"
#include "UartTp.h"
#include "Address.h"
#include "Uart_Integration.h"
#include "Timer_Integration.h"
#include "Breakpoint.h"


/* Current Size of Parameters Added from a Service to be Sent to Tool*/
extern uint8_t SizeOfParams;

/* Current Response Type from a Service to be Sent to Tool */
extern volatile enumRespType_t ServiceResponseType;

/* Array of Parameters that will be sent to Tool */
extern uint8_t ServiceParametersInResponse[USER_MAX_PARAMETERS];

/* Array of Parameters that will be Received from Tool */
extern uint8_t ServiceParamtersInRequest[USER_MAX_PARAMETERS];

static uint8_t isCrewInitCalled = FALSE;

/**
 * @brief Register the Service to Library to be Requested from CrewConnect PC Tool
 *
 * @param service_id ID of Service
 * @param addr Address of Service
 */
void CREWSPY_REGISTER_SERVICE(uint8_t service_id, function_ptr addr)
{
    ServHndl_RegisterService(service_id, addr);
}


/**
 * @brief Get the Desired Parameter that is Received from CrewConnect PC Tool from its Index 
 *
 * @param index_of_param Index of Paramater
 * @return Value of Parameter
 */
uint8_t CREWSPY_GET_PARAM(uint8_t index_of_param)
{
   return ServiceParamtersInRequest[index_of_param];
}


/**
 * @brief Set Response Type POSITIVE_RESPONSE/NEGATIVE_RESPONSE to be Sent to CrewConnect PC tool
 *
 * @param response_type this can be either POSITIVE_RESPONSE/NEGATIVE_RESPONSE
 */
void CREWSPY_SET_RESPONSE_TYPE(uint8_t response_type)
{
    ServiceResponseType = response_type;
}


/**
 * @brief Set Paramater to be Sent to CrewConnect PC Tool
 *
 * @param parameter Value of Paramter in the Array
 * @param paramIndex Index of Parameter in the Array
 */
void CREWSPY_SET_PARAM(uint8_t paramValue, uint8_t paramIndex)
{
    ++SizeOfParams;
   ServiceParametersInResponse[paramIndex] = paramValue;
}


/**
 * @brief Make the id of service to be execute after response
 *
 * @param id id of the service
 */
void CREWSPY_SET_PRIVILEGE_SERVICE(uint8_t id)
{
    ServHndl_SetPrivilege(id);
}


/**
 * @brief Initialize CrewSpy library neccessary peripherals and modules
 *
 */
void CREWSPY_INIT(void)
{

    /*MCAL Initialize Start*/
    vid_Uart_Integration_SetCllbck(UartInterruptProcessing);
    enum_Uart_Integration_Init(0);
    vid_Timer_Init();
    clock_Peripherals_Init();
    /***MCAL Initialize End***/

    /*initialize state machine*/
    CREWSPY_REGISTER_SERVICE(READ_SERIVCE,              Service_ReadVariable);
    CREWSPY_REGISTER_SERVICE(READ_GENERAL_REGISTER,     Service_ReadGPR);
    CREWSPY_REGISTER_SERVICE(READ_REGISTER_SERIVCE,     Service_ReadRegister);
    CREWSPY_REGISTER_SERVICE(WRITE_SERIVCE,             Service_WriteVariable);
    CREWSPY_REGISTER_SERVICE(WRITE_BIT_SERIVCE,         Service_WriteBit);
    CREWSPY_REGISTER_SERVICE(WRITE_REGISTER_SERIVCE,    Service_WriteRegister);
    CREWSPY_REGISTER_SERVICE(GETVERSION_SERIVCE,        Service_GetVersion);
    CREWSPY_REGISTER_SERVICE(SOFTWARERESET_SERIVCE,     Service_SoftwareReset);
    CREWSPY_REGISTER_SERVICE(UNITTESTING_SERIVCE,       Service_UnitTesting);
    CREWSPY_REGISTER_SERVICE(MAXSTACK_SERIVCE,          Service_StackConsumption);
    CREWSPY_REGISTER_SERVICE(EXECUTIONTIME_SERIVCE,     Service_ExecutionTime);
    CREWSPY_REGISTER_SERVICE(BREAKPOINT_CONT_SERIVCE,   Service_BrkContinue);
    CREWSPY_REGISTER_SERVICE(BREAKPOINT_INFO_SERIVCE,   Service_BrkInfo);

    /* Let Software Reset Service Executes After Response */
    CREWSPY_SET_PRIVILEGE_SERVICE(SOFTWARERESET_SERIVCE);

    isCrewInitCalled = TRUE;
}


/**
 * @brief Call this function in dynamic environment
 *
 */
uint8_t CREWSPY_RUN(void){

    uint8_t retval = FALSE;

    if(TRUE == isCrewInitCalled){
        /* Run State Machine of The Library*/
        state_machine();
        retval = TRUE;
    }else{
        retval = FALSE;
    }

    return retval;
}


/**
 * @brief API to make software breakpoint at user code
 * 
 * @param breakname 
 */
void BRK(char* breakname){
    uint8_t size_to_send = 0;
    uint8_t buffer[FRAME_MAX_SIZE] = {0};

    if(breakname != NULLPTR){

        BrkSetName((uint8_t*)breakname);
        Service_BrkInfo();
        Responder_PutServiceIDAndParams(buffer,
                      BREAKPOINT_INFO_SERIVCE,
                      ServiceParametersInResponse,
                      USER_MAX_PARAMETERS);

        if(SizeOfParams <= MAX_PARAM_IN_ONE_FRAME)
        {
            size_to_send = MAX_PARAM_IN_ONE_FRAME + VALUE_OF_ONE;
        }
        else if( SizeOfParams <= MAX_PARAM_IN_TWO_FRAMES)
        {
            size_to_send = MAX_PARAM_IN_TWO_FRAMES + VALUE_OF_ONE;
        }else{
            /* misra c*/
        }
        /* Send the Response Buffer to UartTp to add Frame Constants then Send it to Tool */
        ComAdapterSendBuffer(buffer, ServiceResponseType, size_to_send);

        /* Reset for Next Request from Tool */
        clear_array(ServiceParametersInResponse, USER_MAX_PARAMETERS);
        clear_array(ServiceParamtersInRequest, USER_MAX_PARAMETERS);
        SizeOfParams = 0;

        /* Logic Code of breakpoint */
        BrkPointMain();
    }
}
