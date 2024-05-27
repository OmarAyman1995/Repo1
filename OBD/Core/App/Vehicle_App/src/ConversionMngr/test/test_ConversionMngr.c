#include "unity.h"

#include "services.h"
#include "ConvUnits.h"
#include "ConversionMngr.h"
#include "mock_PIDsDatabase.h"






void test_case_0001(void){
    // setup
    p_getConvFunction_ExpectAndReturn(0x0d, ConvVehicle_Speed);
    u8_t output_string[50] = {0};
    u8_t returnCheck = 0;
    // act
    returnCheck = u8_ConvertOBDToPhysicalValue(0x0d, 255,255,255,255,output_string);

    // assert
    TEST_ASSERT_EQUAL_STRING("255", output_string);
    TEST_ASSERT_EQUAL_CHAR(1, returnCheck);

    // cleanup

}

void test_case_0002(void){
    // setup
    u8_t output_string[50] = {0};
    u8_t returnCheck = 0;

    // act
    returnCheck = u8_ConvertOBDToPhysicalValue(202, 255,255,255,255, output_string);

    // assert
    TEST_ASSERT_EQUAL_STRING("", output_string);
    TEST_ASSERT_EQUAL_CHAR(0, returnCheck);

    // cleanup

}


void test_case_0003(void){
    // setup
    p_getConvFunction_ExpectAndReturn(0x0d, NULLPTR);
    u8_t output_string[50] = {0};
    u8_t returnCheck = 0;
    // act
    returnCheck = u8_ConvertOBDToPhysicalValue(0x0d, 255,255,255,255,output_string);

    // assert
    TEST_ASSERT_EQUAL_STRING("", output_string);
    TEST_ASSERT_EQUAL_CHAR(0, returnCheck);

    // cleanup

}

void test_case_0004(void){
    // setup
    p_getConvFunction_ExpectAndReturn(0x0d, ConvVehicle_Speed);
    u8_t output_string[50] = {0};
    u8_t returnCheck = 0;
    u32_t convertedSize = 0;

    // act
    returnCheck = u8_ConvertOBDToPhysicalValue(0x0d, 255,255,255,255,output_string);
    convertedSize = u32_getConvertedSize();

    // assert
    TEST_ASSERT_EQUAL_STRING("255", output_string);
    TEST_ASSERT_EQUAL_CHAR  (0, returnCheck);
    TEST_ASSERT_EQUAL_UINT32(3, convertedSize);
    // cleanup

}