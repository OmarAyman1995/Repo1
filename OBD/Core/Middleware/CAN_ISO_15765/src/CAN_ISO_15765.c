#include "CAN_ISO_15765.h"
#include "CAN_ISO_Cnfg.h"
#include "typedefs.h"
#include "services.h"
#include "Can.h"
#include "CANConfig.h"
#include "CANTp.h"
#include "QueueInterface.h"

#define MAX_CAN_FRAME_DATAPAYLOAD    8


/*________________________________________DATA_________________________________________*/

#if CAN_ISO_UT == OFF

/**
 * @brief Variable to store CAN Frame ID Type (Standard or extended ID)
 * @note Cover Requirement CCO-CDD-1512
 */
PRIVATE u8_t  GLOB_u8CanIDType;

/**
 * @brief Variale to store CAN ID for functional requests
 * @note  Cover Requirement CCO-CDD-1513
 */
PRIVATE u32_t GLOB_u32DiagnosticCANID;

/**
 * @brief Flag to indicate that reception has occured
 * @note  Cover Requirement CCO-CDD-1514
 */
PRIVATE u8_t GLOB_ReceptionSuccessFlag=FLAG_CLEAR;

/**
 * @brief Flag to indicate that Transmition is complete
 * @note  Cover Requirement CCO-CDD-1515
 * 
 */
PRIVATE u8_t GLOB_TransmitSuccessFlag=FLAG_CLEAR;

/**
 * @brief counter to compare it with Timeout period 
 * @note  Cover Requirement CCO-CDD-1516
 * 
 */
PRIVATE u32_t GLOB_u32TimeoutCount=0;

/// @brief pointer to function for reception callback function
/// @note Covers Requirmenets CCO-CDD-1065
PRIVATE void(*GLOB_ReceptionCallback)(void)=NULL;                                      
 
/// @brief pointer to function for transmission callback function
/// @note Covers Requirmenets CCO-CDD-1064
PRIVATE void(*GLOB_TransmissionCallback)(void)=NULL;  

PRIVATE u8_t GLOB_u8ISOComplint = 0;

#else
u8_t  GLOB_u8CanIDType;
u32_t GLOB_u32DiagnosticCANID;
u8_t GLOB_ReceptionSuccessFlag=FLAG_CLEAR;
u8_t GLOB_TransmitSuccessFlag=FLAG_CLEAR;
u32_t GLOB_u32TimeoutCount=0;
u8_t GLOB_u8ISOComplint = 0;
void(*GLOB_ReceptionCallback)(void)=NULL;                                      
void(*GLOB_TransmissionCallback)(void)=NULL;  

#endif



/*________________________________________________Private Functions Prototypes_______________________________*/

#if CAN_ISO_UT == OFF

/// @brief Function echos (sends) a simple OBD Request for vehicle speed (02,01,0D)
/// @param  CAN_ID Can ID to send msg on(11 bit and 29 bit)
/// @return API Error State
/// @note  Cover Requirement CCO-CDD-1517
PRIVATE enum_CanIsoErrorState enum_EchoFunctionalRequest(u32_t CAN_ID);

/// @brief checks if a timeout has occured due to transmission failling
/// @return Transmit SUCCESS  or TRANSMIT FAILED
/// @note  Cover Requirement CCO-CDD-1518
PRIVATE u8_t u8_CheckFlagState(u8_t *u8Flag);

/// @brief runs verification procedure for 29 bit and 11 identifers according to ISO 15765
/// @param  CAN_ID Can ID to send msg on (11 bit and 29 bit)
/// @return ISO Compilant or not
/// @note  Cover Requirement CCO-CDD-1519
PRIVATE enum_IsoCompliantState enum_VerifyCanID(u32_t CAN_ID);

/// @brief callback funtion called upon successful Transmition, function sets a global flag 
/// @note  Cover Requirement CCO-CDD-1520
PRIVATE void vid_TransmitCallback(void);

/// @brief callback funtion called upon  reception, function sets a global flag
/// @note  Cover Requirement CCO-CDD-1521
PRIVATE void vid_ReceiveCallback(void);

#else
enum_CanIsoErrorState enum_EchoFunctionalRequest(u32_t CAN_ID);
u8_t u8_CheckFlagState(u8_t *u8Flag);
enum_IsoCompliantState enum_VerifyCanID(u32_t CAN_ID);
void vid_TransmitCallback(void);
void vid_ReceiveCallback(void);

#endif

/*________________________________________________Public Functions Implementation_______________________________*/

/*_________________________________________________________________________________*/

