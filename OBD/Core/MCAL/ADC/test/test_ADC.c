#include <unity.h>
#include "ADC.h"
#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_adc.h"
#include "mock_WDT.h"
#include "mock_QueueInterface.h"

PUBLIC u8_t u8InitDoneFlag;

void setUp(void){
	vid_TaskDelay_Ignore();
}

void test_CCO_TC_UT_2100(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(0,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_ADC);
}

void test_CCO_TC_UT_2101(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;

	MX_ADC1_Init_CMockIgnore();

	LOC_enumRet = enum_AdcInit();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);


}



void test_CCO_TC_UT_2102(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_ERROR);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_ERROR);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_ERROR);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_ERROR);

	LOC_enumRet = enum_AdcReadFromChannel(0,NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_ADC);
}


void test_CCO_TC_UT_2103(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(56,HAL_ERROR);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_ERROR);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_ERROR);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_ERROR);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_ERROR);
	
	LOC_enumRet = enum_AdcReadFromChannel(10,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_ADC);
}


void test_CCO_TC_UT_2104(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(73,HAL_OK);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(0,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);
}

void test_CCO_TC_UT_2105(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(89,HAL_OK);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(1,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);
}

void test_CCO_TC_UT_2106(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(105,HAL_OK);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(4,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);
}

void test_CCO_TC_UT_2107(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(121,HAL_OK);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(6,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);
}

void test_CCO_TC_UT_2108(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;
	u32_t buffer = 0 ;

	HAL_ADC_Init_CMockIgnoreAndReturn(137,HAL_OK);
	vid_WdtRefresh_CMockIgnore();
    HAL_ADC_Start_CMockIgnoreAndReturn(13,HAL_OK);
    HAL_ADC_PollForConversion_CMockIgnoreAndReturn(14,HAL_OK);
    HAL_ADC_GetValue_CMockIgnoreAndReturn(15,HAL_OK);
    HAL_ADC_Stop_CMockIgnoreAndReturn(16,HAL_OK);

	LOC_enumRet = enum_AdcReadFromChannel(6,&buffer);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);
}

void test_CCO_TC_UT_2109(void)
{
	enumRetAdc_e LOC_enumRet = UNKOWN_ADC;

	MX_ADC1_Init_CMockIgnore();

	LOC_enumRet = enum_AdcInit();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_ADC);


}

