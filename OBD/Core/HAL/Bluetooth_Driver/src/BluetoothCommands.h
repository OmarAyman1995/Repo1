#ifndef BLUETOOTHCOMMANDS_H
#define BLUETOOTHCOMMANDS_H


#include "typedefs.h"


/**
 * @brief sends bluetooth command
 * 
 * @param LOC_ptr_Command the AT command that will be sent to bluetooth hardware
 * @return u8_t sending failed, 1 sending successed
 */
u8_t  u8_Bluetooth_SendCmnd(u8_t* LOC_ptr_Command);


/**
 * @brief receive AT command response from bluetooth hardware
 * 
 * @param LOC_ptr_Command buffer to collect in it the received command response
 * @return u8_t receiving failed, 1 receiving successed
 */
u8_t  u8_Bluetooth_ReceiveCmnd(u8_t* LOC_ptr_Command);


/**
 * @brief changes the bluetooth name to a new name
 * 
 * @param LOC_ptr_device_name the new desired name
 * @return u8_t operaion failed, 1 operaion successed
 */
u8_t u8_Bluetooth_SetDeviceName(u8_t *LOC_ptr_device_name);


/**
 * @brief changes the LOC_ptr_baudrate to a new LOC_ptr_baudrate
 * 
 * @param LOC_ptr_baudrate the new desired LOC_ptr_baudrate
 * @return u8_t operaion failed, 1 operaion successed
 */
u8_t u8_Bluetooth_SetBaudrate(u8_t *LOC_ptr_baudrate);


/**
 * @brief changes the password to a new password
 * 
 * @param LOC_ptr_passowrd the new desired password
 * @return u8_t operaion failed, 1 operaion successed
 */
u8_t u8_Bluetooth_SetPassword(u8_t *LOC_ptr_passowrd);


/**
 * @brief restore all configurations of bluetooth hardware device to default state
 * 
 * @return u8_t operaion failed, 1 operaion successed
 */
u8_t u8_Bluetooth_RestoreToOrigin(void);


/**
 * @brief reset the power of the board, usually used to switch from setup to normal
 * 
 * @return u8_t operaion failed, 1 operaion successed
 */
u8_t u8_Bluetooth_ResetBoard(void);





#endif
