#include <unity.h>
#include "UART.h"

#include "mock_main.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_uart.h"
#include "mock_stm32f1xx_hal_cortex.h"

void test_CCO_TC_UT_2150(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(14,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1RecData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}
void test_CCO_TC_UT_2151(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(24,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2RecData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2152(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(35,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3RecData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2153(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(46,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1RecITData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}
void test_CCO_TC_UT_2154(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(56,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2RecITData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2155(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(67,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3RecITData(u8DataToRec, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}




void test_CCO_TC_UT_2177(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(81,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2178(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(81,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2179(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(81,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2180(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(115,HAL_OK);

	LOC_enumRet = 	enum_uartInit(UART_CHANNEL_1,115500);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2181(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(127,HAL_OK);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_1,BAUD_RATE_9600);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}
void test_CCO_TC_UT_2182(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(137,HAL_ERROR);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_2,BAUD_RATE_9600);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2183(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(148,HAL_OK);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_3,BAUD_RATE_10400);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}
void test_CCO_TC_UT_2184(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(158,HAL_ERROR);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_1,BAUD_RATE_10400);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2185(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(169,HAL_OK);	
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_2,BAUD_RATE_38400);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}
void test_CCO_TC_UT_2186(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(179,HAL_ERROR);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_3,BAUD_RATE_38400);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2187(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(190,HAL_OK);	
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_3,BAUD_RATE_115200);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}

void test_CCO_TC_UT_2188(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(201,HAL_ERROR);	
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_2,BAUD_RATE_115200);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2189(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(213,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1SendData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2190(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(224,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1SendData(u8DataToSend, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2191(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(235,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1SendData(u8DataToSend, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}


void test_CCO_TC_UT_2192(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(247,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2SendData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}
void test_CCO_TC_UT_2193(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(257,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2SendData(u8DataToSend, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2194(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(213,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2SendData(u8DataToSend, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}

void test_CCO_TC_UT_2195(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(279,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3SendData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}
void test_CCO_TC_UT_2196(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(289,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3SendData(u8DataToSend, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2197(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(300,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3SendData(u8DataToSend, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}




void test_CCO_TC_UT_2198(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(314,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2199(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(326,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2200(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(338,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}


void test_CCO_TC_UT_2201(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(350,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2RecData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2202(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(362,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2RecData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2203(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(374,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}



void test_CCO_TC_UT_2204(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(387,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2205(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(399,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2206(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(411,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}


void test_CCO_TC_UT_2207(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(423,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecITData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2208(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(435,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecITData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2209(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(447,HAL_OK);
	
	LOC_enumRet = 	enum_Uart1RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}


void test_CCO_TC_UT_2210(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(459,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2RecITData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2211(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(471,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2RecITData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2212(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(483,HAL_OK);
	
	LOC_enumRet = 	enum_Uart2RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}



void test_CCO_TC_UT_2213(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(496,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecITData(NULL, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2214(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(508,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecITData(u8DataToRec, 0);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2215(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(520,HAL_OK);
	
	LOC_enumRet = 	enum_Uart3RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}




PUBLIC pFunction pCallbackfuncUart1;
PUBLIC pFunction pCallbackfuncUart2 ;
PUBLIC pFunction pCallbackfuncUart3 ;

void callBack(void)
{

}



void test_CCO_TC_UT_2251(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(NULL,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2252(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart1,NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2253(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart1,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}

void test_CCO_TC_UT_2254(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart2;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(NULL,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2255(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart2;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart2,NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2256(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart2;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart2,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}


void test_CCO_TC_UT_2257(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart3;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(NULL,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2258(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart3;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart3,NULL);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2259(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart3;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart3,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}



void test_CCO_TC_UT_2260(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(638,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2261(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(650,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2262(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	const u8_t* u8DataToSend = "Data to send";
	HAL_UART_Transmit_CMockIgnoreAndReturn(662,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3SendData(u8DataToSend, 10);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}



void test_CCO_TC_UT_2263(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(675,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2264(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(686,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart2RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2265(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_CMockIgnoreAndReturn(697,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}


void test_CCO_TC_UT_2266(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(709,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart1RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2267(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(720,HAL_ERROR);
	
	
	LOC_enumRet = 	enum_Uart2RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2268(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	u8_t u8DataToRec[100] ;
	HAL_UART_Receive_IT_CMockIgnoreAndReturn(732,HAL_ERROR);
	
	LOC_enumRet = 	enum_Uart3RecITData(u8DataToRec, 20);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2269(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart1;
	HAL_NVIC_EnableIRQ_CMockIgnore();
	HAL_UART_Init_CMockIgnoreAndReturn(148,HAL_OK);
	
	LOC_enumRet = enum_uartInit(UART_CHANNEL_3+1,BAUD_RATE_10400);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

void test_CCO_TC_UT_2270(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart3;
	
	
	LOC_enumRet = enum_UartSetCallbackForReception(&huart3 + 0x0000000C,callBack);
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}

/* --- -- - Aborting - -- ---*/
void test_CCO_TC_UT_2271(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart2;
	
	HAL_UART_AbortReceive_IT_CMockIgnoreAndReturn(765,HAL_OK);
	
	LOC_enumRet = enum_Uart2AbortReceive();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,VALID_UART);
}

void test_CCO_TC_UT_2272(void)
{
	enumRetUart_e LOC_enumRet = UNKOWN_UART ; 
	PUBLIC UART_HandleTypeDef huart2;
	
	HAL_UART_AbortReceive_IT_CMockIgnoreAndReturn(765,HAL_ERROR);
	
	LOC_enumRet = enum_Uart2AbortReceive();
	TEST_ASSERT_EQUAL_INT(LOC_enumRet,NOT_VALID_UART);
}