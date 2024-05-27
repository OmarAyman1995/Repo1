#include <unity.h>
#include "BitsManager.h"


void test_CCO_TC_UT_2500(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendHigh(0);

	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2501(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendLow(0);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}


void test_CCO_TC_UT_2502(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendHigh(2);

	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2503(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendLow(2);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2504(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendHigh(1);

	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2505(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
	LOC_enumRetVal = enum_BitsManagerSendLow(1);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2506(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    enumBitsManagerHL_e enumRecBit[100];
	LOC_enumRetVal = enum_BitsManagerGetBits(NULL);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2507(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    enumBitsManagerHL_e enumRecBit[100];
	LOC_enumRetVal = enum_BitsManagerGetBits(enumRecBit);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2508(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    enumBitsManagerHL_e enumRecBit[100];
	LOC_enumRetVal = enum_BitsManagerGetBits(enumRecBit);
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BITS_MANAGER);
}






void test_CCO_TC_UT_2519(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    
	LOC_enumRetVal = enum_BitsManagerSendSOF();
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2520(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    
	LOC_enumRetVal = enum_BitsManagerSendEOD();
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2521(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    
	LOC_enumRetVal = enum_BitsManagerSendSOF();
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}

void test_CCO_TC_UT_2522(void)
{
	/* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    
	LOC_enumRetVal = enum_BitsManagerSendEOD();
	
	TEST_ASSERT_EQUAL_INT(LOC_enumRetVal,NOT_VALID_BITS_MANAGER);
}


