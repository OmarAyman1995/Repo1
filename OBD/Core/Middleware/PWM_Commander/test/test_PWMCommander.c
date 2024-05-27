#include <unity.h>
#include "PwmCommander.h"

extern void vid_SplitBitsFromOBDdata(const u8_t* u8OBDdata);
void test_CCO_TC_UT_2600(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	LOC_enumRetVal = enum_PwmCommanderCollectFrame(NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2601(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	u8_t u8OBDdata[8] = {"01234567"};
	LOC_enumRetVal = enum_PwmCommanderCollectFrame(u8OBDdata);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2602(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	
	LOC_enumRetVal = enum_PwmCommanderRecFrame(NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2603(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	u8_t ptr_u8RecFrame[100];
	LOC_enumRetVal = enum_PwmCommanderRecFrame(ptr_u8RecFrame);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2604(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	u8_t ptr_u8RecFrame[100];
	LOC_enumRetVal = enum_PwmCommanderRecFrame(ptr_u8RecFrame);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2605(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	u8_t ptr_u8RecFrame[100];
	LOC_enumRetVal = enum_PwmCommanderRecFrame(ptr_u8RecFrame);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2612(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	
	LOC_enumRetVal = enum_PwmCommanderSendFrame();
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2613(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	
	LOC_enumRetVal = enum_PwmCommanderSendFrame();
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_PWM_COMMANDER);
}

void test_CCO_TC_UT_2614(void)
{
	enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
	
	 vid_SplitBitsFromOBDdata(NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,UNKOWN_PWM_COMMANDER);
}




