#ifndef __PWM_COMMANDER_H
#define __PWM_COMMANDER_H

/**
 * @file PwmCommander.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      Header file of PwmCommander
 * @version    1.0.0
 * @date       2024-03-20
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "typedefs.h"
#include "BitsManager.h"

/*____________________Macros________________________________________*/

/*The P2-P0 bytes are the message priority with 111 being the lowest priority and 000 the highest priority.*/ 
#define HEADER_SAE1850_PRIORITY0            7
#define HEADER_SAE1850_PRIORITY1            6
#define HEADER_SAE1850_PRIORITY2            5

/*The H-bit is the header type with 0 being the three byte header and 1 being the single byte header. */
#define HEADER_SAE1850_H                    4

/*The K-bit is the In-Frame Response (IFR) with 0 being IFR required and 1 being IFR not allowed.*/ 
#define HEADER_SAE1850_K                    3

/*The Y-bit is the addressing mode with 0 being the functional addressing and 1 being the physical addressing.*/
#define HEADER_SAE1850_Y                    2

/*If the Z1-bit is set to a “one”, then a receiving node(s) knows that the fifth byte of this message is the extended address of this function.*/
#define HEADER_SAE1850_Z1                   1 

/*The Z0-bit indicates whether or not data is contained in this message.
If the Z0-bit is set to a “zero”, then data should be expected with this message. 
If the Z0-bit is set to a “one”, then no data is contained within this message.*/
#define HEADER_SAE1850_Z0                   0



/*____________________UserDatatypes___________________________________*/



/// @brief this enumeration will be used as a return types to indicate if the function
///        returns successfully or Not !.
typedef enum
{
    VALID_PWM_COMMANDER  = 0,
    NOT_VALID_PWM_COMMANDER= 1,
    UNKOWN_PWM_COMMANDER = 2
}enumRetPWMCommander_e;



/*_____________________Prototypes______________________________________*/
/// @brief this function is responsible for collecting the 101 bits of the frame (HEADER + DATA + CRC)
/// @param  u8OBDdata the OBD data Coming from the Upper Layer  
/// @return the validity of function Execution
///         VALID_PWM_COMMANDER   or    NOT_VALID_PWM_COMMANDER    or   UNKOWN_PWM_COMMANDER
/// @note covers Req ID:CCO-CDD-2095
enumRetPWMCommander_e enum_PwmCommanderCollectFrame(const u8_t* u8OBDdata);

/// @brief this function is responsible for sending the Whole frame in PRIVATE array  which includes all 101 bits.
/// @param  NAN
/// @return the validity of function Execution
///         VALID_PWM_COMMANDER   or    NOT_VALID_PWM_COMMANDER    or   UNKOWN_PWM_COMMANDER
/// @note covers Req ID:CCO-CDD-2096
enumRetPWMCommander_e enum_PwmCommanderSendFrame(void);

/// @brief this function is responsible for receiving one frame
/// @param ptr_u8RecFrame (out)the frame we have received 
/// @return the validity of function Execution
///         VALID_PWM_COMMANDER   or    NOT_VALID_PWM_COMMANDER    or   UNKOWN_PWM_COMMANDER
/// @note covers Req ID:CCO-CDD-2096
enumRetPWMCommander_e enum_PwmCommanderRecFrame(u8_t* ptr_u8RecFrame);

#endif