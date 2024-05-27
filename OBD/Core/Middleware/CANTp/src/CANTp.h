
/**
 * @file CANTp.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief This is header file is for the CAN Tp Component. Component is used to Fullfile ISO-TP Goal to 
          construct a re-assembled UDS Frame when Sending and Recieving Data Payloads That exceed the CAN Frame Payload (8 bytes) On CAN BUS 
          
          Transport protocol on CAN according to ISO 15765-2:
              - Segmentation of data in transmit direction
              - Collection of data in receive direction
              - Control of data flow
              - Detection of errors (message loss/doubling/sequence)

 * @version 1.6.0
 * @date 2023-11-14
 * 
 * @copyright Copyright (crewteq) 2023 
 */

/*________________________________Dependencies_______________________________*/

#ifndef CANTP
#define CANTP

#include "typedefs.h"
#include "CANConfig.h"

#define MAX_TRANSMIT_DATA_PAYLOAD      (u8_t)8   

/*________________________________Data Types_______________________________*/

/**
 * @brief structure containing Received Data Payloads
 * @note Covers Requirmenets CCO-CDD-1079 
 * 
 */
typedef struct 
{
    /// @brief Received DataPayload 
    u8_t u8TpDataPayload[TP_RECEIVE_BUFFER_SIZE];             

    /// @brief Size of Data Payload in bytes
    u16_t u8DataPayloadSize;                                
}TpReceiveDataUnitInfo_t;

/**
 * @brief Structure for sending Diagnsotic Request according to ISO-TP
 * @note Covers Requirmenets CCO-CDD-1062 
 * 
 */
typedef struct 
{
    /// @brief DataPayload of UDS Frame
    u8_t u8TpDataPayload[MAX_TRANSMIT_DATA_PAYLOAD];             

    /// @brief Size of Data Payload in bytes
    u16_t u8DataPayloadSize;

    /// @brief CAN ID to send to
    u32_t DiagnosticCANID;                                  

    /// @brief can ID to send flow control frame on
    u32_t FlowControlCANID;                                    
}TpTransmitDataUnitInfo;
/*enum for API ERROR HANDLING*/


/**
 * @brief enum for API ERROR HANDLING
 * @note Covers Requirmenets CCO-CDD-1060 
 * 
 */
typedef enum
{                            
  CAN_TP_API_OK,                                               
  CAN_TP_API_NOT_OK                                            
}enumTpApiError_e;

/**
 * @brief enum for Enabling and disabling ISO-TP Option while receiving msgs through CAN TP SWC
 * @note Covers Requirmenets CCO-CDD-1080
 */
typedef enum
{                            
  ISO_TP_ENABLED,                                               
  ISO_TP_DISABLED                                            
}IsoTpOption_e;

/*________________________________Functions Prototype_______________________________*/

/*__________services Used by upper layer___________*/

/// @brief API used to initalize CAN Integration Componant 
///        sets the callback function for transmission and reception notify from CAN Driver 
/// @note Covers Requirmenets CCO-CDD-1070
void vid_TpInit(void);

/// @brief API used by Upper layer to Transmit a data unit in a CAN Frame acoording to ISO-TP Standard (used BY UDS handler Component)
/// @param DataUnitStruct: pointer to the stucture containing data payloads,length and desired CAN ID of the diagnostic protocol 
/// @note Covers Requirmenets CCO-CDD-1072
enumTpApiError_e vid_TpTransmitDataUnit(const TpTransmitDataUnitInfo *DataUnitStruct);

/// @brief API used by Upper Layer to Receive the re-assembled data unit
/// @param outputBuffer buffer to pass received data to
/// @param size buffer size
/// @return sdu structure containing sdu buffer and it's size
/// @note Covers Requirmenets CCO-CDD-1073
u8_t struct_GetTpReceivedDataUnit(u8_t* outputBuffer,u16_t* size);

/// @brief This function is used to enable upper modules to set a callback function to notify a reception of data units 
///        in the Tp module
/// @param ptrFunc pointer to the notify function in the upper layer
/// @note Covers Requirmenets CCO-CDD-1074
void vid_TpSetReceiveCallBack(void(*ptr_UserCallback)(void));


/// @brief This function is used to enable upper modules to set a callback function to notify a successful transmission of data units 
///        in the Tp module
/// @param ptrFunc pointer to the notify function in the upper layer
/// @note Covers Requirmenets CCO-CDD-1081
void vid_TpSetTransmitCallBack(void(*ptr_UserCallback)(void));


/// @brief enables the iso tp protocol processing when receiving, used with UDS Handler and OBD handler (with modes 3 and 9 only)
/// @param u32_FlowControlID to send ISO-TP flow control frame
/// @note Covers Requirmenets CCO-CDD-1083
void vid_IsoTpSet(u32_t u32_FlowControlID);


/// @brief function called by upper layer (ISO_CAN_15765) to set CAN Frame type (standard or extended)
/// @param CANFrameType IDE Byte (standard or Extended)
/// @note Covers Requirmenets CCO-CDD-1085
void vid_TpsetCanFrameType(u8_t CANFrameType);


/*__________services Used in Lower layers___________*/

/// @brief Function to be called in the lower layer to indicate a reception of a CAN Frame
///  @note Covers Requirmenets CCO-CDD-1076
void vid_TpReceptionIndicator(void);

/// @brief Function to be called in the lower layer to indicate a Successful Transmission of a CAN Frame
///  @note Covers Requirmenets CCO-CDD-1075
void vid_TpTransmissionIndicator(void);



/*__________services called periodically ___________*/

/// @brief tp task called periodically in application, function checks if there is a reception or not, if reception occurs it processes the msg
///        based on the type of diagnsotic frame uds or obd
///  @note Covers Requirmenets CCO-CDD-1071
void vid_TpManage(void);





#endif

