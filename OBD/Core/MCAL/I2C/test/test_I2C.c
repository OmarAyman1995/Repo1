#include <unity.h>
#include "I2C.h"

#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_i2c.h"

void test_CCO_TC_UT_2698(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(12,HAL_OK);

	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2699(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
	HAL_I2C_Mem_Read_CMockIgnoreAndReturn(21,HAL_OK);

	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2700(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	MX_I2C1_Init_CMockIgnore();
	
	LOC_enumRet = enum_I2C1Init();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_I2C);
}

void test_CCO_TC_UT_2701(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(41,HAL_OK);
	
	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_I2C);
}

void test_CCO_TC_UT_2702(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(51,HAL_OK);
	
	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, NULL, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2703(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(61,HAL_OK);
	
	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, u8_pData, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2704(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
    HAL_I2C_Mem_Read_CMockIgnoreAndReturn(71,HAL_OK);

	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_I2C);
}

void test_CCO_TC_UT_2705(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
	HAL_I2C_Mem_Read_CMockIgnoreAndReturn(81,HAL_OK);
	
	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, NULL, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2706(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
	HAL_I2C_Mem_Read_CMockIgnoreAndReturn(91,HAL_OK);
	
	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, u8_pData, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2707(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(101,HAL_OK);
	
	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_I2C);
}

void test_CCO_TC_UT_2708(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
	HAL_I2C_Mem_Read_CMockIgnoreAndReturn(111,HAL_OK);
	
	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, u8_pData, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_I2C);
}

void test_CCO_TC_UT_2709(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16] = "12343134325";
	HAL_I2C_Mem_Write_CMockIgnoreAndReturn(101,HAL_ERROR);
	
	LOC_enumRet = enum_I2C1SendDataToMem(0x10,0x109 , 2, u8_pData, 16);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

void test_CCO_TC_UT_2710(void)
{
	enumRetI2C_e LOC_enumRet = UNKOWN_I2C ; 
	u8_t u8_pData[16];
	HAL_I2C_Mem_Read_CMockIgnoreAndReturn(111,HAL_ERROR);
	
	LOC_enumRet = enum_I2C1RecDataFromMem(0x10,0x109 , 2, u8_pData, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_I2C);
}

