/**
 * @file LowPowerApp.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief This Source file is for the Monitoring Feature for the CrewCopilot Project
          -  string to be sent should be in the form of a JSON file as follows:
          {
          “203“: value,                                                   VehicleBatteryValue
          “204”: state,                                                   VehicleBatteryState
          ”205”:value,                                                    s64OnBoardBatteryValue
          “206”:state,                                                    u8OnBoardBatteryState
          ”207”:value,                                                    CurrentValue      
          “208”:state,                                                    CurrentState
          “209”:value,                                                    TemperatureValue
          “210”:state,                                                    TemperatureState
          “211“:state,                                                    Ignition State
          “212”:state                                                     CANNetworkState 
          }                                                     

 * @version 
 * @date 2024-2-26
 * 
 * @copyright Copyright (crewteq) 2024 
 */



/*_________________________________________________________ Dependencies _____________________________________________*/
#include "MonitoringApp.h"
#include "MonitoringAppCnfg.h"
#include "services.h"
#include "string.h"
#include "stdio.h"

/*_________________________________________________________ Constant Macros_____________________________________________*/
#define FLAG_SET                    1
#define FLAG_CLEAR                  0

/*_________________________________________________________ Data_____________________________________________*/



/*_____________________________________ Private Functions Prototype_____________________________________________*/
#if MONITORING_APP_UT == OFF

/// @note Covers Requirement CCO-CDD-1044
/// @brief Collects both VehicleBattery and onBoard Bttery voltage value and state
/// @param strToFill to store the collected data in
/// @return API retrun Value
PRIVATE MonitroingAppApiReturn_e enum_CollectBatteries(DataToMonitor_t* strToFill);

/// @note Covers Requirement CCO-CDD-1045
/// @brief Collects Temperature Value and State
/// @param strToFill to store the collected data in
/// @return API retrun Value
PRIVATE MonitroingAppApiReturn_e enum_CollectTemperature(DataToMonitor_t* strToFill);


/// @note Covers Requirement CCO-CDD-1046
/// @brief Collects Current Value and State
/// @param strToFill to store the collected data in
/// @return API retrun Value
PRIVATE MonitroingAppApiReturn_e enum_CollectCurrent(DataToMonitor_t* strToFill);


#else

MonitroingAppApiReturn_e enum_CollectBatteries(DataToMonitor_t* strToFill);
MonitroingAppApiReturn_e enum_CollectTemperature(DataToMonitor_t* strToFill);
MonitroingAppApiReturn_e enum_CollectCurrent(DataToMonitor_t* strToFill);
MonitroingAppApiReturn_e enum_CollectCanNetwork(DataToMonitor_t* strToFill);

#endif

/*_____________________________________ Public Functions implementation_____________________________________________*/
/*________________________________________________________________________________________________________________*/

MonitroingAppApiReturn_e enum_MonitorAppInit (void)
{
   /*nothing to do*/
   return MONITORING_APP_SUCCESS;
}

/*________________________________________________________________________________________________________________*/
DataToMonitor_t LOC_strMonitoringData={0};          /*strutcure to fill with the Data Collected */
u8_t LOC_u8MonitorMsgPtr[MONITOR_MSG_LENGTH]={0};  /*buffer for the Monitor Msg*/
Wireless_RequestTypedef MonitorMsg = {0};

