#include "AlarmApp.h"
#include "AlarmAppCnfg.h"
#include "mock_Battery.h"
#include "mock_MQTTSim800.h"
#include "mock_BluetoothDrv.h"
#include "mock_Wireless_App.h"
#include "mock_LEDDriver.h"
#include "mock_LEDDriverCnfg.h"
#include "mock_BuzzerDriver.h"
#include "mock_BuzzerDriverCnfg.h"

#include "unity.h"

#define BLE_PAIRED      1
#define BLE_NOT_PAIRED  0
#define MQTT_PAIRED     1
#define MQTT_NOT_PAIRED 0

extern AlarmAppErrorState_e enum_collectBatteryConnection (AlarmData_t* structToFill);
extern AlarmAppErrorState_e enum_collectBluetoothPairing (AlarmData_t* structToFill);
extern AlarmAppErrorState_e enum_collectMqttPairing (AlarmData_t* structToFill);

extern AlarmAppErrorState_e enum_HandleBatteryAlarm (u8_t state);
extern AlarmAppErrorState_e enum_HandleWirlessAlarmState (u8_t bluetoothState,u8_t mqttState);
extern AlarmAppErrorState_e enum_StartBatteryAlarmSequence (void);
extern AlarmAppErrorState_e enum_StopBatteryAlarmSequence (void);
extern AlarmAppErrorState_e enum_StartWirelessAlarmSequence (void);
extern AlarmAppErrorState_e enum_StopWirelessAlarmSequence (void);

extern AlarmAppErrorState_e enum_CommunicateAlarmMsg (u8_t *stringToSend);


/*Stubs*/
enumRetBat_e enumBattGet_disconnectedStateStub(strBatteriesInfo_t *structToFill,int num)
{
    structToFill->enumVehicleBatteyState=DISCONNECTED_VOLT_BATTERY;
    return VALID_BAT_RETURN;
}

enumRetBat_e  enumBattGet_connectedStateStub(strBatteriesInfo_t *structToFill,int num)
{
    structToFill->enumVehicleBatteyState=NORMAL_VOLT_BATTERY;
    return VALID_BAT_RETURN;
}

/*extern File Data*/

extern u8_t GLOB_u8WirelessAlarmState;
extern u8_t GLOB_u8BatteryAlarmState;

/*____________________________________enum_collectBatteryConnection()______________________________________*/

/*__________________________________________________________________________________________________________________________*/
/// @brief  battery driver function return Invalid, API Fails
void test_CCO_TC_UT_0080(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,NOT_VALID_BAT_RETURN);
   AlarmData_t structToFill={0};
  
    // Act
   returnValue=enum_collectBatteryConnection(&structToFill);



    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}

/*__________________________________________________________________________________________________________________________*/
/// @brief  API Input is NULL Invalid, API Fails
void test_CCO_TC_UT_0081(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   AlarmData_t *structToFill=NULL;
  
    // Act
   returnValue=enum_collectBatteryConnection(structToFill);



    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @brief  All is Valid, API Success
void test_CCO_TC_UT_0082(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   AlarmData_t structToFill={0};
  
    // Act
   returnValue=enum_collectBatteryConnection(&structToFill);



    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}

/*____________________________________enum_collectMqttPairing()______________________________________*/

/*__________________________________________________________________________________________________________________________*/
/// @brief  API Input is NULL Invalid, API Fails
void test_CCO_TC_UT_0083(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,1);
   AlarmData_t *structToFill=NULL;
  
    // Act
   returnValue=enum_collectMqttPairing(structToFill);



    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}

/*__________________________________________________________________________________________________________________________*/
/// @brief  API Input is NULL Invalid, API Fails
void test_CCO_TC_UT_0084(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,1);
   AlarmData_t structToFill={0};
  
    // Act
   returnValue=enum_collectMqttPairing(&structToFill);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*____________________________________enum_collectBluetoothPairing()______________________________________*/

/*__________________________________________________________________________________________________________________________*/
/// @brief  API Input is NULL Invalid, API Fails
void test_CCO_TC_UT_0085(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,1);
   AlarmData_t *structToFill=NULL;
  
    // Act
   returnValue=enum_collectBluetoothPairing(structToFill);



    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}

/*__________________________________________________________________________________________________________________________*/
/// @brief  API Input is NULL Invalid, API Fails
void test_CCO_TC_UT_0086(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,1);
   AlarmData_t structToFill={0};
  
    // Act
   returnValue=enum_collectBluetoothPairing(&structToFill);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*____________________________________enum_CommunicateAlarmMsg()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief  Wireless App API returns error, API Fails
void test_CCO_TC_UT_0087(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_ERROR);
    uint8_t structToFill[30]="Data";
  
    // Act
   returnValue=enum_CommunicateAlarmMsg(structToFill);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}

