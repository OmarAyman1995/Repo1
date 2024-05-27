#include <unity.h>
#include "Battery.h"
#include "mock_main.h"
#include "mock_ADC.h"

/// @brief this flag is set while the calculations (writing) is in progress, when writing is done it is cleared.
PUBLIC    u8_t                    u8BATcalcInProgressFlag ;

/// @brief this container contains the two batteries information (Voltage - State)
PUBLIC    strBatteriesInfo_t      strBatteriesInfo;

/// @brief this flag will be set when enum_BatInit is performed successfully, otherwise it is = 0 !
PUBLIC    u8_t                    u8InitIsDone;



				/* - - - - - - - STUB - - - - - - -*/
// NORMAL (ON board battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub1Normal(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	// Vf  = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU
	// LOC_u32AdcReadValue = 2.9f*ADC_TOTAL_LEVELS_NUMBER/VCC_MCU
	
	float TempResult = 2.9f * ADC_TOTAL_LEVELS_NUMBER / VCC_MCU;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

// Disconnected (ON board battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub1Disconnected(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	// Vf  = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU
	// LOC_u32AdcReadValue = 2.9f*ADC_TOTAL_LEVELS_NUMBER/VCC_MCU
	
	float TempResult = 0.0f * ADC_TOTAL_LEVELS_NUMBER / VCC_MCU;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}
// LOW (ON board battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub1Low(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	// Vf  = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU
	// LOC_u32AdcReadValue = 2.9f*ADC_TOTAL_LEVELS_NUMBER/VCC_MCU
	
	float TempResult = 2.4f * ADC_TOTAL_LEVELS_NUMBER / VCC_MCU;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

// MALFAUNCTION (ON board battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub1Malfunction(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	// Vf  = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU
	// LOC_u32AdcReadValue = 2.9f*ADC_TOTAL_LEVELS_NUMBER/VCC_MCU
	
	float TempResult = 4.9f * ADC_TOTAL_LEVELS_NUMBER / VCC_MCU;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

//NORMAL (Vehicle battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub2Normal(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	//Vf = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU * VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
    //LOC_u32AdcReadValue = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	
	float TempResult = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

//MALFUNCTION (Vehicle battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub2Malfunction(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	//Vf = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU * VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
    //LOC_u32AdcReadValue = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	
	float TempResult = 19.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

//Disconnected (Vehicle battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub2Disconnected(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	//Vf = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU * VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
    //LOC_u32AdcReadValue = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	
	float TempResult = 0.0f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

//HIGH (Vehicle battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub2High(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	//Vf = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU * VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
    //LOC_u32AdcReadValue = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	
	float TempResult = 15.3f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

//LOW (Vehicle battery STUB)
enumRetAdc_e enum_AdcReadFromChannelStub2Low(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	//Vf = LOC_u32AdcReadValue/ADC_TOTAL_LEVELS_NUMBER * VCC_MCU * VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
    //LOC_u32AdcReadValue = 11.5f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	
	float TempResult = 8.7f *ADC_TOTAL_LEVELS_NUMBER/VCC_MCU/VEHICLE_BATTERY_VOLTAGE_DEVIDER_RESISTORS_NUMBERS;
	*u32ReadValue = (u32_t)TempResult;
	return VALID_ADC;
}

void test_CCO_TC_UT_2239(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0;

 	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;

	u8InitIsDone = 0 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BAT_RETURN);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2240(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ; 
	
	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BAT_RETURN);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}	


void test_CCO_TC_UT_2241(void)
{
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	enum_AdcInit_CMockIgnoreAndReturn(38,NOT_VALID_ADC);
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ; 

	LOC_enumRetVal = enum_BattGet(NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BAT_RETURN);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2242(void)
{
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0;

	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1;
	
	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BAT_RETURN);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2244(void)
{


	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState = LOW_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = ON_BOARD_BATTERY_MIN - 0.3f ; 
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;
	
	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,LOW_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
     

}

void test_CCO_TC_UT_2245(void)
{
	
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState =  NORMAL_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = ON_BOARD_BATTERY_MIN + 0.2f ; 
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;

	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;


	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,NORMAL_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2246(void)
{
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState =  MALFUNCTION_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 20.9f ;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,MALFUNCTION_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2247(void)
{
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState =  DISCONNECTED_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f ;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2248(void)
{
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState =  NORMAL_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = ON_BOARD_BATTERY_MIN + 0.2f  ;

	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	

	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,NORMAL_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2249(void)
{
	strBatteriesInfo.enumVehicleBatteyState = MALFUNCTION_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 18.5 ;
	strBatteriesInfo.enumOnBoardBatteryState =  DISCONNECTED_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;

	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,MALFUNCTION_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2250(void)
{
	strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0 ;
	strBatteriesInfo.enumOnBoardBatteryState =  DISCONNECTED_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;

	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2251(void)
{
	strBatteriesInfo.enumVehicleBatteyState = HIGH_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 14.5f ;
	strBatteriesInfo.enumOnBoardBatteryState =  DISCONNECTED_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;

	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,HIGH_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}

void test_CCO_TC_UT_2252(void)
{
	strBatteriesInfo.enumVehicleBatteyState = LOW_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 8.5f ;
	strBatteriesInfo.enumOnBoardBatteryState =  DISCONNECTED_VOLT_BATTERY;
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	
	u8InitIsDone = 1 ;  
	u8BATcalcInProgressFlag = 1 ;

	LOC_enumRetVal = enum_BattGet(&strBatteriesInfo);
	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,LOW_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;
}



void test_CCO_TC_UT_2253(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Normal);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,NORMAL_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2254(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Disconnected);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2255(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Disconnected);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}
void test_CCO_TC_UT_2256(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Low);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,LOW_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2257(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Malfunction);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,MALFUNCTION_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2258(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 0 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Malfunction);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumOnBoardBatteryState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}




void test_CCO_TC_UT_2263(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2Normal);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,NORMAL_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2264(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2Disconnected);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2265(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2High);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,HIGH_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}
void test_CCO_TC_UT_2266(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2Low);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,LOW_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2267(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 1 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2Malfunction);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,MALFUNCTION_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}

void test_CCO_TC_UT_2268(void)
{
    strBatteriesInfo.enumVehicleBatteyState = DISCONNECTED_VOLT_BATTERY; 
	strBatteriesInfo.floatVehicleBatteyVoltage = 0.0f ;
	strBatteriesInfo.enumOnBoardBatteryState = DISCONNECTED_VOLT_BATTERY ; 
	strBatteriesInfo.floatOnBoardBatteryVoltage = 0.0f;
	
	enumRetBat_e LOC_enumRetVal = UNKOWN_BAT_RETURN;
	u8InitIsDone = 0 ; 
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub2Malfunction);
	vid_BattManage();

	TEST_ASSERT_EQUAL_INT(strBatteriesInfo.enumVehicleBatteyState,DISCONNECTED_VOLT_BATTERY);

	// clear GLOBs 
	u8InitIsDone = 0 ;  
	u8BATcalcInProgressFlag = 0;

}




