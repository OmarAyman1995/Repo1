#include "unity.h"
#include "mock_PIDsDatabase.h"
#include "mock_ISO_Uart_MCAL_Interface.h"
#include "ISO_Uart_Protocols.h"

extern u8_t GLOB_u8UartByte;
extern u8_t GLOB_arrVehicleResponse[50];
extern u8_t GLOB_u8ResponseCounter;
extern u8_t GLOB_u8responseLength;

void setUp(void){
    IsoUartInit10400bps_Ignore();
    IsoUartInit5bps_Ignore();
}


// test fast initialize protocol 14230
void test_case_0001(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(1);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 14230
        data[0] = 0x55;
        data[1] = 0x08;
        data[2] = 0x8F; 
        return 1;

    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    // act
    checkInit = u8_fastInitialize();
    checkProtocol = u8_getUartProtocol();

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(1, checkProtocol);

    // cleanup

}

// test fast initialize but keybytes are wrong
void test_case_0002(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(1);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // wrong keybytes
        data[0] = 0x55;
        data[1] = 0;
        data[2] = 0;
        return 1;

    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    // act
    checkInit = u8_fastInitialize();
    checkProtocol = u8_getUartProtocol();
    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    // cleanup

}

// test fast initialize protocl 9141
void test_case_0003(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(1);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0x55;
        data[1] = 0x08;
        data[2] = 0x08;
        return 1;

    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    // act
    checkInit = u8_fastInitialize();
    checkProtocol = u8_getUartProtocol();
    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(2, checkProtocol);
    // cleanup

}


// test slow initialize protocol 14230
void test_case_0004(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(1);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0x55;
        data[1] = 0x08;
        data[2] = 0x08;
        return 1;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    // act
    checkInit = u8_slowInitialize();
    checkProtocol = u8_getUartProtocol();
    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(2, checkProtocol);
    // cleanup

}

// test fast initialize and vehicle didn't respond
void test_case_0005(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(0);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        return 0;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);

    // act
    checkInit = u8_fastInitialize();
    checkProtocol = u8_getUartProtocol();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    // cleanup

}

// test slow initialize and vehicle didn't respond
void test_case_0006(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(0);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        return 0;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);

    // act
    checkInit = u8_slowInitialize();
    checkProtocol = u8_getUartProtocol();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    // cleanup

}

// test slow initialize and vehicle didn't respond
void test_case_0017(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(0);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0x55;
        data[1] = 0;
        data[2] = 0;
        return 0;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);

    // act
    checkInit = u8_slowInitialize();
    checkProtocol = u8_getUartProtocol();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    // cleanup

}

// test slow initialize and vehicle didn't respond
void test_case_0018(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_UartSend_IgnoreAndReturn(0);
    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        return 0;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);

    // act
    checkInit = u8_UartISO_InitSequence();
    checkProtocol = u8_getUartProtocol();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    // cleanup

}

// test sending with protocol 14230
void test_case_0007(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_t checkSend = 0;
    u8_t ISO14230_frame[6] = {0xC2,0x33,0xF1,0x01,0x0d, 0xf4};

    u8_getReturnedBytes_IgnoreAndReturn(1);
    u8_UartReceiveIT_IgnoreAndReturn(1);
    u8_UartSend_IgnoreAndReturn(1);

    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 14230
        data[0] = 0x55;
        data[1] = 0x08;
        data[2] = 0x8f;
        return 1;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    checkInit = u8_fastInitialize();

    u8_t u8_UartSend_stubbing(u8_t *data, u32_t size, int x){
        // iso 14230
        TEST_ASSERT_EQUAL_MEMORY(ISO14230_frame, data, 6);
        return 1;
    }
    u8_UartSend_Stub(u8_UartSend_stubbing);

    // act
    checkProtocol = u8_getUartProtocol();
    checkSend = u8_UartISO_Send(0x01, 0x0d);
    
    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(1, checkProtocol);
    TEST_ASSERT_EQUAL_CHAR(1, checkSend);

    // cleanup

}

// test sending with protocol 9141
void test_case_0008(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_t checkSend = 0;
    u8_t ISO9141_frame[6] = {0x68,0x6A,0xF1,0x01,0x0d, 0xd1};

    u8_getReturnedBytes_IgnoreAndReturn(1);
    u8_UartReceiveIT_IgnoreAndReturn(1);
    u8_UartSend_IgnoreAndReturn(1);

    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0x55;
        data[1] = 0x08;
        data[2] = 0x08;
        return 1;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    checkInit = u8_fastInitialize();

    u8_t u8_UartSend_stubbing(u8_t *data, u32_t size, int x){
        // iso 14230
        TEST_ASSERT_EQUAL_MEMORY(ISO9141_frame, data, 6);
        return 1;
    }
    u8_UartSend_Stub(u8_UartSend_stubbing);
    
    // act
    checkProtocol = u8_getUartProtocol();
    checkSend = u8_UartISO_Send(0x01, 0x0d);
    
    // assert
    TEST_ASSERT_EQUAL_CHAR(1, checkInit);
    TEST_ASSERT_EQUAL_CHAR(2, checkProtocol);
    TEST_ASSERT_EQUAL_CHAR(1, checkSend);

    // cleanup

}

