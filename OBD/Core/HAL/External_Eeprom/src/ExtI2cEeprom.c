/**
 * @file ExtI2cEeprom.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of External EEPROM Memory AT24C512
 * @version    1.0.0
 * @date       2024-01-15
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "ExtI2cEeprom.h"

/*____________________Public APIs___________________________________*/

/*____________________Public Variables___________________________________*/

/// @brief  this is STM32 variable, it is used for initialization I2C module 
PUBLIC I2C_Handle_s GLOB_strHi2c1;

/*____________________Privates___________________________________*/

/// @brief this flag will be set when enum_EepromInit is performed successfully, otherwise it is = 0 !
PRIVATE u8_t u8InitIsDone = 0;
/*____________________Implementations___________________________________*/

enumRetEeprom_e enum_EepromInit(void)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    
    /*--- Implementaion Here ! ---*/
    enum_I2C1Init();
    LOC_enumRetValidOrNot = VALID_Eeprom;
    u8InitIsDone = 1 ;

    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
}

enumRetEeprom_e enum_EepromWriteOnePage(u8_t* u8DataToWrite,u8_t u8DataSize,u16_t u16PageNumber)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    u16_t           LOC_u16Address        = 0x00;
    
    /*--- Implementaion Here ! ---*/
    if((u8InitIsDone==0) || (u16PageNumber > (PAGE_NUM-1)) || (u16PageNumber == 0) || (u8DataSize > PAGE_SIZE) || (u8DataSize == 0) || (u8DataToWrite == NULL))
    {
        /* -- ERROR --*/
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }  
    else 
    {
        LOC_u16Address = u16PageNumber * PAGE_SIZE;
        /*---- Write into External EEPROM ----*/
        if(I2C_Mem_Write(&GLOB_strHi2c1,(u16_t)EEPROM_ADDR,LOC_u16Address,2,u8DataToWrite,u8DataSize,I2C_TIMOUT) == HAL_ERROR)
        {
            /* -- ERROR "in I2C Communication"--*/
            LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
        }
        else
        {
            LOC_enumRetValidOrNot = VALID_Eeprom;
        }
    }  
    WAIT_5ms();
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
} 

enumRetEeprom_e enum_EepromWritePage0(u8_t* u8ConstDataToWrite,u8_t u8DataSize)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    
    /*--- Implementaion Here ! ---*/
    if((u8InitIsDone==0) || (u8DataSize > PAGE_SIZE) || (u8DataSize == 0) || (u8ConstDataToWrite == NULL))
    {
        /* -- ERROR --*/
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }  
    else 
    {
        /*---- Write into External EEPROM ----*/
        if(I2C_Mem_Write(&GLOB_strHi2c1,(u16_t)EEPROM_ADDR,0,2,u8ConstDataToWrite,u8DataSize,I2C_TIMOUT) == HAL_ERROR)
        {
            /* -- ERROR "in I2C Communication"--*/
            LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
        }
        else
        {
            LOC_enumRetValidOrNot = VALID_Eeprom;
        }
    }  
    WAIT_5ms();
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
} 

enumRetEeprom_e enum_EepromReadOnePage(u8_t* u8DataToRead,u8_t u8DataSize,u16_t u16PageNumber)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    u16_t           LOC_u16Address        = 0x00;

    /*--- Implementaion Here ! ---*/
    if((u8InitIsDone==0) || (u16PageNumber > (PAGE_NUM-1)) || (u8DataSize > PAGE_SIZE) || (u8DataSize == 0) || (u8DataToRead == NULL))
    {
        /* -- ERROR --*/
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }  
    else 
    {
        LOC_u16Address = u16PageNumber * PAGE_SIZE;
        /*---- Read From External EEPROM ----*/
        if(I2C_Mem_Read(&GLOB_strHi2c1,(u16_t)EEPROM_ADDR,LOC_u16Address,2,u8DataToRead,u8DataSize,I2C_TIMOUT) == HAL_ERROR)
        {
            /* -- ERROR "in I2C Communication"--*/
            LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
        }
        else
        {
            LOC_enumRetValidOrNot = VALID_Eeprom;
        }
    }
    WAIT_5ms();
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
}

