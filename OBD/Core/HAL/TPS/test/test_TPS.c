#include <unity.h>
#include "TPS.h"
#include "mock_main.h"
#include "mock_ADC.h"

/// @brief this flag will be set in case we are writing on the strNTCInfo, to protect race condition, otherwise it is = 0 !
PUBLIC 			u8_t                   u8UpdateIsDone ;

/// @brief this struct contains the information of the NTC sensor (temperature , state of the sesnor)
PUBLIC 			strTemperatureNtc_t    strNTCInfo   ;

/// @brief this flag will be set when enum_TPSInit is performed successfully, otherwise it is = 0 !
PUBLIC 			u8_t                   u8InitIsDone ;

PUBLIC strTemperatureNtc_t strNTCInfoUT;

/* - - - - - - - - - - - STUP - - - - - - - - - - -*/
// NORMAL 70.0=>Temperature<=5.0
enumRetAdc_e enum_AdcReadFromChannelStub1Normal(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	float32_t TempResult = 0.0f;
   //R = 10000.0f/((4096.0f/(float32_t)u32AdcValue) -1);
   // u32ReadValue = (4096.0f/(10000f/R))+1)
	TempResult = 4096.0f/((10000.0f/15000.0f)+1);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}

// HIGH 70.0<Temperature
enumRetAdc_e enum_AdcReadFromChannelStub1High(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	float32_t TempResult = 0.0f;

	TempResult = 4096.0f/((10000.0f/1000.0f)+1);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}

// Low 5.0>Temperature
enumRetAdc_e enum_AdcReadFromChannelStub1Low(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	float32_t TempResult = 0.0f;

	TempResult = 4096.0f/((10000.0f/30000.0f)+1);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}

// Malfunction 
enumRetAdc_e enum_AdcReadFromChannelStub1Malfunction(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	float32_t TempResult = 0.0f;

	TempResult = 4096.0f/((10000.0f/10.0f)+1);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}



void test_CCO_TC_UT_2220(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
	enum_AdcInit_CMockIgnoreAndReturn(22,VALID_ADC);

	enum_LOCenumRetVal = enum_TPSInit();
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,VALID_TPS);
}

void test_CCO_TC_UT_2221(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
	u32_t LOC_u32ADCValue = 1000;
	float32_t LOC_R = 0.0f;

	enum_LOCenumRetVal = enum_TPSClaculateResistance(LOC_u32ADCValue,&LOC_R);
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,VALID_TPS);
}

void test_CCO_TC_UT_2222(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
	u32_t LOC_u32ADCValue = 0;
	float32_t LOC_R = 0.0f;

	enum_LOCenumRetVal = enum_TPSClaculateResistance(LOC_u32ADCValue,NULL);
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,NOT_VALID_TPS);
}



void test_CCO_TC_UT_2240(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;

 	
	u8InitIsDone = 1 ; 
	u8UpdateIsDone = 0 ;

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,NOT_VALID_TPS);
	
	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
	
}

void test_CCO_TC_UT_2241(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;


    u8InitIsDone = 1 ; 
	u8UpdateIsDone = 1 ;

	enum_LOCenumRetVal = enum_TPSGetTemperature(NULL);
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,NOT_VALID_TPS);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}

void test_CCO_TC_UT_2242(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;


    u8InitIsDone = 1 ; 
	u8UpdateIsDone = 1 ;

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(enum_LOCenumRetVal,VALID_TPS);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}





void test_CCO_TC_UT_2243(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;

 	
	u8InitIsDone = 1 ; 
 	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Normal);
	vid_TPSManage();

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(strNTCInfo.enumTmpState,NORMAL_TEMPERATURE);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}

void test_CCO_TC_UT_2244(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;

	u8InitIsDone = 1 ; 
 	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1High);
	vid_TPSManage();

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(strNTCInfo.enumTmpState,HIGH_TEMPERATURE);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}

void test_CCO_TC_UT_2245(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
 	
 	u8InitIsDone = 1 ; 
 	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Low);
	vid_TPSManage();

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(strNTCInfo.enumTmpState,LOW_TEMPERATURE);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}

void test_CCO_TC_UT_2246(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
	strTemperatureNtc_t strNTCInfoOut;
 	
 	u8InitIsDone = 1 ; 
 	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Malfunction);
	vid_TPSManage();

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(strNTCInfo.enumTmpState,MALFUNCTION_TEMPERATURE);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}

void test_CCO_TC_UT_2247(void)
{
	enumRetTps_e enum_LOCenumRetVal = UNKOWN_TPS ;
	strTemperatureNtc_t strNTCInfoOut;
 	
 	u8InitIsDone = 0 ; 
 	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Malfunction);
	vid_TPSManage();

	enum_LOCenumRetVal = enum_TPSGetTemperature(&strNTCInfo);
	TEST_ASSERT_EQUAL_INT(strNTCInfo.enumTmpState,MALFUNCTION_TEMPERATURE);

	/*clear GLOBs*/
	u8InitIsDone = 0 ; 
	u8UpdateIsDone = 0 ;
}