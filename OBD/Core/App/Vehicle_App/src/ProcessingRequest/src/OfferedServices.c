#include "OfferedServices.h"
#include "OBDIIHandler.h"
#include "CANTp.h"
#include "BitMath.h"
#include "QueueInterface.h"
#define UPDATE_PIDS_MAX_FAILS 7

static VehicleAppState GLOB_enumProcessingState = VEDIAPP_IDLE;
static u8_t GLOB_ArrListofDesiredPIDS[] = {
0x3,
0x4,
0x5,
0x0E,
0x0C,
0x0D,
0x0F,
0x11,
0x1F,
0x2F,
0x31,
0x42,
0x43,
0x50,
0x51,
0x33,
0x67,
0x1C,
0x13,
0x06,
0x6c,
};
PUBLIC u8_t GLOB_arrVinNumber[20];
u8_t u8_MakeManualOBDRequest(u8_t mode, u8_t pid){

    bool requestState = 0;
    u32_t timeoutCounter1 = 0;
    u32_t timeoutCounter2 = 0;

    if(mode == OBD_MODE_1){
        requestState = OBDIIRequestMode1(pid);
    }else if(mode == OBD_MODE_9){
        requestState = OBDIIRequestMode9(pid);
    }else{
        requestState = OBDIIRequestModeDTCs(mode);
    }
    

    if(requestState == 1){

        GLOB_enumProcessingState = VEDIAPP_IS_WAITING;
        enum_Comm_StartTimeForRequest();
        while((GLOB_enumProcessingState == VEDIAPP_IS_WAITING) && ((timeoutCounter1 < 150))){
            // wait on notification from ComM, transmit completed or error
            // vid_ComM_Manage();
            // vid_TpManage();
            vid_TaskDelay(1);
            timeoutCounter1++;
        }

        if(GLOB_enumProcessingState == VEDIAPP_TRANSMIT_CPLT){
            enum_Comm_StartTimeForResponse();
            GLOB_enumProcessingState = VEDIAPP_IS_WAITING;
            while((GLOB_enumProcessingState == VEDIAPP_IS_WAITING) && (timeoutCounter2 < 150)){
                // wait on notification from ComM, response completed or error
                // vid_ComM_Manage();
                // vid_TpManage();
                vid_TaskDelay(1);
                timeoutCounter2++;
            }
        }

    }

    return GLOB_enumProcessingState == VEDIAPP_SUCCESS;
}



void vid_dynamicRequest(pToFuncCallbackStaticService receiveCallback){
    u8_t LOC_u8_isDynamic = 0;
    u8_t LOC_u8_isSupported = 0;
    u8_t LOC_u8_requestCheck = 0;
    u8_t LOC_u8_desiredPID = 0;

    OBDResponse_s OBDIIResponse = {0};

    if(receiveCallback != NULLPTR){

        for(u8_t pidNum = 0; pidNum < sizeof(GLOB_ArrListofDesiredPIDS); ++pidNum){
            LOC_u8_desiredPID = GLOB_ArrListofDesiredPIDS[pidNum];
            LOC_u8_isDynamic = u8_getPidType(LOC_u8_desiredPID);
            LOC_u8_isSupported = u8_getSupportInfo(LOC_u8_desiredPID);

            if( LOC_u8_isDynamic == DYNAMIC )
            {
                if( LOC_u8_isSupported == SUPPORTED ){

                    LOC_u8_requestCheck = u8_MakeManualOBDRequest(OBD_MODE_1, LOC_u8_desiredPID);
                    if(LOC_u8_requestCheck == 1){
                        OBDIIReceiveResponse(&OBDIIResponse);
                        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_COLLET_BUFFER); 
                    }else{
                        // error in the request
                        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_ERROR); 
                    }
                }else{
                    // not supported, don't request it
                    receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_NOT_SUPPORTED); // not supported
                }
            }
            
            else{
                // static pid, don't request it
            }

        }
        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_SEND);
    }
}


void vid_staticRequest(pToFuncCallbackStaticService receiveCallback){
    u8_t LOC_u8_isStatic = 0;
    u8_t LOC_u8_isSupported = 0;
    u8_t LOC_u8_requestCheck = 0;
    u8_t LOC_u8_desiredPID = 0;
    
    OBDResponse_s OBDIIResponse = {0};

    if(receiveCallback != NULLPTR){

        // collect the vin number
        receiveCallback(VI_VIN, GLOB_arrVinNumber, sizeof(GLOB_arrVinNumber), NOTIFICATION_COLLECT_VIN);

        // request static data of mode 1
        for(u8_t pidNum = 0; pidNum < MAX_PIDS; ++pidNum){
            LOC_u8_desiredPID = pidNum;
            LOC_u8_isStatic = u8_getPidType(LOC_u8_desiredPID);
            LOC_u8_isSupported = u8_getSupportInfo(LOC_u8_desiredPID);

            if(LOC_u8_isStatic == STATIC)
            {
                if(LOC_u8_isSupported == SUPPORTED){

                    // request then collect it in buffer
                    LOC_u8_requestCheck = u8_MakeManualOBDRequest(OBD_MODE_1, LOC_u8_desiredPID);
                    if(LOC_u8_requestCheck == 1){
                        OBDIIReceiveResponse(&OBDIIResponse);
                        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_COLLET_BUFFER); 
                    }else{
                        // error in the request
                        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_ERROR); 
                    }
                }else{
                    // not supported, don't request it
                    receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_NOT_SUPPORTED); // not supported
                }
            }
            
            else{
                //don't request it because it is not static pid
            }

        }


        receiveCallback(LOC_u8_desiredPID, OBDIIResponse.Buffer, OBDIIResponse.Length, NOTIFICATION_SEND);
    }
}

