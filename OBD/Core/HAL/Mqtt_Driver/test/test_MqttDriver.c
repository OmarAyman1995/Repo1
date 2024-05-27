#include "unity.h"
#include "string.h"
#include "mock_MQTTPacket.h"
#include "mock_MQTTFormat.h"
#include "mock_MQTTSubscribe.h"
#include "mock_MQTTConnect.h"
#include "mock_MQTTUnsubscribe.h"
#include "mock_MQTTPublish.h"
#include "mock_MQTT_Mcal_Interface.h"
#include "mock_SIM800Handling.h"
#include "MQTTSim800.h"

extern u8_t GLOB_arrUartRx_Buffer[100];
extern u8_t GLOB_arrmqtt_buffer[100];
extern u16_t GLOB_u16mqtt_index;
extern SIM800_t GLOB_strSIM800;

void setUp(void){
    vid_Mqtt_Delay_Ignore();
    u8_Mqtt_UartReceiveIT_IgnoreAndReturn(1);
    u8_Mqtt_UartTransmit_IgnoreAndReturn(1);
    vid_Mqtt_GpioWrite_ResetPin_Ignore();
    MQTTSerialize_connect_IgnoreAndReturn(0);
}


// test initialize sequence in valid scenario
void test_case_0001(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1);
    u8_t returnVal = 0;

    // act
    returnVal = u8_MQTT_Init();

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, returnVal);

    // cleanUp

}


// test initialize sequence ATE0 fails
void test_case_0002(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(0); // ATE0 fails
    u8_t returnVal = 0;

    // act
    returnVal = u8_MQTT_Init();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, returnVal);

    // cleanUp

}


// test publish
void test_case_0003(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1);
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    u8_t returnVal = 0;

    // act
    u8_MQTT_Connect();
    returnVal = u8_MQTT_Publish("testtopic","testpayload",strlen("testpayload"));

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, returnVal);

    // cleanUp

}

// test publish with null
void test_case_0004(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    u8_t returnVal = 0;

    // act
    u8_MQTT_Connect();
    returnVal = u8_MQTT_Publish(NULLPTR,"testpayload",strlen("testpayload"));

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, returnVal);

    // cleanUp

}

// test subscribe
void test_case_0005(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    u8_t returnVal = 0;

    // act
    returnVal = u8_Mqtt_Subscribe("testtopic");

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, returnVal);

    // cleanUp

}

// test subscribe with topic name exceeds 10
void test_case_0006(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    u8_t returnVal = 0;

    // act
    returnVal = u8_Mqtt_Subscribe("testtopic with large name");

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, returnVal);

    // cleanUp

}

// test subscribe with null topic
void test_case_0007(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    u8_t returnVal = 0;

    // act
    returnVal = u8_Mqtt_Subscribe(NULLPTR);

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, returnVal);

    // cleanUp

}

// test connect
void test_case_0008(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    u8_SIM800_SendCommand_IgnoreAndReturn(1); 
    MQTTSerialize_publish_IgnoreAndReturn(1);
    u8_t returnVal = 0;

    // act
    returnVal = u8_MQTT_Connect();

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, returnVal);

    // cleanUp

}


// test connect but conncet fail
void test_case_0009(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(0); // make conncet fail
    u8_SIM800_SendPattern_IgnoreAndReturn(0);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    u8_t returnVal = 0;

    // act
    returnVal = u8_MQTT_Connect();

    // assert
    TEST_ASSERT_EQUAL_CHAR(0, returnVal);

    // cleanUp
    GLOB_strSIM800.mqttServer.connect = 0;
}


/* TODO module test of Manage function */
// test that connection is closed
void test_case_0010(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); // make conncet fail
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    MQTTSerialize_subscribe_IgnoreAndReturn(60); // won't matter
    u8_t returnVal = 0;
    
    // act
    vid_Mqtt_Manage(); // let the driver be initialized and connected
    TEST_ASSERT_EQUAL_CHAR(1, GLOB_strSIM800.mqttServer.connect);

    strcpy(GLOB_arrUartRx_Buffer, "CLOSED\r\n"); // pretend that driver received "CLOSED" from uart
    
    vid_Mqtt_Manage();
    TEST_ASSERT_EQUAL_CHAR(0, GLOB_strSIM800.mqttServer.connect);

    // assert

    // cleanUp
    GLOB_strSIM800.mqttServer.connect = 0;

}


// test that Manage function did subscribe to "test"
void test_case_0011(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); // make conncet fail
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    MQTTSerialize_subscribe_IgnoreAndReturn(60); // won't matter
    u8_t returnVal = 0;
    returnVal = u8_Mqtt_Subscribe("test");
    // act
    vid_Mqtt_Manage(); // let the driver be initialized and connected, then subscribe to "test"

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, GLOB_strSIM800.mqttServer.subscribe_state);
    TEST_ASSERT_EQUAL_CHAR(1, u8_Mqtt_isConnnected());
    TEST_ASSERT_EQUAL_CHAR(1, returnVal);

    // cleanUp

}


// test that Manage function did receive new message from cloud
void test_case_0012(void){

    // setup
    u8_SIM800_SendCommand_IgnoreAndReturn(1); // make conncet fail
    u8_SIM800_SendPattern_IgnoreAndReturn(1);
    MQTTSerialize_publish_IgnoreAndReturn(1);
    MQTTSerialize_subscribe_IgnoreAndReturn(60); // number won't matter
    MQTTDeserialize_publish_IgnoreAndReturn(60); // won't matter
    vid_Mqtt_SetUartCallback_Ignore();
    
    u8_t newMessage[] = {48, 9, 0, 4, 't', 'e', 's', 't', 'h', 'i'};
    u8_t recevied_message[50] = {0};
    u32_t received_size = 0;

    strcpy(GLOB_arrmqtt_buffer, newMessage); // pretend that driver received new mqtt-packet "hi" from a cloud server
    GLOB_u16mqtt_index = 12;

    void myCallback(u8_t *message, u32_t size){
        printf("message: %s, size: %ld\n", message, size);
        strncpy(recevied_message, message, size);
        received_size = size;
        TEST_ASSERT_EQUAL_CHAR(1, GLOB_strSIM800.mqttReceive.newEvent);
    }

    vid_Mqtt_SetCallback(myCallback);

    // act
    vid_Mqtt_Manage(); // let the driver be initialized and connected

    // assert
    TEST_ASSERT_EQUAL_CHAR(1, GLOB_strSIM800.mqttServer.connect);
    TEST_ASSERT_EQUAL_CHAR(1, GLOB_strSIM800.mqttServer.subscribe_state);

    // TEST_ASSERT_EQUAL_STRING("test", GLOB_strSIM800.mqttReceive.topic);
    // TEST_ASSERT_EQUAL_UINT32(4, GLOB_strSIM800.mqttReceive.topicLen);
    // TEST_ASSERT_EQUAL_STRING("hi", GLOB_strSIM800.mqttReceive.payload);
    // TEST_ASSERT_EQUAL_UINT32(2, GLOB_strSIM800.mqttReceive.payloadLen);
    // TEST_ASSERT_EQUAL_STRING("hi", recevied_message);
    // TEST_ASSERT_EQUAL_UINT32(2, received_size);

    // cleanUp
    GLOB_strSIM800.mqttServer.connect = 0;

}