/*__________________________________________________________________________________________________________________________*/
/// @brief  Wireless App API returns Success, API Success
void test_CCO_TC_UT_0088(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   uint8_t structToFill[30]="Data";

  
    // Act
   returnValue=enum_CommunicateAlarmMsg(structToFill);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*____________________________________enum_BatteryAlarmOnActions()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief  Wireless App API returns Success but Buzzer driver API fails, API Fails
void test_CCO_TC_UT_0089(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_NOK);

  
    // Act
   returnValue=enum_StartBatteryAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @brief Buzzer driver API returns Success but Wireless App API fails, API Fails
void test_CCO_TC_UT_0090(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_ERROR);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);

  
    // Act
   returnValue=enum_StartBatteryAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0069
/// @brief Buzzer driver API returns Success, Wireless App API SucCess, API Success
void test_CCO_TC_UT_0091(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);

  
    // Act
   returnValue=enum_StartBatteryAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}



/*____________________________________enum_BatteryAlarmOffActions()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief Buzzer driver API returns error,  API Fails
void test_CCO_TC_UT_0092(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_NOK);
  
    // Act
   returnValue=enum_StopBatteryAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @brief Buzzer driver API returns error,  API Fails
void test_CCO_TC_UT_0093(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
  
    // Act
   returnValue=enum_StopBatteryAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}

/*____________________________________enum_wirelessAlarmOnActions()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief LED driver API returns error,  API Fails
void test_CCO_TC_UT_0094(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_NOK);
  
    // Act
   returnValue=enum_StartWirelessAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @brief LED driver API returns error,  API Fails
void test_CCO_TC_UT_0095(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_StartWirelessAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}



/*____________________________________enum_wirelessAlarmOffActions()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief LED driver API returns error,  API Fails
void test_CCO_TC_UT_0096(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_NOK);
  
    // Act
   returnValue=enum_StopWirelessAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/*__________________________________________________________________________________________________________________________*/
/// @brief LED driver API returns error,  API Fails
void test_CCO_TC_UT_0097(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_StopWirelessAlarmSequence();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}

/*____________________________________enum_wirelessAlarmHandle()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth not paired, mqtt not paired, Alarm is off, LED API return success,  then Alarm is turned on and API returns success
void test_CCO_TC_UT_0098(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_OFF;
   u8_t u8BluetoothPairingState=BLE_NOT_PAIRED;
   u8_t mqttPairingState=MQTT_NOT_PAIRED;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth not paired, mqtt not paired, Alarm is off, LED API return Failed,  then Alarm is in error state and API returns Fail 
void test_CCO_TC_UT_0099(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_OFF;
   u8_t u8BluetoothPairingState=BLE_NOT_PAIRED;
   u8_t mqttPairingState=MQTT_NOT_PAIRED;
    enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_NOK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ERROR,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth paired, mqtt not paired, Alarm is off, LED API return success,  then Alarm is on and API returns success
void test_CCO_TC_UT_0100(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_OFF;
   u8_t u8BluetoothPairingState=BLE_PAIRED;
   u8_t mqttPairingState=MQTT_NOT_PAIRED;
    enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth not paired, mqtt paired, Alarm is off, LED API return success,  then Alarm is on and API returns success
void test_CCO_TC_UT_0101(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_OFF;
   u8_t u8BluetoothPairingState=BLE_NOT_PAIRED;
   u8_t mqttPairingState=MQTT_PAIRED;
    enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}

/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth paired, mqtt paired, Alarm is off, LED API return success,  then Alarm is off and API returns success
void test_CCO_TC_UT_0106(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_OFF;
   u8_t u8BluetoothPairingState=BLE_PAIRED;
   u8_t mqttPairingState=MQTT_PAIRED;
    enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_OFF,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}




/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth not paired, mqtt not paired, Alarm is on, LED API return success,  then Alarm is on and API returns success
void test_CCO_TC_UT_0102(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_ON;
   u8_t u8BluetoothPairingState=BLE_NOT_PAIRED;
   u8_t mqttPairingState=MQTT_NOT_PAIRED;
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}

/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth paired, mqtt not paired, Alarm is on, LED API return success,  then Alarm is on and API returns success
void test_CCO_TC_UT_0103(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_ON;
   u8_t u8BluetoothPairingState=BLE_PAIRED;
   u8_t mqttPairingState=MQTT_NOT_PAIRED;
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth not paired, mqtt paired, Alarm is on, LED API return success,  then Alarm is on and API returns success
void test_CCO_TC_UT_0104(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_ON;
   u8_t u8BluetoothPairingState=BLE_NOT_PAIRED;
   u8_t mqttPairingState=MQTT_PAIRED;
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}

/*__________________________________________________________________________________________________________________________*/
/// @brief bluetooth paired, mqtt paired, Alarm is on, LED API return success,  then Alarm is off and API returns success
void test_CCO_TC_UT_0105(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8WirelessAlarmState=ALARM_ON;
   u8_t u8BluetoothPairingState=BLE_PAIRED;
   u8_t mqttPairingState=MQTT_PAIRED;
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);
  
    // Act
   returnValue=enum_HandleWirlessAlarmState(u8BluetoothPairingState,mqttPairingState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_OFF,GLOB_u8WirelessAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}

