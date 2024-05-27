/**
 * @file BitsManager.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of (Bits Manager) Component
 * @version    1.0.0
 * @date       2024-03-19
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __BITSMANAGER__H__
#define __BITSMANAGER__H__
/*__________________ -Includes- _________________*/
#include    "Timer.h"
#include    "typedefs.h"
/*__________________ -Macros- _________________*/


/*__________________ -UserDataTypes- _________________*/

///@brief :  this enumeration will be used as a return types
///          to indicate if the function returns successfully or Not !.
typedef enum 
{
	VALID_BITS_MANAGER 			= 0,
	NOT_VALID_BITS_MANAGER		= 1,
	UNKOWN_BITS_MANAGER			= 2
}enumRetBitsManager_e;

/// @brief this enumeration contains the HIGH or LOW bit or UNRECOGNIZE bit .
typedef enum 
{
    LOW_BIT_BITS_MANAGER            =  0,
    HIGH_BIT_BITS_MANAGER           =  1,
    SOF_BIT_BITS_MANAGER            =  2,
    UNRECOGNIZE_BIT_BITS_MANAGER    =  3 
}enumBitsManagerHL_e;

/*__________________ -Public- _________________*/


/*__________________ -Prototypes- _________________*/

/// @brief this function is responsible for sending one or multiple High bits of the (SAE J1850 PWM) frame .
/// @param u8BitsNumber how many High bits we want to send
/// @return the validity of function Execution
///         VALID_BITS_MANAGER   or    NOT_VALID_BITS_MANAGER    or   UNKOWN_BITS_MANAGER
/// @note covers Req ID:CCO-CDD-2090
enumRetBitsManager_e enum_BitsManagerSendHigh(u8_t u8BitsNumber);


/// @brief this function is responsible for sending one or multiple Low bits of the (SAE J1850 PWM) frame .
/// @param u8BitsNumber how many Low bits we want to send
/// @return the validity of function Execution
///         VALID_BITS_MANAGER   or    NOT_VALID_BITS_MANAGER    or   UNKOWN_BITS_MANAGER
/// @note covers Req ID:CCO-CDD-2090
enumRetBitsManager_e enum_BitsManagerSendLow(u8_t u8BitsNumber);

/// @brief this function is responsible for sending SOF (200us) potential HIGH 
/// @param NAN
/// @return the validity of function Execution
///         VALID_BITS_MANAGER   or    NOT_VALID_BITS_MANAGER    or   UNKOWN_BITS_MANAGER
/// @note covers Req ID:CCO-CDD-2091
enumRetBitsManager_e enum_BitsManagerSendSOF(void);

/// @brief  this function is responsible for sending EOD (200us) potential LOW  
/// @param  
/// @return the validity of function Execution
///         VALID_BITS_MANAGER   or    NOT_VALID_BITS_MANAGER    or   UNKOWN_BITS_MANAGER
/// @note covers Req ID:CCO-CDD-2093  
enumRetBitsManager_e enum_BitsManagerSendEOD(void);


/// @brief this function is responsible for Receiving one or multiple High/Low bits
///        of the (SAE J1850 PWM) frame .
/// @param enumRecBit the received bit.
///    LOW_BIT_BITS_MANAGER   or HIGH_BIT_BITS_MANAGER or UNRECOGNIZE_BIT_BITS_MANAGER     
/// @return the validity of function Execution
///         VALID_BITS_MANAGER   or    NOT_VALID_BITS_MANAGER    or   UNKOWN_BITS_MANAGER
/// @note covers Req ID:CCO-CDD-2093 
enumRetBitsManager_e enum_BitsManagerGetBits(enumBitsManagerHL_e* enumRecBit);


#endif 

