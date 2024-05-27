#include "HandlingBluetooth.h"



PUBLIC u8_t GLOB_u8byteReceived;
PUBLIC u8_t GLOB_u8ffReceived;




PRIVATE u8_t GLOB_u8RequestBufferr[BUFFER_SIZE] = {0};
PRIVATE i8_t GLOB_u8CounterAtBufferr = 0;



void vid_HandlingBluetooth_resetAfterRequest(void){

    // Reset the counter for next Request 
    GLOB_u8CounterAtBufferr = 0;

    // Reset the buffer for next Request
    for(u8_t i = 0; (i < BUFFER_SIZE); ++i){
        GLOB_u8RequestBufferr[i] = 0;

    }

}


void vid_HandlingBluetooth_Listen(void){

    // Start listening on Client Requests to get first byte
    u8_Bluetooth_Receive(&GLOB_u8RequestBufferr[GLOB_u8CounterAtBufferr], 1);
    
    GLOB_u8CounterAtBufferr += 1;

    // protect from overflow
    if(GLOB_u8CounterAtBufferr >= BUFFER_SIZE){
        GLOB_u8CounterAtBufferr = 0;
    }
}


void vid_HandlingBluetooth_Callback(void){

    // Get each byte received from BLE and store in GLOB_u8RequestBuffer
    if(LINE_END == GLOB_u8RequestBufferr[GLOB_u8CounterAtBufferr - 1]){

        // store the request in the queue, then reset the buffer
        u8_QueueIF_Push(WIRELESS_RECV_HANDLER, GLOB_u8RequestBufferr);
        vid_HandlingBluetooth_resetAfterRequest();

        GLOB_u8ffReceived = 1;
    }
    
    vid_HandlingBluetooth_Listen();
    
    // byte received
    GLOB_u8byteReceived = 1;
}

// wrapper
u8_t u8_HandlingBluetooth_Send(u8_t *pData, u32_t size){
    u8_t LOC_arrEndMessage[] = {'\r','\n'};
    u8_t LOC_u8CheckSend = 0;
    LOC_u8CheckSend = u8_Bluetooth_Send(pData, size);
    u8_Bluetooth_Send(LOC_arrEndMessage, sizeof(LOC_arrEndMessage));

    return LOC_u8CheckSend;
}



u8_t u8_HandlingBluetooth_updateConfigurations(void){
    u8_t LOC_u8returnVal = 0;
    u8_t LOC_u8checkInitialize = 0;
    u8_t LOC_u8checkConfigured = 0;
    Bluetooth_Config_t LOC_strdesiredConfigs = {
        .baudrate = "115200",
        .device_name = "Crew-Copilot",
        .pass="1234"
    };

    // TODO(mab) get configuration info from EEPROM
    LOC_u8checkConfigured = 1;

    if(LOC_u8checkConfigured == 1){
        LOC_u8returnVal = 1;
    }else{
        // if not configured, do the configuration sequence abstracted in bluetooth driver
        LOC_u8checkInitialize = u8_Bluetooth_Init(&LOC_strdesiredConfigs);
        LOC_u8returnVal = LOC_u8checkInitialize;
    }

    return LOC_u8returnVal;
}
