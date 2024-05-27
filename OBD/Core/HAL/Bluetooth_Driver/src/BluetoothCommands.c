#include "BluetoothCommands.h"
#include "string.h"
#include "stdio.h"
#include "Bluetooth_MCAL_Interface.h"

#define CMND_SET_DEVICE_NAME    "AT+NAME="
#define CMND_GET_DEVICE_NAME    "AT+NAME?"
#define CMND_GET_DEVNAME_RESP_PREFIX "+NAME:"
#define CMND_GET_DEVNAME_RESP_PREFIX_SIZE 6U
#define DEVICE_NAME_IDX 6U

#define CMND_SET_BAUDRATE       "AT+UART="
#define CMND_GET_BAUDRATE       "AT+UART?"
#define CMN_GET_BAUDRATE_RESP_PREFIX   "+UART:"
#define CMN_GET_BAUDRATE_RESP_PREFIX_SIZE   6U
#define CMN_GET_BAUDRATE_RESP_SUFFIX   ","

#define BAUDRATE_IDX 6U

#define CMND_SET_PSWRD          "AT+PSWD="
#define CMND_GET_PSWRD          "AT+PSWD?"
#define CMND_GET_PSWD_RESP_PREFIX "+PSWD:"
#define CMND_GET_PSWD_RESP_PREFIX_SIZE   6U

#define PSWRD_IDX 6U

#define CMND_RESET              "AT+RESET"

#define CR_LF "\r\n"
#define TERMINATION_SIGN '\n'
#define AT_OK "OK\r\n"



#define MAX_BAUDRATE_SIZE 6U



u8_t u8_Bluetooth_SetDeviceName(u8_t *LOC_ptr_device_name){
    u8_t LOC_arr_Sendbuffer[50] = {0};
    u8_t LOC_arrRecvbuffer[BUFFER_SIZE] = {0};
    u8_t LOC_u8_retVal = 0;
    
    if(NULLPTR != LOC_ptr_device_name){

        sprintf(LOC_arr_Sendbuffer, "AT+NAME=%s\r\n",LOC_ptr_device_name);

        u8_Bluetooth_SendCmnd(LOC_arr_Sendbuffer);
        u8_Bluetooth_ReceiveCmnd(LOC_arrRecvbuffer);

        LOC_u8_retVal = BLCompareString(LOC_arrRecvbuffer, AT_OK);

    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}



u8_t u8_Bluetooth_SendCmnd(u8_t* LOC_ptr_Command){
    u8_t LOC_u8_dataLoop = 0;
    u32_t LOC_u32_size = 0;
    u8_t LOC_u8_ret = 0;

    if(NULLPTR != LOC_ptr_Command){

        LOC_u32_size = strlen(LOC_ptr_Command);

        /* Send untill termination sign or untill the calculated LOC_u32_size */
        while(LOC_u8_dataLoop < LOC_u32_size){
            BlUartSend(&LOC_ptr_Command[LOC_u8_dataLoop],1);
            ++LOC_u8_dataLoop;
            if(TERMINATION_SIGN == LOC_ptr_Command[LOC_u8_dataLoop]){
                BlUartRecv(&LOC_ptr_Command[LOC_u8_dataLoop], 1);
                LOC_u8_ret = 1;
                break;
            }
        }

    }else{
        LOC_u8_ret = 0;
    }

    return LOC_u8_ret;
}




u8_t u8_Bluetooth_ReceiveCmnd(u8_t* LOC_ptr_Command){
    u8_t LOC_u8_dataLoop = 0;
    u8_t LOC_u8_ret = 0;

    if(NULLPTR != LOC_ptr_Command){
        /* Receive untill termination sign */
        while(LOC_u8_dataLoop < BUFFER_SIZE){
            BlUartRecv(&LOC_ptr_Command[LOC_u8_dataLoop], 1);
            if(TERMINATION_SIGN == LOC_ptr_Command[LOC_u8_dataLoop]){
                LOC_u8_ret = 1;
                break;
            }
            ++LOC_u8_dataLoop;
        }
    }else{
        LOC_u8_ret = 0;
    }

    return LOC_u8_ret;
}



u8_t u8_Bluetooth_SetBaudrate(u8_t *baudrate){

    u8_t LOC_arr_Sendbuffer[50] = {0};
    u8_t LOC_arr_Recvbuffer[BUFFER_SIZE] = {0};
    u8_t LOC_u8_retVal = 0;

    if(NULLPTR != baudrate){
        /* change baudrate to string */
        sprintf(LOC_arr_Sendbuffer, "AT+UART=%s,1,0,\r\n",baudrate);

        u8_Bluetooth_SendCmnd(LOC_arr_Sendbuffer);
        u8_Bluetooth_ReceiveCmnd(LOC_arr_Recvbuffer);

        LOC_u8_retVal = BLCompareString(LOC_arr_Recvbuffer, AT_OK);

    }else{
        LOC_u8_retVal = 0;

    }

    return LOC_u8_retVal;
}




u8_t u8_Bluetooth_ResetBoard(void){

    u8_t LOC_arr_Sendbuffer[50] = {0};
    u8_t LOC_arr_Recvbuffer[BUFFER_SIZE] = {0};
    u8_t LOC_u8_retVal = 0;

    sprintf(LOC_arr_Sendbuffer, "AT+RESET\r\n");

    u8_Bluetooth_SendCmnd(LOC_arr_Sendbuffer);
    u8_Bluetooth_ReceiveCmnd(LOC_arr_Recvbuffer);
    
    LOC_u8_retVal = BLCompareString(LOC_arr_Recvbuffer, AT_OK);

    return LOC_u8_retVal;
}



u8_t u8_Bluetooth_SetPassword(u8_t *password){
    u8_t LOC_arr_Sendbuffer[50] = {0};
    u8_t LOC_arr_Recvbuffer[BUFFER_SIZE] = {0};
    u8_t LOC_u8_retVal = 0;

    if(password != NULLPTR){

        sprintf(LOC_arr_Sendbuffer, "AT+PSWD=%s\r\n",password);

        u8_Bluetooth_SendCmnd(LOC_arr_Sendbuffer);
        u8_Bluetooth_ReceiveCmnd(LOC_arr_Recvbuffer);

        LOC_u8_retVal = BLCompareString(LOC_arr_Recvbuffer, AT_OK);
    }else{
        LOC_u8_retVal = 0;
    }


    return LOC_u8_retVal;
}





u8_t u8_Bluetooth_RestoreToOrigin(void){
    u8_t LOC_arr_Sendbuffer[50] = {0};
    u8_t LOC_arr_Recvbuffer[BUFFER_SIZE] = {0};
    u8_t LOC_u8_retVal = 0;

    sprintf(LOC_arr_Sendbuffer, "AT+ORGL\r\n");

    u8_Bluetooth_SendCmnd(LOC_arr_Sendbuffer);
    u8_Bluetooth_ReceiveCmnd(LOC_arr_Recvbuffer);

    LOC_u8_retVal = BLCompareString(LOC_arr_Recvbuffer, AT_OK);

    return LOC_u8_retVal;
}
