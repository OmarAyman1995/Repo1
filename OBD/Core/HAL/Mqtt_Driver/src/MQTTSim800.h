/*
 * MQTTSim800.h
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
 *
 */

/*
 * -----------------------------------------------------------------------------------------------------------------------------------------------
                    Version 2, December 2004

 Copyright (C) 2020 Bulanov Konstantin <leech001@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION


  MQTT packet https://github.com/eclipse/paho.mqtt.embedded-c/tree/master/MQTTPacket
 * ------------------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef  _MQTTSIM800_H
#define  _MQTTSIM800_H

#include "typedefs.h"
#include "MQTTPacket.h"
#include "MQTTFormat.h"
#include "MQTTConnect.h"
#include "MQTTSubscribe.h"
#include "MQTTUnsubscribe.h"
#include "MQTTPublish.h"
#include "MQTT_Mcal_Interface.h"
#include "SIM800Handling.h"

// === CONFIG ===

#define SIM800_RESET_DELAY      1000
#define SIM800_STARTUP_DELAY    2000
#define CMD_DELAY   200
// ==============


#define MQTT_MAX_SUBS 2
#define MQTT_MAX_TOPIC_SIZE 10
#define MAX_SUBSCRIBE_TRIALS 5
/**
 * @brief SIM Card APN configurations
 * 
 */
typedef struct {
    char *apn;
    char *apn_user;
    char *apn_pass;
} sim_t;


/**
 * @brief mqtt cloud server configurations 
 * 
 */
typedef struct {
    char *host;
    u16_t port;
    u8_t connect;
    u8_t subscribe_state;
} mqttServer_t;


/**
 * @brief mqtt client configurations
 * 
 */
typedef struct {
    char *username;
    char *pass;
    char *clientID;
    unsigned short keepAliveInterval;
} mqttClient_t;


/**
 * @brief receive object datatype
 * 
 */
typedef struct {
    u8_t newEvent;
    unsigned char dup;
    int qos;
    unsigned char retained;
    unsigned short msgId;
    unsigned char payload[64];
    int payloadLen;
    unsigned char topic[20];
    int topicLen;
} mqttReceive_t;


/**
 * @brief driver base object datatype
 * 
 */
typedef struct {
    sim_t sim;
    mqttServer_t mqttServer;
    mqttClient_t mqttClient;
    mqttReceive_t mqttReceive;
} SIM800_t;




/**
 * @brief initialize mqtt sequence (establishes 2G Conncetion then connects to server)
 * 
 * @return u8_t 1 sequence done successfully, 0 sequence failed
 */
u8_t u8_MQTT_Init(void);


/**
 * @brief periodic function of mqtt driver
 * 
 */
void vid_Mqtt_Manage(void);


/**
 * @brief publish a message to a certain topic
 * 
 * @param topic topic name
 * @param payload data that will be published
 * @param size size of the data
 * @return u8_t 1 success, 0 fail
 */
u8_t u8_MQTT_Publish(char *topic, char *payload, u32_t size);


/**
 * @brief register a topic to be subscribed to (subscription sequence will be done at Manage function)
 * 
 * @param topic topic name
 * @return u8_t 1 registering success, 0 registering fail
 */
u8_t u8_Mqtt_Subscribe(u8_t *topic);

/**
 * @brief register a callback function, will be called whenever new published message from a subscribed topic has been received
 * 
 * @param callback callback function
 */
void vid_Mqtt_SetCallback(MqttCallback callback);


/**
 * @brief must be called at the interrupt of the UART
 * 
 */
void vid_Mqtt_Uart_Interrupt(void);

/**
 * @brief gets the 2G connection status
 * 
 * @return u8_t 1 connceted, 0 not connected
 */
u8_t u8_Mqtt_isConnnected(void);


/**
 * Connect to MQTT server in Internet over TCP.
 * @param NONE
 * @return NONE
 */
u8_t u8_MQTT_Connect(void);
#endif
