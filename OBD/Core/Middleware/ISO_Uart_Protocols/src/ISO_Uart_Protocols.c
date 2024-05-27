#include "ISO_Uart_Protocols.h"
#include "string.h"
#include "PIDsDatabase.h"

#define STANDARD9141_KEY_BYTE_VALUE_1 0x08
#define STANDARD9141_KEY_BYTE_VALUE_2 0x96
#define STANDARD14230_KEY_BYTE 0x8F
#define STANDARD_SYNC_BYTE 0x55

#define STANDARD_FRAME_SIZE 6
#define STANDARD_HEADER_SIZE 4
#define STANDARD_CHECKSUM_INDEX 5
#define STANDARD_RESPONSE_BUFFER_SIZE 3


void emptyFunction(void){
    /*left empty*/
}

#if TEST_ON == 1
u8_t GLOB_u8vehicleISO = 0;
pFunction GLOB_pUserCallback = NULLPTR;
u8_t GLOB_arrVehicleResponse[50] = {0};
u8_t GLOB_arrDatafield[25] = {0};
u8_t GLOB_u8ResponseCounter = 0;
u8_t GLOB_u8UartByte = 0;
u8_t GLOB_u8responseLength = 0;
#else
PRIVATE u8_t GLOB_u8vehicleISO = 0;
PRIVATE pFunction GLOB_pUserCallback = emptyFunction;
PRIVATE u8_t GLOB_arrVehicleResponse[50] = {0};
PRIVATE u8_t GLOB_arrDatafield[25] = {0};
PRIVATE u8_t GLOB_u8ResponseCounter = 0;
PRIVATE u8_t GLOB_u8UartByte = 0;
PRIVATE u8_t GLOB_u8responseLength = 0;
#endif






/**
 * @brief calculates LOC_u32_checksum byte to complete the request message structure
 * 
 * @param LOC_arr_Buffer 
 * @param LOC_u32_size 
 * @return uint8_t the checksum byte
 */
static u8_t calculateChecksum(u8_t LOC_arr_Buffer[], u32_t LOC_u32_size){
    u32_t LOC_u32_checksum = 0;

    for(u8_t i = 0; i < LOC_u32_size; ++i){
        LOC_u32_checksum += LOC_arr_Buffer[i];
    }

    return (u8_t)LOC_u32_checksum;
}


static u8_t determineProtocol(u8_t LOC_u8_keybyte){
    u8_t LOC_u8_Protocol = 0;

    if((LOC_u8_keybyte == STANDARD9141_KEY_BYTE_VALUE_1) || (LOC_u8_keybyte == STANDARD9141_KEY_BYTE_VALUE_2)){
        LOC_u8_Protocol = VEHICLE_ISO_9141;
    }else if(LOC_u8_keybyte == STANDARD14230_KEY_BYTE){
        LOC_u8_Protocol = VEHICLE_ISO_14230;
    }else{
        LOC_u8_Protocol = VEHICLE_PROT_ERR;
    }

    return LOC_u8_Protocol;
}

/**
 * @brief makes fast initialize sequence
 * 
 * @return uint8_t 1 successed, 0 failed
 */
u8_t u8_fastInitialize(void){
    u8_t LOC_u8_checkSuccess = 0;
    u8_t LOC_u8_checkUart = 0;
    u8_t LOC_arr_InitRequest[] =      {0xC1,0x33,0xF1,0x81,0x66};
    u8_t LOC_u8_ReceiveBuffer[STANDARD_RESPONSE_BUFFER_SIZE] = {0};
    u8_t LOC_u8_ackByte = 0;

    IsoUartInit10400bps();
    LOC_u8_checkUart = u8_UartSend(LOC_arr_InitRequest, sizeof(LOC_arr_InitRequest));
    LOC_u8_checkUart = u8_UartReceive(LOC_u8_ReceiveBuffer, sizeof(LOC_u8_ReceiveBuffer));

    if((LOC_u8_ReceiveBuffer[0] == STANDARD_SYNC_BYTE) && (LOC_u8_checkUart == 1)){
        LOC_u8_checkSuccess = 1;
        LOC_u8_ackByte = ~LOC_u8_ReceiveBuffer[2]; // second key byte must be inverted and acknowledged
        LOC_u8_checkUart = u8_UartSend(&LOC_u8_ackByte, 1);
    }else{
       LOC_u8_checkSuccess = 0;
    }

    GLOB_u8vehicleISO = determineProtocol(LOC_u8_ReceiveBuffer[2]);

    return LOC_u8_checkSuccess && LOC_u8_checkUart;
}

/**
 * @brief makes slow initialize sequence
 * 
 * @return uint8_t 1 successed, 0 failed
 */
