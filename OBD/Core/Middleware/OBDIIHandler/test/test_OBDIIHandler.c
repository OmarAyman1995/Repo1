#include "unity.h"
#include "mock_CANTp.h"
#include "mock_ISO_Uart_Protocols.h"
#include "mock_CAN_ISO_15765.h"
#include "OBDIIHandler.h"

// testing initializing OBDIIHandler
void testcase0001(void){

    // Setup
    bool init_retval = 0;
    vid_CanIsoSetTransmitCallBack_Ignore();
    vid_CanIsoSetReceiveCallBack_Ignore();
    enum_DetectCANComm_IgnoreAndReturn(1);
    // Act
    OBDII_Initialize();
    init_retval = OBDII_DetectVehicleProtocol();

    // Assert
    TEST_ASSERT_TRUE(init_retval);
    // Cleanup
}

// testing initializing OBDIIHandler with fail scenario
void testcase0002(void){

    // Setup
    bool init_retval = 0;
    enum_DetectCANComm_IgnoreAndReturn(0);
    u8_UartISO_InitSequence_IgnoreAndReturn(1);
    // Act
    init_retval = OBDII_DetectVehicleProtocol();

    // Assert
    TEST_ASSERT_TRUE(init_retval);
    // Cleanup
}

// testing initializing OBDIIHandler with fail scenario
void testcase0040(void){

    // Setup
    bool init_retval = 0;
    enum_DetectCANComm_IgnoreAndReturn(0);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    // Act
    init_retval = OBDII_DetectVehicleProtocol();

    // Assert
    TEST_ASSERT_FALSE(init_retval);
    // Cleanup
}

// testing transmit of OBDIIHandler
void testcase0003(void){

    // Setup
    bool transmit_retval = 0;

    // Act
    u8_UartISO_Send_IgnoreAndReturn(1);
    transmit_retval = OBDIIRequestMode1(PID_VEHICLE_SPEED);
    
    // Assert
    TEST_ASSERT_EQUAL_INT(1, transmit_retval);



    // Cleanup
}

// testing transmit of OBDIIHandler
void testcase0004(void){

    // Setup
    bool transmit_retval = 0;


    u8_UartISO_Send_IgnoreAndReturn(0);

    // Act
    transmit_retval = OBDIIRequestMode1(PID_VEHICLE_SPEED);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, transmit_retval);



    // Cleanup
}

// testing transmit of OBDIIHandler but pass wrong message id
void testcase0005(void){

    // Setup
    bool transmit_retval = 0;
    u8_t wrong_msgid = 202;

    u8_UartISO_Send_IgnoreAndReturn(1);

    // Act
    transmit_retval = OBDIIRequestMode1(wrong_msgid);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, transmit_retval);



    // Cleanup
}

// testing receive of OBDIIHandler
void testcase0006(void){

    // Setup
    u8_t receive_retval = 0;
    OBDResponse_s resp = {0};
    // Act
    receive_retval = OBDIIReceiveResponse(&resp);

    // Assert
    TEST_ASSERT_TRUE(receive_retval);


    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0007(void){

    // Setup
    u8_t receive_retval = 0;
    OBDResponse_s resp = {0};
    // Act
    receive_retval = OBDIIReceiveResponse(NULLPTR);

    // Assert
    TEST_ASSERT_FALSE(receive_retval);


    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0008(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_OK);
    // Act
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode1(PID_VEHICLE_SPEED);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_TRUE(init_retva2);

    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0009(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_OK);
    // Act
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode2(PID_VEHICLE_SPEED, 123);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_TRUE(init_retva2);

    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0010(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    bool init_retva3 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_OK);
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetTxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode2(202, 123);
    init_retva3 = OBDIIRequestModeDTCs(SHOW_DTCS);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_FALSE(init_retva2);
    TEST_ASSERT_TRUE(init_retva3);

    // Cleanup
}


// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0011(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_OK);
    vid_IsoTpSet_Ignore();
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetTxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode9(VI_SUPPORTED_PIDS);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_TRUE(init_retva2);

    // Cleanup
}


// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0012(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_OK);
    vid_IsoTpSet_Ignore();
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetTxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode9(80);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_FALSE(init_retva2);

    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0013(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(1);
    u8_UartISO_InitSequence_IgnoreAndReturn(0);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_NOK);
    vid_IsoTpSet_Ignore();
    CanIsoReceive_Ignore();
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetTxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode9(VI_SUPPORTED_PIDS);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_FALSE(init_retva2);

    OBDII_TxCplt();
    OBDII_RxCplt();
    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0014(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(0);
    u8_UartISO_InitSequence_IgnoreAndReturn(1);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_NOK);
    vid_IsoTpSet_Ignore();
    u8_UartISO_Receive_IgnoreAndReturn(1);
    u8_UartISO_Send_IgnoreAndReturn(0);
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetRxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode9(VI_SUPPORTED_PIDS);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_FALSE(init_retva2);

    OBDII_TxCplt();
    OBDII_RxCplt();
    // Cleanup
}

// testing receive of OBDIIHandler but status isn't OBDII_RESPONSE_CPLT
void testcase0015(void){

    // Setup
    bool init_retval = 0;
    bool init_retva2 = 0;
    enum_DetectCANComm_IgnoreAndReturn(0);
    u8_UartISO_InitSequence_IgnoreAndReturn(1);
    enum_CanIsoSendData_IgnoreAndReturn(CAN_ISO_NOK);
    vid_IsoTpSet_Ignore();
    u8_UartISO_Receive_IgnoreAndReturn(1);
    u8_UartISO_Send_IgnoreAndReturn(1);
    void vidFunc(void){

    }
    // Act
    OBDII_SetTxCallback(vidFunc);
    OBDII_SetRxCallback(vidFunc);
    init_retval = OBDII_DetectVehicleProtocol();
    init_retva2 = OBDIIRequestMode9(VI_SUPPORTED_PIDS);

    TEST_ASSERT_TRUE(init_retval);
    TEST_ASSERT_TRUE(init_retva2);

    OBDII_TxCplt();
    OBDII_RxCplt();
    // Cleanup
}

