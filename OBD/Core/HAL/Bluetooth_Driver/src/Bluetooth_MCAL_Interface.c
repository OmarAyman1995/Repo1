#include "Bluetooth_MCAL_Interface.h"
#include "UART.h"
#include "GPIO.h"
#include "BluetoothDrv.h"
#include "string.h"

extern UART_HandleTypeDef huart2;





void BlUartInit38400(void){
    enum_uartInit(UART_CHANNEL_2,BAUD_RATE_38400);
}

void BlUartInit115200(void){
    enum_uartInit(UART_CHANNEL_2,BAUD_RATE_115200);
}

void BlUartSend(u8_t *pData, u32_t size){
    enum_Uart2SendData(pData, (u16_t)size);
}


void BlUartRecv(u8_t *pData, u32_t size){
    enum_Uart2RecData(pData, (u16_t)size);
}

void BlUartRecvIT(u8_t *pData, u32_t size){
    enum_Uart2RecITData(pData, (u16_t)size);
}

void BlUartAbort(void){
    enum_Uart2AbortReceive();
}



void BlUartSetCallback(pFunction pISR){
    enum_UartSetCallbackForReception(&huart2,pISR);
}

void BlGpioSet(void){
    enum_GpioWritePin(BLUETOOTH_ENABLE_PORT, BLUETOOTH_ENABLE_PIN, GPIO_PIN_SET);
}

void BlGpioReset(void){
    enum_GpioWritePin(BLUETOOTH_ENABLE_PORT, BLUETOOTH_ENABLE_PIN, GPIO_PIN_RESET);
}

u8_t BlGpioRead(void){
    GPIO_PinState pinState = 0;
    u8_t retVal = 0;
    enum_GpioReadPin(BLUETOOTH_STATE_PORT, BLUETOOTH_STATE_PIN, &pinState);
    if(pinState == GPIO_PIN_SET){
        retVal = 1;
    }else{
        retVal = 0;
    }
    return retVal;
}


u8_t BLCompareString(u8_t *str1, u8_t *str2){
    u8_t retVal = 0;

    if(strcmp(str1, str2) != 0){
        retVal = 0;
    }else{
        retVal = 1;
    }
    return retVal;
}