MonitroingAppApiReturn_e enum_MonitorAppManage (void)
{
    MonitroingAppApiReturn_e    LOC_enumApiReturnValue=MONITORING_APP_SUCCESS;
    MonitroingAppApiReturn_e    LOC_enumReturnValue1=0;
    MonitroingAppApiReturn_e    LOC_enumReturnValue2=0;
    MonitroingAppApiReturn_e    LOC_enumReturnValue3=0;
    WirelessApp_StatusTypeDef   LOC_enumReturnValue4=0;
    
    
    u8_t LOC_u8arrVehicleBatteryValueString[5] = {0};             /*string to store Vehicle Battery value after converting it from float to string*/
    u8_t LOC_u8arrOnBoardBatteryValueString[5] = {0};            /*string to store Onboard Battery value after converting it from float to string*/
    u8_t LOC_u8ArrCurrentValueString[5] = {0};                  /*string to store current value after converting it from float to string*/
    u8_t LOC_u8ArrTemperatureString[5]  = {0};                 /*string to store Temperature value after converting it from float to string*/
   
    /*Collect Data*/
    LOC_enumReturnValue1=enum_CollectBatteries(&LOC_strMonitoringData);
    LOC_enumReturnValue2=enum_CollectTemperature(&LOC_strMonitoringData);
    LOC_enumReturnValue3=enum_CollectCurrent(&LOC_strMonitoringData);
    LOC_strMonitoringData.enumCanNetworkState= enum_isCanBusOff();
    LOC_strMonitoringData.u8IgnitionState = u8_VehicleApp_getMotorState();
    
    /* Convert the values of vehicle battery and onboard battery and current and temperature values to string */
    floatToString((float32_t)LOC_strMonitoringData.s64VehicleBatteryValue, LOC_u8arrVehicleBatteryValueString, 2);
    floatToString((float32_t)LOC_strMonitoringData.s64OnBoardBatteryValue, LOC_u8arrOnBoardBatteryValueString, 2);
    floatToString((float32_t)LOC_strMonitoringData.s64CurrentValue, LOC_u8ArrCurrentValueString, 2);
    floatToString((float32_t)LOC_strMonitoringData.s64TemperatureValue, LOC_u8ArrTemperatureString, 2);
    
    /*construct Montoring Msg*/
    snprintf(LOC_u8MonitorMsgPtr, MONITOR_MSG_LENGTH,
         "{\"203\":%s,\"204\":%d,\"205\":%s,\"206\":%d,\"207\":%s,\"208\":%d,\"209\":%s,\"210\":%d,\"211\":%d,\"212\":%d}",
         LOC_u8arrVehicleBatteryValueString,
         LOC_strMonitoringData.u8VehicleBatteryState,
         LOC_u8arrOnBoardBatteryValueString,
         LOC_strMonitoringData.u8OnBoardBatteryState,
         LOC_u8ArrCurrentValueString,
         LOC_strMonitoringData.enumCurrentState,
         LOC_u8ArrTemperatureString,
         LOC_strMonitoringData.enumTemperatureState,
         LOC_strMonitoringData.u8IgnitionState,
         LOC_strMonitoringData.enumCanNetworkState);

    /*Communicate msg via wireless SWC*/
    MonitorMsg.pData = LOC_u8MonitorMsgPtr;
    MonitorMsg.size = strlen(LOC_u8MonitorMsgPtr);
    LOC_enumReturnValue4=enum_WirelessApp_Request(&MonitorMsg);

    /*Error Condition*/
    bool ErrorCondition= LOC_enumReturnValue4 ==WIRELESS_APP_ERROR || LOC_enumReturnValue1==MONITORING_APP_FAILED 
                         || LOC_enumReturnValue2==MONITORING_APP_FAILED || LOC_enumReturnValue3==MONITORING_APP_FAILED;
    
    /*error handling*/
    if(ErrorCondition==TRUE)
    {
        LOC_enumApiReturnValue=MONITORING_APP_FAILED;
    }

    else
    {
       /*do nothing*/
    }

    
    
    

    return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/




/*_____________________________________ Privatre Functions implementation_____________________________________________*/
/*_____________________________________________________________________________________________________________________________*/



MonitroingAppApiReturn_e enum_CollectBatteries(DataToMonitor_t* strToFill)
{
    MonitroingAppApiReturn_e LOC_enumApiReturnValue=MONITORING_APP_SUCCESS;
    enumRetBat_e LOC_enumReturnValue=0;
    strBatteriesInfo_t LOC_strBatterysInfo={0};
    
    /*get vehicle batter and onBoard Battery Data*/
    LOC_enumReturnValue=enum_BattGet(&LOC_strBatterysInfo);
    
    /*check on return value*/
    if(LOC_enumReturnValue!= VALID_BAT_RETURN)
    {
      /*return API Failed if false*/
       LOC_enumApiReturnValue=MONITORING_APP_FAILED;
    }
    
    else
    {
      /*Store the collected Data in the Global Variable*/
      strToFill->s64VehicleBatteryValue=LOC_strBatterysInfo.floatVehicleBatteyVoltage;
      strToFill->u8VehicleBatteryState=LOC_strBatterysInfo.enumVehicleBatteyState;
      strToFill->s64OnBoardBatteryValue=LOC_strBatterysInfo.floatOnBoardBatteryVoltage;
      strToFill->u8OnBoardBatteryState=LOC_strBatterysInfo.enumOnBoardBatteryState;

    }

    return LOC_enumApiReturnValue;

}

/*_______________________________________________________________________________________________________________________*/

MonitroingAppApiReturn_e enum_CollectTemperature(DataToMonitor_t* strToFill)
{
    MonitroingAppApiReturn_e LOC_enumApiReturnValue=MONITORING_APP_SUCCESS;
    enumRetTps_e LOC_enumReturnValue=0;
    strTemperatureNtc_t LOC_strTempInfo={0};
    
    /*get vehicle batter and onBoard Battery Data*/
    LOC_enumReturnValue=enum_TPSGetTemperature(&LOC_strTempInfo);
    
    /*check on return value*/
    if(LOC_enumReturnValue == NOT_VALID_TPS ||LOC_enumReturnValue == UNKOWN_TPS )
    {
      /*return API Failed if false*/
       LOC_enumApiReturnValue=MONITORING_APP_FAILED;
    }
    
    else
    {
      /*Store the collected Data in the Global Variable*/
      strToFill->s64TemperatureValue=LOC_strTempInfo.doubleTmp;
      strToFill->enumTemperatureState=LOC_strTempInfo.enumTmpState;
    }

    return LOC_enumApiReturnValue;

}

/*_______________________________________________________________________________________________________________________*/

MonitroingAppApiReturn_e enum_CollectCurrent(DataToMonitor_t* strToFill)
{
    MonitroingAppApiReturn_e LOC_enumApiReturnValue=MONITORING_APP_SUCCESS;
    enumRetCrs_e LOC_enumReturnValue=0;
    strCurrent_t LOC_strCurrentInfo={0};
    
    /*get current sensor data*/
    LOC_enumReturnValue=enum_CRSGetCurrent(&LOC_strCurrentInfo);
    
    /*check on return value*/
    if(LOC_enumReturnValue == NOT_VALID_CRS || LOC_enumReturnValue == UNKOWN_CRS)
    {
      /*return API Failed if false*/
       LOC_enumApiReturnValue=MONITORING_APP_FAILED;
    }
    
    else
    {
      /*Store the collected Data in the Global Variable*/
      strToFill->s64CurrentValue=LOC_strCurrentInfo.doubleMilliAmp;
      strToFill->enumCurrentState=LOC_strCurrentInfo.enumCurrentState;
    }

    return LOC_enumApiReturnValue;

}


















