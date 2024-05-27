/**
 * @file TPS.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of Temperature sensor
 * @version    1.0.0
 * @date       2024-03-07
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "TPS.h"
#include <math.h>
#include "services.h"
/*______________________MACROs__________________________________*/
/*A_TPS @ -55  .. B_TPS @ -25 .. C_TPS @ +75 .. D_TPS @ +125*/
#define     A_TPS  (float32_t)0.001213614044361f
#define     B_TPS  (float32_t)0.00024875849689f
#define     C_TPS  (float32_t)-4.187664613763E-06f
#define     D_TPS  (float32_t)2.571954081307E-07f



/*____________________Public___________________________________*/


/*____________________Privates___________________________________*/
#if(TPS_UT==OFF)
/// @brief this flag will be set in case we are writing on the strNTCInfo, to protect race condition, otherwise it is = 0 !
PRIVATE    u8_t                   u8UpdateIsDone = 0;

/// @brief this struct contains the information of the NTC sensor (temperature , state of the sesnor)
PRIVATE    strTemperatureNtc_t    strNTCInfo       ={25.0,MALFUNCTION_TEMPERATURE};

/// @brief this flag will be set when enum_TPSInit is performed successfully, otherwise it is = 0 !
PRIVATE    u8_t                   u8InitIsDone = 0;

/// @brief this function Claculates resistance of NTC sensor using this equation Rntc=10000.0/((4096.0/adcValue)-1)
/// @param doubleNtcResistanceInOhms the resistance of NTC sensor
/// @param u32AdcValue : the adc value.
/// @return the state of function execution.
///         VALID_TPS (0) - NOT_VALID_TPS (1) - UNKOWN_TPS (2) - WRITING_IN_PROGRESS_TPS(3)

/// @covers Req ID:CCO-CDD-2008
PRIVATE enumRetTps_e enum_TPSClaculateResistance(u32_t u32AdcValue,float32_t *floatNtcResistanceInOhms)
{
    /*------ LOCALs -----*/
    enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
    float32_t LOC_X = 0.0;
    /*------- Actions -----*/
    if(floatNtcResistanceInOhms != NULL)
    {
        /*--- we are following the equation mentioned in the comment of this API in the TPS.h file */
        LOC_X = 4096.0f/(float32_t)u32AdcValue;
        *floatNtcResistanceInOhms = 10000.0f/(LOC_X -1);
        enum_LOCenumRetVal = VALID_TPS;
    }
    else 
    {
        enum_LOCenumRetVal = NOT_VALID_TPS;
    }
    /*------- Return ------*/
    return enum_LOCenumRetVal;
}
#endif

#if(TPS_UT==ON)
/// @brief this flag will be set in case we are writing on the strNTCInfo, to protect race condition, otherwise it is = 0 !
    u8_t                   u8UpdateIsDone = 0;

/// @brief this struct contains the information of the NTC sensor (temperature , state of the sesnor)
    strTemperatureNtc_t    strNTCInfo       ={25.0,MALFUNCTION_TEMPERATURE};

/// @brief this flag will be set when enum_TPSInit is performed successfully, otherwise it is = 0 !
    u8_t                   u8InitIsDone = 0;

enumRetTps_e enum_TPSClaculateResistance(u32_t u32AdcValue,float32_t *floatNtcResistanceInOhms)
{
    /*------ LOCALs -----*/
    enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
    float32_t LOC_X = 0.0;
    /*------- Actions -----*/
    if(floatNtcResistanceInOhms != NULL)
    {
        /*--- we are following the equation mentioned in the comment of this API in the TPS.h file */
        LOC_X = 4096.0f/(float32_t)u32AdcValue;
        *floatNtcResistanceInOhms = 10000.0f/(LOC_X -1);
        enum_LOCenumRetVal = VALID_TPS;
    }
    else 
    {
        enum_LOCenumRetVal = NOT_VALID_TPS;
    }
    /*------- Return ------*/
    return enum_LOCenumRetVal;
}