u8_t u8_update_pids_database(void){
    OBDII_MsgID_e pids_of_request_pidsSupported[7] = {PID_PIDS_SUPPORTED_1_20,PID_PIDS_SUPPORTED_21_40     /*static PIDs used by other application Software components In mode 1*/
                                                     ,PID_PIDS_SUPPORTED_41_60,PID_PIDS_SUPPORTED_61_80
                                                     ,PID_PIDS_SUPPORTED_81_A0,PID_PIDS_SUPPORTED_A1_C0
                                                     ,PID_PIDS_SUPPORTED_C1_E0};
    u32_t LOC_u32SupportedPIDs = 0;
    u8_t LOC_u8_failFlag = 0;
    u32_t LOC_u32_indexValue = 0;
    u8_t LOC_u8_supportBit = 0;
    u8_t LOC_u8_pidNumberInDatabase = 0;

    OBDResponse_s OBDIIResponse = {0};

    // request all PIDS_SUPPORTED data
    for(u8_t pidNum = 0; pidNum < sizeof(pids_of_request_pidsSupported); ++pidNum){
        
        u8_MakeManualOBDRequest(OBD_MODE_1, (u8_t)pids_of_request_pidsSupported[pidNum]);
        if(GLOB_enumProcessingState == VEDIAPP_SUCCESS){
            OBDIIReceiveResponse(&OBDIIResponse);

            // save the values A,B,C,D from OBD response in a u32 variable to help in updating the database
            LOC_u32SupportedPIDs = 
            (
                    ((u32_t)OBDIIResponse.Buffer[D_INDEX]<<0U)   |
                    ((u32_t)OBDIIResponse.Buffer[C_INDEX]<<8U)   |
                    ((u32_t)OBDIIResponse.Buffer[B_INDEX]<<16U)  |
                    ((u32_t)OBDIIResponse.Buffer[A_INDEX]<<24U) 
            );

            // update pids database algorithm
            LOC_u8_pidNumberInDatabase = 31 + (32*pidNum);
            LOC_u32_indexValue = LOC_u32SupportedPIDs;
            for(u8_t bit = 0; bit < 32; ++bit){
                LOC_u8_supportBit = GET_BIT(LOC_u32_indexValue, bit);
                vid_setSupportInfo(LOC_u8_pidNumberInDatabase, LOC_u8_supportBit);
                --LOC_u8_pidNumberInDatabase;
            }

        }else{
            // no response, update pids database with NOT SUPPORTED value
            for(u8_t j = 0; j < 32; ++j){
                vid_setSupportInfo(j+(32*pidNum), NOT_SUPPORTED);
            }

            LOC_u8_failFlag += 1;
        }
    }

    // check if all requests has been failed
    return LOC_u8_failFlag != UPDATE_PIDS_MAX_FAILS;
}



u8_t u8_make_manual_uds_request(UDSList_e uds_request, u8_t did1, u8_t did2){
    // static UdsHandlerStatus_e status_of_handler = 0;
    // enumUdsHandlerApiError_e transmit_state = 0;
    // SduDataUnit_t uds_data_transmit = {0};

    // // prepare transmit structure
    // uds_data_transmit.DiagnosticCanID = 0x7e0;
    // uds_data_transmit.DataPayloadSize = 0;
    // uds_data_transmit.responseCanID = 0x7e8;
    // uds_data_transmit.ServiceOption = (u16_t)(256*(u16_t)did1) + did2;

    // switch (uds_request)
    // {
    // case READ_BY_LOCAL_IDENTIFIER:
    //     transmit_state = enum_RequestReadByIdentifier(&uds_data_transmit);
    //     break;
    // case ECU_RESET:
    //     transmit_state = enum_RequestEcuReset(&uds_data_transmit);
    //     break;
    // case TESTER_PRESENT:
    //     transmit_state = enum_RequestTesterPresent(&uds_data_transmit);
    //     break;
    
    // default:
    //     break;
    // }

    // if(transmit_state == API_OK_TRANSMIT_PENDING){
    //     status_of_handler = enum_GetUdsHandlerStatus();
    //     while((status_of_handler == REQUEST_PENDING_CONFIRMATION) || (status_of_handler == REQUEST_SENT)){
    //         status_of_handler = enum_GetUdsHandlerStatus();
    //     }

    //     if(status_of_handler == REQUEST_SEND_FAILED){
    //         GLOB_enumProcessing_State = VEDIHANDLER_TRANSMIT_ERROR;
    //     }else if(status_of_handler == REQUEST_RESPONSE_FAILED){
    //         GLOB_enumProcessing_State = VEDIHANDLER_RESPONSE_ERROR;
    //     }else{
    //         GLOB_enumProcessing_State = VEDIAPP_SUCCESS;
    //     }
    // }

    return 1;
}


void vid_notificationFunction(TypeOfNotification_t notification){
    if(notification == TRANSMIT_CPLT){
        GLOB_enumProcessingState = VEDIAPP_TRANSMIT_CPLT;
    }
    else if (notification == RECEIVE_CPLT){
        GLOB_enumProcessingState = VEDIAPP_SUCCESS;
    }
    else if (notification == TRANSMIT_TIMEOUT){
        GLOB_enumProcessingState = VEDIHANDLER_TRANSMIT_ERROR;
    }
    else if(notification == RECEIVE_TIMEOUT){
        GLOB_enumProcessingState = VEDIHANDLER_RESPONSE_ERROR;
    }else{
        // error
    }
}
