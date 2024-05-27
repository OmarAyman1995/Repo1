/*
 * MQTTSim800.c
 *
 *  Created on: Jan 4, 2020
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :   leech001@gmail.com
 * telegram :   https://t.me/leech001
 *
 */

/*
 * -----------------------------------------------------------------------------------------------------------------------------------------------
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2020 Bulanov Konstantin <leech001@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

  MQTT packet https://github.com/eclipse/paho.mqtt.embedded-c/tree/master/MQTTPacket
 * ------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include "MQTTSim800.h"
#include <string.h>

#define PATTERN_END 0x1A
#define START_OF_PUBLISH_PACKET 48

SIM800_t GLOB_strSIM800;
u8_t GLOB_arrUartRx_Buffer[100] = {0};
u8_t GLOB_arrmqtt_buffer[100] = {0};
u16_t GLOB_u16mqtt_index = 0;

PRIVATE u8_t GLOB_u8UartRx_oneByte = 0;
PRIVATE u16_t GLOB_u16UartRx_Index = 0;
PRIVATE u8_t GLOB_u8mqtt_receiveMode = 0;
PRIVATE MqttCallback GLOB_pUserCallback = NULLPTR;
PRIVATE u8_t GLOB_arrSubscription_Requests[MQTT_MAX_SUBS][MQTT_MAX_TOPIC_SIZE] = {0};
PRIVATE u8_t GLOB_u8Sub_Pos = 0;
PRIVATE u8_t GLOB_u8Subscribers_Number = 0;

PRIVATE u8_t u8_Subscribe(char *topic);
PRIVATE void vid_clearMqttBuffer(void);
PRIVATE void vid_MQTT_Receive(unsigned char *LOC_arr_tempBuffer);

void vid_clearRxBuffer(void); // not static because it is used in Sim800Handling





u8_t u8_Mqtt_Subscribe(u8_t *topic){
    u8_t LOC_u8_checkInput  = (GLOB_u8Sub_Pos != MQTT_MAX_SUBS) && (topic != NULLPTR);
    size_t LOC_u32_topicSize = 0;
    u8_t LOC_u8_retVal = 0;

    if(LOC_u8_checkInput == 1){
        LOC_u32_topicSize = strlen(topic);

        if(LOC_u32_topicSize < MQTT_MAX_TOPIC_SIZE){
            strncpy(GLOB_arrSubscription_Requests[GLOB_u8Sub_Pos], topic, LOC_u32_topicSize);
            ++GLOB_u8Sub_Pos;
            ++GLOB_u8Subscribers_Number;
            LOC_u8_retVal = 1;
        }else{
            LOC_u8_retVal = 0;
        }

    }else{
        LOC_u8_retVal = 0;
    }



    return LOC_u8_retVal;
}


void vid_Mqtt_Uart_Interrupt(void)
{
    GLOB_arrUartRx_Buffer[GLOB_u16UartRx_Index++] = GLOB_u8UartRx_oneByte;

    // new message from any subscribed topics event
    if ((GLOB_strSIM800.mqttServer.connect == 1) && (GLOB_u8UartRx_oneByte == START_OF_PUBLISH_PACKET)){
        GLOB_u8mqtt_receiveMode = 1;
    }

    if (GLOB_u8mqtt_receiveMode == 1){
        // receiving in another buffer other than GLOB_arrUartRx_Buffer
        GLOB_arrmqtt_buffer[GLOB_u16mqtt_index++] = GLOB_u8UartRx_oneByte;
    }

    // listen to another byte from UART
    u8_Mqtt_UartReceiveIT(&GLOB_u8UartRx_oneByte, 1);
}


void vid_Mqtt_Manage(void){
    static u8_t GLOB_u8_subscriptionTrials = 0;
    static u8_t GLOB_u8_checkInit = 0;
    static u8_t GLOB_u8_checkConnect = 0;
    u8_t LOC_u8_checkSubscription = 0;

    // make the initialize sequence of SIM800
    if(GLOB_strSIM800.mqttServer.connect == 0){
        
        if(GLOB_u8_checkInit == 0){
            GLOB_u8_checkInit = u8_MQTT_Init();
        }
        if((GLOB_u8_checkConnect == 0) && (GLOB_u8_checkInit == 1)){
            GLOB_u8_checkConnect = u8_MQTT_Connect();
        }
    }

    // tcp connection closed event
    if ( GLOB_strSIM800.mqttServer.connect == 1  ){
        if ( strstr((char *)GLOB_arrUartRx_Buffer, "CLOSED\r\n") != NULL ){
            GLOB_strSIM800.mqttServer.connect = 0; // reconnect to the cloud server
            GLOB_u8_checkConnect = 0;
            GLOB_u8Sub_Pos = GLOB_u8Subscribers_Number; // resubscribe to the queued topics
            vid_clearRxBuffer();
        }
    }

    // safe from overflow on GLOB_arrmqtt_buffer
    if (GLOB_u16UartRx_Index >= sizeof(GLOB_arrmqtt_buffer)){
        vid_clearRxBuffer();
        vid_clearMqttBuffer();
    }

    // check subscription queue
    if((GLOB_u8Sub_Pos > 0) && (GLOB_strSIM800.mqttServer.connect == 1)){
        LOC_u8_checkSubscription = u8_Subscribe(GLOB_arrSubscription_Requests[GLOB_u8Sub_Pos-1]);
        if(LOC_u8_checkSubscription == 1){
            --GLOB_u8Sub_Pos;
            GLOB_u8_subscriptionTrials = 0;
        }else{
            ++GLOB_u8_subscriptionTrials;
        }

        if(GLOB_u8_subscriptionTrials == MAX_SUBSCRIBE_TRIALS){
            GLOB_strSIM800.mqttServer.connect = 0; // cannot subscribe, reconnect to the cloud server
            GLOB_u8_checkConnect = 0;
        }
    }

    // check if any new message received to process it and route to the user callback
    if(GLOB_arrmqtt_buffer[0] == START_OF_PUBLISH_PACKET){
        if ((GLOB_u16mqtt_index > 1) && ((GLOB_u16mqtt_index - 1) > GLOB_arrmqtt_buffer[1])){
            vid_MQTT_Receive((unsigned char *)GLOB_arrmqtt_buffer);
            vid_clearRxBuffer();
            vid_clearMqttBuffer();
        }
        if (GLOB_u16mqtt_index >= sizeof(GLOB_arrmqtt_buffer)){
            vid_clearMqttBuffer();
        }
    }

    // check if new message received, call user callback function
    if(GLOB_strSIM800.mqttReceive.newEvent == 1){

        if(GLOB_pUserCallback != NULLPTR){
            GLOB_pUserCallback(GLOB_strSIM800.mqttReceive.payload, (u32_t)GLOB_strSIM800.mqttReceive.payloadLen);
        }
        GLOB_strSIM800.mqttReceive.newEvent = 0;
    }
}


/**
 * Clear SIM800 UART RX buffer.
 * @param NONE
 * @return NONE
 */
