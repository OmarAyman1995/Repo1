/**
 * @file UDSHandler.c
 * @author  Ahmed Bahaa Alkomy - (https://crewteq.com/)
 
 * @brief  this file contains the functions offered by UDSHanlder Module

 * @version 1.6.0
 * @date 2023-11-20
 * 
 * @copyright Copyright (crewteq) 2023 
 */

#include "UDSHandler.h"
#include "UDSHandlerConfig.h"
#include "services.h"
#include "CANTp.h"


/*_____________________________Constant Macros_________________________________*/
#define SID_BYTE0_INDEX               (u8_t)  0U
#define REJECTED_SID_INDEX            (u8_t)  1U
#define NRC_INDEX                     (u8_t)  2U

#define BYTE0_INDEX      (u8_t) 0U
#define BYTE1_INDEX      (u8_t) 1U
#define BYTE2_INDEX      (u8_t) 2U
#define BYTE3_INDEX      (u8_t) 3U
#define BYTE4_INDEX      (u8_t) 4U
#define BYTE5_INDEX      (u8_t) 5U
#define BYTE6_INDEX      (u8_t) 6U
#define BYTE7_INDEX      (u8_t) 7U

/*_____________________________Global Variables____________________________*/

/// @brief structure to store received DataUnit from CanTp
///  @note  Cover Requiremnet CCO-CDD-1113
UDSReceiveInfo_t          GLOB_SduDataUnit={0}; 


/// @brief pointer to received DataPayload in CAN TP
///  @note  Cover Requiremnet CCO-CDD-1133
TpReceiveDataUnitInfo_t GLOB_PtrToTpDataUnit = {0};

/// @brief status of module for request status indication
///  @note  Cover Requiremnet CCO-CDD-1114
UdsHandlerStatus_e     GLOB_UdsState;        

/// @brief services that requires a DID (two bytes)
///  @note  Cover Requiremnet CCO-CDD-1115
const u8_t GLOB_ServicesWithDID[]={0x62,0x6A,0x6E,0x6C}; 


/// @brief pointer to function for reception callback function
/// @note Covers Requirmenets CCO-CDD-1116
PRIVATE void(*GLOB_pCallbackfunc1)(void)=NULL;                                      

/// @brief pointer to function for transmission callback function
/// @note Covers Requirmenets CCO-CDD-1117
PRIVATE void(*GLOB_pCallbackfunc2)(void)=NULL;     


/*______________________Private Functions Prototypes____________________________*/

/// @brief function to decide response SID type (has a DID num, has a subfunction, negative SID)
/// @param responseSID SID number of response
/// @return NEGATIVE_SID_RESPONSE , POSITIVE_SID_DID_TYPE , POSITIVE_SID_SUB_FUNC_TYPE
/// @note Covers Requirmenets CCO-CDD-1132 
u8_t u8DecideSIDType(u8_t responseSID);

/// @brief this function seprated the SID , DID/SubFunction and Data Payload and assign them into separte variables 
///         function assigns Reponse ID, Data size, Response Type, Service Option (DID/SUB_Func)
/// @param DataUnitBuffer the incoming data buffer from comManger
void vid_NegativeResponseFrameProcessing(u8_t *DataUnitBuffer);


/// @brief this function seprated the SID , DID/SubFunction and Data Payload and assign them into separte variables 
///         function assigns Reponse ID, Data size, Response Type, Service Option (DID/SUB_Func)
/// @param DataUnitBuffer the incoming data buffer from comManger
/// @return 
void vid_PositiveFrameWithDIDProcessing(const u8_t *DataUnitBuffer,u16_t size);

/// @brief this function seprated the SID , DID/SubFunction and Data Payload and assign them into separte variables 
///         function assigns Reponse ID, Data size, Response Type, Service Option (DID/SUB_Func)
/// @param DataUnitBuffer the incoming data buffer from comManger
void vid_PositiveFrameWithSubFuncProcessing(const u8_t *DataUnitBuffer,u16_t size);


/// @brief this function is responsible for seperating and assigning incoming Data units from Lower module and prepare it to upper modules
/// @param DataPayload received DataPayload from Lower Component (CAN TP)
enumUdsHandlerApiError_e UdsProcessing(TpReceiveDataUnitInfo_t* DataPayload);


