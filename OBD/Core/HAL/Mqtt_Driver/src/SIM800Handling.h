#ifndef  _SIM800HANDLING_H
#define  _SIM800HANDLING_H

#include "typedefs.h"
#include "MQTT_Mcal_Interface.h"

/**
 * @brief Send AT command to SIM800 over UART.
 * @param command the command to be used the send AT command
 * @param reply to be used to set the correct answer to the command
 * @param delay to be used to the set pause to the reply
 * @return u8_t 1 if received "SEND OK", 0 if not
 */
u8_t u8_SIM800_SendCommand(char *command, char *reply, u32_t sizeofcommand);


/**
 * @brief sends mqtt certain patterns such as connect, subscribe, publish
 * 
 * @param pattern pattern message
 * @param length size of the message
 * @return u8_t 1 if received "SEND OK", 0 if not
 */
u8_t u8_SIM800_SendPattern(char *pattern, u16_t length);



#endif
