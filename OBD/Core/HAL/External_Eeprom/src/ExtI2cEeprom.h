#ifndef __External_EEPROM_H
#define __External_EEPROM_H

/**
 * @file ExtI2cEeprom.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of External EEPROM Memory AT24C512
 * @version    1.0.0
 * @date       2024-03-12
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "typedefs.h"
#include "I2C.h"
/*____________________Macros________________________________________*/

#define             EEPROM_ADDR             EEPROM1_ADDR
#define             WAIT_5ms()              HAL_Delay(5)                              
#define             PAGE_SIZE               128     // in Bytes
#define             PAGE_NUM                512    // number of pages
#define             BLETOOTH_SECTION_SIZE   9U
#define             EEPROM_EMPTY_VALUE      0xff
/*____________________UserDatatypes___________________________________*/

/// @brief this enumeration will be used as a return types to indicate if the function
///        returns successfully or Not !.
typedef enum
{
    VALID_Eeprom  = 0,
    NOT_VALID_Eeprom = 1,
    UNKOWN_Eeprom = 2
}enumRetEeprom_e;

/// @brief  this enumeration stores the valid 4 EEPROM device Addresses (00,01,10,11) --- > (A0,A1),
///         this address should match with HW Connection on Pins (1(A0),2(A1))
typedef enum
{                                    //(0 A1 A0 RW)
    EEPROM0_ADDR      =   0XA0,      //(0 0  0  0)
    EEPROM1_ADDR     =    0XA2,      //(0 0  1  0)
    EEPROM2_ADDR     =    0XA4,      //(0 1  0  0)
    EEPROM3_ADDR     =    0XA6       //(0 1  1  0)
}enumEepromId_e;

/*_____________________Prototypes______________________________________*/

/// @brief this function initializes the External EEPROM chip.
/// @param NAN
/// @return the validity of initialization of External EEPROM chip :
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2003
enumRetEeprom_e enum_EepromInit(void);

/// @brief this function writes one page of External EEPROM using I2C protocol
/// @param u8DataToWrite pointer to string we want to write to External EEPROM.
/// @param u16PageNumber number of page we want to write in
/// @param u8DataSize    size of data we want to save to a page (MAX = 128 bytes)
/// @return the validity of writing to External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom
/// @note covers Req ID : CCO-CDD-2005
enumRetEeprom_e enum_EepromWriteOnePage(u8_t* u8DataToWrite,u8_t u8DataSize,u16_t u16PageNumber);

/// @brief this function reads a single page from External EEPROM using I2C protocol
/// @param u8DataToRead (out) pointer to string we want to read from External EEPROM.
/// @param u8DataSize size of data we want to read from External EEPROM.
/// @param u16PageNumber number of page we want to read from 
/// @return the validity of reading from External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2004
enumRetEeprom_e enum_EepromReadOnePage(u8_t* u8DataToRead,u8_t u8DataSize,u16_t u16PageNumber);

/// @brief this function writes one byte of External EEPROM using I2C protocol.
/// @param u8ByteToWrite byte we want to write it to External EEPROM.
/// @param u16PageNumber number of page we want to write in (0) ~ (511)
/// @param u16ByteNumber number of byte  (0) ~ (127)
/// @return the validity of writing to External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2005
enumRetEeprom_e enum_EepromWriteOneByte(u8_t* u8DataToWrite,u16_t u16PageNumber, u8_t u16ByteNumber);

/// @brief this function reads a single Byte from External EEPROM using I2C protocol
/// @param u8DataToRead (out)pointer to byte we want to read from External EEPROM.
/// @param u16PageNumber number of page we want to read from
/// @param u16ByteNumber number of byte from (0) ~ (127)
/// @return the validity of reading from External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2004
enumRetEeprom_e enum_EepromReadOneByte(u8_t* u8DataToRead,u16_t u16PageNumber,u8_t u16ByteNumber);

/// @brief this function clears the entire 64Kbytes of EEPROM.
/// @param NAN
/// @return the validity of writing to External EEPROM chip.
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2004 , CCO-CDD-2005
enumRetEeprom_e enum_EepromCleanAllPages(void);

/// @brief this function just  writes our private data on page0  (END of Line ) of External EEPROM using I2C protocol
/// @param u8ConstDataToWrite pointer to string we want to write on page0 of External EEPROM.
/// @param u8DataSize size of data we want to save on page0 (MAX = 128 bytes)
/// @return the validity of writing to External EEPROM chip.
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom 
/// @note covers Req ID : CCO-CDD-2005
enumRetEeprom_e enum_EepromWritePage0(u8_t* u8ConstDataToWrite,u8_t u8DataSize);

/*end __External_EEPROM_H*/
#endif