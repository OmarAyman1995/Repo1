#include "unity.h"
#include "string.h"
#include "BluetoothCommands.h"
// #include "mock_Uart_Integration.h"
#include "mock_Bluetooth_MCAL_Interface.h"


void setUp(void){
    // enum_Uart_Integration_Send_IgnoreAndReturn(UART_OK);
    // enum_Uart_Integration_RecvPOLL_IgnoreAndReturn(UART_OK);
    BlUartSend_Ignore();
    BlUartRecv_Ignore();
}


// testing  sending command
void testcase0001(void){
    // setup
    
    u8_t ret = 0;
    u8_t *pCommand = "AT+PASSWORD\r\n";
    
    // act
    ret = u8_Bluetooth_SendCmnd(pCommand);

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}

void testcase0002(void){
    // setup
    u8_t ret = 0;
    
    // act
    ret = u8_Bluetooth_SendCmnd(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}

// testing receiving
void testcase0003(void){
    // setup
    u8_t ret = 0;
    u8_t *pCommand = "AT+PASSWORD\r\n";
    
    // act
    ret = u8_Bluetooth_ReceiveCmnd(pCommand);

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}

void testcase0004(void){
    // setup
    u8_t ret = 0;
    
    // act
    ret = u8_Bluetooth_ReceiveCmnd(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}


void testcase0005(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    // act
    ret = u8_Bluetooth_SetDeviceName("mohame");

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}


void testcase0006(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_SetDeviceName(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}

void testcase00111(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(0);
    
    // act
    ret = u8_Bluetooth_SetDeviceName("mohame");

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}


void testcase0007(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_SetBaudrate("115200");

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}



void testcase0008(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_SetBaudrate(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}

void testcase0108(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(0);
    
    // act
    ret = u8_Bluetooth_SetBaudrate("115200");

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}



void testcase0009(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_ResetBoard();

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}



void testcase0029(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(0);
    
    // act
    ret = u8_Bluetooth_ResetBoard();

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}



void testcase0014(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_SetPassword("7841");

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}


void testcase0015(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(0);
    
    // act
    ret = u8_Bluetooth_SetPassword("7841");

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}



void testcase0016(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_SetPassword(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}


void testcase0017(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(1);
    
    // act
    ret = u8_Bluetooth_RestoreToOrigin();

    // assert
    TEST_ASSERT_EQUAL_INT(1, ret);

    // cleanup
}




void testcase0018(void){
    // setup
    u8_t ret = 0;
    BLCompareString_IgnoreAndReturn(0);
    
    // act
    ret = u8_Bluetooth_RestoreToOrigin();

    // assert
    TEST_ASSERT_EQUAL_INT(0, ret);

    // cleanup
}


