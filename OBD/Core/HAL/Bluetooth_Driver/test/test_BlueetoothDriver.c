#include "unity.h"
#include "string.h"
#include "BluetoothDrv.h"
#include "mock_BluetoothCommands.h"
#include "mock_Bluetooth_MCAL_Interface.h"


void setUp(void){
    // empty for now
    BlGpioSet_Ignore();
    BlGpioReset_Ignore();
    BlUartInit38400_Ignore();
    BlUartInit115200_Ignore();
    BlUartSend_Ignore();
    BlUartSetCallback_Ignore();
    BlUartRecvIT_Ignore();
    BlUartAbort_Ignore();

}



void printtest(void){
        printf("test");
}

void cleanup(void){

}
// testing init funciton
void testcase0001(void){

    // setup
    u8_Bluetooth_SetDeviceName_IgnoreAndReturn(1);
    u8_Bluetooth_SetPassword_IgnoreAndReturn(1);
    u8_Bluetooth_SetBaudrate_IgnoreAndReturn(1);
    u8_Bluetooth_ResetBoard_IgnoreAndReturn(1);

    u8_t init_return_value = 0;
    Bluetooth_Config_t configs = {0};
    strcpy(configs.device_name, "CrewCopilot");
    strcpy(configs.baudrate, "115200");
    strcpy(configs.pass, "1234");

    // act
    init_return_value = u8_Bluetooth_Init(&configs);

    // assert
    TEST_ASSERT_EQUAL_INT(1, init_return_value);
    // cleanup
}

void testcase0002(void){

    // setup
    u8_Bluetooth_SetDeviceName_IgnoreAndReturn(1);
    u8_Bluetooth_SetPassword_IgnoreAndReturn(1);
    u8_Bluetooth_SetBaudrate_IgnoreAndReturn(1);
    u8_Bluetooth_ResetBoard_IgnoreAndReturn(1);

    u8_t init_return_value = 0;
    Bluetooth_Config_t configs = {0};
    strcpy(configs.device_name, "CrewCopilot");
    strcpy(configs.baudrate, "115200");
    strcpy(configs.pass, "1234");

    // act
    init_return_value = u8_Bluetooth_Init(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(0, init_return_value);
    // cleanup
}

void testcase0003(void){

    // setup
    u8_Bluetooth_SetDeviceName_IgnoreAndReturn(1);
    u8_Bluetooth_SetPassword_IgnoreAndReturn(1);
    u8_Bluetooth_SetBaudrate_IgnoreAndReturn(1);
    u8_Bluetooth_ResetBoard_IgnoreAndReturn(0);

    u8_t init_return_value = 0;
    Bluetooth_Config_t configs = {0};
    strcpy(configs.device_name, "CrewCopilot");
    strcpy(configs.baudrate, "115200");
    strcpy(configs.pass, "1234");

    // act
    init_return_value = u8_Bluetooth_Init(&configs);

    // assert
    TEST_ASSERT_EQUAL_INT(0, init_return_value);

    // cleanup
}

// testing send function
void testcase0004(void){
    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";
    // act
    send_return_value = u8_Bluetooth_Send(pData, strlen(pData));

    // assert
    TEST_ASSERT_EQUAL_INT(1, send_return_value);

    // cleanup
    cleanup();
}


void testcase0011(void){
    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";
    // act
    send_return_value = u8_Bluetooth_Send(NULL, strlen(pData));

    // assert
    TEST_ASSERT_EQUAL_INT(0, send_return_value);

    // cleanup
    cleanup();
}

void testcase0012(void){
    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";
    // act
    send_return_value = u8_Bluetooth_Send(pData, 0);

    // assert
    TEST_ASSERT_EQUAL_INT(0, send_return_value);

    // cleanup
    cleanup();
}

// testing getting connectivity
void testcase0006(void){
    // setup
    u8_t getConnectivityStatus_return_value = 0;
    BlGpioRead_IgnoreAndReturn(1);
    // act
    getConnectivityStatus_return_value = u8_Bluetooth_getConnectivityStatus();

    // assert
    TEST_ASSERT_EQUAL_INT(1, getConnectivityStatus_return_value);

    // cleanup
    cleanup();
}

void testcase0007(void){
    // setup
    u8_t getConnectivityStatus_return_value = 0;
    BlGpioRead_IgnoreAndReturn(0);
    // act
    getConnectivityStatus_return_value = u8_Bluetooth_getConnectivityStatus();

    // assert
    TEST_ASSERT_EQUAL_INT(0, getConnectivityStatus_return_value);

    // cleanup
    cleanup();
}

// testing receive
void testcase0013(void){

    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";

    // act
    send_return_value = u8_Bluetooth_Receive(pData, strlen(pData));
    vid_Bluetooth_AbortReceive();
    // assert
    TEST_ASSERT_EQUAL_INT(1, send_return_value);

    // cleanup
    cleanup();
}


void testcase0015(void){

    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";

    // act
    send_return_value = u8_Bluetooth_Receive(NULL, strlen(pData));

    // assert
    TEST_ASSERT_EQUAL_INT(0, send_return_value);

    // cleanup
    cleanup();
}

void testcase0017(void){

    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";

    // act
    send_return_value = u8_Bluetooth_Receive(pData, 0);

    // assert
    TEST_ASSERT_EQUAL_INT(0, send_return_value);

    // cleanup
    cleanup();
}

void testcase0016(void){

    
    // setup
    u8_t send_return_value = 0;
    u8_t *pData = "testing";

    // act
    vid_Bluetooth_setCallback(printtest);

    // assert
    TEST_ASSERT_EQUAL_INT(0, send_return_value);

    // cleanup
    cleanup();
}
