
/**
 * @file UART.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of  (UART) Component
 * @version    1.0.0
 * @date       2024-03-05
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "UART.h"
#include "stm32f1xx_hal.h"


/*__________________ -Macros- _________________*/

/*_________________ - Privates _______________*/


/*__________________ -Public- _________________*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
/*__________________ -Privates- _________________*/

/// @brief this function is used just to initialize all pFunction variables
/// @param  NAN
/// @return NAN
PRIVATE void vid_emptyFunction(void)
{
  /* --- Empty block, this API is used just for initializing all pFunction variables---*/
} 
PRIVATE u8_t u8InitDoneFlag = 0;
PRIVATE pFunction pCallbackfuncUart1 = (pFunction)vid_emptyFunction;
PRIVATE pFunction pCallbackfuncUart2 = vid_emptyFunction;
PRIVATE pFunction pCallbackfuncUart3 = vid_emptyFunction;

/*ISR Handlers Prototypes*/
 void USART1_IRQHandler(void);
 void USART2_IRQHandler(void);
 void USART3_IRQHandler (void);

/*__________________ -Implementations- _________________*/

enumRetUart_e enum_uartInit(enumUartChannels_e enumUartChannel,enumBaudRates_e enumBaudRate)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  /*--- initialization ----*/
  if(
      (enumBaudRate == BAUD_RATE_9600) || (enumBaudRate == BAUD_RATE_10400)
      ||
      (enumBaudRate == BAUD_RATE_38400) || (enumBaudRate == BAUD_RATE_115200) 
    )
  {
    if(UART_CHANNEL_1 == enumUartChannel )
    {
      huart1.Instance = USART1;
      huart1.Init.BaudRate = enumBaudRate;
      huart1.Init.WordLength = UART_WORDLENGTH_8B;
      huart1.Init.StopBits = UART_STOPBITS_1;
      huart1.Init.Parity = UART_PARITY_NONE;
      huart1.Init.Mode = UART_MODE_TX_RX;
      huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
      huart1.Init.OverSampling = UART_OVERSAMPLING_16;
      HAL_NVIC_EnableIRQ(USART1_IRQn);
      if (HAL_UART_Init(&huart1) != HAL_OK)
      {
        LOC_enumRetVal  = NOT_VALID_UART;

      }
      else
      {
        u8InitDoneFlag  = 1;
        LOC_enumRetVal  = VALID_UART;
      }
    }
    else if(UART_CHANNEL_2 == enumUartChannel )
    {
      huart2.Instance = USART2;
      huart2.Init.BaudRate = enumBaudRate;
      huart2.Init.WordLength = UART_WORDLENGTH_8B;
      huart2.Init.StopBits = UART_STOPBITS_1;
      huart2.Init.Parity = UART_PARITY_NONE;
      huart2.Init.Mode = UART_MODE_TX_RX;
      huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
      huart2.Init.OverSampling = UART_OVERSAMPLING_16;
      HAL_NVIC_EnableIRQ(USART2_IRQn);
      if(HAL_UART_Init(&huart2) != HAL_OK)
      {
        LOC_enumRetVal  = NOT_VALID_UART;
      }
      else
      {
        u8InitDoneFlag  = 1;
        LOC_enumRetVal  = VALID_UART;
      }
    }
    else if(UART_CHANNEL_3 == enumUartChannel )
    {
      huart3.Instance = USART3;
      huart3.Init.BaudRate = enumBaudRate;
      huart3.Init.WordLength = UART_WORDLENGTH_8B;
      huart3.Init.StopBits = UART_STOPBITS_1;
      huart3.Init.Parity = UART_PARITY_NONE;
      huart3.Init.Mode = UART_MODE_TX_RX;
      huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
      huart3.Init.OverSampling = UART_OVERSAMPLING_16;
      HAL_NVIC_EnableIRQ(USART3_IRQn);
      if (HAL_UART_Init(&huart3) != HAL_OK)
      {
        LOC_enumRetVal  = NOT_VALID_UART;
      }
      else
      {
        u8InitDoneFlag  = 1;
        LOC_enumRetVal  = VALID_UART;
      }
    } 
    else
    {
      LOC_enumRetVal  = NOT_VALID_UART;
    }
  }
  else 
  {
    LOC_enumRetVal  = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart1SendData(const u8_t* u8DataToSend, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToSend!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Transmit(&huart1, u8DataToSend, u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart2SendData(const u8_t* u8DataToSend, u16_t u16DataSize)
{
   /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToSend!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Transmit(&huart2, u8DataToSend,u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart3SendData(const u8_t* u8DataToSend, u16_t u16DataSize)
{
   /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToSend!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Transmit(&huart3, u8DataToSend,u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart1RecData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive(&huart1, u8DataToRec,u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart2RecData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive(&huart2, u8DataToRec,u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart3RecData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive(&huart3, u8DataToRec,u16DataSize, UARTx_TIMEOUT) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart1RecITData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive_IT(&huart1, u8DataToRec,u16DataSize) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart2RecITData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive_IT(&huart2, u8DataToRec,u16DataSize) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_Uart3RecITData(u8_t *u8DataToRec, u16_t u16DataSize)
{
  /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;

  if((u8InitDoneFlag == 1) && (u8DataToRec!=NULL) && (u16DataSize!=0))
  {
    /*------------ Action --------------*/
    if(HAL_UART_Receive_IT(&huart3, u8DataToRec,u16DataSize) == HAL_OK)
    {
      LOC_enumRetVal = VALID_UART;
    }
    else
    {
      LOC_enumRetVal = NOT_VALID_UART;
    }  
  }
  else
  {
    LOC_enumRetVal = NOT_VALID_UART;
  }
  return LOC_enumRetVal;
}

enumRetUart_e enum_UartSetCallbackForReception(const UART_HandleTypeDef *huart,pFunction pUserCallback)
{
   /*------- LOCALS ----- */
  enumRetUart_e LOC_enumRetVal = UNKOWN_UART;
  if((pUserCallback != NULLPTR) && (huart!=NULL))
  {
    LOC_enumRetVal = VALID_UART;
    if(huart == &huart1)
    {
      pCallbackfuncUart1 = pUserCallback;
    }
    else if(huart == &huart2)
    {
      pCallbackfuncUart2 = pUserCallback;
    }
    else if(huart == &huart3)
    {
      pCallbackfuncUart3 = pUserCallback;
    }
    else 
    {
      LOC_enumRetVal = NOT_VALID_UART;
    } 
  }
  else 
  {
    LOC_enumRetVal = NOT_VALID_UART;
  } 
  return LOC_enumRetVal;
}


#if(UART_UT==OFF)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if ((huart == &huart1) && (pCallbackfuncUart1 != NULLPTR))
    {
      /*------ Uart1 Reception callBack ----*/
      /*------ call the API you want to execute when the reception interrupt of uart1 occures here! ----*/
      pCallbackfuncUart1();
    }
    else if((huart == &huart2) && (pCallbackfuncUart2 != NULLPTR))
    {
      /*------ Uart2 Reception callBack ----*/
      /*------ call the API you want to execute when the reception interrupt of uart2 occures here! ----*/
      pCallbackfuncUart2();
    }
    else if((huart == &huart3) && (pCallbackfuncUart3 != NULLPTR))
    {
      /*------ Uart3 Reception callBack ----*/
      /*------ call the API you want to execute when the reception interrupt of uart3 occures here! ----*/
      pCallbackfuncUart3();
    }
    else 
    {
      /* -- Do nothing -- */
    }
  
}
#endif

void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}

void USART2_IRQHandler(void)
{
   HAL_UART_IRQHandler(&huart2);
}

void USART3_IRQHandler (void)
{
  HAL_UART_IRQHandler(&huart3);
}


enumRetUart_e enum_Uart2AbortReceive(void){
  HAL_StatusTypeDef LOC_enumRetValue = 0;
  enumRetUart_e LOC_enumFuncRetValue = 0;

  LOC_enumRetValue = HAL_UART_AbortReceive_IT(&huart2);
  if(LOC_enumRetValue != HAL_OK){
    LOC_enumFuncRetValue = NOT_VALID_UART;
  }else{
    LOC_enumFuncRetValue = VALID_UART;
  }

  return LOC_enumFuncRetValue;
}
