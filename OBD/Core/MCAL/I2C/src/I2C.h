
/**
 * @file I2C.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of (I2C) Component
 * @version    1.0.0
 * @date       2024-03-06
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __I2CCREWTEQ__H__
#define __I2CCREWTEQ__H__



/*__________________ -Includes- _________________*/

#include "main.h"
#include "typedefs.h"
/*__________________ -Macros- _________________*/
#define I2C_UT 		UT

#define I2C_Init                MX_I2C1_Init
#define I2C_Mem_Write           HAL_I2C_Mem_Write
#define I2C_Mem_Read            HAL_I2C_Mem_Read
#define I2C_Status_e            HAL_StatusTypeDef
#define I2C_Handle_s            I2C_HandleTypeDef

#define I2C_TIMOUT 			100U /*-- 100 ms --*/
/*__________________ -Public- _________________*/



/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_I2C 			= 0,
	NOT_VALID_I2C 		= 1,
	UNKOWN_I2C			= 2
}enumRetI2C_e;

/*__________________ -Prototypes- _________________*/

/// @brief this function is responsible for Initialization of I2C1 with a specific speed (100khz in SRS).
/// @param  NAN
/// @return the validity of executing the function
///         VALID_I2C Or NOT_VALID_I2C Or UNKOWN_I2C
/// @covers Req ID:CCO-CDD-2080
enumRetI2C_e enum_I2C1Init(void);


/// @brief this function is responsible for Sending Data to External EEPROM using I2C1
/// @param u16DevAddress Target device address: The device 7 bits address value
///                   in datasheet must be shifted to the left before calling the interface
/// @param u16MemAddress Internal memory address
/// @param u16MemAddSize Size of internal memory address
/// @param u8_pData Pointer to data buffer
/// @param u16Size Amount of data to be sent
/// @return the validity of executing the function
///         VALID_I2C Or NOT_VALID_I2C Or UNKOWN_I2C
/// @covers Req ID:CCO-CDD-2080
enumRetI2C_e enum_I2C1SendDataToMem( u16_t u16DevAddress, u16_t u16MemAddress, u16_t u16MemAddSize, u8_t *u8_pData, u16_t u16Size);


/// @brief this function is responsible for Retrieving Data from External EEPROM using I2C1
/// @param u16DevAddress Target device address: The device 7 bits address value
///                   in datasheet must be shifted to the left before calling the interface
/// @param u16MemAddress Internal memory address
/// @param u16MemAddSize Size of internal memory address
/// @param u8_pData Pointer to data buffer
/// @param u16Size Amount of data to be Receive
/// @return the validity of executing the function
///         VALID_I2C Or NOT_VALID_I2C Or UNKOWN_I2C
/// @covers Req ID:CCO-CDD-2080
enumRetI2C_e enum_I2C1RecDataFromMem(u16_t u16DevAddress, u16_t u16MemAddress, u16_t u16MemAddSize, u8_t *u8_pData, u16_t u16Size);


#endif
