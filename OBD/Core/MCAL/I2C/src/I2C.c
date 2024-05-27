
/**
 * @file I2C.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Source file of  (I2C) Component
 * @version    1.0.0
 * @date       2024-03-06
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


/*__________________ -Includes- _________________*/
#include "I2C.h"

/*__________________ -Macros- _________________*/

/*_________________ - Privates _______________*/


/*__________________ -Public- _________________*/
I2C_HandleTypeDef GLOB_strHi2c1;

/*__________________ -Privates- _________________*/
PRIVATE u8_t u8InitDoneFlag = 0;

/*__________________ -Implementations- _________________*/

enumRetI2C_e enum_I2C1Init(void)
{
  /*----- Locals -----*/
  enumRetI2C_e LOC_enumRetVal = UNKOWN_I2C;

  /*-------Action Here ! --------*/
  MX_I2C1_Init();
  u8InitDoneFlag = 1 ; 
  LOC_enumRetVal = VALID_I2C;
  return LOC_enumRetVal;
}

enumRetI2C_e enum_I2C1SendDataToMem(u16_t u16DevAddress, u16_t u16MemAddress, u16_t u16MemAddSize, u8_t *u8_pData, u16_t u16Size)
{
  /*----- Locals -----*/
  enumRetI2C_e LOC_enumRetVal = UNKOWN_I2C;

  /*-------Action Here ! --------*/
  if((u8InitDoneFlag == 1) && (&GLOB_strHi2c1!=NULL) && (u8_pData!=NULL) && (u16Size!=0) )
  {
    if(HAL_I2C_Mem_Write(&GLOB_strHi2c1,u16DevAddress,u16MemAddress,u16MemAddSize,u8_pData,u16Size,I2C_TIMOUT)  == HAL_OK)
    {
      LOC_enumRetVal = VALID_I2C;
    }
    else 
    {
      LOC_enumRetVal = NOT_VALID_I2C;
    }
  }
  else 
  {
    LOC_enumRetVal = NOT_VALID_I2C;
  }
  return LOC_enumRetVal;
}

enumRetI2C_e enum_I2C1RecDataFromMem(u16_t u16DevAddress, u16_t u16MemAddress, u16_t u16MemAddSize, u8_t *u8_pData, u16_t u16Size)
{
    /*----- Locals -----*/
  enumRetI2C_e LOC_enumRetVal = UNKOWN_I2C;

  /*-------Action Here ! --------*/
  if((u8InitDoneFlag == 1)&&(&GLOB_strHi2c1 != NULL) && (u8_pData!=NULL) && (u16Size!=0) )
  {
    if(HAL_I2C_Mem_Read(&GLOB_strHi2c1,u16DevAddress,u16MemAddress,u16MemAddSize,u8_pData,u16Size,I2C_TIMOUT)  == HAL_OK)
    {
      LOC_enumRetVal = VALID_I2C;
    }
    else 
    {
      LOC_enumRetVal = NOT_VALID_I2C;
    }
  }
  else 
  {
    LOC_enumRetVal = NOT_VALID_I2C;
  }
  return LOC_enumRetVal;
}
