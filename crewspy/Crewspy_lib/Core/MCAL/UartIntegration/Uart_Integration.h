#ifndef UART_INTEGRATION_H
#define UART_INTEGRATION_H

#include "GlobalCnfg.h"


typedef enum{
    UART_OK,
    UART_NOK,
    UART_BAD_CHANNEL
}Uart_State;



Uart_State enum_Uart_Integration_Init(uint8_t u8Channel);
Uart_State enum_Uart_Integration_DeInit(uint8_t u8Channel);
Uart_State enum_Uart_Integration_Send(uint8_t u8Channel, uint8_t*  pData, uint8_t u8Size);
Uart_State enum_Uart_Integration_RecvPOLL(uint8_t u8Channel, uint8_t *pData, uint8_t u8Size);
Uart_State enum_Uart_Integration_RecvIT(uint8_t u8Channel, uint8_t *pData, uint8_t u8Size);
void vid_Uart_Integration_SetCllbck(function_ptr_d pUserCallback);

void Uart_Callback(uint8_t u8Data);
#endif
