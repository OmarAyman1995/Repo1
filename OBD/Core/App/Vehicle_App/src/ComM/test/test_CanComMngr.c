#include "unity.h"
#include "CanComCommonDataTypes.h"
#include "CanComMngr.h"
#include "Subscribers.h"
#include "mock_ReceiveQueue.h"
#include "mock_Com_SM.h"
#include "mock_TransmitQueue.h"
#include "mock_ComAL.h"

/* 
Test Cases Coverage Table:
    testcase0001: DDD-OBDCAN-0030
    testcase0002: DDD-OBDCAN-0032
*/

void setUp(void) {
    transmit_queue_create_IgnoreAndReturn(1);
    receive_queue_create_IgnoreAndReturn(1);
    receive_queue_enqueue_Ignore();
    state_machine_init_Ignore();
    state_machine_switchto_Ignore();
    state_machine_run_Ignore();
    ComAL_transmit_Ignore();
    ComAL_set_transmitCallback_Ignore();
    ComAL_set_receiveCallback_Ignore();
    ComAL_Processing_Ignore();
}

void emptyNotifyFunc(ComData_t* com_data, TypeOfNotification_t notification_type){

}

// testing initialize of the module, shouldn't go runtime error
void testcase0001(void){
    
    // Setup
    ComM_StatusTypeDef retval = 0;

    // Act
    retval = enum_Comm_init();

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_INIT_OK, retval);

    // Cleanup
}


// testing subscribing
void testcase0002(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    u8_t database_size = 0;
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(55, emptyNotifyFunc);
    database_size = u8_database_getsize();

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_INIT_OK, retval_init);
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK, retval_subscribe);
    TEST_ASSERT_EQUAL_INT(1, database_size);

    // Cleanup
    vid_database_removeSubscription(55);
}


// testing subscribing but exist id
void testcase0003(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    u8_t database_size = 0;
    
    // Act
    retval_init = enum_Comm_init();
    enum_Comm_subscribe(55, emptyNotifyFunc);
    retval_subscribe = enum_Comm_subscribe(55, emptyNotifyFunc);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_INIT_OK, retval_init);
    TEST_ASSERT_EQUAL_INT(ID_TAKEN, retval_subscribe);
    TEST_ASSERT_EQUAL_INT(0, database_size);

    // Cleanup
    vid_database_removeSubscription(55);
}


// testing subscribing but NULLPTR notifyfunc
void testcase0004(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    u8_t database_size = 0;
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(55, NULLPTR);
    database_size = u8_database_getsize();

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_INIT_OK, retval_init);
    TEST_ASSERT_EQUAL_INT(NOTIFY_FUNC_ARG_INVALID, retval_subscribe);
    TEST_ASSERT_EQUAL_INT(0, database_size);

    // Cleanup
    vid_database_removeSubscription(55);
}


// testing subscribing but database is full
void testcase0005(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    u8_t database_size = 0;
    
    // Act
    retval_init = enum_Comm_init();
    for(u8_t i = 0; i < SUBSCRIBERS_MAXSIZE; i++){
        enum_Comm_subscribe(i + 10, emptyNotifyFunc);
    }
 
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    database_size = u8_database_getsize();

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_INIT_OK, retval_init);
    TEST_ASSERT_EQUAL_INT(SUBSCRIBERS_REACHED_MAX, retval_subscribe);
    TEST_ASSERT_EQUAL_INT(SUBSCRIBERS_MAXSIZE, database_size);

    // Cleanup
    for(u8_t i = 0; i < SUBSCRIBERS_MAXSIZE; i++){
        vid_database_removeSubscription(i + 10);
    }
    
    
}


