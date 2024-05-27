#include "ISO_Uart_MCAL_Interface.h"
#include "stm32f1xx_hal.h"
#include "UART.h"

extern UART_HandleTypeDef huart3;

#define CONST_UART_TIMEOUT 50


void IsoUartInit10400bps(void){
    enum_uartInit(UART_CHANNEL_3, BAUD_RATE_10400);

}
void IsoUartInit5bps(void){
    enum_uartInit(UART_CHANNEL_3, BAUD_RATE_5);

}
/**
 * @brief handles sending on UART using MCAL Driver
 * 
 * @param data 
 * @param size 
 * @return u8_t 
 */
u8_t u8_UartSend(u8_t arrData[], u32_t u32size){
    HAL_StatusTypeDef LOC_enum_uartCheck = 0;
    u8_t LOC_u8_retVal = 0;

    HAL_HalfDuplex_EnableTransmitter(&huart3);
    LOC_enum_uartCheck = HAL_UART_Transmit(&huart3, arrData, (u16_t)u32size, CONST_UART_TIMEOUT);

    if(LOC_enum_uartCheck == HAL_OK){
        LOC_u8_retVal = 1;
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}

/**
 * @brief handles receiving on UART using MCAL Driver
 * 
 * @param data 
 * @param size 
 * @return u8_t 
 */
u8_t u8_UartReceive(u8_t arrData[], u32_t u32size){
    HAL_StatusTypeDef LOC_enum_uartCheck = 0;
    u8_t LOC_u8_retVal = 0;

    HAL_HalfDuplex_EnableReceiver(&huart3);
    LOC_enum_uartCheck = HAL_UART_Receive(&huart3, arrData, (u16_t)u32size, CONST_UART_TIMEOUT);

    if(LOC_enum_uartCheck == HAL_OK){
        LOC_u8_retVal = 1;
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}


u8_t u8_UartReceiveIT(u8_t arrData[], u32_t u32size){
    HAL_StatusTypeDef LOC_enum_uartCheck = 0;
    u8_t LOC_u8_retVal = 0;

    HAL_HalfDuplex_EnableReceiver(&huart3);
    LOC_enum_uartCheck = HAL_UART_Receive_IT(&huart3, arrData, (u16_t)u32size);

    if(LOC_enum_uartCheck == HAL_OK){
        LOC_u8_retVal = 1;
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}