/*____________________________________enum_BatteryAlarmHandle()______________________________________*/
/*__________________________________________________________________________________________________________________________*/
/// @brief battery is disconnected and Alarm is off , Buzzer API returns success,  then Alarm goes ON and API returns Success
void test_CCO_TC_UT_0107(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_OFF;
   u8_t BatteryConnectionState=DISCONNECTED_VOLT_BATTERY;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);

  
    // Act
   returnValue=enum_HandleBatteryAlarm(BatteryConnectionState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8BatteryAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
}

/*__________________________________________________________________________________________________________________________*/
/// @brief battery is disconnected and Alarm is off , Buzzer API returns failed,  then Alarm goes ON  and API returns Failed
void test_CCO_TC_UT_0108(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_OFF;
   u8_t BatteryConnectionState=DISCONNECTED_VOLT_BATTERY;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_NOK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_ERROR);

  
    // Act
   returnValue=enum_HandleBatteryAlarm(BatteryConnectionState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ERROR,GLOB_u8BatteryAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
}

/*__________________________________________________________________________________________________________________________*/
/// @brief battery is connected and Alarm is off , Buzzer API returns success,  then Alarm is off  and API returns success
void test_CCO_TC_UT_0109(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_OFF;
   u8_t BatteryConnectionState=NORMAL_VOLT_BATTERY;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);

  
    // Act
   returnValue=enum_HandleBatteryAlarm(BatteryConnectionState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_OFF,GLOB_u8BatteryAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief battery is disconnected and Alarm is ON , Buzzer API returns success,  then Alarm is on  and API returns success
void test_CCO_TC_UT_0110(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_ON;
   u8_t BatteryConnectionState=DISCONNECTED_VOLT_BATTERY;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);

  
    // Act
   returnValue=enum_HandleBatteryAlarm(BatteryConnectionState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_ON,GLOB_u8BatteryAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
}


/*__________________________________________________________________________________________________________________________*/
/// @brief battery is connected and Alarm is ON , Buzzer API returns success,  then Alarm is off  and API returns success
void test_CCO_TC_UT_0111(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_ON;
   u8_t BatteryConnectionState=NORMAL_VOLT_BATTERY;
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);

  
    // Act
   returnValue=enum_HandleBatteryAlarm(BatteryConnectionState);

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_OFF,GLOB_u8BatteryAlarmState);
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
}


/*____________________________________enum_AlarmAppManage ()______________________________________*/
/// @brief battery is connected and Alarm is ON , Buzzer API returns success,  then Alarm is off  and API returns success
void test_CCO_TC_UT_0112(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,1);
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,1);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);

  
    // Act
   returnValue=enum_AlarmAppManage();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/// @brief only battery reading invalid, API return Fail
void test_CCO_TC_UT_0113(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,NOT_VALID_BAT_RETURN);
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,1);
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,1);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);

  
    // Act
   returnValue=enum_AlarmAppManage();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
}


/// @brief buzzer API returns error, API return Fail
void test_CCO_TC_UT_0114(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   GLOB_u8BatteryAlarmState=ALARM_ON;
   enum_BattGet_Stub(enumBattGet_connectedStateStub);
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,MQTT_NOT_PAIRED);
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,BLE_NOT_PAIRED);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_NOK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_OK);

  
    // Act
   returnValue=enum_AlarmAppManage();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}


/// @brief LED API returns error, API return Fail
void test_CCO_TC_UT_0115(void)
{
   
   // Setup
   AlarmAppErrorState_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(17,BLE_NOT_PAIRED);
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(17,MQTT_NOT_PAIRED);
   enum_SetBuzzerState_CMockIgnoreAndReturn(17,BUZZER_DRV_OK);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_SetIndicatorLedState_CMockIgnoreAndReturn(17,LED_DRV_NOK);

  
    // Act
   returnValue=enum_AlarmAppManage();

    // Assert
     TEST_ASSERT_EQUAL_INT(ALARM_APP_FAILED,returnValue);
 
    // Cleanup
    GLOB_u8BatteryAlarmState=ALARM_OFF;
    GLOB_u8WirelessAlarmState=ALARM_OFF;
}







