/**
 * @file LowPowerApp.c
 
 * @brief This is source file is for the LowPower Feature for the CrewCopilot Project
           the Device goes to the Low power Mode if all following conditions are true:
           - Vehicle battery is ON (0 v) 
           - Ignition is OFF
           - No Bluetooth connected is established with mobile 
           - No mobile network connection is established 
           - No requests received from wireless communication channel (BLUETOOTH or Mobile Network) for more than 15 min

 
  * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 * @version 
 * @date 2024-2-25
 * 
 * @copyright Copyright (crewteq) 2024 
 */

#include "MQTTSim800.h"
#include "Battery.h"
#include "Wireless_App.h"
#include "CmsisAbstract.h"
#include "LowPowerApp.h"
#include "Can.h"
#include "LowPowerAppCnfg.h"
#include "BluetoothDrv.h"
#include "Vehicle_App.h"

/*_____________________________________ Data_____________________________________________*/
#if LOW_POWER_APP_UT == OFF
/**
 * @brief  Current Device Operating State
 * @note   Covers Requirement CCO-CDD-1094
 * 
 */
PRIVATE DeviceState_e       GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;

#else
DeviceState_e       GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;

#endif

/*_____________________________________ Private Functions Prototype_____________________________________________*/

#if LOW_POWER_APP_UT == OFF

/// @brief collects the vehicle Battery Voltage from the Battery Drv and decides if the related condition is true or False
/// @return API Error State
/// @note Covers Requirement CCO-CDD-1097 
PRIVATE bool enum_EvaluateVehicleBatteryCondition(void);


/// @note Covers Requirement CCO-CDD-1098
/// @brief collects the bluetooth pairing state from the BLE Driver and decides if the related condition is true or False
/// @return API Error State
PRIVATE bool enum_EvaluateBluetoothPairingCondition(void);


/// @note Covers Requirement CCO-CDD-1099
/// @brief collects the MQTT pairing state from the MQTT Driver and decides if the related condition is true or False
/// @return API Error State
PRIVATE bool enum_EvaluateMQTTPairingCondition(void);


/// @note Covers Requirement CCO-CDD-1100
/// @brief collects the MQTT requests state from the MQTT Driver and decides if the related condition is true or False
/// @return API Error State
PRIVATE bool enum_EvaluateWirelessRequestCondition(void);



/// @note Covers Requirement CCO-CDD-1101
/// @brief collect the ignition state from Monitoring SWC and evaluate if the related condition is true or false
/// @return API Error State
PRIVATE bool enum_EvaluateIgnitionCondition(void);


/// @note Covers Requirement CCO-CDD-1102
/// @brief evaluates if device should go to low power mode or not
/// @param strConditionStates: states of the low power conditions (true or false)
/// @return Device State
PRIVATE DeviceState_e enum_DecideDeviceMode(const LowPowerFactors_t* strConditionStates); 


/// @note Covers Requirement CCO-CDD-1103
/// @brief Executes the Low Power Actions if all conditions are true
PRIVATE void enum_ExecuteLowPowerActions(void); 



/// @note Covers Requirement CCO-CDD-1104
/// @brief Executes Normal Mode Actions if wake up event occurs, this is a callback function called in CanDriver when a wakeup msg is present on CAN Network
/// @return API Error State
PRIVATE void enum_goToNormalMode(void); 

#else

bool enum_EvaluateVehicleBatteryCondition(void);
bool enum_EvaluateBluetoothPairingCondition(void);
bool enum_EvaluateMQTTPairingCondition(void);
bool enum_EvaluateWirelessRequestCondition(void);
bool enum_EvaluateIgnitionCondition(void);
DeviceState_e enum_DecideDeviceMode(const LowPowerFactors_t* strConditionStates); 
void enum_ExecuteLowPowerActions(void); 
void enum_goToNormalMode(void); 

#endif

/*_____________________________________ Public Functions Implemntation_____________________________________________*/

LowPowerApiReturn_e enum_LowPowerAppInit (void)
{
  /*set CallbackFunction to be called from Can Driver for wake up notification*/
  vid_CanDrvSetIDWakeUp(CAN_ID_WAKEUP ,enum_goToNormalMode);

  return LOW_POWER_SUCCESS;
}


/*________________________________________________________________________________________________________________*/

LowPowerApiReturn_e enum_LowPowerAppManage(void)
{
    DeviceState_e       LOC_enumNewDeviceMode=DEVICE_MODE_NORMAL;          /*New Device State to go to*/
    LowPowerFactors_t LOC_strConditionsStates={0};                     /*States Of TheLowPower Conditions (True or False)*/
    LowPowerApiReturn_e LOC_enumApiReturnValue=0;

 if(GLOB_enumCurrentDeviceMode==DEVICE_MODE_LOW_POWER)
 {
    /*do nothing and return Low power State*/
    LOC_enumApiReturnValue=LOW_POWER_STATE;
 }

 else
 {
   /*evaluate all conditions */
    LOC_strConditionsStates.u8VehicleBatteryCondition=enum_EvaluateVehicleBatteryCondition();
    LOC_strConditionsStates.u8BluetoothPairingCondition=enum_EvaluateBluetoothPairingCondition();
    LOC_strConditionsStates.u8MQTTPairingCondition=enum_EvaluateMQTTPairingCondition();
    LOC_strConditionsStates.u8WirelessRequestCondition=enum_EvaluateWirelessRequestCondition();
    LOC_strConditionsStates.u8IgnitionCondition=enum_EvaluateIgnitionCondition();
 
    /*evaluate should the device go to low power mode*/
    LOC_enumNewDeviceMode=enum_DecideDeviceMode(&LOC_strConditionsStates);

    if(LOC_enumNewDeviceMode==DEVICE_MODE_LOW_POWER)
    {
        LOC_enumApiReturnValue=TRANSITION_TO_LOW_POWER;
        enum_ExecuteLowPowerActions();
    }

    else
    {
       /*do nothing and return Normal State*/
       LOC_enumApiReturnValue=NORMAL_STATE;
    }
    
 }

 return LOC_enumApiReturnValue;
}