u8_t u8_slowInitialize(void){
    u8_t LOC_u8_checkSuccess = 0;
    u8_t LOC_u8_checkUart = 0;
    u8_t LOC_arr_InitRequest[] = {0x33};
    u8_t LOC_u8_ReceiveBuffer[3] = {0};
    u8_t LOC_u8_ackByte = 0;
    u8_t LOC_u8_syncByte = 0;
    u8_t LOC_u8_keyByte1 = 0;
    u8_t LOC_u8_keyByte2 = 0;

    IsoUartInit5bps();
    LOC_u8_checkUart = u8_UartSend(LOC_arr_InitRequest, sizeof(LOC_arr_InitRequest));
    LOC_u8_checkUart = u8_UartReceive(LOC_u8_ReceiveBuffer, STANDARD_RESPONSE_BUFFER_SIZE);

    // check vehicle has responded successfully or not
    LOC_u8_syncByte = LOC_u8_ReceiveBuffer[0];
    LOC_u8_keyByte1 = LOC_u8_ReceiveBuffer[1];
    LOC_u8_keyByte2 = LOC_u8_ReceiveBuffer[2];
    if((LOC_u8_syncByte == STANDARD_SYNC_BYTE) && (LOC_u8_checkUart == 1)){
        LOC_u8_checkSuccess = 1;
        LOC_u8_ackByte = ~LOC_u8_keyByte2; // second key byte must be inverted and acknowledged
        LOC_u8_checkUart = u8_UartSend(&LOC_u8_ackByte, 1);
    }else{
       LOC_u8_checkSuccess = 0;
    }

    // determine which protocol 14230 or 9141 based on the second key byte
    GLOB_u8vehicleISO = determineProtocol(LOC_u8_keyByte2);

    return LOC_u8_checkSuccess && LOC_u8_checkUart;
}


u8_t u8_UartISO_InitSequence(void){
    u8_t LOC_u8_checkSuccess = 0;

    // try fast initialization
    LOC_u8_checkSuccess = u8_fastInitialize();

    if(LOC_u8_checkSuccess != 1){
        // if fast initialization didn't successed, try slow initialization
        LOC_u8_checkSuccess = u8_slowInitialize();
    }

    return LOC_u8_checkSuccess;
}


u8_t u8_UartISO_Send(u8_t mode, u8_t pid){

    u8_t LOC_arr_ISO14230_frame[STANDARD_FRAME_SIZE] = {0xC2,0x33,0xF1,mode,pid,0};
    u8_t LOC_arr_ISO9141_frame[STANDARD_FRAME_SIZE] =  {0x68,0x6A,0xF1,mode,pid,0};
    u8_t LOC_u8_checksumByte = 0;
    u8_t LOC_u8_returnValue = 0;

    GLOB_u8responseLength = STANDARD_HEADER_SIZE + 2; // header length + mode 1byte + pid 1byte
    GLOB_u8responseLength += u8_getReturnedBytes(pid);

    // reset buffers
    memset(GLOB_arrVehicleResponse, 0, GLOB_u8ResponseCounter);
    memset(GLOB_arrDatafield, 0, sizeof(GLOB_arrDatafield));
    GLOB_u8ResponseCounter = 0;

    if(GLOB_u8vehicleISO == VEHICLE_ISO_14230){
        LOC_u8_checksumByte = calculateChecksum(LOC_arr_ISO14230_frame, STANDARD_FRAME_SIZE);
        LOC_arr_ISO14230_frame[STANDARD_CHECKSUM_INDEX] = LOC_u8_checksumByte;
        LOC_u8_returnValue = u8_UartSend(LOC_arr_ISO14230_frame, sizeof(LOC_arr_ISO14230_frame));

    }else if(GLOB_u8vehicleISO == VEHICLE_ISO_9141){
        LOC_u8_checksumByte = calculateChecksum(LOC_arr_ISO9141_frame, STANDARD_FRAME_SIZE);
        LOC_arr_ISO9141_frame[STANDARD_CHECKSUM_INDEX] = LOC_u8_checksumByte;
        LOC_u8_returnValue = u8_UartSend(LOC_arr_ISO9141_frame, sizeof(LOC_arr_ISO9141_frame));
    }else{
        // error
        LOC_u8_returnValue = 0;
    }
    

    u8_UartReceiveIT(&GLOB_u8UartByte,1);

    return LOC_u8_returnValue;
}



void vid_UartISO_RegisterCallback(pFunction LOC_p_callback){
    GLOB_pUserCallback = LOC_p_callback;
}


void vid_UartISO_MCALCallback(void){
    // this function called whenever one byte recieved at UART
    
    // store the received byte in the buffer
    GLOB_arrVehicleResponse[GLOB_u8ResponseCounter++] = GLOB_u8UartByte;

    // check if it is last byte or not
    if(GLOB_u8ResponseCounter == GLOB_u8responseLength){

        if(GLOB_pUserCallback != NULLPTR){
            GLOB_pUserCallback();
        }

    }else{
        u8_UartReceiveIT(&GLOB_u8UartByte,1);
    }
}


u8_t u8_getUartProtocol(void){
    return GLOB_u8vehicleISO;
}


u8_t u8_UartISO_Receive(u8_t LOC_arr_userBuffer[]){
    u8_t LOC_u8_returnVal = 0;
    u8_t LOC_u32_size = 0;

    if(LOC_arr_userBuffer != NULLPTR){
        // extract data field from the response buffer
        LOC_u32_size =  GLOB_u8responseLength - STANDARD_HEADER_SIZE; // LOC_u32_size of data field (minus 4 because of header bytes)
        GLOB_arrDatafield[0] = LOC_u32_size;
        memcpy(GLOB_arrDatafield+1, GLOB_arrVehicleResponse+3, LOC_u32_size); // [LOC_u32_size, mode, pid, data....]

        // copy the data to the user buffer
        memcpy(LOC_arr_userBuffer, GLOB_arrDatafield, GLOB_u8responseLength);

        LOC_u8_returnVal = 1;
    }else{
        LOC_u8_returnVal = 0;
    }
    return LOC_u8_returnVal;
}