#endif



/*_____________________Implementations______________________________________*/
double double_CustomePow(double Base,char Pow)
{
    double Ret = Base ;
    while(Pow>1)
    {
        Ret*=Base;
        Pow--;
    }
    return Ret;
}

enumRetTps_e enum_TPSInit(void)
{
    /*------ LOCALs -----*/
    enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;

    /*------- Actions -----*/
    enum_AdcInit();
    u8InitIsDone = 1 ;
    enum_LOCenumRetVal = VALID_TPS;
   
    /*------- Return ------*/
    return enum_LOCenumRetVal;
}

void vid_TPSManage(void)
{
    /*-------- LOCALs -------*/
    float32_t LOC_floatTemperatureNow = 25.0;
    float32_t LOC_R = 0.0;
    float32_t LOC_A = A_TPS;
    float32_t LOC_B = 0.0;
    float32_t LOC_C = 0.0;
    float32_t LOC_D = 0.0;
    float32_t LOC_lnR= 0.0;
    u32_t LOC_u32ADCValue = 0;
    
    if(u8InitIsDone == 1 )
    {
        /*----- Update u8UpdateIsDone ---- */
        u8UpdateIsDone =  0 ;

        /*__Get ADC Value (0~4095)*/
        enum_AdcReadFromChannel(ADC_CHANNEL_TPS,&LOC_u32ADCValue);

        /*__Convert to Temperature ----- >     1/T  = A + B⋅ln(R) + C⋅((ln(R))^2) + D⋅((ln(R))^3)    */
        enum_TPSClaculateResistance(LOC_u32ADCValue,&LOC_R);
        LOC_lnR= (float32_t)log(LOC_R);
        LOC_B = B_TPS * LOC_lnR;
        LOC_C = C_TPS * (float32_t)double_CustomePow(LOC_lnR,2);
        LOC_D = D_TPS * (float32_t)double_CustomePow(LOC_lnR,3);
        LOC_floatTemperatureNow = 1.0f/(LOC_A + LOC_B + LOC_C + LOC_D) ;
        LOC_floatTemperatureNow = LOC_floatTemperatureNow - 273.15f;

        /*-------- Update structure ----------*/
        strNTCInfo.doubleTmp = LOC_floatTemperatureNow;

        if(LOC_floatTemperatureNow >90.0f)
        {
            strNTCInfo.enumTmpState = MALFUNCTION_TEMPERATURE;
        } 
        else if(LOC_floatTemperatureNow >=5.0f && LOC_floatTemperatureNow <=70.0f)
        {
            strNTCInfo.enumTmpState = NORMAL_TEMPERATURE;
        }  
        else if (LOC_floatTemperatureNow >70.0f) 
        {
            strNTCInfo.enumTmpState = HIGH_TEMPERATURE;
        }
        else if (LOC_floatTemperatureNow <5.0f) 
        {
            strNTCInfo.enumTmpState = LOW_TEMPERATURE;
        }
        else
        {
            strNTCInfo.enumTmpState = MALFUNCTION_TEMPERATURE;
        }
        u8UpdateIsDone = 1;
    }
    else 
    {
        /* Do nothing - returns*/
    }
    
}

enumRetTps_e enum_TPSGetTemperature(strTemperatureNtc_t* strNTCInfoOut)
{
    /*------ LOCALs -----*/
    enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
            /*------- Actions -----*/
        if((u8UpdateIsDone == 1) && (strNTCInfoOut!=NULL))
        {
            strNTCInfoOut->doubleTmp = strNTCInfo.doubleTmp;
            strNTCInfoOut->enumTmpState = strNTCInfo.enumTmpState;
            enum_LOCenumRetVal = VALID_TPS;
        }
        else 
        {
            enum_LOCenumRetVal = NOT_VALID_TPS;
        }
    /*------- Return ------*/
    return enum_LOCenumRetVal;
}
