#ifndef  _MQTT_MCAL_INTERFACE_H
#define  _MQTT_MCAL_INTERFACE_H




#include "typedefs.h"
#include "MQTTSim800.h"

#define RESET_HIGH 1
#define RESET_LOW 0


/**
 * @brief delay abstraction
 * 
 * @param delay delay number
 */
void vid_Mqtt_Delay(u32_t delay);


/**
 * @brief Uart Transmit transmit abstraction
 * 
 * @param LOC_ptr_pData array of data
 * @param LOC_u16_size size of data
 * @param LOC_u32_timeout timeout number
 */
u8_t u8_Mqtt_UartTransmit(u8_t *LOC_ptr_pData, u16_t LOC_u16_size, u32_t LOC_u32_timeout);


/**
 * @brief receive interrupt abstraction
 * 
 * @param LOC_ptr_pData array of data
 * @param LOC_u16_size size of data
 */
u8_t u8_Mqtt_UartReceiveIT(u8_t *LOC_ptr_pData, u16_t LOC_u16_size);



/**
 * @brief reset pin abstraction
 * 
 * @param LOC_u8_level high or low
 */
void vid_Mqtt_GpioWrite_ResetPin(u8_t LOC_u8_level);


void vid_Mqtt_SetUartCallback(MqttCallback callback);
#endif

