#include "MonitoringApp.h"
#include "mock_Battery.h"
#include "mock_Wireless_App.h"
#include "mock_services.h"
#include "mock_TPS.h"
#include "mock_CRS.h"
#include "mock_Can.h"
#include "mock_Vehicle_App.h"

#include "unity.h"

/*Private Function Extern*/
extern MonitroingAppApiReturn_e enum_CollectBatteries  (DataToMonitor_t* structToFill);
extern MonitroingAppApiReturn_e enum_CollectTemperature(DataToMonitor_t* structToFill);
extern MonitroingAppApiReturn_e enum_CollectCurrent(DataToMonitor_t* structToFill);
extern MonitroingAppApiReturn_e enum_CommunicateMonitorMsg(u8_t* CompleteMonitorMsg);


/*Variable Extern*/
extern u8_t GLOB_u8IgnitionStateReceptionFlag; 



/*stubs*/


/*Macros*/
#define FLAG_SET                     1
#define FLAG_CLEAR                   0


/*________________________________________________________________enum_CollectBatteries()___________________________________*/

/*___________________________________________________________________________________________________________________________*/
/// @brief Battery API returns invalid read state  
void test_CCO_TC_UT_0040(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,NOT_VALID_BAT_RETURN);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectBatteries(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief Battery API return valid read state,  
void test_CCO_TC_UT_0041(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectBatteries(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*_____________________________________________________________enum_CollectTemperature()___________________________________*/

/*___________________________________________________________________________________________________________________________*/
/// @brief Temperature reading is valid 
void test_CCO_TC_UT_0042(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,VALID_TPS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectTemperature(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief temperature reading is invalid  
void test_CCO_TC_UT_0043(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,NOT_VALID_TPS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectTemperature(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief temperature reading is unkown  
void test_CCO_TC_UT_0044(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,UNKOWN_TPS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectTemperature(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief Temperature reading is not avaialbe due to a write operation  
void test_CCO_TC_UT_0045(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,WRITING_IN_PROGRESS_TPS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectTemperature(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}



/*_____________________________________________________________enum_CollectCurrent()___________________________________*/

/*___________________________________________________________________________________________________________________________*/
/// @brief current reading is valid 
void test_CCO_TC_UT_0046(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,VALID_CRS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectCurrent(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief current reading is invalid  
void test_CCO_TC_UT_0047(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,NOT_VALID_CRS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectCurrent(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief Current reading is unkown  
void test_CCO_TC_UT_0048(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,UNKOWN_CRS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectCurrent(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief current reading is blocked due to a write operation  
void test_CCO_TC_UT_0049(void)
{
   
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,WRITING_IN_PROGRESS_CRS);
   DataToMonitor_t structToFill={0};

  
    // Act
    returnValue=enum_CollectCurrent(&structToFill);


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*_____________________________________________________enum_MonitorAppManage()___________________________________*/
/*___________________________________________________________________________________________________________________________*/
/// @brief Monitor App Success, no readings error , no communication error
void test_CCO_TC_UT_0054(void)
{
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   DataToMonitor_t structToFill={0};

   enum_BattGet_CMockIgnoreAndReturn(17,VALID_BAT_RETURN);
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,VALID_TPS);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(17,1);
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,VALID_CRS);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(1,0);
   enum_isCanBusOff_CMockIgnoreAndReturn(1,0);
   floatToString_CMockIgnoreAndReturn(1,32);
   decimalToString_CMockIgnoreAndReturn(1,32);

    // Act
    returnValue=enum_MonitorAppManage();


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_SUCCESS,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief battery reading error only, API returns error
void test_CCO_TC_UT_0055(void)
{
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   DataToMonitor_t structToFill={0};

   enum_BattGet_CMockIgnoreAndReturn(17, NOT_VALID_BAT_RETURN);
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,VALID_TPS);
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,VALID_CRS);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_isCanBusOff_CMockIgnoreAndReturn(1,0);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(1,0);
   floatToString_CMockIgnoreAndReturn(1,32);
   decimalToString_CMockIgnoreAndReturn(1,32);

    // Act
    returnValue=enum_MonitorAppManage();


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}

/*___________________________________________________________________________________________________________________________*/
/// @brief Monitor App Error, temperature reading error only
void test_CCO_TC_UT_0056(void)
{
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   DataToMonitor_t structToFill={0};

   enum_BattGet_CMockIgnoreAndReturn(17, VALID_BAT_RETURN);
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,NOT_VALID_TPS);
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,VALID_CRS);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_isCanBusOff_CMockIgnoreAndReturn(1,0);
   floatToString_CMockIgnoreAndReturn(1,32);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(1,0);
   decimalToString_CMockIgnoreAndReturn(1,32);

    // Act
    returnValue=enum_MonitorAppManage();


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}


/*___________________________________________________________________________________________________________________________*/
/// @brief Monitor App Error, current reading and battery error 
void test_CCO_TC_UT_0057(void)
{
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   DataToMonitor_t structToFill={0};

   enum_BattGet_CMockIgnoreAndReturn(17, VALID_BAT_RETURN);
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,VALID_TPS);
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,NOT_VALID_CRS);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_OK);
   enum_isCanBusOff_CMockIgnoreAndReturn(1,0);
   floatToString_CMockIgnoreAndReturn(1,32);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(1,0);
   decimalToString_CMockIgnoreAndReturn(1,32);

    // Act
    returnValue=enum_MonitorAppManage();


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}

/*___________________________________________________________________________________________________________________________*/
/// @brief Monitor App Error, wireless App API returns error
void test_CCO_TC_UT_0059(void)
{
   // Setup
   MonitroingAppApiReturn_e returnValue=0;
   DataToMonitor_t structToFill={0};

   enum_BattGet_CMockIgnoreAndReturn(17, VALID_BAT_RETURN);
   enum_TPSGetTemperature_CMockIgnoreAndReturn(17,VALID_TPS);
   enum_CRSGetCurrent_CMockIgnoreAndReturn(17,VALID_CRS);
   enum_WirelessApp_Request_CMockIgnoreAndReturn(17,WIRELESS_APP_ERROR);
   enum_isCanBusOff_CMockIgnoreAndReturn(1,0);
   floatToString_CMockIgnoreAndReturn(1,32);
   u8_VehicleApp_getMotorState_CMockIgnoreAndReturn(1,0);
   decimalToString_CMockIgnoreAndReturn(1,32);

    // Act
    returnValue=enum_MonitorAppManage();


    // Assert
     TEST_ASSERT_EQUAL_INT(MONITORING_APP_FAILED,returnValue);
 
    // Cleanup
}