void vid_clearRxBuffer(void)
{
    GLOB_u16UartRx_Index = 0;
    memset(GLOB_arrUartRx_Buffer, 0, sizeof(GLOB_arrUartRx_Buffer));
}

/**
 * Clear MQTT buffer.
 * @param NONE
 * @return NONE
 */
static void vid_clearMqttBuffer(void)
{
    GLOB_u8mqtt_receiveMode = 0;
    GLOB_u16mqtt_index = 0;
    memset(GLOB_arrmqtt_buffer, 0, sizeof(GLOB_arrmqtt_buffer));
}







u8_t u8_MQTT_Init(void)
{
    u8_t LOC_u8_Error = 3;
    u8_t LOC_u8_retval = 0;

    vid_Mqtt_GpioWrite_ResetPin(RESET_HIGH); // reset the module
    vid_Mqtt_Delay(SIM800_RESET_DELAY);
    vid_Mqtt_GpioWrite_ResetPin(RESET_LOW);
    vid_Mqtt_Delay(SIM800_STARTUP_DELAY);
    
    // close echo, must success if not it means hardware module not exist
    if(u8_SIM800_SendCommand("ATE0\r\n", "OK", 7) == 1){

        vid_Mqtt_Delay(CMD_DELAY);
        LOC_u8_Error -= u8_SIM800_SendCommand("AT+CIPSHUT\r\n", "OK", 13);  // Deactivate GPRS PDP Context
        vid_Mqtt_Delay(CMD_DELAY);
        LOC_u8_Error -= u8_SIM800_SendCommand("AT+CGATT=1\r\n", "OK", 13);  // Attach GPRS Service
        vid_Mqtt_Delay(CMD_DELAY);
        LOC_u8_Error -= u8_SIM800_SendCommand("AT+CIPMODE=0\r\n", "OK", 15);// Select TCPIP Application Mode (NORMAL)
        vid_Mqtt_Delay(CMD_DELAY);
    }else{
        // hardware module not exist
    }

    if(LOC_u8_Error == 0){
        LOC_u8_retval = 1;
    }else{
        LOC_u8_retval = 0;
    }

    return LOC_u8_retval;
}


