#ifndef __ISO_UART_PROTOCOLS_H
#define __ISO_UART_PROTOCOLS_H




#include "typedefs.h"
#include "ISO_Uart_MCAL_Interface.h"

#define TEST_ON UT

#define VEHICLE_PROT_ERR 0
#define VEHICLE_ISO_14230 1
#define VEHICLE_ISO_9141 2


/**
 * @brief makes the initialize sequence ISO 14230 & ISO 9141 protocols
 * 
 * @return u8_t 1 if success and you can get the protocol (14230 or 9141), 0 fails (vehicle didn't respond)
 */
u8_t u8_UartISO_InitSequence(void);


/**
 * @brief sends OBD ISO 14230 or ISO 9141 OBD request to vehicle
 * 
 * @param mode OBD Mode
 * @param pid OBD Pid
 * @return u8_t 1 if send successed, 0 if send failed
 */
u8_t u8_UartISO_Send(u8_t mode, u8_t pid);


/**
 * @brief copies the vehicle OBD response to user memory
 * 
 * @param userBuffer user memory
 * @return u8_t 1 success, 0 fail
 */
u8_t u8_UartISO_Receive(u8_t userBuffer[]);


/**
 * @brief registers a callback function gets called whenever the component receives a vehicle OBD response,
 * in the callback function you can use u8_UartISO_Receive to get the data received from vehicle,
 * with buffer of size max 25
 * 
 * @param callback 
 */
void vid_UartISO_RegisterCallback(pFunction callback);


/**
 * @brief gets the protocol if it is 14230 or 9141 or 0 (vehicle didn't respond if 0)
 * 
 * @return u8_t 1 = 14230, 2 = 9141, 0 = error
 */
u8_t u8_getUartProtocol(void);


/**
 * @brief this function must be called in Uart ISR
 * 
 */
void vid_UartISO_MCALCallback(void);

/**
 * @brief fast initialize of ISO 14230 and ISO 9141
 * 
 * @return u8_t 1 success, 0 failed
 */
u8_t u8_fastInitialize(void);


/**
 * @brief slow initialize of ISO 14230 and ISO 9141
 * 
 * @return u8_t 1 success, 0 failed
 */
u8_t u8_slowInitialize(void);
#endif