/// @brief callback function called by lower SWC to indicate a Transmission Complete
void vid_UdsHandlerTransmissionCallback (void);


/// @brief callback function called by lower SWC to indicate a reception Complete
void vid_UdsHandlerReceptionCallback (void);


/// @brief empty function to avoid hard fault error resulted from not setting pointer to functions (reception notify and transmission notify)
///        this occurs when SWC user forgets to call Tp_init function
///        address of the function is assigned to the Global pointer to functions at the Tp_Init function
PRIVATE void CallbackPtrDefaultFunc(void);

/*______________________Private Functions Implementation____________________________*/

PRIVATE void CallbackPtrDefaultFunc(void)
{
  /*do nothing*/
}


/*_________________________________________________________________________________________________________________________________________*/

 u8_t u8DecideSIDType(u8_t responseSID)
{
  u8_t returnValue=0;
  i32_t searchResult=0;

  /*check if the SID is negative SID*/
  if(responseSID==NEGATIVE_SID_RESPONSE)
  {
    returnValue=NEGATIVE_SID_TYPE;
  }
  
  /*if not*/
  else
  {
    /*search for the SID in the Services with a DID number*/
     searchResult=linearSearch(responseSID,GLOB_ServicesWithDID,sizeof(GLOB_ServicesWithDID)/sizeof(GLOB_ServicesWithDID[0]));

    /*if SID is not found*/
     if(searchResult!=NEGATIVE_SEARCH)
     {
      /*Service has a DID, DID two bytes will be needed to be seprated from the datapayload */
      returnValue=POSITIVE_SID_DID_TYPE;
     }
   
     else
     {
      /*Service has a sub function, one bytes will be needed to be seprated from the datapayload */
      returnValue=POSITIVE_SID_SUB_FUNC_TYPE;
     }

  }

return returnValue;
}


/*____________________________________________________________________________________________________________________________________*/

void vid_NegativeResponseFrameProcessing( u8_t *DataUnitBuffer)
{
  /*assign response Type*/
   GLOB_SduDataUnit.ResponseType=NEGATIVE_RESPONSE;

   /*assign NRC to the first byte of uds data unit buffer*/
   GLOB_SduDataUnit.DataPayloadBuffer=DataUnitBuffer+NRC_INDEX;

   /*assign size to be equal 1*/
   GLOB_SduDataUnit.DataPayloadSize=1;
}


/*___________________________________________________________________________________________________________________________________________*/

void vid_PositiveFrameWithDIDProcessing(const u8_t *DataUnitBuffer,u16_t size)
{
  /*assign response type*/
  GLOB_SduDataUnit.ResponseType=POSITIVE_RESPONSE;

  /*copy data payload in sdu buffer*/
  cpy_array(GLOB_SduDataUnit.DataPayloadBuffer
            ,DataUnitBuffer+BYTE3_INDEX
            ,size-3);
  /*assign size (size is input size minus 1 SID byte and 2 DID bytes)*/
  GLOB_SduDataUnit.DataPayloadSize=size-3;
}


/*______________________________________________________________________________________________________________________________________*/

 void vid_PositiveFrameWithSubFuncProcessing(const u8_t *DataUnitBuffer,u16_t size)
{

  GLOB_SduDataUnit.ResponseType=POSITIVE_RESPONSE;

  cpy_array(GLOB_SduDataUnit.DataPayloadBuffer
            ,DataUnitBuffer+BYTE2_INDEX
            ,size-2);

  GLOB_SduDataUnit.DataPayloadSize=size-2;
}


/*______________________________________________________________________________________________________________________________________________*/

enumUdsHandlerApiError_e UdsProcessing( TpReceiveDataUnitInfo_t* DataPayload)
{
    enumUdsHandlerApiError_e LOC_ApiReturnValue=UDS_HANDLER_API_OK;
    u8_t LOC_SIDType=0;

    /*decide type of response SID*/
     LOC_SIDType=u8DecideSIDType(DataPayload->u8TpDataPayload[SID_BYTE0_INDEX]);
    
    switch (LOC_SIDType)
    {
      /*case of negative SID*/
      case NEGATIVE_SID_TYPE:
      vid_NegativeResponseFrameProcessing(DataPayload->u8TpDataPayload);
      break;

      /*case of SID that has A DID Number*/
      case POSITIVE_SID_DID_TYPE:
      vid_PositiveFrameWithDIDProcessing(DataPayload->u8TpDataPayload,DataPayload->u8DataPayloadSize);
      break;
      
      /*case of SID that has A Sub Function Number*/
      case POSITIVE_SID_SUB_FUNC_TYPE:
      vid_PositiveFrameWithSubFuncProcessing(DataPayload->u8TpDataPayload,DataPayload->u8DataPayloadSize);
      break;

      default:
      LOC_ApiReturnValue=UDS_HANDLER_API_NOK;

    }
  return LOC_ApiReturnValue;
}


