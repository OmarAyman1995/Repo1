#include "SIM800Handling.h"
#include <stdio.h>
#include "string.h"


#define COMMAND_TIMEOUT 500
#define WAIT_REPLAY_TIMEOUT 300
#define WAIT_REPLAY_DELAY 5

PUBLIC u8_t GLOB_arrUartRx_Buffer[100];
PUBLIC void vid_clearRxBuffer(void);


u8_t u8_SIM800_SendCommand(char *command, char *reply, u32_t sizeofcommand)
{
    u16_t LOC_u16_counter = 0;
    u8_t LOC_u8_replyOk = 0;
    u8_t LOC_u8_checkInput = (command != NULLPTR) && (reply != NULLPTR) && (sizeofcommand != 0);

    if(LOC_u8_checkInput == 1){

        u8_Mqtt_UartTransmit((unsigned char *)command, (u16_t)sizeofcommand,COMMAND_TIMEOUT);

        // wait for the proper reply
        while((LOC_u8_replyOk != 1) && (LOC_u16_counter != WAIT_REPLAY_TIMEOUT)){
            // waiting on a certain response of a command
            if(strstr(GLOB_arrUartRx_Buffer, reply) != NULL){
                LOC_u8_replyOk = 1;
            }
            ++LOC_u16_counter;
            vid_Mqtt_Delay(WAIT_REPLAY_DELAY);

        }

        vid_clearRxBuffer();
    }else{
        LOC_u8_replyOk = 0;
    }

    return LOC_u8_replyOk;
}




u8_t u8_SIM800_SendPattern(char *pattern, u16_t length){
    u16_t LOC_u16_counter = 0;
    u8_t LOC_u8_replyOk = 0;
    u8_t LOC_u8_checkInput = (pattern != NULLPTR) && (length != 0);
    
    if(LOC_u8_checkInput == 1){

        u8_Mqtt_UartTransmit((unsigned char *)pattern, length, COMMAND_TIMEOUT);

        // wait for SEND OK message
        while((LOC_u8_replyOk != 1) && (LOC_u16_counter != WAIT_REPLAY_TIMEOUT)){
            // waiting on a certain response of a command
            if( strstr((char *)GLOB_arrUartRx_Buffer, "SEND OK") != NULL ){
                vid_clearRxBuffer();
                LOC_u8_replyOk = 1;
            }
            ++LOC_u16_counter;
            vid_Mqtt_Delay(WAIT_REPLAY_DELAY);
        }

        vid_clearRxBuffer();
    }else{
        LOC_u8_replyOk = 0;
    }

    return LOC_u8_replyOk;
}