enum_CanIsoErrorState enum_CanIsoinit(void)
{
   vid_TpSetTransmitCallBack(vid_TransmitCallback);
   vid_TpSetReceiveCallBack(vid_ReceiveCallback);

   return CAN_ISO_OK;
}

/*_________________________________________________________________________________*/

enum_CanIsoErrorState enum_CanIsoSendData (const u8_t *DataArray, u8_t  size)
{
    enum_CanIsoErrorState LOC_ApiReturnValue=CAN_ISO_OK;

    /*construct CAN Frame*/
    strCanDrvFrameInfo LOC_CANFrame={
    .RTR=DATA_FRAME,
    .DLC=MAX_CAN_FRAME_DATAPAYLOAD ,
    .IDE=GLOB_u8CanIDType,
    .FrameID=GLOB_u32DiagnosticCANID
  };

    /*Error Handling for Input Arguments*/
   if( DataArray==NULL ||size> MAX_CAN_FRAME_DATAPAYLOAD  )
   {
      /*Return Not OK*/
      LOC_ApiReturnValue=CAN_ISO_NOK;
   }
   
   /*if no error with input arguments */
   else
   {
      /*put the input data in the Can Frame Data Field*/
      cpy_array(LOC_CANFrame.data, DataArray, size); 


     /*Send CAN Frame*/ 
    enum_CanDrvTransmit(&LOC_CANFrame);
   }

   
   return LOC_ApiReturnValue;

}

/*_________________________________________________________________________________*/

enum_IsoCompliantState enum_DetectCANComm (const u32_t *u8baudrateRecord,u8_t size)
{
    enum_IsoCompliantState LOC_ApiReturnValue= ISO15765_NOT_COMPLIANT;
    enum_IsoCompliantState LOC_VerifyReturnvalue=0;
    u8_t u8Count=0; /*counter for Iteration on buad record*/

    /*error Handling for Input Arguments*/
    if (u8baudrateRecord == NULL || size > MAX_BAUDRATE_RECORD_SIZE)
    {
        LOC_ApiReturnValue=ERROR_IN_BAUDRATE_RECORD;
    }
    
    /*if Input Arguments are valid*/
    else
    {
      /* iterate on the baudrateRecord Given*/
       while (u8Count<size && LOC_ApiReturnValue!= ISO15765_COMPLIANT)
       {
              /*set bit timing of the CAN Driver according to the current baudrate in the record*/
              enum_CanDrvSetBitTiming(u8baudrateRecord[u8Count],CLOCK);

              /*execute verification procedure for 11 Bit ID*/
              LOC_VerifyReturnvalue=enum_VerifyCanID(DIAGNOSTIC_CAN_ID_11BIT);

               if(LOC_VerifyReturnvalue == ISO15765_COMPLIANT)
              {
                 /*set Functional Addressing CAN ID to global variable*/
                 GLOB_u32DiagnosticCANID=DIAGNOSTIC_CAN_ID_11BIT;

                 /*set CAN Frame ID Type to standrad */
                 GLOB_u8CanIDType=STANDARD_FORMAT;

                 /*return ISO Compliant*/
                 LOC_ApiReturnValue=ISO15765_COMPLIANT;

                 GLOB_u8ISOComplint = 1;
              }

          else
          {
              /*execute Verification Procedure for 29 Bit ID*/
              LOC_VerifyReturnvalue=enum_VerifyCanID(DIAGNOSTIC_CAN_ID_29BIT);

              if(LOC_VerifyReturnvalue == ISO15765_COMPLIANT)
              {
                /*set Functional Addressing CAN ID to global variable*/
               GLOB_u32DiagnosticCANID=DIAGNOSTIC_CAN_ID_29BIT;

               /*set CAN Frame ID Type to standrad */
               GLOB_u8CanIDType=EXTENDED_FORMAT;

               /*return ISO Compliant*/
               LOC_ApiReturnValue=ISO15765_COMPLIANT;
               GLOB_u8ISOComplint = 1;
              }

              else
              {
                /*return ISO NOT COMPLIANT as a result*/
              LOC_ApiReturnValue= ISO15765_NOT_COMPLIANT;
              }
          }       

          u8Count++;

        }
    }

    



    return LOC_ApiReturnValue;
}


void vid_CanIsoSetReceiveCallBack(void(*ptr_UserCallback)(void))
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_ReceptionCallback== NULL))
     {
        GLOB_ReceptionCallback = ptr_UserCallback;
     }

      else
     {
        /*do nothing*/
     }
}

void vid_CanIsoSetTransmitCallBack(void(*ptr_UserCallback)(void))
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_TransmissionCallback== NULL))
     {
        GLOB_TransmissionCallback = ptr_UserCallback;
     }

      else
     {
        /*do nothing*/
     }
}


