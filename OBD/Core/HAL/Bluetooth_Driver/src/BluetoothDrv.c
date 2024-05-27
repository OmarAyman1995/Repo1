#include "BluetoothDrv.h"
#include <string.h>
#include <stdlib.h>
#include "Bluetooth_MCAL_Interface.h"

/*  BLE Commands obtained from Datasheet
    Datasheet link: https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf
*/



/**
 * @brief switches the hardware bluetooth module to setup mode
 * 
 * @return u8_t 
 */
PRIVATE u8_t u8_Bluetooth_SwitchToSetupMode(void){
    
    BlGpioSet();
    BlUartInit38400();
    return 1;
}


/**
 * @brief switches the hardware bluetooth module to normal mode
 * 
 * @return u8_t 
 */
PRIVATE u8_t u8_Bluetooth_SwitchToNormal(void){
    BlGpioReset();
    BlUartInit115200();
    return 1;
}




u8_t u8_Bluetooth_Init(Bluetooth_Config_t *LOC_ptr_configs){

    u8_t LOC_u8_functionReturn = 0;
    u8_t LOC_u8_error = 4;
    u8_t LOC_u8_numOfTries = 10;

    if(LOC_ptr_configs != NULLPTR){

        u8_Bluetooth_SwitchToSetupMode();

        
        while((LOC_u8_numOfTries != 0) && (LOC_u8_error != 0)){
           // check if all has successed or not (all must return 1).
           LOC_u8_error = 4;
           LOC_u8_error -= u8_Bluetooth_SetDeviceName(LOC_ptr_configs->device_name);
           LOC_u8_error -= u8_Bluetooth_SetPassword(LOC_ptr_configs->pass);
           LOC_u8_error -= u8_Bluetooth_SetBaudrate(LOC_ptr_configs->baudrate);
           LOC_u8_error -= u8_Bluetooth_ResetBoard();
           --LOC_u8_numOfTries;
        }

        // check numOfTries reached limit or not.
        if(LOC_u8_numOfTries == 0){
            LOC_u8_functionReturn = 0;
        }
        else{
            LOC_u8_functionReturn = 1;
        }


        u8_Bluetooth_SwitchToNormal();
    }else{
        LOC_u8_functionReturn = 0;
    }

    return LOC_u8_functionReturn;
}


u8_t u8_Bluetooth_Send(u8_t* LOC_p_Data, u32_t LOC_u32_size){

    u8_t LOC_u8_checkInput = (LOC_p_Data != NULLPTR) && (LOC_u32_size != 0);
    u8_t LOC_u8_retVal = 0;
    if(LOC_u8_checkInput == 1){
        BlUartSend(LOC_p_Data, (u16_t)LOC_u32_size);
        LOC_u8_retVal = 1;
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}


u8_t u8_Bluetooth_Receive(u8_t* LOC_p_Data, u32_t LOC_u32_size){
    u8_t LOC_u8_checkInput = (LOC_p_Data != NULLPTR) && (LOC_u32_size != 0);
    u8_t LOC_u8_retVal = 0;

    if(LOC_u8_checkInput == 1){
        BlUartRecvIT(LOC_p_Data, (u16_t)LOC_u32_size);
        LOC_u8_retVal = 1;
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}


void vid_Bluetooth_setCallback(pFunction pISR){
    BlUartSetCallback(pISR);
}


u8_t u8_Bluetooth_getConnectivityStatus(void)
{
    // take three samples.
    u8_t LOC_enum_pinState_s1 = 0;
    u8_t LOC_enum_pinState_s2 = 0;
    u8_t LOC_enum_pinState_s3 = 0;

    // these three reads should be PIN_SET so there is connectivity, otherwise consider the state as PIN_RESET so no connectivity.
    LOC_enum_pinState_s1  = BlGpioRead();
    LOC_enum_pinState_s2  = BlGpioRead();
    LOC_enum_pinState_s3  = BlGpioRead();


   return LOC_enum_pinState_s1 && LOC_enum_pinState_s2 && LOC_enum_pinState_s3;
}


void vid_Bluetooth_AbortReceive(void){
    BlUartAbort();
}
