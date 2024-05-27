#include "unity.h"
#include "services.h"
#include "ConvUnits.h"
#include "PIDsDatabase.h"





void test_case_0001(void){
    TEST_ASSERT_EQUAL_CHAR(NOT_SUPPORTED, u8_getSupportInfo(0x0d));
}


void test_case_0002(void){
    TEST_ASSERT_EQUAL_CHAR(DYNAMIC, u8_getPidType(0x0d));
}

void test_case_0003(void){
    vid_setSupportInfo(0x0d, SUPPORTED);
    TEST_ASSERT_EQUAL_CHAR(SUPPORTED, u8_getSupportInfo(0x0d));
}

void test_case_0004(void){

    TEST_ASSERT_EQUAL_PTR(ConvVehicle_Speed, p_getConvFunction(0x0d));
}