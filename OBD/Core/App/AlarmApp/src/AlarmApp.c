/**
 * @file AlarmApp.c
 
 * @brief This source file is for the Alarming Feature for the CrewCopilot Project
          alarming Fetaure is as follows: 
            - if Bluetooth is paired, interface with LED Driver to turn on the LED INDICATOR.
            - if Bluetooth is not paired, interface with LED Driver to blink the LED INDICATOR 1 sec.
            - if Mqtt is connected, interface with LED Driver to turn on the LED INDICATOR.
            - if Mqtt is not connected, interface with LED Driver blink the LED INDICATOR 1 sec.
            - if vehicle battery is disconnected, buzzer will be activated for 5sec toggling each 0.5s and “DISCONNECTED” is sent over wireless comm.
 
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @version 
 * @date 2024-2-29
 * 
 * @copyright Copyright (crewteq) 2024 
 */

#include "Battery.h"
#include "MQTTSim800.h"
#include "BluetoothDrv.h"
#include "Wireless_App.h"
#include "LEDDriver.h"
#include "LEDDriverCnfg.h"
#include "BuzzerDriver.h"
#include "BuzzerDriverCnfg.h"
#include "AlarmApp.h"
#include "AlarmAppCnfg.h"
#include "string.h"

#define BLE_PAIRED      1
#define BLE_NOT_PAIRED  0
#define MQTT_PAIRED     1
#define MQTT_NOT_PAIRED 0


/*_________________________________________________Data______________________________________*/

#if ALARM_APP_UT == OFF

/// @brief variable to store WirlessComm Alarm current State (ON/OFF)
/// @note  Covers Requirement CCO-CDD-1715
PRIVATE u8_t GLOB_u8WirelessAlarmState=ALARM_OFF;

/// @brief variable to store Battery Alarm current State (ON/OFF)
/// @note  Covers Requirement CCO-CDD-1716
PRIVATE u8_t GLOB_u8BatteryAlarmState=ALARM_OFF;

#else
u8_t GLOB_u8WirelessAlarmState=ALARM_OFF;
u8_t GLOB_u8BatteryAlarmState=ALARM_OFF;

#endif

/*________________________________________________Private Functions Prototype_______________________________________________*/

#if ALARM_APP_UT == OFF

/// @note Covers Requirement CCO-CDD-1704 
/// @brief collects vehicle battery voltage u8State from Battery Driver
/// @param strToFill structure to fill with the collected data
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_collectBatteryConnection (AlarmData_t* strToFill);

/// @note Covers Requirement CCO-CDD-1705
/// @brief collects Bluetooth pairing u8State from Bluetooth driver
/// @param strToFill structure to fill with the collected data
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_collectBluetoothPairing (AlarmData_t* strToFill);


/// @note Covers Requirement CCO-CDD-1706
/// @brief collects MQTT pairing u8State from Bluetooth driver
/// @param strToFill structure to fill with the collected data
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_collectMqttPairing (AlarmData_t* strToFill);


/// @note Covers Requirement CCO-CDD-1707
/// @brief handles the alarming actions needed for battery connection based on the u8State
/// @param u8_t collected Battery u8State
PRIVATE AlarmAppErrorState_e enum_HandleBatteryAlarm (enumBatteryState_e u8State);


/// @note Covers Requirement CCO-CDD-1708
/// @brief handles the alarming actions needed for bluetooth connection based on the u8State
/// @param u8State collected MQTT pairing u8State
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_HandleWirlessAlarmState (u8_t u8BluetoothState,u8_t u8MqttState);


/// @note Covers Requirement CCO-CDD-1710
/// @brief executes the alarming sequence for battery connection/disconnection
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_StartBatteryAlarmSequence (void);


/// @note Covers Requirement CCO-CDD-1711
/// @brief handles the actions need when Transitioning from alarm to Normal
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_StopBatteryAlarmSequence (void);


/// @note Covers Requirement CCO-CDD-1712
/// @brief executes the alarming sequence for wirlessComm not being paired
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_StartWirelessAlarmSequence (void);


/// @note Covers Requirement CCO-CDD-1713
/// @brief handles the actions need when Transitioning from alarm to Normal
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_StopWirelessAlarmSequence (void);



/// @note Covers Requirement CCO-CDD-1709
/// @brief sends a alarm string to wirelessApp component
/// @param u8_t* Alarm msg string to send to wirelessApp
/// @return the u8State of function execution.
PRIVATE AlarmAppErrorState_e enum_CommunicateAlarmMsg (u8_t *stringToSend);

#else

AlarmAppErrorState_e enum_collectBatteryConnection (AlarmData_t* strToFill);
AlarmAppErrorState_e enum_collectBluetoothPairing (AlarmData_t* strToFill);
AlarmAppErrorState_e enum_collectMqttPairing (AlarmData_t* strToFill);
AlarmAppErrorState_e enum_HandleBatteryAlarm (enumBatteryState_e u8State);
AlarmAppErrorState_e enum_HandleWirlessAlarmState (u8_t u8BluetoothState,u8_t u8MqttState);
AlarmAppErrorState_e enum_StartBatteryAlarmSequence (void);
AlarmAppErrorState_e enum_StopBatteryAlarmSequence (void);
AlarmAppErrorState_e enum_StartWirelessAlarmSequence (void);
AlarmAppErrorState_e enum_StopWirelessAlarmSequence (void);
AlarmAppErrorState_e enum_CommunicateAlarmMsg (u8_t *stringToSend);