/*_____________________________________ Private Functions implementation_____________________________________________*/

bool enum_EvaluateVehicleBatteryCondition(void)
{
    bool LOC_enumApiReturnValue=LOW_POWER_CONDITION_FALSE;
    strBatteriesInfo_t LOC_strBatterysInfo={0};

    /*get battery voltage from battery driver*/
    enum_BattGet(&LOC_strBatterysInfo);

    /*check if the condition is true or not*/
    if (LOC_strBatterysInfo.enumVehicleBatteyState != DISCONNECTED_VOLT_BATTERY)
    {
       LOC_enumApiReturnValue=LOW_POWER_CONDITION_TRUE;
    }

    else
    {
      /*do nothing*/
    }

    /*return condition state*/
    return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/
bool enum_EvaluateBluetoothPairingCondition(void)
{
   
    bool LOC_enumApiReturnValue=LOW_POWER_CONDITION_FALSE;
    bool LOC_returnValue=0;
    
    /*get pairing state*/
    LOC_returnValue=u8_Bluetooth_getConnectivityStatus();
    
    /*check condition*/
    if(LOC_returnValue == 0)
    {
        LOC_enumApiReturnValue=LOW_POWER_CONDITION_TRUE;
    }

    else
    {
        /*do nothing*/
    }

    /*return condition state*/
 return LOC_enumApiReturnValue;
}


/*________________________________________________________________________________________________________________*/
bool enum_EvaluateMQTTPairingCondition(void)
{
    bool LOC_enumApiReturnValue=LOW_POWER_CONDITION_FALSE;
    bool LOC_returnValue=0;

    /*get pairing state*/
    LOC_returnValue = u8_Mqtt_isConnnected();

    /*check Condition */
    if(LOC_returnValue==0)
    {
        LOC_enumApiReturnValue=LOW_POWER_CONDITION_TRUE;
    }

    else
    {
        /*do nothing*/
    }

/*return condition state*/
 return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/
bool enum_EvaluateWirelessRequestCondition(void)
{
    bool LOC_enumApiReturnValue=LOW_POWER_CONDITION_FALSE;
    bool LOC_returnValue=0;

    /*get pairing state*/
    LOC_returnValue= u8_isWirelessCommActive();

    if(LOC_returnValue == 0)
    {
        LOC_enumApiReturnValue=LOW_POWER_CONDITION_TRUE;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/
bool enum_EvaluateIgnitionCondition(void)
{
    bool LOC_enumApiReturnValue=LOW_POWER_CONDITION_FALSE;
    bool LOC_returnValue=0;

    /*get ignitionState*/
    LOC_returnValue= u8_VehicleApp_getMotorState();
    if(LOC_returnValue == 0)
    {
        LOC_enumApiReturnValue=LOW_POWER_CONDITION_TRUE;
    }

    else
    {
        /*do nothing*/
    }

    return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/
DeviceState_e enum_DecideDeviceMode(const LowPowerFactors_t* strConditionStates)
{
    DeviceState_e LOC_enumApiReturnValue=DEVICE_MODE_NORMAL;

    if(  strConditionStates->u8BluetoothPairingCondition == LOW_POWER_CONDITION_TRUE
       &&strConditionStates->u8MQTTPairingCondition      == LOW_POWER_CONDITION_TRUE
       &&strConditionStates->u8IgnitionCondition         == LOW_POWER_CONDITION_TRUE
       &&strConditionStates->u8WirelessRequestCondition  == LOW_POWER_CONDITION_TRUE
       &&strConditionStates->u8VehicleBatteryCondition   == LOW_POWER_CONDITION_TRUE )

       {
        
       LOC_enumApiReturnValue=DEVICE_MODE_LOW_POWER;

       }

    else
       {
        /*do nothing*/
       }

     return LOC_enumApiReturnValue;
}

/*________________________________________________________________________________________________________________*/
void enum_ExecuteLowPowerActions(void)
{
    /*set acceptance filter to 0x5FC as a wake up CAN ID*/
    enum_SetAcceptenceFilter(CAN_ID_WAKEUP,STANDARD_FORMAT,WAKE_UP_FILTER_BANK);

    /*send uC to sleep mode*/
    vid_GoToWFI();

    /*set device state to Low Power*/
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_LOW_POWER;

}

/*________________________________________________________________________________________________________________*/
void enum_goToNormalMode(void)
{
    /*clear wake up filter*/
    enum_ClearAcceptenceFilter(WAKE_UP_FILTER_BANK);

    /*set Device Current State to Normal*/
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;
}









