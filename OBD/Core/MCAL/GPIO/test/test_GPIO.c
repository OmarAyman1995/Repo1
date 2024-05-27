#include <unity.h>
#include "GPIO.h"
#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_gpio.h"

PUBLIC u8_t u8InitDoneFlag;
/*---- not init yet !---*/
void test_CCO_TC_UT_2045(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	HAL_GPIO_WritePin_CMockIgnore();
	LOC_enumRet = enum_GpioWritePin((( GPIO_TypeDef*)(0x40000000)),0x0009,GPIO_PIN_SET);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
}

/*---- not init yet !---*/
void test_CCO_TC_UT_2046(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	HAL_GPIO_TogglePin_CMockIgnore();
	LOC_enumRet = enum_GpioTogglePin((( GPIO_TypeDef*)(0x40000000)),0x0008);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
} 


/*---- not init yet !---*/
void test_CCO_TC_UT_2047(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	vid_GpioManage();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
}


/*---- not init yet !---*/
void test_CCO_TC_UT_2048(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	HAL_GPIO_ReadPin_CMockIgnoreAndReturn(79,1);
	LOC_enumRet = enum_GpioReadPin((( GPIO_TypeDef*)(0x40000000)),0x0008,&PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
} 

/*---- not init yet !---*/
void test_CCO_TC_UT_2049(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	HAL_GPIO_Init_CMockIgnore();
	vid_GpioInitUnusedPins();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
} 

/*---- not init yet !---*/
void test_CCO_TC_UT_2050(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	HAL_GPIO_Init_CMockIgnore();
	vid_GpioInitUsedPins();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
} 

/*---- after init  !---*/
void test_CCO_TC_UT_2051(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_Init_CMockIgnore();
	vid_GpioInitUnusedPins();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 

/*---- after init  !---*/
void test_CCO_TC_UT_2052(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_Init_CMockIgnore();
	vid_GpioInitUsedPins();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 




/* --GPIOx=NULL-- */
void test_CCO_TC_UT_2054(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_ReadPin_CMockIgnoreAndReturn(79,1);
	LOC_enumRet = enum_GpioReadPin(NULL,0x0008,&PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 


/* --u16Pinx >0x8000-- */
void test_CCO_TC_UT_2055(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_ReadPin_CMockIgnoreAndReturn(79,1);
	LOC_enumRet = enum_GpioReadPin((( GPIO_TypeDef*)(0x40000000)),0x9000,&PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 

/* --enumPinState = NULL -- */
void test_CCO_TC_UT_2056(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_ReadPin_CMockIgnoreAndReturn(79,1);
	LOC_enumRet = enum_GpioReadPin((( GPIO_TypeDef*)(0x40000000)),0x0200,NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

/* -- TRUE -- */
void test_CCO_TC_UT_2057(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_ReadPin_CMockIgnoreAndReturn(79,1);
	LOC_enumRet = enum_GpioReadPin((( GPIO_TypeDef*)(0x40000000)),0x0010,&PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

/* --GPIOx=NULL-- */
void test_CCO_TC_UT_2058(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_WritePin_CMockIgnore();
	LOC_enumRet = enum_GpioWritePin(NULL,0x0008,PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 

/* --u16Pinx >0x8000-- */
void test_CCO_TC_UT_2059(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_WritePin_CMockIgnore();
	LOC_enumRet = enum_GpioWritePin((( GPIO_TypeDef*)(0x40000000)),0x9000,PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
} 

/* -- TRUE -- */
void test_CCO_TC_UT_2060(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_WritePin_CMockIgnore();
	LOC_enumRet = enum_GpioWritePin((( GPIO_TypeDef*)(0x40000000)),0x0010,PinState);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

/* --GPIOx=NULL-- */
void test_CCO_TC_UT_2061(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_TogglePin_CMockIgnore();
	LOC_enumRet = enum_GpioTogglePin(NULL,0x9000);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

/* --u16Pinx >0x8000-- */
void test_CCO_TC_UT_2062(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_TogglePin_CMockIgnore();
	LOC_enumRet = enum_GpioTogglePin((( GPIO_TypeDef*)(0x40000000)),0x9000);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

/* -- TRUE -- */
void test_CCO_TC_UT_2063(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	GPIO_PinState PinState =  GPIO_PIN_RESET ;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	HAL_GPIO_TogglePin_CMockIgnore();
	LOC_enumRet = enum_GpioTogglePin((( GPIO_TypeDef*)(0x40000000)),0x0010);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_GPIO);

	/*-- CLEAR GLOBs*/
	u8InitDoneFlag = 0 ;
}

void test_CCO_TC_UT_2064(void)
{
	enumRetGpio_e LOC_enumRet = NOT_VALID_GPIO;
	MX_GPIO_Init_CMockIgnore();
	enum_GpioInit();
	for(int i = 1 ; i<=9 ; i++)
	{
		HAL_GPIO_Init_CMockIgnore();
	} 
	
	vid_GpioManage();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_GPIO);
}