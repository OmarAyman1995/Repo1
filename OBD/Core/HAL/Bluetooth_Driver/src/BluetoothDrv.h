#ifndef BLUETOOTHDRV_H
#define BLUETOOTHDRV_H

#include "StdFile.h"
#include "BluetoothCommands.h"



#define BLUETOOTH_STATE_PORT  GPIOB
#define BLUETOOTH_STATE_PIN   GPIO_PIN_1

#define BLUETOOTH_ENABLE_PORT GPIOB
#define BLUETOOTH_ENABLE_PIN  GPIO_PIN_5



/**
 * @brief new configurations to bluetooth hardware
 * 
 */
typedef struct{
  u8_t device_name[20];
  u8_t pass[20];
  u8_t baudrate[20];
  
}Bluetooth_Config_t;





/**
 * @brief initialize Bluetooth hardware module with the input configurations from user
 * 
 * @param LOC_ptr_configs new configurations of the hardware bluetooth module
 * @return u8_t 0 initialize failed, 1 initialize successed
 */
u8_t u8_Bluetooth_Init(Bluetooth_Config_t *LOC_ptr_configs);


/**
 * @brief sends data over bluetooth
 * 
 * @param pData pointer to the data
 * @param LOC_u32_size LOC_u32_size of the data
 * @return u8_t 0 sending failed, 1 sending successed
 */
u8_t u8_Bluetooth_Send(u8_t* LOC_p_Data, u32_t LOC_u32_size);


/**
 * 
 * @brief makes bluetooth listens to the data with number of LOC_u32_size given to the function 
 * 
 * @param pData pointer to the buffer that bluetooth will buffer the received data in 
 * @param LOC_u32_size the desired LOC_u32_size user wants to receive
 * @return u8_t receiving failed, 1 receiving successed
 */
u8_t u8_Bluetooth_Receive(u8_t* LOC_p_Data, u32_t LOC_u32_size);


/**
 * @brief register a callback function so whenever LOC_u32_size given to u8_Bluetooth_Receive has been received, this callback will be called
 * 
 * @param pISR callback function, gets called whenever desired LOC_u32_size gets received
 */
void vid_Bluetooth_setCallback(pFunction pISR);


/**
 * @brief gets the connectivity status of bluetooth, user linked with the device or not
 * 
 * @return u8_t 1 connected, 0 not connected
 */
u8_t u8_Bluetooth_getConnectivityStatus(void);

/**
 * @brief cancel any previous receive request
 * 
 */
void vid_Bluetooth_AbortReceive(void);

#endif
