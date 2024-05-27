#include "LowPowerApp.h"
#include "LowPowerAppCnfg.h"
#include "mock_MQTTSim800.h"
#include "mock_Battery.h"
#include "mock_Wireless_App.h"
#include "mock_CmsisAbstract.h"
#include "mock_LowPowerAppCnfg.h"
#include "mock_BluetoothDrv.h"
#include "mock_Vehicle_App.h"
#include "mock_Can.h"
#include "unity.h"

#define connected 1
#define disconnected 0
#define wireless_requests_inActive 0
#define wireless_requests_Active 1
#define Ignition_OFF 0
#define Ignition_ON 1
extern bool enum_EvaluateVehicleBatteryCondition(void);
extern bool enum_EvaluateBluetoothPairingCondition(void);
extern bool enum_EvaluateMQTTPairingCondition(void);
extern bool enum_EvaluateWirelessRequestCondition(void);
extern bool enum_EvaluateIgnitionCondition(void);
extern DeviceState_e enum_DecideDeviceMode(const LowPowerFactors_t* ConditionStates);

extern DeviceState_e       GLOB_enumCurrentDeviceMode;

/*Stubs*/
enumRetBat_e enum_BattGet_disconnectedStateStub(strBatteriesInfo_t *structToFill,int num)
{
    structToFill->enumVehicleBatteyState=DISCONNECTED_VOLT_BATTERY;
    return VALID_BAT_RETURN;
}

enumRetBat_e  enum_BattGet_connectedStateStub(strBatteriesInfo_t *structToFill,int num)
{
    structToFill->enumVehicleBatteyState=NORMAL_VOLT_BATTERY;
    return VALID_BAT_RETURN;
}





/*_______________________________________enum_EvaluateVehicleBatteryCondition()___________________________________*/
/*_______________________________________________________________________________________________________________________*/
/// @brief Battery is connected, API return Low Power condition is true 
void test_CCO_TC_UT_0001(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
    enum_BattGet_Stub(enum_BattGet_connectedStateStub);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateVehicleBatteryCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_TRUE,returnValue);
 
    // Cleanup
}

/*_______________________________________________________________________________________________________________________*/
/// @brief Battery is disconnected, API return Low Power condition is false  
void test_CCO_TC_UT_0002(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   enum_BattGet_Stub(enum_BattGet_disconnectedStateStub);

    // Act
   /*call function*/
   returnValue=enum_EvaluateVehicleBatteryCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_FALSE,returnValue);
 
    // Cleanup
}


/*_______________________________________enum_EvaluateBluetoothPairingCondition()___________________________________*/

/*_______________________________________________________________________________________________________________________*/
/// @brief Bluetooth is not paired, LowPower condition is true
void test_CCO_TC_UT_0003(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(16,disconnected);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateBluetoothPairingCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_TRUE,returnValue);
 
    // Cleanup
}

/*_______________________________________________________________________________________________________________________*/
/// @brief Bluetooth is connected,  LowPower condition is false
void test_CCO_TC_UT_0004(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(16,connected);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateBluetoothPairingCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_FALSE,returnValue);
 
    // Cleanup
}

/*_______________________________________enum_EvaluateMQTTPairingCondition()___________________________________*/

/*_______________________________________________________________________________________________________________________*/
/// @brief MQTT is not paired,  LowPower condition is true
void test_CCO_TC_UT_0005(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(16,disconnected);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateMQTTPairingCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_TRUE,returnValue);
 
    // Cleanup
}

/*_______________________________________________________________________________________________________________________*/
/// @brief MQTT is disconneted, LowPower condition is false
void test_CCO_TC_UT_0006(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_Mqtt_isConnnected_CMockIgnoreAndReturn(16,connected);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateMQTTPairingCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_FALSE,returnValue);
 
    // Cleanup
}

/*_______________________________________enum_EvaluateWirelessRequestCondition()___________________________________*/

/*_______________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0007
/// @brief Wireless requests Inactive, ,Low Power Condition true 
void test_CCO_TC_UT_0007(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_isWirelessCommActive_CMockIgnoreAndReturn(16,wireless_requests_inActive);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateWirelessRequestCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_TRUE,returnValue);
 
    // Cleanup
}


/*_______________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0008
/// @brief Wireless requests active , Low Power Condition not true  
void test_CCO_TC_UT_0008(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_isWirelessCommActive_CMockIgnoreAndReturn(16,wireless_requests_Active);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateWirelessRequestCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_FALSE,returnValue);
 
    // Cleanup
}


/*_______________________________________enum_EvaluateIgnitionCondition()___________________________________*/


/*_______________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0009
/// @brief ignition Off, ,Low Power Condition true 
void test_CCO_TC_UT_0009(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(16,Ignition_OFF);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateIgnitionCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_TRUE,returnValue);
 
    // Cleanup
}


/*_______________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0010
/// @brief Ignition On , Low Power Condition not true  
void test_CCO_TC_UT_0010(void)
{
   
   // Setup
    bool returnValue=LOW_POWER_CONDITION_FALSE;
   /*Mock get Battery Function to return Battery Disconnected*/
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(16,Ignition_ON);

  
    // Act
   /*call function*/
   returnValue=enum_EvaluateIgnitionCondition();


    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_CONDITION_FALSE,returnValue);
 
    // Cleanup
}