void CanIsoReceive(u8_t* DataPayloadBuffer,u16_t* size)
{
  
  /*Get Data from CAN Tp*/
  struct_GetTpReceivedDataUnit(DataPayloadBuffer,size);
  

}

/*________________________________________________Private Functions Implementation_______________________________*/

/*_________________________________________________________________________________*/


enum_CanIsoErrorState enum_EchoFunctionalRequest(u32_t CAN_ID)
{
    enum_CanIsoErrorState LOC_ApiReturnValue=0;
    EnumCanDrvApiError    LOC_returnValue=CAN_API_OK;
    
    /*construct CAN Frame with a OBD request in the data field to request vehicle speed*/
    strCanDrvFrameInfo LOC_CANFrame={
    .RTR=DATA_FRAME,
    .DLC=MAX_CAN_FRAME_DATAPAYLOAD ,
    .IDE=GLOB_u8CanIDType,
    .FrameID=CAN_ID,
    .data={2,0x01,0x0D,0xAA,0xAA,0xAA,0xAA,0xAA}
  };

/*Send CAN Frame*/ 
LOC_returnValue=enum_CanDrvTransmit(&LOC_CANFrame);

/*error Handling*/
if (LOC_returnValue==CAN_ISO_NOK)
{
    LOC_ApiReturnValue=CAN_ISO_NOK;
}

else
{
    /*do nothing*/
}

return LOC_ApiReturnValue;

}

/*_________________________________________________________________________________*/

 enum_IsoCompliantState enum_VerifyCanID(u32_t CAN_ID)
{
    enum_IsoCompliantState LOC_ApiReturnValue=ISO15765_NOT_COMPLIANT;
    u8_t LOC_u8TransmitState=0;
    u8_t LOC_u8ReceptionState=0;

        /*send an echo frame on input CAN Address*/
        enum_EchoFunctionalRequest(CAN_ID);

        /* busy wait for transmit flag until its set or timeout occurs*/
        LOC_u8TransmitState=u8_CheckFlagState(&GLOB_TransmitSuccessFlag);
        
        /*check on transmit state, if transmit failed*/
        if (LOC_u8TransmitState==OPERATION_FAILED)
        {   
            /*return ISO_NOT_COMPLIANT*/
            LOC_ApiReturnValue=ISO15765_NOT_COMPLIANT;
        }
        
        /*else if success*/
        else
        {
              /*busy wait on reception flag until its set or timeout occurs */
              LOC_u8ReceptionState=u8_CheckFlagState(&GLOB_ReceptionSuccessFlag);
              
              /*check on the Function return, if No Reception occured*/
              if(LOC_u8ReceptionState==OPERATION_FAILED)
              {
                /*return not COMPLIANT*/
                LOC_ApiReturnValue=ISO15765_NOT_COMPLIANT;
              }
              
              /*if Reception happened, */
              else
              {
                /*return ISO COMPLIANT*/
                   LOC_ApiReturnValue=ISO15765_COMPLIANT;
              }
        }

    return LOC_ApiReturnValue;
}

/*_________________________________________________________________________________*/

u8_t u8_CheckFlagState(u8_t* u8Flag)
{
    u8_t LOC_ApiReturnValue=0;
    
    /* busy wait unitl Transmit is Successful*/
         while (*u8Flag == FLAG_CLEAR && GLOB_u32TimeoutCount<TIMEOUT_COUNT  )
         {
            // vid_TpManage();
            vid_TaskDelay(1);
            GLOB_u32TimeoutCount++;
         }
        
        /*check the reason for exiting busy wait, if transmit flag is set*/
         if (*u8Flag == FLAG_SET)
         {
            /*return transmitt Success*/
            LOC_ApiReturnValue=OPERATION_SUCCESS;
            
         }
        
        /*else if Timeout occured and flag is not set*/
         else
         {
             LOC_ApiReturnValue=OPERATION_FAILED;
         }

        /*reset count*/
        GLOB_u32TimeoutCount=0;

        *u8Flag=FLAG_CLEAR;
        
        return LOC_ApiReturnValue;
}

/*_________________________________________________________________________________*/

void vid_TransmitCallback(void)
{
        GLOB_TransmitSuccessFlag=FLAG_SET;
        if(GLOB_u8ISOComplint == 1){

          GLOB_TransmissionCallback();
        }
}

/*_________________________________________________________________________________*/

void vid_ReceiveCallback(void)
{
        GLOB_ReceptionSuccessFlag=FLAG_SET;
        if(GLOB_u8ISOComplint == 1){

        GLOB_ReceptionCallback();
        }
}
