#ifndef CAN_ISO_15765
#define CAN_ISO_15765

#include "typedefs.h"
#include "CANTp.h"

/*__________________________________________________________Data Types_______________________________________________*/

/**
 * @brief this enumeration defines the Component APIs error states
 * @note  Cover Requirement CCO-CDD-1500
 * 
 */
typedef enum
{
   CAN_ISO_OK, CAN_ISO_NOK
}enum_CanIsoErrorState;

/**
 * @brief ISO 15765 compliant State
 * @note  Cover Requirement CCO-CDD-1501
 */
typedef enum
{
   ISO15765_NOT_COMPLIANT , ISO15765_COMPLIANT, ERROR_IN_BAUDRATE_RECORD
}enum_IsoCompliantState;



/*__________________________________________________________Public Functions Prototypes_______________________________________________*/

/// @brief sets callback functions for Transmitions and reception complete callback functions
/// @return API Error State
/// @note  Cover Requirement CCO-CDD-1506
enum_CanIsoErrorState enum_CanIsoinit(void);


/// @brief Puts the CAN Frame Header and transmits data to CAN TP Module
/// @param DataArray data to send
/// @param size size of data
/// @return API Execution state
/// @note Cover Requirement CCO-CDD-1510
enum_CanIsoErrorState enum_CanIsoSendData (const u8_t *DataArray, u8_t  size);

/**
 * @brief Construct a new Can Iso Receive object
 * 
 * @param DataPayloadBuffer buffer to store received data in Tp
 * @param size  size of data
 */
void CanIsoReceive(u8_t* DataPayloadBuffer,u16_t* size);

/// @brief detects the baudrate and the CAN ID type (Standard or extended) of the vehicle based on the ISO15765 initalization sequence, and sets the baudrate in the can driver based on the detected baudrate
/// @param baudrateRecord record of baudrate to check
/// @param size size of record
/// @return Detection result state (compilant or not )
/// @note Cover Requirement CCO-CDD-1511
enum_IsoCompliantState enum_DetectCANComm (const u32_t *baudrateRecord,u8_t size);


/// @brief This function is used to enable upper modules to set a callback function to notify a reception of data units 
///        in the Tp module
/// @param ptrFunc pointer to the notify function in the upper layer
/// @note Covers Requirmenets CCO-CDD-1074
void vid_CanIsoSetReceiveCallBack(void(*ptr_UserCallback)(void));


/// @brief This function is used to enable upper modules to set a callback function to notify a successful transmission of data units 
///        in the Tp module
/// @param ptrFunc pointer to the notify function in the upper layer
/// @note Covers Requirmenets CCO-CDD-1081
void vid_CanIsoSetTransmitCallBack(void(*ptr_UserCallback)(void));
















#endif