u8_t u8_MQTT_Connect(void)
{
    GLOB_strSIM800.mqttServer.connect = 0;
    GLOB_strSIM800.mqttReceive.newEvent = 0;
    MQTTPacket_connectData datas = MQTTPacket_connectData_initializer;
    u32_t size = 0;
    u16_t LOC_u16_mqtt_len = 0;
    u8_t str[128] = {0};
    u8_t LOC_arr_tempBuffer[128] = {0};
    u8_t trialsCounter = 0;

    // connect to the server
    size = (u32_t)sprintf(str, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", GLOB_strSIM800.mqttServer.host, GLOB_strSIM800.mqttServer.port);  // Start Up TCP Connection
    if(u8_SIM800_SendCommand(str, "OK", size) == 1){
        GLOB_strSIM800.mqttServer.connect = 1;
    }
    
    vid_Mqtt_Delay(CMD_DELAY);

    if(GLOB_strSIM800.mqttServer.connect == 1){

        // send MQTT connect pattern
        datas.username.cstring = GLOB_strSIM800.mqttClient.username;
        datas.password.cstring = GLOB_strSIM800.mqttClient.pass;
        datas.clientID.cstring = GLOB_strSIM800.mqttClient.clientID;
        datas.keepAliveInterval = GLOB_strSIM800.mqttClient.keepAliveInterval;
        datas.cleansession = 1;
        LOC_u16_mqtt_len = (u16_t)MQTTSerialize_connect(LOC_arr_tempBuffer, sizeof(LOC_arr_tempBuffer), &datas);
        LOC_arr_tempBuffer[LOC_u16_mqtt_len] = PATTERN_END;
        ++LOC_u16_mqtt_len;

        while(trialsCounter != 3){
            if(u8_SIM800_SendCommand("AT+CIPSEND\r\n", "> ", 13) == 1){
                break;
            }
            ++trialsCounter;
        }
        
        vid_Mqtt_Delay(CMD_DELAY);

        if(u8_SIM800_SendPattern(LOC_arr_tempBuffer, LOC_u16_mqtt_len) != 1){
            GLOB_strSIM800.mqttServer.connect = 0;
        }

    }

    return GLOB_strSIM800.mqttServer.connect;
}


/**
 * Public on the MQTT broker of the message in a topic
 * @param topic to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return 1 publish successfully, 0 failed
 */
u8_t u8_MQTT_Publish(char *topic, char *payload, u32_t size)
{
    u8_t LOC_u8_retval = 0;
    u8_t LOC_u8_checkInput = (topic != NULLPTR) 
                             && (payload != NULLPTR) 
                             && (size != 0)
                             && (GLOB_strSIM800.mqttServer.connect != 0);

    if(LOC_u8_checkInput == 1){
        u8_t header[256] = {0};
        u8_t endPacket = PATTERN_END;
        u32_t LOC_u16_mqtt_len = 0;
        u32_t payload_size = size;
        MQTTString LOC_str_topicString = MQTTString_initializer;
        LOC_str_topicString.cstring = topic;

        LOC_u16_mqtt_len = MQTTSerialize_publish(header, 256, 0, 0, 0, 0,
                                             LOC_str_topicString, payload, payload_size);

        u8_SIM800_SendCommand("AT+CIPSEND\r\n", "> ", 13);

        u8_Mqtt_UartTransmit(header, (u16_t)(LOC_u16_mqtt_len - payload_size), CMD_DELAY);
        vid_Mqtt_Delay(1);
        u8_Mqtt_UartTransmit(payload, (u16_t)payload_size, CMD_DELAY);
        vid_Mqtt_Delay(1);
        u8_Mqtt_UartTransmit(&endPacket, 1, CMD_DELAY);
        vid_Mqtt_Delay(1);
        LOC_u8_retval = u8_SIM800_SendPattern(payload, (u16_t)LOC_u16_mqtt_len);
    }else{
        LOC_u8_retval = 0;
    }


    return LOC_u8_retval;
}



/**
 * Subscribe on the MQTT broker of the message in a topic
 * @param topic to be used to the set topic
 * @return 1 subscribe successfully, 0 failed
 */
static u8_t u8_Subscribe(char *topic)
{
    u8_t LOC_u8_checkInput = (topic != NULLPTR) && (GLOB_strSIM800.mqttServer.connect != 0);
    u8_t LOC_u8_retval = 0;
    u8_t LOC_arr_tempBuffer[256] = {0};
    u16_t LOC_u16_mqtt_len = 0;

    MQTTString LOC_str_topicString = MQTTString_initializer;

    if(LOC_u8_checkInput == 1){

        LOC_str_topicString.cstring = topic;
        LOC_u16_mqtt_len = MQTTSerialize_subscribe(LOC_arr_tempBuffer, sizeof(LOC_arr_tempBuffer), 0, 1, 1, &LOC_str_topicString, 0);
        LOC_arr_tempBuffer[LOC_u16_mqtt_len] = PATTERN_END;
        ++LOC_u16_mqtt_len;
    
        u8_SIM800_SendCommand("AT+CIPSEND\r\n", "> ", 13);
        if(u8_SIM800_SendPattern(LOC_arr_tempBuffer, LOC_u16_mqtt_len) == 1){
            GLOB_strSIM800.mqttServer.subscribe_state = 1;
            LOC_u8_retval = 1;
        }else{
            GLOB_strSIM800.mqttServer.subscribe_state = 0;
            LOC_u8_retval = 0;
        }
    }else{
        LOC_u8_retval = 0;
    }

    return LOC_u8_retval;
}

/**
 * Receive message from MQTT broker
 * @param receive mqtt bufer
 * @return NONE
 */
static void vid_MQTT_Receive(unsigned char *LOC_arr_tempBuffer)
{
    MQTTString receivedTopic;
    unsigned char *payload;


    // clear buffers
    memset(GLOB_strSIM800.mqttReceive.topic, 0, sizeof(GLOB_strSIM800.mqttReceive.topic));
    memset(GLOB_strSIM800.mqttReceive.payload, 0, sizeof(GLOB_strSIM800.mqttReceive.payload));
    
    // extract the message from the mqtt packet
    MQTTDeserialize_publish(&GLOB_strSIM800.mqttReceive.dup, &GLOB_strSIM800.mqttReceive.qos, &GLOB_strSIM800.mqttReceive.retained,
                            &GLOB_strSIM800.mqttReceive.msgId,
                            &receivedTopic, &payload, &GLOB_strSIM800.mqttReceive.payloadLen, LOC_arr_tempBuffer,
                            sizeof(LOC_arr_tempBuffer));

    // copy the received message for the user
    if((receivedTopic.lenstring.len < 20) && (GLOB_strSIM800.mqttReceive.payloadLen < 64)){
        memcpy(GLOB_strSIM800.mqttReceive.topic, receivedTopic.lenstring.data, receivedTopic.lenstring.len);
        GLOB_strSIM800.mqttReceive.topicLen = receivedTopic.lenstring.len;
        memcpy(GLOB_strSIM800.mqttReceive.payload, payload, GLOB_strSIM800.mqttReceive.payloadLen); 
        GLOB_strSIM800.mqttReceive.newEvent = 1;
    }

}


void vid_Mqtt_SetCallback(MqttCallback callback){
    GLOB_pUserCallback = callback;
    vid_Mqtt_SetUartCallback(callback);
}


u8_t u8_Mqtt_isConnnected(void){
    return (GLOB_strSIM800.mqttServer.connect && GLOB_strSIM800.mqttServer.subscribe_state);
}
