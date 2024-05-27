#ifndef __HANDLINGBLUETOOTH_H
#define __HANDLINGBLUETOOTH_H



#include "typedefs.h"
#include "BluetoothDrv.h"
#include "QueueInterface.h"




/**
 * @brief used to send data on bluetooth
 * 
 * @param pData data that will be sent on bluetooth
 * @param size size of the data
 * @return u8_t 1 if success, 0 if fail
 */
u8_t u8_HandlingBluetooth_Send(u8_t *pData, u32_t size);

/**
 * @brief makes the bluetooth listening for new byte
 * 
 */
void vid_HandlingBluetooth_Listen(void);

/**
 * @brief callback function will be called whenever new byte has been recieved
 * 
 */
void vid_HandlingBluetooth_Callback(void);


/**
 * @brief resets the buffer
 * 
 */
void vid_HandlingBluetooth_resetAfterRequest(void);

/**
 * @brief updates the configurations of bluetooth hardware module
 * 
 * @return u8_t 1 if update is successed, 0 if failed
 */
u8_t u8_HandlingBluetooth_updateConfigurations(void);

#endif
