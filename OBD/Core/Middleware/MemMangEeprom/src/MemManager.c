/**
 * @file MemManager.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of Memory Manager of External EEPROM
 * @version    1.0.0
 * @date       2024-03-13
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "MemManager.h"

/*____________________Public APIs___________________________________*/

/*____________________Public Variables___________________________________*/


/*____________________Privates___________________________________*/

/// @brief this function update the specific static PID data 
/// @param strDataToWrite PID,MODE,Data
/// @param u16CurrentPage number of page in EEPROM
/// @return the validity of writing to External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom
PRIVATE enumRetEeprom_e enum_FillPIDstaticData(strPIDstatic_t *strDataToWrite,u16_t u16CurrentPage)
{
    /* ----- LOCALs ------*/
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    u8_t             LOC_u8Counter = 0 ;

    /*------ ACTIONs ------*/

    /*Update the PID field*/
    for(u8_t LOC_u8Counter1 = 0; LOC_u8Counter1<=3 ; LOC_u8Counter1++,LOC_u8Counter++)
    {
        LOC_enumRetFromEEPROM = enum_EepromWriteOneByte(&(strDataToWrite->u8StaticPid[LOC_u8Counter1]),u16CurrentPage,LOC_u8Counter);
    }
    (void)LOC_enumRetFromEEPROM;
    
    /*Update the Mode field*/
    for(u8_t LOC_u8Counter2 = 0; LOC_u8Counter2<=2 ; LOC_u8Counter2++,LOC_u8Counter++)
    {
        LOC_enumRetFromEEPROM = enum_EepromWriteOneByte(&(strDataToWrite->u8Mode[LOC_u8Counter2]),u16CurrentPage,LOC_u8Counter);
    }
    (void)LOC_enumRetFromEEPROM;
    
    /*Update the Data field*/
    for(u8_t LOC_u8Counter3 = 0; LOC_u8Counter3<=15 ; LOC_u8Counter3++,LOC_u8Counter++)
    {
        LOC_enumRetFromEEPROM = enum_EepromWriteOneByte(&(strDataToWrite->u8StaticData[LOC_u8Counter3]),u16CurrentPage,LOC_u8Counter);
    }
    (void)LOC_enumRetFromEEPROM;
    
    /*Add Extra Space*/
    LOC_enumRetFromEEPROM = enum_EepromWriteOneByte(&(strDataToWrite->u8StaticData[16]),u16CurrentPage,LOC_u8Counter);

    /*----- Return -----*/
    return  LOC_enumRetFromEEPROM;
}

/// @brief this function Retrieve the specific static PID data 
/// @param strDataToWrite PID,MODE,Data
/// @param u16CurrentPage number of page in EEPROM
/// @return the validity of writing to External EEPROM chip : 
///         VALID_Eeprom  Or  NOT_VALID_Eeprom Or UNKOWN_Eeprom
PRIVATE enumRetEeprom_e enum_RetrievePIDstaticData(strPIDstatic_t *strDataToWrite,u16_t u16CurrentPage)
{
    /* ----- LOCALs ------*/
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    u8_t             LOC_u8Counter = 0 ;

    /*------ ACTIONs ------*/

    /*Read the PID field*/
    for(u8_t LOC_u8Counter1 = 0; LOC_u8Counter1<=3 ; LOC_u8Counter1++,LOC_u8Counter++)
    {
        LOC_enumRetFromEEPROM = enum_EepromReadOneByte(&(strDataToWrite->u8StaticPid[LOC_u8Counter1]),u16CurrentPage,LOC_u8Counter);
    }
    
    
    /*read the Mode field*/
    if(LOC_enumRetFromEEPROM == VALID_Eeprom)
    {
        for(u8_t LOC_u8Counter2 = 0; LOC_u8Counter2<=2 ; LOC_u8Counter2++,LOC_u8Counter++)
        {
            LOC_enumRetFromEEPROM = enum_EepromReadOneByte(&(strDataToWrite->u8Mode[LOC_u8Counter2]),u16CurrentPage,LOC_u8Counter);
        }
    }
    else 
    {
        LOC_enumRetFromEEPROM = NOT_VALID_Eeprom;
    }
    
    
    
    /*Read the Data field*/
    if(LOC_enumRetFromEEPROM == VALID_Eeprom)
    {
        for(u8_t LOC_u8Counter3 = 0; LOC_u8Counter3<=15 ; LOC_u8Counter3++,LOC_u8Counter++)
        {
            LOC_enumRetFromEEPROM = enum_EepromReadOneByte(&(strDataToWrite->u8StaticData[LOC_u8Counter3]),u16CurrentPage,LOC_u8Counter);
        }
    }
    else 
    {
        LOC_enumRetFromEEPROM = NOT_VALID_Eeprom;
    }
    
    /*Read Extra Element*/
    if(LOC_enumRetFromEEPROM == VALID_Eeprom)
    {
        LOC_enumRetFromEEPROM = enum_EepromReadOneByte(&(strDataToWrite->u8StaticData[16]),u16CurrentPage,LOC_u8Counter);
    }
    else 
    {
        LOC_enumRetFromEEPROM = NOT_VALID_Eeprom;
    }
    /*----- Return -----*/
    return  LOC_enumRetFromEEPROM;
}
/*____________________Implementations___________________________________*/