/*___________________________________________Public Functions Implementation_____________________________________________________________*/

/*________________________________________________________________________________________________________________________________________*/
/// @brief function calls the init function of the ComManager, intiatlizes the goal variables 
///        and subscribes the module to the com manager module
void vid_UDSHandlerInit(void)
{

   /*initalize global Variables*/
   GLOB_UdsState=FREE;                                   
   GLOB_pCallbackfunc1=CallbackPtrDefaultFunc;
   GLOB_pCallbackfunc2=CallbackPtrDefaultFunc;


   /* set transmisison and reception callback in lower layer*/
   vid_TpSetReceiveCallBack(vid_UdsHandlerReceptionCallback);
   vid_TpSetTransmitCallBack(vid_UdsHandlerTransmissionCallback);


}


/*______________________________________________________________________________________________________________________________________________*/

UdsHandlerStatus_e enum_GetUdsHandlerStatus(void)
{
    return GLOB_UdsState;
}

/*______________________________________________________________________________________________________________________________________________*/

enumUdsHandlerApiError_e enum_UdsHandlerSetReceptionNotify(void(*ptr_UserCallback)(void))
{
    enumUdsHandlerApiError_e LOC_ApiReturnValue=UDS_HANDLER_API_OK;
     if(ptr_UserCallback != NULLPTR)
     {
        GLOB_pCallbackfunc1 = ptr_UserCallback;
        LOC_ApiReturnValue=UDS_HANDLER_API_OK;
     }

     else
     {
        /*do nothing*/
        LOC_ApiReturnValue=UDS_HANDLER_API_NOK;
     }

     return LOC_ApiReturnValue;

}

/*______________________________________________________________________________________________________________________________________________*/

enumUdsHandlerApiError_e enum_UdsHandlerSetTransmissionNotify(void(*ptr_UserCallback)(void))
{

       enumUdsHandlerApiError_e LOC_ApiReturnValue=UDS_HANDLER_API_OK;

     if(ptr_UserCallback != NULLPTR)
     {
        GLOB_pCallbackfunc2 = ptr_UserCallback;
        LOC_ApiReturnValue=UDS_HANDLER_API_OK;

     }

     else
     {
        /*do nothing*/
        LOC_ApiReturnValue=UDS_HANDLER_API_NOK;
     }
  return LOC_ApiReturnValue;
}
    

/*______________________________________________________________________________________________________________________________________________*/

void vid_UdsHandlerTransmissionCallback (void)
{
    /*set Module status to indicate request has been sent, and set return value to API ok*/
    GLOB_UdsState=REQUEST_SENT;

  
    
    /*call calback funtion of the upper layer*/
    GLOB_pCallbackfunc1();

}


void vid_UdsHandlerReceptionCallback (void)
{

   /*get received Data unit from Lower Layer*/
   struct_GetTpReceivedDataUnit(GLOB_PtrToTpDataUnit.u8TpDataPayload,&GLOB_PtrToTpDataUnit.u8DataPayloadSize);
   
   /*set module state*/
   GLOB_UdsState=REQUEST_RESPONSE_RECEIVED;

   /*reset ISO-TP Option in CAN Tp Module*/
     
   
}


/*______________________________________________________________________________________________________________________________________________*/

 UDSReceiveInfo_t* vid_ReceiveUdsData(void)
{
 UDSReceiveInfo_t *returnPtrStruct=NULL;

  if(GLOB_UdsState!= DATA_READY)
  {
     returnPtrStruct=NULL;

  }
  
  else
  {
    /*set module to Free*/
    GLOB_UdsState=FREE;
    returnPtrStruct= &GLOB_SduDataUnit;
  }

  return returnPtrStruct;

}


