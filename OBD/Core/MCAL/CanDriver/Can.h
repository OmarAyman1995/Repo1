/**
 * @file Can.h
 * @author  Ahmed bahaa - (https://crewteq.com/)
 
 * @brief This is the header file for a CAN Driver Component for STM32F103C8T6, Target Device has Only One Can Peripheral 
          File Contains Macros,Data Typee and functions definitions for the CAN Driver Component
 
 * @version 1.6.0
 * @date 2023-10-8
 * 
 * @copyright Copyright (crewteq) 2023
 * 
 */

#ifndef CAN_H
#define CAN_H

 /*________________________________Includes_______________________________*/
#include "typedefs.h"
#include <stddef.h>
 /*________________________________Macros_______________________________*/

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1


/*
Example of iniitalizing CAN Driver:
  vid_CanDrvInit();
  enum_CanDrvSetBitTiming(500000, 64000000);
  enum_SetAcceptenceFilter(0x7df, STANDARD_FORMAT, 0);
  enum_SetAcceptenceFilter(0x18DB33F1, EXTENDED_FORMAT, 1);
  vid_CanDrvStart();
*/

 /*________________________________Data Types_______________________________*/

/**
 * @brief Structure For CAN Frame Format info
 * @note Cover Requirement CCO-CDD-1201
 */
typedef struct  
{
/// @brief Frame Identifer
u32_t FrameID;                          

/// @brief Frame Type (Data frame or Remote frame
u8_t RTR;   

/// @brief Frame Format (standard or extended)
u8_t IDE;                             

/// @brief Frame Data length
u8_t DLC;                              

/// @brief Frame Data
u8_t data[8];                             
} strCanDrvFrameInfo;

/*Enum For CAN Protocol Errors*/

/**
 * @brief Enum For CAN Protocol Errors
 * @note Cover Requirement CCO-CDD-1215
 * 
 */
typedef enum
{
No_ERROR,                           /*No Error With CAN Frame*/
STUFF_ERROR,                        /*Stuffing bits not as expected*/
FORM_ERROR,                         /*Violations of the fixed frame format*/
ACK_ERROR,                          /*Acknowledgement check failed */
BIT_RECESSIVE_ERROR,                /*A 1 was transmitted and a 0 was sensed*/
BIT_DOMINANT_ERROR,                 /*A 0 was transmitted and a 1 was read back*/
CRC_ERROR                           /*CRC failed*/
}EnumCanDrvErrorType;


/**
 * @brief Enum for Can Node Error State
 * @note Cover Requirement CCO-CDD-1202
 */

typedef enum
{
  ACTIVE_ERROR_STATE,
  PASSIVE_ERROR_SATE,
  BUS_OFF_STATE,
}EnumCanNodeErrorState;


/**
 * @brief Enum for CAN Driver's APIs ERROR State
 * @note Cover Requirement CCO-CDD-1200
 * 
 */

typedef enum
{
  CAN_API_OK,
  CAN_API_NOT_OK,
}EnumCanDrvApiError;


/*________________________________Functions Prototypes_______________________________*/

/// @brief This Function is responsible for initalizing CAN Driver
/// @note  Cover Requirement CCO-CDD-1207 
void vid_CanDrvInit (void);

/// @brief  This Function is Responsible for Setting the CAN Bit Timing register to obtain Node baudrate
/// @param baudrate the desired baudrate
/// @return API Error State (OK or not ok)
/// @note  Cover Requirement CCO-CDD-1223  
EnumCanDrvApiError enum_CanDrvSetBitTiming(u32_t baudrate, u32_t u32Clock);

/// @brief this function is responsible for starting CAN Channel
/// @note  Cover Requirement CCO-CDD-1208 
void vid_CanDrvStart(void);

/// @brief this function is responsible for stoping CAN Channel
/// @note  Cover Requirement CCO-CDD-1209
void vid_CanDrvStop(void);

/// @brief This function is responsible for tranmsitting a frame on can bus
/// @param Frame Structure containing Frame info
/// @return API Error State (OK or not ok)
/// @note  Cover Requirement CCO-CDD-1210 
EnumCanDrvApiError enum_CanDrvTransmit(const strCanDrvFrameInfo *frame);

 /// @brief This function is repsonsible for Receiving CAN Frame
 /// @return Structure containing Frame info
 /// @note  Cover Requirement CCO-CDD-1211 
 void vid_CanRecieve(strCanDrvFrameInfo* frame);

 /// @brief This function sets an acceptence filter for a message frame
 /// @param id Msg ID
 /// @param format Msg Format
 /// @note  Cover Requirement CCO-CDD-1212
EnumCanDrvApiError enum_SetAcceptenceFilter(u32_t id,u8_t format,u8_t filterNumber);


 /// @brief This function clears an acceptence filter be disabling it
 /// @param filterNumber Filter Number
 /// @note  Cover Requirement CCO-CDD-1223
void enum_ClearAcceptenceFilter(u8_t filterNumber);


 /// @brief this function Enables LoopBack Test mode in the CAN controller to test the CAN Controller without the need of a CAN Network
  /// @note  Cover Requirement CCO-CDD-1225
void vid_CanLoopBacktestModeEnable(void);

/// @brief this function sets the can node to be a plain listener to all incoming valid CAN Frames, useful to scan CAN msgs Traffic on a CAN Network
  /// @note  Cover Requirement CCO-CDD-1226
void vid_CanSilenttestMode(void);

/// @brief Set Callback in case of Successful Transmission in INTERRUPT mode.
/// @param ptr_UserCallback  pointer to function used called in callback method in CAN_RX_IRQ Handler
 /// @note  Cover Requirement CCO-CDD-1213
void vid_CanDrvSetTransmitCallPack(void(*ptr_UserCallback)(void));


/// @brief Set Callback in case of receiving in INTERRUPT mode.
/// @param ptr_UserCallback pointer to function used called in callback method in CAN_RX_IRQ Handler
 /// @note  Cover Requirement CCO-CDD-1214
void vid_CanDrvSetReceiveCallPack(void(*ptr_UserCallback)(void));



/// @brief Set Callback in case of busOff error
/// @param ptr_UserCallback  pointer to function used called in callback method in CAN_RX_IRQ Handler
 /// @note  Cover Requirement CCO-CDD-1224
void vid_CanDrvSetBusOffErrorCallback(void(*ptr_UserCallback)(void));


/// @brief Set Callback to be called when a reception occurs on a specific CAN ID
/// @param ptr_UserCallback  pointer to function used called in callback method in CAN_RX_IRQ Handler
/// @param CANID ID for WakeUp
 /// @note  Cover Requirement CCO-CDD-1215
void vid_CanDrvSetIDWakeUp(u32_t CANID,void(*ptr_UserCallback)(void));


/// @brief This function is responsible for returning the current error type detected by the CAN node by reading CAN_ESR Register
/// @return API Error State (OK or not ok)
 /// @note  Cover Requirement CCO-CDD-1217
EnumCanDrvErrorType enum_CanDrvGetLastError(void);

/// @brief This function is responsible for returning the current error type detected by the CAN node by reading CAN_ESR Register
/// @return API Error State (OK or not ok)
bool enum_isCanBusOff (void);

#endif


