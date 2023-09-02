/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef USART_H
#define USART_H

#include "usartcnfg.h"
#include <stdint.h>

#pragma pack(4)
/*******************   USART channels   **********************************/
enum usart_peripheral {
    USART1_PERIPHERAL,
    USART2_PERIPHERAL,
    USART3_PERIPHERAL
};

/*******************   USART Modes   **********************************/

#define INTERRUPT                        0
#define POLLING                          1
#define USART_MODE                       INTERRUPT

/***************   USART BAUDRATE     ********************************************/
#define USART_BAUDRATE_115200            0x45
#define BAUDRATE                         USART_BAUDRATE_115200

/***************   CONFIGURATION FOR TIMEOUT    *************************************/
#define THRESHOLD_VALUE                  1000UL
#define NULL                             ((void *)0)


/***************   Function definition    ****************************************/
void USART_voidInit(void);
void USART_VoidTransmitChar(uint8_t Copy_u8Char );
void USART_VoidTransmitString(uint8_t *copy_u8DataPtr, uint16_t Copy_u8Size);
uint8_t USART_VoidRecieveChar(void);
uint8_t USART_CheckError(void);

#endif
