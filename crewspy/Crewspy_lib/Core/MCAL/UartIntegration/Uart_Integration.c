#include "Uart_Integration.h"
#include "usart.h"
#include "Address.h"

PRIVATE function_ptr_d pCallbackfunc = NULLPTR;
/**
 * @brief Initalize Uart
 *
 * @param u8Channel This can be CHANNEL_1/CHANNEL_2/CHANNEL_3
 */
Uart_State enum_Uart_Integration_Init(uint8_t u8Channel){

    Uart_State ret = UART_OK;
    USART_voidInit();

    return ret;
}


/**
 * @brief Deinitialize Uart
 *
 * @param u8Channel This can be CHANNEL_1/CHANNEL_2/CHANNEL_3
 */
Uart_State enum_Uart_Integration_DeInit(uint8_t u8Channel){

    Uart_State ret = UART_OK;

    return ret;
}


/**
 * @brief Send Data on UART
 *
 * @param u8Channel This can be Channel_1/CHANNEL_2/CHANNEL_3
 * @param pData data
 * @param u8Size size of data
 */
Uart_State enum_Uart_Integration_Send(uint8_t u8Channel, uint8_t*  pData, uint8_t u8Size){

    Uart_State ret = UART_OK;
    USART_VoidTransmitString(pData, u8Size);

    return ret;
}


/**
 * @brief Receive Data from UART on POLLING Mode
 *
 * @param u8Channel This can be CHANNEL_1/CHANNEL_2/CHANNEL_3
 * @param pData data
 * @param u8Size size of data
 */
Uart_State enum_Uart_Integration_RecvPOLL(uint8_t u8Channel, uint8_t *pData, uint8_t u8Size){

    Uart_State ret = UART_OK;

    return ret;

}


/**
 * @brief Receives Data from UART on INTERRUPT Mode
 *
 * @param u8Channel This can be CHANNEL_1/CHANNEL_2/CHANNEL_3
 * @param pData data
 * @param u8Size size of data
 */
Uart_State enum_Uart_Integration_RecvIT(uint8_t u8Channel, uint8_t *pData, uint8_t u8Size){

    Uart_State ret = UART_OK;

    return ret;
}


/**
 * @brief Set Callback in case of receiving in INTERRUPT mode
 *
 * @param callback pointer to function
 */
void vid_Uart_Integration_SetCllbck(function_ptr_d pUserCallback){

    if((pUserCallback != NULLPTR) && (pCallbackfunc == NULLPTR)){
        pCallbackfunc = pUserCallback;
    }

}


/**
 * @brief ISR of the UART
 *
 * @param huart handler of Uart intance
 */
void Uart_Callback(uint8_t u8Data){

    if(pCallbackfunc != NULLPTR)
    {   
        pCallbackfunc(u8Data);
    }
}
