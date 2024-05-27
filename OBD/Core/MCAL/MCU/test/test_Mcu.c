#include <unity.h>
#include "Mcu.h"
#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
/*----- trying to use APIs without calling enum_McuSetClockSource ---*/
void test_CCO_TC_UT_2000(void)
{
	enumRetMcu_e LOC_enumRet = UNKOWN_MCU ; 
	LOC_enumRet = enum_McuEnablePeripherals();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_MCU);
}
void test_CCO_TC_UT_2001(void)
{
	enumRetMcu_e LOC_enumRet = UNKOWN_MCU ; 
	LOC_enumRet = enum_McuDisablePeripherals();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_MCU);
} 
void test_CCO_TC_UT_2002(void)
{
	enumPLLstability_e LOC_enumRet = PLL_UNKNOWN ; 
	LOC_enumRet = enum_McuGetPllStatus();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,PLL_UNSTABLE);
} 

/*----- trying to use APIs after calling enum_McuSetClockSource ---*/
void test_CCO_TC_UT_2003(void)
{
	enumRetMcu_e LOC_enumRet = UNKOWN_MCU ; 
	HAL_Init_CMockIgnoreAndReturn(41,0);
	SystemClock_Config_CMockIgnore();
	enum_McuSetClockSource();
	LOC_enumRet = enum_McuEnablePeripherals();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_MCU);
}
void test_CCO_TC_UT_2004(void)
{
	enumRetMcu_e LOC_enumRet = UNKOWN_MCU ;
	HAL_Init_CMockIgnoreAndReturn(41,0);
	SystemClock_Config_CMockIgnore();
	enum_McuSetClockSource(); 
	LOC_enumRet = enum_McuDisablePeripherals();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_MCU);
} 
void test_CCO_TC_UT_2005(void)
{
	enumPLLstability_e LOC_enumRet = PLL_UNKNOWN ; 
	HAL_Init_CMockIgnoreAndReturn(41,0);
	SystemClock_Config_CMockIgnore();
	enum_McuSetClockSource();
	LOC_enumRet = enum_McuGetPllStatus();

	TEST_ASSERT_EQUAL_INT(LOC_enumRet,PLL_STABLE);
}  