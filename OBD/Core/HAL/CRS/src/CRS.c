/**
 * @file CRS.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of Current sensor
 * @version    1.0.0
 * @date       2024-03-11
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "CRS.h"
#include "typedefs.h"

/*____________________Public___________________________________*/


/*____________________Privates___________________________________*/

#if(CRS_UT==OFF)

/// @brief this flag will be set when enum_CRSInit is performed successfully, otherwise it is = 0 !
PRIVATE     u8_t            u8InitIsDone            = 0;

/// @brief this flag will be set in case we are writing on the strCurrentInfo, to protect race condition, otherwise it is = 0 !
PRIVATE     u8_t            u8UpdateInProgress      = 0;

/// @brief this struct contains the information of the current sensor (current , state of the sesnor)
PRIVATE     strCurrent_t    strCurrentInfo          = {0.0,MALFUNCTION_CURRENT};
#endif

#if(CRS_UT==ON)
/// @brief this flag will be set when enum_CRSInit is performed successfully, otherwise it is = 0 !
     u8_t            u8InitIsDone            = 0;

/// @brief this flag will be set in case we are writing on the strCurrentInfo, to protect race condition, otherwise it is = 0 !
     u8_t            u8UpdateInProgress      = 0;

/// @brief this struct contains the information of the current sensor (current , state of the sesnor)
     strCurrent_t    strCurrentInfo          = {0.0,MALFUNCTION_CURRENT};
#endif
/*_____________________Implementations______________________________________*/

enumRetCrs_e enum_CRSInit(void)
{   
    /*___Locals____*/
    enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;

    /*___Init____*/
    enum_AdcInit();

    /*___Set return value and Init is Done variable*/
    LOC_enumValidOrNot = VALID_CRS;
    u8InitIsDone   = 1 ;

    /*___Return____*/
    return LOC_enumValidOrNot;
}

void vid_CRSManage(void)
{
    /*---- LOCALs ----*/
    u32_t LOC_u32AdcValue = 0;


    if(u8InitIsDone == 1)
    {
        /*--- starting the calculations ---- */
        u8UpdateInProgress = 0;

        /*__Get ADC Value (0~4095)*/
        enum_AdcReadFromChannel(ADC_CHANNEL_CURRENT_SENSOR,&LOC_u32AdcValue);
        
        /* A = ---> {   [ADCvalue * (Vcc/4096)] - (Vcc/2) } * (1/185mv )*/
        strCurrentInfo.doubleMilliAmp = ((double)LOC_u32AdcValue * (VCC_CRS/(double)CRS_MODULE_ADC_ACCURACY));
        strCurrentInfo.doubleMilliAmp = strCurrentInfo.doubleMilliAmp - CRS_MODULE_OUT_AT_0A;
        if(strCurrentInfo.doubleMilliAmp < 0.0)
        {
            strCurrentInfo.doubleMilliAmp  = 0.0 ;
        }
        else 
        {
            strCurrentInfo.doubleMilliAmp = strCurrentInfo.doubleMilliAmp / CRS_MODULE_SENSITIVITY;
            strCurrentInfo.doubleMilliAmp = strCurrentInfo.doubleMilliAmp * 1000.0; /*in mA*/
        }

        /* ---- State -----*/
        ///        HIGH    :  >  2000mA
        ///        LOW     :  <  10mA
        ///        NORMAL  :  >= 10 mA   && <= 2000mA
        ///        MALFUNCTION : anything else
        ///        DISCONNECTED : 0A
        if((strCurrentInfo.doubleMilliAmp >= 10.0) && (strCurrentInfo.doubleMilliAmp <= 2000.0))
        {
            strCurrentInfo.enumCurrentState = NORMAL_CURRENT;
        }
        else if(strCurrentInfo.doubleMilliAmp > 2000.0)
        {
            strCurrentInfo.enumCurrentState = HIGH_CURRENT;
        }
        else if(strCurrentInfo.doubleMilliAmp == 0.0)
        {
            strCurrentInfo.enumCurrentState = DISCONNECTED_CURRENT;
        }
        else if(strCurrentInfo.doubleMilliAmp < 10.0)
        {
            strCurrentInfo.enumCurrentState = LOW_CURRENT;
        }
        else 
        {
            strCurrentInfo.enumCurrentState = MALFUNCTION_CURRENT;
        }
        /* Calculations END*/
        u8UpdateInProgress = 1;
    }
    else 
    {
        /* Do nothing */
    }
}

enumRetCrs_e enum_CRSGetCurrent(strCurrent_t *strCurrent)
{
    /*___Locals____*/
    enumRetCrs_e  LOC_enumValidOrNot = UNKOWN_CRS;
    /* --- Action ----*/
    if((u8InitIsDone == 1) && (u8UpdateInProgress == 1) && (strCurrent!=NULL))
    {
        strCurrent->doubleMilliAmp = strCurrentInfo.doubleMilliAmp;
        strCurrent->enumCurrentState = strCurrentInfo.enumCurrentState;
        LOC_enumValidOrNot = VALID_CRS;
    }
    else 
    {
        LOC_enumValidOrNot = NOT_VALID_CRS;
    }
    /*--- return ----*/
    return LOC_enumValidOrNot;
}