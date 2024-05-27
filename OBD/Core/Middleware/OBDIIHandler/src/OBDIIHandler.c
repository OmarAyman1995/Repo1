#include "OBDIIHandler.h"
#include "CANTp.h"
#include "ISO_Uart_Protocols.h"
#include "CAN_ISO_15765.h"
#include <string.h>


#if OBDIIHandler_TEST_ON == 0

/* Private Data */

static volatile OBDIIRequestStatus_e RequestStatus = OBDII_IDLE;
static u8_t ReceivedDatafield[MAX_DATAFIELD_SIZE] = {0};
static u32_t ReceivedDatasize = 0;
static pFunction GLOB_pTx_callback = NULLPTR;
static pFunction GLOB_pRx_callback = NULLPTR;
static OBDII_Protocols currentProtocol = 0;
static u8_t requestedMode = 0;
static u8_t requestedPid = 0;

/* Private Functions */

static bool OBDII_SendAccordingToProtocol(OBDIIRequestFrame_t *request);
static void OBDII_TxCplt(void);
static void OBDII_RxCplt(void);
#else
/* Private Data */

 volatile OBDIIRequestStatus_e RequestStatus = OBDII_IDLE;
 u8_t ReceivedDatafield[MAX_DATAFIELD_SIZE] = {0};
 u32_t ReceivedDatasize = 0;
 pFunction GLOB_pTx_callback = NULLPTR;
 pFunction GLOB_pRx_callback = NULLPTR;
 OBDII_Protocols currentProtocol = 0;
 u8_t requestedMode = 0;
 u8_t requestedPid = 0;

/* Private Functions */

 bool OBDII_SendAccordingToProtocol(OBDIIRequestFrame_t *request);
 void OBDII_TxCplt(void);
 void OBDII_RxCplt(void);

#endif

/* Implementation of public functions */
void OBDII_Initialize(void){
    vid_CanIsoSetTransmitCallBack(OBDII_TxCplt);
    vid_CanIsoSetReceiveCallBack(OBDII_RxCplt);
}

bool OBDII_DetectVehicleProtocol(void){
    bool return_value = 0;
    u32_t listOfBaudrates[2] = {500000, 250000};
    enum_IsoCompliantState canCheck = 0;
    u8_t uartCheck = 0;

    // Initlaize all global variables
    RequestStatus = OBDII_IDLE;

    memset(ReceivedDatafield, 0, MAX_DATAFIELD_SIZE);


    // try all ISO untill one of them success
    canCheck = enum_DetectCANComm(listOfBaudrates, 2); // ISO 15765 (250k and 500k)
    if(canCheck == 1){
        currentProtocol = ISO_CAN_15765;
    }else{

        uartCheck = u8_UartISO_InitSequence();  // ISO 14230 and ISO 9141
        if(uartCheck == 1){
            currentProtocol = ISO_UART_14230;
        }
    }

    return_value = (canCheck == 1) || (uartCheck == 1);
    return return_value;
}


bool OBDIIRequestMode1(OBDII_MsgID_e pid){
    bool return_value = 0;
    OBDIIRequestFrame_t request_frame = {
        .bytes = 2,.mode = 1, .pid = (u8_t)pid, .A = 0xAA, .B = 0xAA, .C = 0xAA, .D = 0xAA
    };

    
    if(pid < OBD_MESSAGES_SIZE){   
      
        return_value = OBDII_SendAccordingToProtocol(&request_frame);
        requestedMode = request_frame.mode;
        requestedPid = request_frame.pid;
    }else{
        return_value = 0;
    }

    return return_value;
}


bool OBDIIRequestMode2(OBDII_MsgID_e  pid, u8_t frame_number){
    bool return_value = 0;
    OBDIIRequestFrame_t request_frame = {
        .bytes = 3,.mode = 2, .pid = (u8_t)pid, .A = frame_number, .B = 0xAA, .C = 0xAA, .D = 0xAA
    };

    if(pid < OBD_MESSAGES_SIZE){

        return_value = OBDII_SendAccordingToProtocol(&request_frame);
        requestedMode = request_frame.mode;
        requestedPid = request_frame.pid;
    }else{
        return_value = 0;
    }

    return return_value;
}


