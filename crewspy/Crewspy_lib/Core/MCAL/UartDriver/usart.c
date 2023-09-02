/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
 /****************************************includes*******************************************************/
#include "usart.h"
#include "Address.h"
#include "BitMath.h"
#include "UartTp.h"
#include "Uart_Integration.h"


/* pointer to the address of selected usart*/
volatile USART_t *current_usart;

/* Selected USART periphral number, User selection*/
enum usart_peripheral selected_usart = USART1_PERIPHERAL;


/**
 * @brief Initialize USART peripheral
 * 
 */
void USART_voidInit(void)
    { 
      
        
        switch (selected_usart)
        {
           case USART1_PERIPHERAL:
                current_usart=USART1;

                 SET_BIT(RCC_APB2ENR_REG,14);                // USART1 clock enable
                 SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT2_IOPAEN);                   // IO port A clock enable
                 
                 CLR_BIT(USART1->CR1,USART_CR1_REG_BIT12_M );                            //set Word length
                 USART1->BRR=BAUDRATE;                                                   // set baudrate
           
                 SET_BIT(USART1->CR1,USART_CR1_REG_BIT2_RE);                             // reciever enable
                 SET_BIT(USART1->CR1,USART_CR1_REG_BIT3_TE);                             // Transmitter enable
                 SET_BIT(USART1->CR1,USART_CR1_REG_BIT13_UE);                            //  USART enable
                 #if USART_MODE == INTERRUPT
                 NVIC_ISER0_REG[ (37 / 32) ] = 1 << (37 % 32);                           // Equation for enable global interrupt
                 SET_BIT(USART1->CR1,5);                                                  // enable Recieve interupt
                #elif USART_MODE == POLLING
                 CLR_BIT(USART1->CR1,USART_CR1_REG_BIT5_RXNEIE);                         // enable Recieve interupt
                #endif
                 

                 /*Port configuration register high */
                 SET_BIT(GPIOA_CRH_REG,7);                                              
                 SET_BIT(GPIOA_CRH_REG,4);

                 CLR_BIT(GPIOA_CRH_REG,11);
                 SET_BIT(GPIOA_CRH_REG,10);
                 
                 CLR_BIT(GPIOA_CRH_REG,8);
                 CLR_BIT(GPIOA_CRH_REG,9);
                 
                 CLR_BIT(AFIO_MAPR_REG,AFIO_MAPR_REG_BIT2_USART1_REMAP);               //USART1 remapping
              
             break;
           case USART2_PERIPHERAL:
                current_usart=USART2;
             break;

           case USART3_PERIPHERAL:
                current_usart=USART3;
             break;

           default:
              break;
    }
   
 }


/**
 * @brief transmitting single byte on USART1
 * 
 * @param Copy_u8Char copy of the byte
 */
void USART_VoidTransmitChar(uint8_t Copy_u8Char )
 {
    switch(selected_usart)
    {
        case USART1_PERIPHERAL:
          current_usart=USART1;
          USART1->DR= Copy_u8Char;
          while (GET_BIT(USART1->SR,USART_SR_REG_BIT6_TC) == 0);                          //Transmission complete
          CLR_BIT(USART1->SR,USART_SR_REG_BIT6_TC);
        break;

        case USART2_PERIPHERAL:
          current_usart=USART2;
        break;
        case USART3_PERIPHERAL:
          current_usart=USART3;
        break;
    }
    
 }


/**
 * @brief transmitting more than one byte on USART1
 * 
 * @param ref_u8DataPtr pointer to the data
 * @param Copy_u8Size size of data
 */
void USART_VoidTransmitString(uint8_t *ref_u8DataPtr, uint16_t Copy_u8Size)
 {
    uint8_t local_iterator=0;
    while ( local_iterator < Copy_u8Size ){

		USART_VoidTransmitChar( ref_u8DataPtr[ local_iterator ] );
		local_iterator++ ;
	}
 }


/**
 * @brief receiving single byte on USART1
 * 
 * @return uint8_t the byte recevied
 */
