#include <unity.h>
#include "CRS.h"
#include "mock_main.h"
#include "mock_ADC.h"


/// @brief this flag will be set when enum_CRSInit is performed successfully, otherwise it is = 0 !
PUBLIC    u8_t            u8InitIsDone          ;

/// @brief this flag will be set in case we are writing on the strCurrentInfo, to protect race condition, otherwise it is = 0 !
PUBLIC    u8_t            u8UpdateInProgress     ;

/// @brief this struct contains the information of the current sensor (current , state of the sesnor)
PUBLIC    strCurrent_t    strCurrentInfo          ;

/* - - - - - - - - - - - STUP - - - - - - - - - - -*/
///        HIGH    :  >  2000mA
///        LOW     :  <  10mA
///        NORMAL  :  >= 10 mA   && <= 2000mA
///        MALFUNCTION : anything else
///        DISCONNECTED : 0A

// NORMAL (1000mA)
enumRetAdc_e enum_AdcReadFromChannelStub1Normal(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	double TempResult = 0.0f;
   
	
	//TempResult = ((1000.0 *0.185 ) + 2.5) * (4096.0/5.0);
	TempResult = ((0.185*(1100.0/1000.0))+2.5)*(4096.0/5.0);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}

// LOW (4mA)
enumRetAdc_e enum_AdcReadFromChannelStub1Low(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	double TempResult = 0.0f;
   
	
	//TempResult = ((1000.0 *0.185 ) + 2.5) * (4096.0/5.0);
	TempResult = ((0.185*(9.0/1000.0))+2.5)*(4096.0/5.0);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}


// HIGH (2400mA)
enumRetAdc_e enum_AdcReadFromChannelStub1High(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	double TempResult = 0.0f;
   
	
	//TempResult = ((1000.0 *0.185 ) + 2.5) * (4096.0/5.0);
	TempResult = ((0.185*(2400.0/1000.0))+2.5)*(4096.0/5.0);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}
// Disconnected (0mA)
enumRetAdc_e enum_AdcReadFromChannelStub1Disconnected(u8_t u8Channel, u32_t *u32ReadValue,int num)
{
	double TempResult = 0.0f;
   
	
	//TempResult = ((1000.0 *0.185 ) + 2.5) * (4096.0/5.0);
	TempResult = ((0.185*(0.0/1000.0))+2.5)*(4096.0/5.0);
	*u32ReadValue = (u32_t )TempResult;
	return VALID_ADC;
}

void test_CCO_TC_UT_2280(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	strCurrent_t strCurrent = {0.0,MALFUNCTION_CURRENT};
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;

	enum_AdcReadFromChannel_CMockIgnoreAndReturn(25,VALID_ADC);
	vid_CRSManage();
	
	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrent);
	TEST_ASSERT_EQUAL_INT(LOC_enumValidOrNot,NOT_VALID_CRS);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}

void test_CCO_TC_UT_2281(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	strCurrent_t strCurrent = {0.0,MALFUNCTION_CURRENT};
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;

	enum_AdcInit_CMockIgnoreAndReturn(43,VALID_ADC);
	enum_CRSInit();
	
	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrent);
	TEST_ASSERT_EQUAL_INT(LOC_enumValidOrNot,NOT_VALID_CRS);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}






void test_CCO_TC_UT_2282(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	strCurrent_t strCurrent = {0.0,MALFUNCTION_CURRENT};
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;

	enum_AdcInit_CMockIgnoreAndReturn(65,VALID_ADC);
	enum_CRSInit();

	enum_AdcReadFromChannel_CMockIgnoreAndReturn(71,VALID_ADC);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumValidOrNot,NOT_VALID_CRS);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}


void test_CCO_TC_UT_2283(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
	
	enum_AdcInit_CMockIgnoreAndReturn(65,VALID_ADC);
	enum_CRSInit();
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Normal);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrentInfo);
	TEST_ASSERT_EQUAL_INT(strCurrentInfo.enumCurrentState,NORMAL_CURRENT);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;

}

void test_CCO_TC_UT_2284(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
	
	enum_AdcInit_CMockIgnoreAndReturn(65,VALID_ADC);
	enum_CRSInit();
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Low);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrentInfo);
	TEST_ASSERT_EQUAL_INT(strCurrentInfo.enumCurrentState,LOW_CURRENT);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}

void test_CCO_TC_UT_2285(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
	
	enum_AdcInit_CMockIgnoreAndReturn(65,VALID_ADC);
	enum_CRSInit();
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1High);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrentInfo);
	TEST_ASSERT_EQUAL_INT(strCurrentInfo.enumCurrentState,HIGH_CURRENT);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}

void test_CCO_TC_UT_2286(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
	
	enum_AdcInit_CMockIgnoreAndReturn(65,VALID_ADC);
	enum_CRSInit();
	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Disconnected);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrentInfo);
	TEST_ASSERT_EQUAL_INT(strCurrentInfo.enumCurrentState,DISCONNECTED_CURRENT);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}
void test_CCO_TC_UT_2287(void)
{
	enumRetCrs_e LOC_enumValidOrNot = UNKOWN_CRS;
	
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
	

	
	enum_AdcReadFromChannel_Stub(enum_AdcReadFromChannelStub1Disconnected);
	vid_CRSManage();

	LOC_enumValidOrNot = enum_CRSGetCurrent(&strCurrentInfo);
	TEST_ASSERT_EQUAL_INT(LOC_enumValidOrNot,NOT_VALID_CRS);

	/*clear*/
	u8InitIsDone  = 0 ;
	u8UpdateInProgress = 0 ;
}



