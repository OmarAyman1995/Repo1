#include <unity.h>
#include "WDT.h"
#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_wwdg.h"



void test_CCO_TC_UT_2160(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ; 
	HAL_WWDG_Refresh_CMockIgnoreAndReturn(12,HAL_OK);
	vid_WdtRefresh();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,UNKOWN_WDT);
}

void test_CCO_TC_UT_2161(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ;
	
	HAL_WWDG_Init_CMockIgnoreAndReturn(22,HAL_OK);
	Error_Handler_CMockIgnore();

	LOC_enumRet = enum_WdtSetResetTime(50);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_WDT);
}

void test_CCO_TC_UT_2162(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ; 

	HAL_WWDG_Init_CMockIgnoreAndReturn(22,HAL_ERROR);
	Error_Handler_CMockIgnore();

	LOC_enumRet = enum_WdtSetResetTime(150);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_WDT);
}

void test_CCO_TC_UT_2163(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ; 

	HAL_WWDG_Init_CMockIgnoreAndReturn(22,HAL_ERROR);
	Error_Handler_CMockIgnore();

	LOC_enumRet = enum_WdtSetResetTime(5);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_WDT);
}

void test_CCO_TC_UT_2164(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ; 

	HAL_WWDG_Init_CMockIgnoreAndReturn(22,HAL_ERROR);
	Error_Handler_CMockIgnore();

	LOC_enumRet = enum_WdtSetResetTime(50);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_WDT);
}



void test_CCO_TC_UT_2165(void)
{
	enumRetWdt_e LOC_enumRet = UNKOWN_WDT ; 

	HAL_WWDG_Refresh_CMockIgnoreAndReturn(12,HAL_OK);
	
	vid_WdtRefresh();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,UNKOWN_WDT);
}