void vid_UDSHandlerManage(void)
{
  /*check for Component State , if a response is received and needs to be processed*/
  if(GLOB_UdsState==REQUEST_RESPONSE_RECEIVED)
  {
    /*process Response*/
     UdsProcessing(&GLOB_PtrToTpDataUnit);

    /*set Module State to Data Unit ready*/
    GLOB_UdsState=DATA_READY;
    
    /*clear ISOTpOption*/
     

    /*Call the Reception Call back funtion of upper layer*/
    GLOB_pCallbackfunc1();
  }

  else
  {
    /*do nothing*/
  }

}








/*__________________________________________________________________________________________________________________*/
/// @note - This Service Uses a DID Num - between 0xF180 and 0xF19E
///       - Bytes sent are three bytes One Byte SID - Two Bytes DID
enumUdsHandlerApiError_e enum_RequestReadByIdentifier(const UDSTransmitInfo_t *inputStruct)
{

    TpTransmitDataUnitInfo LOC_DataUnitToSend={0};      /*structure containing data unit going to ComMangr*/
    enumTpApiError_e LOC_returnValue=0;
    enumUdsHandlerApiError_e LOC_ApiReturnValue=0;   /*API return Value*/
   

    /*validate Service Option Num (DID/Sub Func) is within Service Standard DID's Range*/
    /*if Valid*/
    if((inputStruct->ServiceOption >=READ_BY_IDENTIFIER_RANGE_L_LIMIT) && (inputStruct->ServiceOption <=READ_BY_IDENTIFIER_RANGE_H_LIMIT))
      
      {
             /*copy data of the input structure to the data unit */
             LOC_DataUnitToSend.u8TpDataPayload [0]                  =  READ_BY_IDENTIFIER_SID;
             LOC_DataUnitToSend.u8TpDataPayload [1]                  =  (u8_t) (inputStruct->ServiceOption>>8);
             LOC_DataUnitToSend.u8TpDataPayload [2]                  =  (u8_t)(inputStruct->ServiceOption) & READ_BY_IDENTIFIER_R_BYTE_MASK ;

             /*copy size of data to structure data unit*/
             LOC_DataUnitToSend.u8DataPayloadSize       =  READ_BY_IDENTIFIER_BYTES_COUNT;

             /*Assign Can ID*/
             LOC_DataUnitToSend.DiagnosticCANID         =  inputStruct->DiagnosticCanID;

             LOC_DataUnitToSend.FlowControlCANID = inputStruct->responseCanID;
             
            /*send data unit to COM manager module*/
             LOC_returnValue = vid_TpTransmitDataUnit(&LOC_DataUnitToSend);
            
            /*check the return of the CanCom_setRequest function*/
            /*if not OK*/
             if(CAN_TP_API_OK!=LOC_returnValue)
             {
              /*return error*/
             LOC_ApiReturnValue=API_ERROR_REQUEST_SENDING_FAILED;
             }

             else
             {
              /*Update Handler module Status and return transmit pending*/
             GLOB_UdsState=REQUEST_PENDING_CONFIRMATION;
             LOC_ApiReturnValue=API_OK_TRANSMIT_PENDING;

             }
      }

    /*if DID/Sub is out of range*/
      else
      {
          LOC_ApiReturnValue=API_ERROR_SERVICE_CODE_INVALID;
      }
  return LOC_ApiReturnValue;
}


