
/**
 * @file UART.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of (UART) Component
 * @version    1.0.0
 * @date       2024-03-05
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __UARTCREWTEQ__H__
#define __UARTCREWTEQ__H__



/*__________________ -Includes- _________________*/
#include "main.h"
#include "typedefs.h"
#include "stm32f1xx_hal.h"

/*__________________ -Macros- _________________*/
#define UART_UT 		UT

#define 	UARTx_TIMEOUT 	  1000U
/*__________________ -Public- _________________*/



/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_UART 			= 0,
	NOT_VALID_UART 		= 1,
	UNKOWN_UART			= 2
}enumRetUart_e;

/// @brief this enumeration will be used to save the available uart channels
typedef enum 
{
	UART_CHANNEL_1 			= 1,
	UART_CHANNEL_2 			= 2,
	UART_CHANNEL_3			= 3
}enumUartChannels_e;

/// @brief this enumeration will be used to save the available baudrates.
typedef enum 
{
	BAUD_RATE_5 = 5,
	BAUD_RATE_9600   = 9600,
	BAUD_RATE_10400  = 10400,
	BAUD_RATE_38400  = 38400,
	BAUD_RATE_115200 = 115200
}enumBaudRates_e;
/*__________________ -Prototypes- _________________*/


/// @brief this function is responsible for initializing a specific cannel of uart with specific baudRate.
/// @param u8UartChannel the channel of UART
/// @param enumBaudRates_e  the Baud-Rate  
/// 						BAUD_RATE_9600 OR BAUD_RATE_10400 OR BAUD_RATE_38400 OR BAUD_RATE_112500,
///                         Other wise The Api returns NOT_VALID_UART
/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2065
enumRetUart_e enum_uartInit(enumUartChannels_e enumUartChannel,enumBaudRates_e enumBaudRate);

/// @brief this function is responsible for sending a string over uart1
/// @param u8DataToSend the string we want to send Over Uart channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2066
enumRetUart_e enum_Uart1SendData(const u8_t* u8DataToSend, u16_t u16DataSize);

/// @brief this function is responsible for sending a string over uart2
/// @param u8DataToSend the string we want to send Over Uart channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2066
enumRetUart_e enum_Uart2SendData(const u8_t* u8DataToSend, u16_t u16DataSize);

/// @brief this function is responsible for sending a string over uart3
/// @param u8DataToSend the string we want to send Over Uart channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2066
enumRetUart_e enum_Uart3SendData(const u8_t* u8DataToSend, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart1.
/// @param u8DataToSend the string we want to receive Over Uart1 channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart1RecData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart2.
/// @param u8DataToSend the string we want to receive Over Uart2 channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart2RecData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart3.
/// @param u8DataToSend the string we want to receive Over Uart3 channel
/// @param u16DataSize the size of string
/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart3RecData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart1 using interrupt.
/// @param u8DataToSend the string we want to receive Over Uart1 channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart1RecITData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart2 using interrupt.
/// @param u8DataToSend the string we want to receive Over Uart2 channel
/// @param u16DataSize the size of string

/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart2RecITData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function is responsible for receiving string over uart3 using interrupt.
/// @param u8DataToSend the string we want to receive Over Uart3 channel
/// @param u16DataSize the size of string
/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_Uart3RecITData(u8_t* u8DataToRec, u16_t u16DataSize);

/// @brief this function set the private pointer to points to a specific function.
///	       in other words, set what the function user want to execute when a specific reception (Uart1 or Uart2 or Uart3) occures
/// @param huart &huart1 Or &huart2 Or &huart3
/// @param pUserCallback :address of the function we want to set the private pointer to .
/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART

/// @covers Req ID : CCO-CDD-2067
enumRetUart_e enum_UartSetCallbackForReception(const UART_HandleTypeDef *huart,pFunction pUserCallback);
 
/// @brief cancels the receive by interrupt
/// @param  none
/// @return the validity of executing the function
///         VALID_UART Or NOT_VALID_UART Or UNKOWN_UART
enumRetUart_e enum_Uart2AbortReceive(void);
#endif