enumRetMemMang_e enum_MemMngUpdateBlueTooth(u8_t *u8BluetoothConfigStatus)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    /*------ ACTIONs ------*/

    /*Error happens here so returns*/
    if(
        (u8BluetoothConfigStatus == NULL)
        ||
        ((strcmp(u8BluetoothConfigStatus,MEM_MANAGER_BLUETOOTH_NOT_INITIALIZED)!=0)
        &&
        (strcmp(u8BluetoothConfigStatus,MEM_MANAGER_BLUETOOTH_SUCCESS)!=0)
        &&
        (strcmp(u8BluetoothConfigStatus,MEM_MANAGER_BLUETOOTH_FAIL)!=0))
      )
    {
        LOC_enumRetVal = NOT_VALID_MEM_MANG;
    }
    else 
    {
        LOC_enumRetFromEEPROM = enum_EepromWriteOnePage(u8BluetoothConfigStatus,BLETOOTH_SECTION_SIZE,MEM_MANAGER_BLUETOOTH_BLOCK);
        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
        }
    }
    
    /*------- Return ------*/
    return LOC_enumRetVal;
}

enumRetMemMang_e enum_MemMngReadBlueTooth(u8_t *u8BluetoothConfigStatus)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    if(u8BluetoothConfigStatus != NULL)
    {
        /*------ ACTIONs ------*/
        LOC_enumRetFromEEPROM = enum_EepromReadOnePage(u8BluetoothConfigStatus,9,MEM_MANAGER_BLUETOOTH_BLOCK);

        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
        }
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_MEM_MANG;
    }

    /*------- Return ------*/
    return LOC_enumRetVal;
}

enumRetMemMang_e enum_MemMngUpdateDevInfo(u8_t *u8DeviceInfo,u8_t u8DeviceInfoSize)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    /*------ ACTIONs ------*/
    if(u8DeviceInfo == NULL)
    {
        LOC_enumRetVal = NOT_VALID_MEM_MANG;
    }
    else 
    {
        LOC_enumRetFromEEPROM = enum_EepromWritePage0(u8DeviceInfo,u8DeviceInfoSize);
        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;           
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
        }
    }
    
    /*------- Return ------*/
    return LOC_enumRetVal;
}

enumRetMemMang_e enum_MemMngReadDevInfo(u8_t *u8DeviceInfo)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    /*------ ACTIONs ------*/
    if(u8DeviceInfo == NULL)
    {
        LOC_enumRetVal = NOT_VALID_MEM_MANG;
    }
    else 
    {
        LOC_enumRetFromEEPROM = enum_EepromReadOnePage(u8DeviceInfo,PAGE_SIZE,MEM_MANAGER_DEVICE_INFO_BLOCK);
        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
        }
    }
    
    /*------- Return ------*/
    return LOC_enumRetVal;
}

enumRetMemMang_e enum_MemMngUpdateStatic(strPIDstatic_t *strDataToWrite, enumStaticPIDs_e enumStaticPID)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    /*---- ACTIONs ----*/
    if((strDataToWrite == NULL) || (enumStaticPID >= PIDs_NUMBERS))
    {
        LOC_enumRetVal  = NOT_VALID_MEM_MANG;
    }
    else 
    {
        LOC_enumRetFromEEPROM = enum_FillPIDstaticData(strDataToWrite,(u16_t)enumStaticPID+1);
        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else 
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
        }
    }

    /*---- Return -----*/
    return LOC_enumRetVal;
}

enumRetMemMang_e enum_MemMngReadStatic(strPIDstatic_t *strPIDdataStored, enumStaticPIDs_e enumStaticPID)
{
    /*------ LOCALs -------*/
    enumRetMemMang_e LOC_enumRetVal = UNKOWN_MEM_MANG; 
    enumRetEeprom_e  LOC_enumRetFromEEPROM = UNKOWN_Eeprom;
    
    /*---- ACTIONs ----*/
    if((strPIDdataStored == NULL) || (enumStaticPID >= PIDs_NUMBERS))
    {
        LOC_enumRetVal  = NOT_VALID_MEM_MANG;
    }
    else 
    {
        LOC_enumRetFromEEPROM = enum_RetrievePIDstaticData(strPIDdataStored,(u16_t)enumStaticPID+1);
        if(LOC_enumRetFromEEPROM == VALID_Eeprom)
        {
            LOC_enumRetVal = VALID_MEM_MANG;
        }
        else if(LOC_enumRetFromEEPROM == NOT_VALID_Eeprom)
        {
            LOC_enumRetVal = NOT_VALID_MEM_MANG;
        }
        else 
        {
            LOC_enumRetVal = UNKOWN_MEM_MANG;
            }
    }

    /*---- Return -----*/
    return LOC_enumRetVal;
}