#endif


/*________________________________________________Public Functions Implementation_______________________________________________*/
/*__________________________________________________________________________________________________________________________*/


AlarmAppErrorState_e enum_AlarmAppManage (void)
{
    /*define Local variables*/
    AlarmData_t      LOC_strDataForAlarm={0};
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    AlarmAppErrorState_e LOC_enumReturnValue1=0;
    AlarmAppErrorState_e LOC_enumReturnValue2=0;
    AlarmAppErrorState_e LOC_enumReturnValue3=0;

    /*collect Data*/
    enum_collectBluetoothPairing(&LOC_strDataForAlarm);
    enum_collectMqttPairing(&LOC_strDataForAlarm);
    LOC_enumReturnValue1=enum_collectBatteryConnection(&LOC_strDataForAlarm);

    /*handle states for alarming*/
    LOC_enumReturnValue2=enum_HandleBatteryAlarm  (LOC_strDataForAlarm.enumVehicleBatteryConnection);
    LOC_enumReturnValue3=enum_HandleWirlessAlarmState     (LOC_strDataForAlarm.u8BluetoothPairingState,LOC_strDataForAlarm.u8MQTTPairingState);

    /*error handling for called APIs*/
    if(  (LOC_enumReturnValue1 == ALARM_APP_FAILED) || (LOC_enumReturnValue2 == ALARM_APP_FAILED) || (LOC_enumReturnValue3 == ALARM_APP_FAILED)  )

       {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
       }
    
    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
}