/*_______________________________________enum_DecideDeviceMode()___________________________________*/


/*_______________________________________________________________________________________________________________________*/
/// @name  CCO-TC-UT-0011
/// @brief all Low Power Conditions are True, ,Device Mode is Low Power
void test_CCO_TC_UT_0011(void)
{ 
    
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_TRUE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_TRUE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_TRUE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_TRUE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_TRUE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_LOW_POWER,returnValue);
 
    // Cleanup
}


/// @name  CCO-TC-UT-0012
/// @brief not all Low Power Conditions are true, ,Device Mode is Nomral
void test_CCO_TC_UT_0012(void)
{
   
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_FALSE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_TRUE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_TRUE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_TRUE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_TRUE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_NORMAL,returnValue);
 
    // Cleanup
}

/// @name  CCO-TC-UT-0012
/// @brief not all Low Power Conditions are true, ,Device Mode is Nomral
void test_CCO_TC_UT_0013(void)
{
   
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_TRUE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_FALSE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_TRUE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_TRUE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_TRUE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_NORMAL,returnValue);
 
    // Cleanup
}

/// @name  CCO-TC-UT-0012
/// @brief not all Low Power Conditions are true, ,Device Mode is Nomral
void test_CCO_TC_UT_0014(void)
{
   
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_TRUE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_TRUE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_FALSE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_TRUE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_TRUE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_NORMAL,returnValue);
 
    // Cleanup
}

/// @name  CCO-TC-UT-0012
/// @brief not all Low Power Conditions are true, ,Device Mode is Nomral
void test_CCO_TC_UT_0015(void)
{
   
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_TRUE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_TRUE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_TRUE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_FALSE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_TRUE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_NORMAL,returnValue);
 
    // Cleanup
}


/// @name  CCO-TC-UT-0012
/// @brief not all Low Power Conditions are true, ,Device Mode is Nomral
void test_CCO_TC_UT_0016(void)
{
   
   // Setup
    bool returnValue=DEVICE_MODE_NORMAL; 
    LowPowerFactors_t LOC_ConditionsStates=
    {
        .u8IgnitionCondition        =LOW_POWER_CONDITION_TRUE,
        .u8BluetoothPairingCondition=LOW_POWER_CONDITION_TRUE,
        .u8MQTTPairingCondition     =LOW_POWER_CONDITION_TRUE,
        .u8VehicleBatteryCondition  =LOW_POWER_CONDITION_TRUE,
        .u8WirelessRequestCondition =LOW_POWER_CONDITION_FALSE
    };

    // Act
   /*call function*/
   returnValue=enum_DecideDeviceMode(&LOC_ConditionsStates);


    // Assert
    TEST_ASSERT_EQUAL_INT(DEVICE_MODE_NORMAL,returnValue);
 
    // Cleanup
}



/*_______________________________________enum_LowPowerAppManage()___________________________________*/

/// @name  CCO-TC-UT-0013
/// @brief Device is in Low Power Mode, Manage function will return Low Power State
void test_CCO_TC_UT_0017(void)
{ 
   // Setup
   LowPowerApiReturn_e returnValue=0;
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_LOW_POWER;

    // Act
   /*call function*/
   returnValue=enum_LowPowerAppManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(LOW_POWER_STATE,returnValue);
 
    // Cleanup
}


/// @name  CCO-TC-UT-0014
/// @brief Device is in Normal Mode and not all Conditions Are true, Manage function will return Normal_State
void test_CCO_TC_UT_0018(void)
{ 
   // Setup
   LowPowerApiReturn_e returnValue=0;
    u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(16,Ignition_ON);
    u8_isWirelessCommActive_CMockIgnoreAndReturn(16,wireless_requests_inActive);
    u8_Mqtt_isConnnected_CMockIgnoreAndReturn(16,disconnected);
    u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(16,disconnected);
    enum_BattGet_CMockIgnoreAndReturn(16,connected);
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;


    // Act
   /*call function*/
   returnValue=enum_LowPowerAppManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(NORMAL_STATE,returnValue);
 
    // Cleanup
}

/// @name  CCO-TC-UT-0014
/// @brief Device is in Normal Mode and all Conditions Are true, Manage function will return Transitioning to low power
void test_CCO_TC_UT_0019(void)
{ 
   // Setup
   LowPowerApiReturn_e returnValue=0;
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;
    u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(16,Ignition_OFF);
    u8_isWirelessCommActive_CMockIgnoreAndReturn(16,wireless_requests_inActive);
    u8_Mqtt_isConnnected_CMockIgnoreAndReturn(16,disconnected);
    u8_Bluetooth_getConnectivityStatus_CMockIgnoreAndReturn(16,disconnected);
    enum_BattGet_CMockIgnoreAndReturn(16,connected);
    enum_SetAcceptenceFilter_CMockIgnoreAndReturn(1,CAN_API_OK);
    vid_GoToWFI_CMockIgnore();
    GLOB_enumCurrentDeviceMode=DEVICE_MODE_NORMAL;


    // Act
   /*call function*/
   returnValue=enum_LowPowerAppManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(TRANSITION_TO_LOW_POWER,returnValue);
 
    // Cleanup
}