/*___________________________________________________________________________________________________________________*/
/// @note - This Service Uses a Sub Function Num - either 0x00 (SuppressPosResMsgIndication Not supported)
///                                              -   or   0x80 (SuppressPosResMsgIndication supported)
///       - Bytes sent are two bytes One Byte SID and one byte Sub function
enumUdsHandlerApiError_e enum_RequestTesterPresent(const UDSTransmitInfo_t *inputStruct)
{

    enumUdsHandlerApiError_e LOC_ApiReturnValue=0;   /*API return Value*/
    enumTpApiError_e LOC_returnValue=0;
    TpTransmitDataUnitInfo LOC_DataUnitToSend={0};                                  /*structure containing data unit going to ComMangr*/

    /*validate Service Option Num (DID/Sub Func) is within Service Standard DID's Range*/
    /*if Valid*/
    if(inputStruct->ServiceOption == TESTER_PRESENT_SUB_VALUE_1 || inputStruct->ServiceOption == TESTER_PRESENT_SUB_VALUE_2)
      
      {
             /*copy data of the input structure to the data unit going to COM Manger*/
             LOC_DataUnitToSend.u8TpDataPayload [0]                  =  TESTER_PRESENT_SID;
             LOC_DataUnitToSend.u8TpDataPayload [1]                  =  (u8_t)(inputStruct->ServiceOption);

             /*copy size of data to structure data unit*/
             LOC_DataUnitToSend.u8DataPayloadSize       =  TESTER_PRESENT_BYTES_COUNT;

             /*Assign Can ID*/
             LOC_DataUnitToSend.DiagnosticCANID         =  inputStruct->DiagnosticCanID;

            /*send data unit to COM manager module*/
            LOC_returnValue = vid_TpTransmitDataUnit(&LOC_DataUnitToSend);
            
            /*check the return of the CanCom_setRequest function*/
            /*if not OK*/
             if(CAN_TP_API_OK!=LOC_returnValue)
             {
              /*return error*/
             LOC_ApiReturnValue=API_ERROR_REQUEST_SENDING_FAILED;
             }

             else
             {
              /*Update Handler module Status and return transmit pending*/
             GLOB_UdsState=REQUEST_PENDING_CONFIRMATION;
             LOC_ApiReturnValue=API_OK_TRANSMIT_PENDING;

             }
      }

      /*if DID/Sub is out of range*/
      else
      {
      LOC_ApiReturnValue=API_ERROR_SERVICE_CODE_INVALID;
      }

  return LOC_ApiReturnValue;

}


/*___________________________________________________________________________________________________________________*/
/// @note - This Service Uses a Sub Function Num -  0x1  (Hard reset)
///                                              -  0x2  (Key Off On reset)
///                                              -  0x3  (Software reset)
///                                              -  0x4  (Enable Rapid Power Shutdown)
///                                              -  0x5  (Disable Rapid Power shut down)
///       - Bytes sent are two bytes One Byte SID and one byte Sub function
enumUdsHandlerApiError_e enum_RequestEcuReset(const UDSTransmitInfo_t *inputStruct)
{

    TpTransmitDataUnitInfo LOC_DataUnitToSend={0};                                  /*structure containing data unit going to ComMangr*/
    enumTpApiError_e LOC_returnValue=0;
    enumUdsHandlerApiError_e LOC_ApiReturnValue=0;   /*API return Value*/


    /*validate Service Option Num (DID/Sub Func) is within Service Standard DID's Range*/
    /*if Valid*/
    if(inputStruct->ServiceOption <=ECU_RESET_RANGE_H_LIMIT)
      
      {
             /*copy data of the input structure to the data unit going to COM Manger*/
             LOC_DataUnitToSend.u8TpDataPayload [0]                  =  ECU_RESET_SID;
             LOC_DataUnitToSend.u8TpDataPayload [1]                  =  (u8_t)(inputStruct->ServiceOption);

             /*copy size of data to structure data unit*/
             LOC_DataUnitToSend.u8DataPayloadSize     =  ECU_RESET_BYTES_COUNT;

             /*Assign Can ID*/
             LOC_DataUnitToSend.DiagnosticCANID        =  inputStruct->DiagnosticCanID;

            /*send data unit to COM manager module*/
             LOC_returnValue = vid_TpTransmitDataUnit(&LOC_DataUnitToSend);

            
            /*check the return of the CanCom_setRequest function*/
            /*if not OK*/
             if(CAN_TP_API_OK!=LOC_returnValue)
             {
              /*return error*/
             LOC_ApiReturnValue=API_ERROR_REQUEST_SENDING_FAILED;
             }

             else
             {
              /*Update Handler module Status and return transmit pending*/
             GLOB_UdsState=REQUEST_PENDING_CONFIRMATION;
             LOC_ApiReturnValue=API_OK_TRANSMIT_PENDING;

             }
      }

      /*if DID/Sub is out of range*/
      else
      {
      LOC_ApiReturnValue=API_ERROR_SERVICE_CODE_INVALID;
      }

  return LOC_ApiReturnValue;
}


