uint8_t USART_VoidRecieveChar(void)
{ 
    uint8_t Local_u8Data = 0;

    /* attribute unused to stop the unused-warning of gcc */
	  uint16_t __attribute__((unused)) Local_TimeOut = 0 ;
    
    switch(selected_usart)
    {
        case USART1_PERIPHERAL:
        current_usart=USART1;
        #if USART_MODE == POLLING
	    while( ( GET_BIT ( USART1 -> SR,USART_SR_REG_BIT5_RXNE ) == 0 ) || Local_TimeOut <= THRESHOLD_VALUE)    // Transmission is not complete
	      {
		    Local_TimeOut++;
	      }
	    if( Local_TimeOut == THRESHOLD_VALUE )                                        //if it reaches the time out
	      {
		  Local_u8Data = 255;
	      }
          else
          {
           Local_u8Data=USART1->DR;
          }

        #elif USART_MODE == INTERRUPT                                           
               Local_u8Data=USART1->DR;
        #endif
        /* Check for USART errors*/
        uint8_t error_flags = USART_CheckError();
        if (error_flags)
        {
            // Handle the USART errors as needed
            if (error_flags & GET_BIT(USART1->SR,USART_SR_REG_BIT0_PE))                      // handle Parity error
                 {
                    CLR_BIT(USART1->SR,USART_SR_REG_BIT0_PE);
                 }

            if (error_flags & GET_BIT(USART1->SR,USART_SR_REG_BIT1_FE))                       // handle Frame error
                 {
                    CLR_BIT(USART1->SR,USART_SR_REG_BIT1_FE);
        
                 }
            if (error_flags & GET_BIT(USART1->SR,USART_SR_REG_BIT2_NE))                       //handle Noise error
                 {
                    CLR_BIT(USART1->SR,USART_SR_REG_BIT2_NE);
       
                 }          
            if (error_flags & GET_BIT(USART1->SR,USART_SR_REG_BIT3_ORE))                      //handle Overrun error
                 {
                    CLR_BIT(USART1->SR,USART_SR_REG_BIT3_ORE);
       
                 }
            
        }

         break;

          case USART2_PERIPHERAL:
          current_usart=USART2;
        break;

        case USART3_PERIPHERAL:
          current_usart=USART3;
        break;
    }
     
return Local_u8Data;
}


/**
 * @brief checking all errors of UART, Parity err - Framing err - Noise err - Overrun err
 * 
 * @return uint8_t 
 */
uint8_t USART_CheckError(void)
{
    uint8_t errors = 0;
    switch(selected_usart)
    {
        case USART1_PERIPHERAL:
        current_usart=USART1;
        if (GET_BIT( USART1->SR,USART_SR_REG_BIT0_PE))                                    // Parity error Flag
    {
        // Parity error occurred
        errors |= GET_BIT( USART1->SR,USART_SR_REG_BIT0_PE);
    }

    if (GET_BIT( USART1->SR,USART_SR_REG_BIT1_FE))                                       // Framing error Flag
    {
        // Framing error occurred
       errors |= GET_BIT( USART1->SR,USART_SR_REG_BIT1_FE);
    }

    if (GET_BIT( USART1->SR,USART_SR_REG_BIT2_NE))                                       // Noise error flag
    {
        // Noise error occurred
        errors |=GET_BIT( USART1->SR,USART_SR_REG_BIT2_NE);
    }

    if (GET_BIT( USART1->SR,USART_SR_REG_BIT3_ORE))                                       //Overrun error Flag
    {
        // Overrun error occurred
        errors |= GET_BIT( USART1->SR,USART_SR_REG_BIT3_ORE);
    }
    break;
    
    case USART2_PERIPHERAL:
          current_usart=USART2;
        break;

        case USART3_PERIPHERAL:
          current_usart=USART3;
        break;
    }
    

    return errors;
}


/**
 * @brief ISR of USART1, used to store each byte recevied till request frame is fully collected
 * 
 */
void USART1_IRQHandler(void)
{
  Uart_Callback((uint8_t)USART1->DR);
}