// test sending with protocol error
void test_case_0009(void){
    // setup
    u8_t checkInit = 0;
    u8_t checkProtocol = 0;
    u8_t checkSend = 0;
    u8_t ISO9141_frame[6] = {0x68,0x6A,0xF1,0x01,0x0d, 0xd1};

    u8_getReturnedBytes_IgnoreAndReturn(1);
    u8_UartReceiveIT_IgnoreAndReturn(1);
    u8_UartSend_IgnoreAndReturn(1);

    u8_t u8_UartReceive_stubbing(u8_t data[], u32_t size, int x){
        // iso 9141
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        return 1;
    }
    u8_UartReceive_Stub(u8_UartReceive_stubbing);
    checkInit = u8_fastInitialize();

    u8_t u8_UartSend_stubbing(u8_t *data, u32_t size, int x){
        // iso 14230
        TEST_ASSERT_EQUAL_MEMORY(ISO9141_frame, data, 6);
        return 1;
    }
    u8_UartSend_Stub(u8_UartSend_stubbing);
    
    // act
    checkProtocol = u8_getUartProtocol();
    checkSend = u8_UartISO_Send(0x01, 0x0d);
    
    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkInit);
    TEST_ASSERT_EQUAL_CHAR(0, checkProtocol);
    TEST_ASSERT_EQUAL_CHAR(0, checkSend);

    // cleanup

}

// test receiving
void test_case_0010(void){
    // setup
    u8_t checkProtocol = 0;
    u8_t checkReceive = 0;
    u8_t checkSend = 0;
    u8_t expectedBuffer[] = {3, 0x41 , 0xd , 0x54};

    u8_getReturnedBytes_IgnoreAndReturn(1);
    u8_UartReceiveIT_IgnoreAndReturn(1);
    u8_UartSend_IgnoreAndReturn(1);

    void mycallback(void){
        uint8_t buffer[25] = {0};
        checkReceive = u8_UartISO_Receive(buffer);
        // for(uint8_t i = 0; i < sizeof(buffer); i++){
        //     printf("%x ", buffer[i]);
        // }
        TEST_ASSERT_EQUAL_MEMORY(expectedBuffer, buffer, sizeof(expectedBuffer));
        TEST_ASSERT_EQUAL_CHAR(1, checkReceive);

    }
    vid_UartISO_RegisterCallback(mycallback);

    // act
    checkSend = u8_UartISO_Send(0x01, 0x0d);
    // printf("GLOB_u8responseLength %d\n", GLOB_u8responseLength);

    GLOB_u8UartByte = 0x83;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xf1;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x11;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x41;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xd;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x54;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xd3;
    vid_UartISO_MCALCallback();

    // printf("GLOB_u8ResponseCounter %d\n", GLOB_u8ResponseCounter);

    
    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkSend);

    // cleanup

}


// test receiving but null buffer
void test_case_0011(void){
    // setup
    u8_t checkProtocol = 0;
    u8_t checkReceive = 0;
    u8_t checkSend = 0;
    u8_t expectedBuffer[] = {0};

    u8_getReturnedBytes_IgnoreAndReturn(1);
    u8_UartReceiveIT_IgnoreAndReturn(1);
    u8_UartSend_IgnoreAndReturn(1);

    void mycallback(void){
        uint8_t buffer[25] = {0};
        checkReceive = u8_UartISO_Receive(NULLPTR);
        // for(uint8_t i = 0; i < sizeof(buffer); i++){
        //     printf("%x ", buffer[i]);
        // }
        TEST_ASSERT_EQUAL_CHAR(0, checkReceive);
        TEST_ASSERT_EQUAL_MEMORY(expectedBuffer, buffer, sizeof(expectedBuffer));

    }
    vid_UartISO_RegisterCallback(mycallback);

    // act
    checkSend = u8_UartISO_Send(0x01, 0x0d);
    // printf("GLOB_u8responseLength %d\n", GLOB_u8responseLength);

    GLOB_u8UartByte = 0x83;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xf1;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x11;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x41;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xd;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0x54;
    vid_UartISO_MCALCallback();
    GLOB_u8UartByte = 0xd3;
    vid_UartISO_MCALCallback();

    // printf("GLOB_u8ResponseCounter %d\n", GLOB_u8ResponseCounter);

    
    // assert
    TEST_ASSERT_EQUAL_CHAR(0, checkSend);

    // cleanup

}