bool OBDIIRequestModeDTCs(OBDII_DTCsRequest_e msg_id){
    bool return_value = 0;
    OBDIIRequestFrame_t request_frame = {
        .bytes = 1,.mode = (u8_t)msg_id, .pid = 0xAA, .A = 0xAA, .B = 0xAA, .C = 0xAA, .D = 0xAA
    };

    // we still don't know if the response requires ISO TP or not
    return_value = OBDII_SendAccordingToProtocol(&request_frame);
    requestedMode = request_frame.mode;
    requestedPid = request_frame.pid;
    return return_value;

}


bool OBDIIRequestMode9(OBDII_VehicleInfoID_e  pid){
    bool return_value = 0;
    OBDIIRequestFrame_t request_frame = {
        .bytes = 2,.mode = 9, .pid = (u8_t)pid, .A = 0xAA, .B = 0xAA, .C = 0xAA, .D = 0xAA
    };

    if(pid <= INUSE_PERFORMANCE_TRACK_FOR_COMPRESSION_IGNITION_VEHICLES){

        // transmit from the proper protocol (for now its CANTp)
        vid_IsoTpSet(OBDII_FLOWCONTROL_CANID);
        return_value = OBDII_SendAccordingToProtocol(&request_frame);
        requestedMode = request_frame.mode;
        requestedPid = request_frame.pid;
    }else{
        return_value = 0;
    }

    return return_value;
}




bool OBDIIReceiveResponse(OBDResponse_s* outputResponse){
    bool functionReturn = 0;

    if(outputResponse != NULLPTR){

        // copy all information to user
        memcpy(outputResponse->Buffer, ReceivedDatafield, ReceivedDatasize);
        outputResponse->Length = ReceivedDatasize;
        outputResponse->Mode = requestedMode;
        outputResponse->Pid = requestedPid;

        // reset all
        memset(ReceivedDatafield, 0, sizeof(ReceivedDatafield));
        requestedMode = 0;
        requestedPid = 0;

        RequestStatus = OBDII_IDLE;
        functionReturn = 1;
    }else{

        functionReturn = 0;
    }

    return functionReturn;
}




bool OBDII_SendAccordingToProtocol(OBDIIRequestFrame_t *request){
    u8_t canDataArr[8] = {0};
    bool functionReturn = 0;
    enum_CanIsoErrorState checkCANSend = 0;
    u8_t checkUARTSend = 0;

    if(currentProtocol == ISO_UART_14230){
        // uart iso
        checkUARTSend = u8_UartISO_Send(request->mode, request->pid);
        if(checkUARTSend == 1){
            functionReturn = 1;
        }else{
            functionReturn = 0;
        }
        
    }else{
        // can iso
        canDataArr[0] = request->bytes;
        canDataArr[1] = request->mode;
        canDataArr[2] = request->pid;
        canDataArr[3] = request->A;
        canDataArr[4] = request->B;
        canDataArr[5] = request->C;
        canDataArr[6] = request->D;
        canDataArr[7] = 0xAA;
        checkCANSend = enum_CanIsoSendData(canDataArr, 8);
        if(checkCANSend == CAN_ISO_OK){
            functionReturn = 1;
        }else{
            functionReturn = 0;
        }
    }

    return functionReturn;
}

void OBDII_TxCplt(void){
    RequestStatus = OBDII_TRANSMIT_SENT;
    if(GLOB_pTx_callback != NULLPTR){
        GLOB_pTx_callback();
    }
}


void OBDII_RxCplt(void){
    u8_t *response = NULLPTR;
    u32_t size = 0;
    TpReceiveDataUnitInfo_t cantp_s = {0};
    
    // receive according to the proper protocol
    if(currentProtocol == ISO_UART_14230){
        // uart iso
        u8_UartISO_Receive(ReceivedDatafield);
        ReceivedDatasize = ReceivedDatafield[0];
    }else{
        // can iso
        CanIsoReceive(cantp_s.u8TpDataPayload,&cantp_s.u8DataPayloadSize);
        size = cantp_s.u8DataPayloadSize;
        response = cantp_s.u8TpDataPayload;
        
        // save the datafield and size
        if(size < 50){
            memcpy(ReceivedDatafield, response, size);
        }
        ReceivedDatasize = size;
    }

    RequestStatus = OBDII_RESPONSE_CPLT;

    if(GLOB_pRx_callback != NULLPTR){
        GLOB_pRx_callback();
    }

}


void OBDII_SetTxCallback(pFunction tx_callback){
    GLOB_pTx_callback = tx_callback;
}

void OBDII_SetRxCallback(pFunction Rx_callback){
    GLOB_pRx_callback = Rx_callback;
}