/*________________________________________________Private Functions Implementation_______________________________________________*/
/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_collectBatteryConnection (AlarmData_t* strToFill)
{
    /*local variables*/
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    enumRetBat_e LOC_enumReturnValue=0;
    strBatteriesInfo_t LOC_strBatterysInfo={0};
    
    /*get battery*/
    LOC_enumReturnValue=enum_BattGet(&LOC_strBatterysInfo);

    /*check for errors*/
    if((LOC_enumReturnValue== NOT_VALID_BAT_RETURN) || (strToFill==NULLPTR) )
    {
      LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
       /*store in the input structure*/
       strToFill->enumVehicleBatteryConnection=LOC_strBatterysInfo.enumVehicleBatteyState;
    }

    return LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_collectMqttPairing (AlarmData_t* strToFill)
{
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    if(strToFill==NULLPTR)
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        strToFill->u8MQTTPairingState=u8_Mqtt_isConnnected();
    }
    return LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_collectBluetoothPairing (AlarmData_t* strToFill)
{
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    if(strToFill==NULLPTR)
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        strToFill->u8BluetoothPairingState=u8_Bluetooth_getConnectivityStatus();
    }
    return  LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_HandleBatteryAlarm (enumBatteryState_e u8State)
{
   /*Local variables*/
   AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
   AlarmAppErrorState_e LOC_enumReturnValue1=ALARM_APP_SUCCESS;


   /*check for u8State*/
   /*if disconnected*/
   if((u8State==DISCONNECTED_VOLT_BATTERY) && (GLOB_u8BatteryAlarmState==ALARM_OFF) )
   {
        /*execute the alarming actions*/
        LOC_enumReturnValue1=enum_StartBatteryAlarmSequence();
        /*update static variable with on u8State*/
        GLOB_u8BatteryAlarmState=ALARM_ON;
   }

   else if ((u8State!=DISCONNECTED_VOLT_BATTERY) && (GLOB_u8BatteryAlarmState==ALARM_ON))
   {
    /*Turn OFF Alarm*/
           LOC_enumReturnValue1=enum_StopBatteryAlarmSequence();
          /*update static variable with off u8State*/
           GLOB_u8BatteryAlarmState=ALARM_OFF;
   }

   else
   {
      /*do nothing*/
   }


   /*error handling*/
   if (LOC_enumReturnValue1==ALARM_APP_FAILED )

       {
            LOC_enumApiReturnValue=ALARM_APP_FAILED;
            GLOB_u8BatteryAlarmState=ALARM_ERROR;
       }

    else
      {
        /*do nothing*/
      }
return LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_HandleWirlessAlarmState (u8_t u8BluetoothState,u8_t u8MqttState)
{
   /*Local variables*/
   AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
   AlarmAppErrorState_e LOC_enumReturnValue1=ALARM_APP_SUCCESS;

   /*check for u8State*/
   /*if on of the wireless comm is not paired and alarm is off*/
   if((GLOB_u8WirelessAlarmState==ALARM_OFF) && ( (u8BluetoothState==BLE_NOT_PAIRED) || (u8MqttState==MQTT_NOT_PAIRED) ))
   {
        /*execute the alarming actions*/
        LOC_enumReturnValue1=enum_StartWirelessAlarmSequence();
        /*update static variable with on u8State*/
        GLOB_u8WirelessAlarmState=ALARM_ON;
   }
   
   /* if both are paired and alarm is ON*/
   else if ((GLOB_u8WirelessAlarmState==ALARM_ON) && ( (u8BluetoothState==BLE_PAIRED) && (u8MqttState==MQTT_PAIRED) ) )
   {
       /*Turn OFF Alarm*/
           LOC_enumReturnValue1=enum_StopWirelessAlarmSequence();
          /*update static variable with off u8State*/
           GLOB_u8WirelessAlarmState=ALARM_OFF;
   }

   else
   {
      /*do nothing*/
      
   }


   /*error handling*/
   if (LOC_enumReturnValue1==ALARM_APP_FAILED)

       {
            LOC_enumApiReturnValue=ALARM_APP_FAILED;
            GLOB_u8WirelessAlarmState=ALARM_ERROR;
       }

    else
    {
        /*do nothing*/
    }

return LOC_enumApiReturnValue;

}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_StartWirelessAlarmSequence (void)
{
    /*local Variables*/
   AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
   LedDrvErrorState_e LOC_enumReturnValue1=LED_DRV_OK;
   LedConfig_t LOC_strConfig={
        .enumState=LED_TOGGLE,
        .u16StateTime=BUZZER_MAX_TIME,
        .u16TogglePeriod=WIRELESS_ALARM_TOGGLE_PERIOD };

    /*set configuration*/
    LOC_enumReturnValue1=enum_SetIndicatorLedState(&LOC_strConfig);


    /*error Handling*/
    if(LOC_enumReturnValue1==LED_DRV_NOK)
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_StopWirelessAlarmSequence (void)
{
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    LedDrvErrorState_e LOC_enumReturnValue1=LED_DRV_OK;
    LedConfig_t LOC_strConfig={
        .enumState=LED_ON,
        .u16StateTime=BUZZER_MAX_TIME,
        .u16TogglePeriod = 0 };

    /*set configuration*/
    LOC_enumReturnValue1=enum_SetIndicatorLedState(&LOC_strConfig);

      /*error Handling*/
    if(LOC_enumReturnValue1==LED_DRV_NOK)
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_StartBatteryAlarmSequence (void)
{
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    BuzzerDrvErrorState_e LOC_enumReturnValue1=BUZZER_DRV_OK;
    AlarmAppErrorState_e  LOC_enumReturnValue2=ALARM_APP_SUCCESS;
    BuzzerConfig_t LOC_strConfig={
        .enumState=BUZZER_TOGGLE,
        .u16TogglePeriod=BATTERY_ALARM_TOGGLE_PERIOD,
        .u16StateTime=BATTERY_ALARM_TOGGLE_TIME};

    /*set buzzer u8State*/
    LOC_enumReturnValue1=enum_SetBuzzerState(&LOC_strConfig);

    /*communicate a msg to wireless App*/
    LOC_enumReturnValue2=enum_CommunicateAlarmMsg(ALARM_MSG);


    /*error Handling*/
    if((LOC_enumReturnValue1==BUZZER_DRV_NOK) || (LOC_enumReturnValue2==ALARM_APP_FAILED) )
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;

}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_StopBatteryAlarmSequence (void)
{
    AlarmAppErrorState_e LOC_enumApiReturnValue=ALARM_APP_SUCCESS;
    BuzzerDrvErrorState_e LOC_enumReturnValue1=BUZZER_DRV_OK;
    BuzzerConfig_t LOC_strConfig={
        .enumState=BUZZER_OFF,
        .u16StateTime=BUZZER_MAX_TIME,
        .u16TogglePeriod = 0};

    /*set buzzer u8State*/
    LOC_enumReturnValue1=enum_SetBuzzerState(&LOC_strConfig);

    /*error Handling*/
    if(LOC_enumReturnValue1==BUZZER_DRV_NOK)
    {
        LOC_enumApiReturnValue=ALARM_APP_FAILED;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;

}


/*__________________________________________________________________________________________________________________________*/

AlarmAppErrorState_e enum_CommunicateAlarmMsg (u8_t *stringToSend)
{
  AlarmAppErrorState_e LOC_enumApiReturnValue= ALARM_APP_SUCCESS;
  WirelessApp_StatusTypeDef LOC_enumReturnValue=0;
  Wireless_RequestTypedef AlarmMsg = {.pData = stringToSend, .size = strlen(stringToSend), .callback = NULLPTR};

  /*communicate msg on wireless component*/
  LOC_enumReturnValue=enum_WirelessApp_Request(&AlarmMsg);

  if(LOC_enumReturnValue==WIRELESS_APP_ERROR )
  {
    LOC_enumApiReturnValue=ALARM_APP_FAILED;
  }

  else
  {
    /*do nothing*/
  }

  return LOC_enumApiReturnValue;
}