// testing setrequest after subscribing 
void testcase0006(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_request = 0;
    Comm_DataTypedef can_request = {.com_data = {0},
                                  .subscriber_id = 66};
    transmit_queue_enqueue_Ignore();
    transmit_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    retval_request = enum_Comm_setRequest(&can_request);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(COM_SETREQUEST_OK,retval_request);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing setrequest but without subscribe
void testcase0007(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_request = 0;
    Comm_DataTypedef can_request = {.com_data = {0},
                                  .subscriber_id = 66};
    transmit_queue_enqueue_Ignore();
    transmit_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_request = enum_Comm_setRequest(&can_request);

    // Assert
    TEST_ASSERT_EQUAL_INT(NOT_SUBSCRIBED,retval_request);

    // Cleanup
}


// testing setrequest but null can_request pointer
void testcase0008(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_request = 0;
    Comm_DataTypedef can_request = {.com_data = {0},
                                  .subscriber_id = 66};
    transmit_queue_enqueue_Ignore();
    transmit_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    retval_request = enum_Comm_setRequest(NULLPTR);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(CAN_TRANSMIT_ARG_INVALID,retval_request);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing setrequest but transmit queue is full
void testcase0099(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_request = 0;
    Comm_DataTypedef can_request = {.com_data = {0},
                                  .subscriber_id = 66};
    transmit_queue_enqueue_Ignore();
    transmit_queue_isfull_IgnoreAndReturn(1);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);

    retval_request = enum_Comm_setRequest(&can_request);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(TRANSMIT_QUEUE_FULL,retval_request);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing expectresponse after subscribing
void testcase0009(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_response = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
    receive_queue_enqueue_Ignore();
    receive_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    retval_response = enum_Comm_setResponse(&can_receive);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(COM_EXPECTRECEIVE_OK, retval_response);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing expectresponse but not subscribed
void testcase0010(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_response = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
     (CAN_OK);
    receive_queue_enqueue_Ignore();
    receive_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_response = enum_Comm_setResponse(&can_receive);

    // Assert
    TEST_ASSERT_EQUAL_INT(NOT_SUBSCRIBED, retval_response);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing expectresponse but null can_receive
void testcase0011(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_response = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
     (CAN_OK);
    receive_queue_enqueue_Ignore();
    receive_queue_isfull_IgnoreAndReturn(0);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    retval_response = enum_Comm_setResponse(NULLPTR);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(CAN_RECEIVE_ARG_INVALID, retval_response);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing expectresponse but full receive queueu
void testcase0012(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComM_StatusTypeDef retval_response = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
     (CAN_OK);
    receive_queue_enqueue_Ignore();
    receive_queue_isfull_IgnoreAndReturn(1);
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    enum_Comm_setResponse(&can_receive);
    enum_Comm_setResponse(&can_receive);
    enum_Comm_setResponse(&can_receive);
    enum_Comm_setResponse(&can_receive);
    enum_Comm_setResponse(&can_receive);
    retval_response = enum_Comm_setResponse(&can_receive);

    // Assert
    TEST_ASSERT_EQUAL_INT(COM_SUBSCRIBE_OK,retval_subscribe);
    TEST_ASSERT_EQUAL_INT(RECEIVE_QUEUE_FULL, retval_response);

    // Cleanup
    vid_database_removeSubscription(66);
}


// testing main in IDLE state
void testcase0013(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComStatus_e  retval_main = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
     (CAN_OK);
    receive_queue_enqueue_Ignore();
    receive_queue_isempty_IgnoreAndReturn(0);
    transmit_queue_isempty_IgnoreAndReturn(0);
    receive_queue_isfull_IgnoreAndReturn(0);
    state_machine_switchto_Ignore();
    state_machine_run_Ignore();
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    determineState_IgnoreAndReturn(IDLE);
    retval_main = enum_Comm_main();

    // Assert
    TEST_ASSERT_EQUAL_INT(IDLE, retval_main);

    // Cleanup
    vid_database_removeSubscription(66);
    
}

// testing main in MAKE_TRANSMIT state
void testcase0014(void){
    
    // Setup
    ComM_StatusTypeDef retval_init = 0;
    ComM_StatusTypeDef retval_subscribe = 0;
    ComStatus_e  retval_main = 0;
    Comm_ReceiveTypedef can_receive = {.expected_canid = 0x7DF,
                                 .subscriber_id = 66};
     (CAN_OK);
    receive_queue_isempty_IgnoreAndReturn(0);
    transmit_queue_isempty_IgnoreAndReturn(0);
    receive_queue_isfull_IgnoreAndReturn(0);
    
    
    // Act
    retval_init = enum_Comm_init();
    retval_subscribe = enum_Comm_subscribe(66, emptyNotifyFunc);
    determineState_IgnoreAndReturn(TRANSMITTING_STATE);
    retval_main = enum_Comm_main();

    // Assert
    TEST_ASSERT_EQUAL_INT(TRANSMITTING_STATE, retval_main);

    // Cleanup
    vid_database_removeSubscription(66);
    
}