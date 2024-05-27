/**
 * @file Battery.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of Battery Driver
 * @version    1.0.0
 * @date       2024-03-10
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "Battery.h"

/*____________________Public___________________________________*/


/*____________________Privates___________________________________*/

#if(BATTERY_UT==OFF)
/// @brief this flag is set while the calculations (writing) is in progress, when writing is done it is cleared.
PRIVATE    u8_t                    u8BATcalcInProgressFlag   =   0;

/// @brief this container contains the two batteries information (Voltage - State)
PRIVATE    strBatteriesInfo_t      strBatteriesInfo;

/// @brief this flag will be set when enum_BatInit is performed successfully, otherwise it is = 0 !
PRIVATE    u8_t                    u8InitIsDone = 0;
#endif

#if(BATTERY_UT==ON)
/// @brief this flag is set while the calculations (writing) is in progress, when writing is done it is cleared.
    u8_t                    u8BATcalcInProgressFlag   =   0;

/// @brief this container contains the two batteries information (Voltage - State)
    strBatteriesInfo_t      strBatteriesInfo;

/// @brief this flag will be set when enum_BatInit is performed successfully, otherwise it is = 0 !
    u8_t                    u8InitIsDone = 0;
#endif
/*_____________________Implementations______________________________________*/
/// @brief this fuction initialize Battery Driver to use the readings of batteries with montoring tasks.
/// @param  NAN
/// @return the validity of function execution of  Battery driver
///         VALID_BAT_RETURN  or NOT_VALID_BAT_RETURN or UNKNOWN_BAT_RETURN  

/// @covers Req ID :CCO-CDD-2016
enumRetBat_e enum_BatInit(void)
{
    /* ----- LOCALs -----*/
    enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
    
    /* ----- Actions -----*/
    enum_AdcInit();
    LOC_enumRetVal = VALID_BAT_RETURN;
    u8InitIsDone = 1 ;
    /* ----- Returns -----*/
    return LOC_enumRetVal;
}


void vid_BattManage(void)
{
    /* ----- LOCALs -----*/
    u32_t LOC_u32AdcReadValue = 0x00;
    /* ----- Actions -----*/
    if(u8InitIsDone == 1 )
    {   
        /*starting the conversion*/ 
        u8BATcalcInProgressFlag = 0 ;
        
        //#if(BATTERY_UT == OFF)
        /*getting the Adc value of On board battery channel*/ 
        enum_AdcReadFromChannel(ADC_CHANNEL_ONBOARD_BATTERY,&LOC_u32AdcReadValue);
        /*claculating the voltage  & save the value at the private structure*/
        strBatteriesInfo.floatOnBoardBatteryVoltage = (float32_t)LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU;
        //#endif
        /*determine the battery state & save the value at the private structure*/
        if((strBatteriesInfo.floatOnBoardBatteryVoltage > ON_BOARD_BATTERY_MIN) && (strBatteriesInfo.floatOnBoardBatteryVoltage<ON_BOARD_BATTERY_MAX))
        {
            strBatteriesInfo.enumOnBoardBatteryState = NORMAL_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatOnBoardBatteryVoltage == 0.0f)
        {
            strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatOnBoardBatteryVoltage < ON_BOARD_BATTERY_MIN)
        {
            strBatteriesInfo.enumOnBoardBatteryState = LOW_VOLT_BATTERY;
        }
        else 
        {
            strBatteriesInfo.enumOnBoardBatteryState = MALFUNCTION_VOLT_BATTERY;
        }
       
        /*reset the Local*/
        LOC_u32AdcReadValue = 0x00;

        //#if(BATTERY_UT == OFF)
        /*getting the Adc value of On Vehicle battery channel*/ 
        enum_AdcReadFromChannel(ADC_CHANNEL_VEHICLE_BATTERY,&LOC_u32AdcReadValue);
        /*claculating the voltage & save the value at the private structure */
        strBatteriesInfo.floatVehicleBatteyVoltage = (float32_t)LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU;
        strBatteriesInfo.floatVehicleBatteyVoltage *= VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
        //#endif
        /*determine the battery state & save the value at the private structure */
        if((strBatteriesInfo.floatVehicleBatteyVoltage >=VEHICLE_BATTERY_LEVEL1) && (strBatteriesInfo.floatVehicleBatteyVoltage<=VEHICLE_BATTERY_LEVEL2))
        {
            strBatteriesInfo.enumVehicleBatteyState = NORMAL_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatVehicleBatteyVoltage>VEHICLE_BATTERY_LEVEL3)
        {
            strBatteriesInfo.enumVehicleBatteyState = MALFUNCTION_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatVehicleBatteyVoltage==0.0f)
        {
            strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatVehicleBatteyVoltage>VEHICLE_BATTERY_LEVEL2)
        {
            strBatteriesInfo.enumVehicleBatteyState = HIGH_VOLT_BATTERY;
        }
        else if(strBatteriesInfo.floatVehicleBatteyVoltage<VEHICLE_BATTERY_LEVEL1)
        {
            strBatteriesInfo.enumVehicleBatteyState = LOW_VOLT_BATTERY;
        }
        else 
        {
            strBatteriesInfo.enumVehicleBatteyState = MALFUNCTION_VOLT_BATTERY;
        }
        /*conversion progress Ends here !*/ 
        u8BATcalcInProgressFlag = 1 ; 
    }
    else 
    {
        /* --- do Nothing ... returns*/
    }
}

enumRetBat_e enum_BattGet(strBatteriesInfo_t* strBatteriesInfoArg)
{
    /* ----- LOCALs -----*/
    enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
    
    /* ----- Actions -----*/
    if((u8InitIsDone == 1) && (u8BATcalcInProgressFlag == 1) && (strBatteriesInfoArg!=NULL))
    {
        /* save On board battery state and voltage in the private variable*/
        strBatteriesInfoArg->enumOnBoardBatteryState = strBatteriesInfo.enumOnBoardBatteryState;
        strBatteriesInfoArg->floatOnBoardBatteryVoltage = strBatteriesInfo.floatOnBoardBatteryVoltage;
        
        /* save Vehicle battery state and voltage in the private variable*/
        strBatteriesInfoArg->enumVehicleBatteyState = strBatteriesInfo.enumVehicleBatteyState; 
        strBatteriesInfoArg->floatVehicleBatteyVoltage = strBatteriesInfo.floatVehicleBatteyVoltage;
        LOC_enumRetVal = VALID_BAT_RETURN;
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BAT_RETURN;
    }
    /* ----- Returns -----*/
    return LOC_enumRetVal;
}