enumRetEeprom_e enum_EepromWriteOneByte(u8_t* u8ByteToWrite, u16_t u16PageNumber, u8_t u16ByteNumber)
{
  /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    u16_t           LOC_u16Address        = 0x00;
    
    /*--- Implementaion Here ! ---*/
    if((u8InitIsDone==0) || (u16PageNumber > (PAGE_NUM-1)) || (u16PageNumber == 0) || (u8ByteToWrite == NULL) || (u16ByteNumber > (PAGE_SIZE-1)))
    {
        /* -- ERROR --*/
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }  
    else 
    {
        LOC_u16Address =  u16ByteNumber + (u16PageNumber * PAGE_SIZE);
        /*---- Write into External EEPROM ----*/
        if(I2C_Mem_Write(&GLOB_strHi2c1,(u16_t)EEPROM_ADDR,LOC_u16Address,2,u8ByteToWrite,1,I2C_TIMOUT) == HAL_ERROR)
        {
            /* -- ERROR "in I2C Communication"--*/
            LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
        }
        else
        {
            LOC_enumRetValidOrNot = VALID_Eeprom;
        }
    }  
    WAIT_5ms();
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;  
}

enumRetEeprom_e enum_EepromReadOneByte(u8_t *u8ByteToRead, u16_t u16PageNumber, u8_t u16ByteNumber)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    u16_t           LOC_u16Address        = 0x00;

    /*--- Implementaion Here ! ---*/
    if((u8InitIsDone==0) || (u16PageNumber > (PAGE_NUM-1)) || (u16PageNumber == 0) || (u8ByteToRead == NULL) || (u16ByteNumber > (PAGE_SIZE-1)))
    {
        /* -- ERROR --*/
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }  
    else 
    {
        LOC_u16Address =  u16ByteNumber + (u16PageNumber * PAGE_SIZE);
        /*---- Read from External EEPROM ----*/
        if(I2C_Mem_Read(&GLOB_strHi2c1,(u16_t)EEPROM_ADDR,LOC_u16Address,2,u8ByteToRead,1,I2C_TIMOUT) == HAL_ERROR)
        {
            /* -- ERROR "in I2C Communication"--*/
            LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
        }
        else
        {
            LOC_enumRetValidOrNot = VALID_Eeprom;
        }
    }
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
}

enumRetEeprom_e enum_EepromCleanAllPages(void)
{
    /*--- Locals ---*/
    enumRetEeprom_e LOC_enumRetValidOrNot = UNKOWN_Eeprom;
    u8_t           LOC_u8DataToWrite[PAGE_SIZE];
    u16_t          LOC_u16Counter = 0;
    
    /*--- Implementaion Here ! ---*/
    if(u8InitIsDone==1)
    {
        /*set return to VALID_Eeprom initially, it will be NOT_VALID_Eeprom if any error occurs in writing!*/
        LOC_enumRetValidOrNot = VALID_Eeprom;

        /* fill the internal array with 0xff value*/
        for(LOC_u16Counter=0;LOC_u16Counter<PAGE_SIZE;LOC_u16Counter++)
        {
            LOC_u8DataToWrite[LOC_u16Counter] = EEPROM_EMPTY_VALUE;
        }

        /*clear the eeprom pages*/
        for(LOC_u16Counter=1;LOC_u16Counter<PAGE_NUM;LOC_u16Counter++)
        {
            if(enum_EepromWriteOnePage(LOC_u8DataToWrite,PAGE_SIZE,LOC_u16Counter) == NOT_VALID_Eeprom)
            {
                LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
                break;
            }
            WAIT_5ms();
        }
    }
    else 
    {
        LOC_enumRetValidOrNot = NOT_VALID_Eeprom;
    }
    
    /*--- Return ---*/
    return LOC_enumRetValidOrNot;
}







      
