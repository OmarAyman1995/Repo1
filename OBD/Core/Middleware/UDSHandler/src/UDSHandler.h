/**
 * @file UDSHandler.h
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief  

 * @version 1.6.0
 * @date 2023-11-20
 * 
 * @copyright Copyright (crewteq) 2023 
 */

#ifndef UDS_HANDLER
#define UDS_HANDLER

#include "typedefs.h"
   
/*________________________________Data Types_______________________________*/

/**
 * @brief this enumeration defines the component error states
 * @note  Cover Requiremnet CCO-CDD-1110 
 * 
 */
typedef enum
{                            
  API_ERROR_SERVICE_CODE_INVALID,                         
  API_ERROR_REQUEST_SENDING_FAILED,
  API_ERROR_RESPONSE_RECEPTION_FAILED,
  API_OK_TRANSMIT_PENDING, 
  UDS_HANDLER_API_OK,
  UDS_HANDLER_API_NOK,                                              
}enumUdsHandlerApiError_e;


/**
 * @brief this enumeration defines the component operating states
 * @note  Cover Requiremnet CCO-CDD-1111
 * 
 */
typedef enum 
{
    FREE,
    REQUEST_PENDING_CONFIRMATION,
    REQUEST_SENT,
    REQUEST_RESPONSE_RECEIVED,
    REQUEST_SEND_FAILED,
    REQUEST_RESPONSE_FAILED,
    DATA_READY
}UdsHandlerStatus_e;


/**
 * @brief this enumeration defines the UDS Response Types
 * @note  Cover Requiremnet CCO-CDD-1112
 */
typedef enum
{
  POSITIVE_RESPONSE,
  NEGATIVE_RESPONSE,
  UNKNOWN_RESPONSE
}UdsResponseFrameType;


/**
 * @brief structure that holds UDSDataUnit recieved from lower layers
 * @note  Cover Requiremnet CCO-CDD-1150
 * 
 */
typedef struct 
{
    /// @brief Data Payload size
    u16_t DataPayloadSize;                          /*Data Payload size*/

    /// @brief positive Response or negative response
    UdsResponseFrameType ResponseType;              

    /// @brief pointer to DataPayload in CAN TP
    u8_t* DataPayloadBuffer;                        
}UDSReceiveInfo_t;


/*structure that holds UDSDataUnit sent and recieved from lower layers*/

/**
 * @brief structure that holds UDSDataUnit sent and recieved from lower layers
 * @note  Cover Requiremnet CCO-CDD-1112
 */
typedef struct 
{
    /// @brief UDS Service Name
    u8_t  ServiceID;  

    /// @brief Could be the DID or Sub function asscoiated with the Service
    u16_t ServiceOption;                            

    /// @brief The diagnostic CAN ID to send diagnostic request
    u32_t DiagnosticCanID;                          

    /// @brief ID that I will get response from
    u32_t responseCanID;                            
    
}UDSTransmitInfo_t;

/*________________________________Functions Prototype_______________________________*/

/// @brief Function for initalizing Module and setting Transmission and reception callback
///  @note  Cover Requiremnet CCO-CDD-1119
void vid_UDSHandlerInit(void);

/// @brief Function to be used by upper layers to receive Response DataUnits from UDS Handler 
/// @return API error state
///  @note  Cover Requiremnet CCO-CDD-1125
UDSReceiveInfo_t* vid_ReceiveUdsData(void);

/// @brief returns the status of the handler module
/// @return status of the handler
///  @note  Cover Requiremnet CCO-CDD-1126
UdsHandlerStatus_e enum_GetUdsHandlerStatus(void);

/// @brief sets a callback funtion to e called for transmission notify
/// @param ptr_UserCallback pointer to the address of the callback function
/// @return API return error
///  @note  Cover Requiremnet CCO-CDD-1127
enumUdsHandlerApiError_e enum_UdsHandlerSetTransmissionNotify(void(*ptr_UserCallback)(void));


/// @brief sets a callback funtion to e called for reception notify
/// @param ptr_UserCallback pointer to the address of the callback function
/// @return API return error
///  @note  Cover Requiremnet CCO-CDD-1128
enumUdsHandlerApiError_e enum_UdsHandlerSetReceptionNotify(void(*ptr_UserCallback)(void));


 /*___________________________UDS Services_________________________*/

/// @brief Function Validates Service Option Num (DID/sub func) and if valid sends a read by identifer Request
/// @param inputStruct structure from upper layer containing CAN Diagnsotic ID,DID
/// @return API error type
///  @note  Cover Requiremnet CCO-CDD-1129
enumUdsHandlerApiError_e enum_RequestReadByIdentifier(const UDSTransmitInfo_t *inputStruct);



/// @brief Function to request UDS Service Tester Present
/// @param inputStruct structure from upper layer containing CAN Diagnsotic ID,DID
/// @return API error type
///  @note  Cover Requiremnet CCO-CDD-1130
enumUdsHandlerApiError_e enum_RequestTesterPresent(const UDSTransmitInfo_t *inputStruct);

/// @brief Function to request UDS Service ECU reset
/// @param inputStruct structure from upper layer containing CAN Diagnsotic ID,DID
/// @return API error type
///  @note  Cover Requiremnet CCO-CDD-1131
enumUdsHandlerApiError_e enum_RequestEcuReset(const UDSTransmitInfo_t *inputStruct);


/*___________________________Periodic Function_________________________*/

/// @brief Function Called periodically to check for any new reception, process the reception and delivery a new Data unit to upper layer without the UDS Bytes (SID,DID/SUB)
void vid_UDSHandlerManage(void);






















#endif