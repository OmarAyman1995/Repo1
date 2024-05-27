/**
 * @file CANTp.c
 * @brief This is the source file of the CAN TP module, Module is respnsible for Sending and recieving Diagnostic CAN Frames according to ISO TP Standard
 *         to use this component you need to:
 *           -  call the Can TP Init Function
 *           -  call Can TP Task Periodically
 *           -  call the functions "ISO TP set" and "ISO TP reset" when requesting a UDS request or an OBD request which requires ISO-TP (mode 3 and mode 9)
 * and OBD II protocols
 * @version 1.5.0
 * @date 2023-11-15
 *  * @author  Ahmed Bahaa Alkomy
 * 
 * @copyright Copyright (crewteq) 2023
 * 
 */

/*______________________Includes____________________________*/
#include "CANTp.h"
#include "CANConfig.h"
#include "Can.h"
#include "services.h"
#include "math.h"
#include "string.h"
#include "CmsisAbstract.h"

/*______________________Global Variables____________________________*/

#if CAN_TP_UT ==OFF

/// @brief structure containing the data unit of the TP Module
/// @note Covers Requirmenets CCO-CDD-1084
PRIVATE TpReceiveDataUnitInfo_t GLOB_strTpDataUnit={0};                            

/// @brief pointer to function for reception callback function
/// @note Covers Requirmenets CCO-CDD-1065
PRIVATE void(*GLOB_pCallbackfunc1)(void)=NULL;                                      
 
/// @brief pointer to function for transmission callback function
/// @note Covers Requirmenets CCO-CDD-1064
PRIVATE void(*GLOB_pCallbackfunc2)(void)=NULL;                                      

/// @brief flag to indicate a a reception has occured
/// @note Covers Requirmenets CCO-CDD-1066
PRIVATE u8_t GLOB_ReceptionFlag;                                               

/// @brief global flag raised when a new data unit is ready to be delivered by upper layers
/// @note Covers Requirmenets CCO-CDD-1067
PRIVATE u8_t GLOB_DataUnitReadyFlag;                                         

/// @brief Structure for recieved CAN Frame
/// @note Covers Requirmenets CCO-CDD-1063
PRIVATE strCanDrvFrameInfo GLOB_ReceivedCanFrame={0};                         

/// @brief for storing the CAN ID to send the flow control frame for ISO-TP 
/// @note Covers Requirmenets CCO-CDD-1080
PRIVATE u32_t GLOB_u8FlowControlID=0;                                          

/// @brief Variable to enable and disable iso tp protocol in can tp
/// @note  Covers Requirmenets CCO-CDD-1088
PRIVATE IsoTpOption_e GLOB_u8IsoTpOption = ISO_TP_DISABLED;                                         

/// @brief Extended or standrad type
/// @note  Covers Requirmenets CCO-CDD-1089
PRIVATE u8_t GLOB_u8CANFrameType=0;           

/// @brief concective frame counter
/// @note  Covers Requirmenets CCO-CDD-1090
PRIVATE u8_t    GLOB_ConsecutiveFramesCounter=0;

#else
TpReceiveDataUnitInfo_t GLOB_strTpDataUnit={0};                            
void(*GLOB_pCallbackfunc1)(void)=NULL;                                      
void(*GLOB_pCallbackfunc2)(void)=NULL;                                      
u8_t GLOB_ReceptionFlag;                                               
u8_t GLOB_DataUnitReadyFlag;                                         
strCanDrvFrameInfo GLOB_ReceivedCanFrame={0};                         
u32_t GLOB_u8FlowControlID=0;                                          
IsoTpOption_e GLOB_u8IsoTpOption = ISO_TP_DISABLED;                                         
u8_t GLOB_u8CANFrameType=0;           
u8_t    GLOB_ConsecutiveFramesCounter=0;

#endif


/*____________________________________________Private Functions Prototype___________________________________*/


#if CAN_TP_UT == OFF
/// @brief processes the single UDS frame received 
///        - extracts datapayload and size
/// @param Frame CAN Frame info structure
/// @note  Covers Requirmenets CCO-CDD-1700
PRIVATE void vid_UdsSingleFrameReceptionProcessing(const strCanDrvFrameInfo* Frame);


/// @brief extracts two informations from UDS First Frame's data payload : DL and 6 bytes of data
/// @param Frame a can frame
/// @return number of bytes received
/// @note  Covers Requirmenets CCO-CDD-1701
PRIVATE u16_t u16_UdsFirstFrameReceptionProcessing(const strCanDrvFrameInfo* frame);


/// @brief Process Concective response frame, extracts Data payload and return if all concective frames is received or not
/// @param frame a can frame
/// @param currentIndex index to start filling the exctrating data payload in our global Tpdata unit
/// @param expetcedNumOfFrames number of concective frames expected
/// @return return if all cocective frames are received or not
/// @note  Covers Requirmenets CCO-CDD-1702
PRIVATE u8_t u8_ConcectiveFrameResponseReception(const strCanDrvFrameInfo* frame, u16_t currentIndex,u16_t expectedNumOfFrames);

/// @brief send a flow control CAN Frame according to ISO-TP Standrad
/// @param CANID CAN ID to send flow control to
/// @note  Covers Requirmenets CCO-CDD-1703
PRIVATE void vid_sendFlowControl(u32_t CANID);


/// @brief a function for processing obd frame and extracting datapayload and size 
/// @param frame Can Frame
/// @note  Covers Requirmenets CCO-CDD-1704
PRIVATE void vid_TpNormalCanProcessingSequence(const strCanDrvFrameInfo* frame);


/// @brief a function for processing UDS frame and OBD requests with more than 8 bytes of data and extracting datapayload and size 
/// @param frame Can Frame
/// @note  Covers Requirmenets CCO-CDD-1705
PRIVATE u8_t u8_TpIsoProcessingSequence(const strCanDrvFrameInfo* frame);

/// @brief empty function to avoid hard fault error resulted from not setting pointer to functions (reception notify and transmission notify)
///        this occurs when SWC user forgets to call Tp_init function
///        address of the function is assigned to the Global pointer to functions at the Tp_Init function
/// @note  Covers Requirmenets CCO-CDD-1706
PRIVATE void CallbackPtrDefaultFunc(void);

#else
void vid_UdsSingleFrameReceptionProcessing(const strCanDrvFrameInfo* Frame);
u16_t u16_UdsFirstFrameReceptionProcessing(const strCanDrvFrameInfo* frame);
u8_t u8_ConcectiveFrameResponseReception(const strCanDrvFrameInfo* frame, u16_t currentIndex,u16_t expectedNumOfFrames);
void vid_sendFlowControl(u32_t CANID);
void vid_TpNormalCanProcessingSequence(const strCanDrvFrameInfo* frame);
u8_t u8_TpIsoProcessingSequence(const strCanDrvFrameInfo* frame);
void CallbackPtrDefaultFunc(void);

#endif

/*_______________________________________Private Functions Implementation____________________________*/

void CallbackPtrDefaultFunc(void)
{
   /*Emtpy func does nothing*/
}


void vid_UdsSingleFrameReceptionProcessing(const strCanDrvFrameInfo* Frame)
{
  /*store incoming bytes in the tp data Unit structure starting from byte 1*/
             cpy_array(GLOB_strTpDataUnit.u8TpDataPayload
                      ,(Frame->data)+DATA_PAYLOAD_BYTE1_INDEX
                      ,DATA_PAYLOAD_IN_SINGLE_FRAME);

             /*store the data length in the tp data unit structure*/         
             GLOB_strTpDataUnit.u8DataPayloadSize=(Frame->DLC)-1;

}


/*____________________________________________________________________________________________________________________________________*/


 u16_t u16_UdsFirstFrameReceptionProcessing(const strCanDrvFrameInfo* frame)
{
    u16_t LOC_u8bytesCounter=0;

     /*copy data bytes*/
            cpy_array(GLOB_strTpDataUnit.u8TpDataPayload
            ,(frame->data)+DATA_PAYLOAD_BYTE2_INDEX
            ,DATA_PAYLOAD_IN_FIRST_FRAME);
     
      /*store data length in the bytes counter, in first frame data length is the first nibble of byte 0 + byte 1*/
            LOC_u8bytesCounter= (u16_t)((frame->data[DATA_PAYLOAD_BYTE0_INDEX] & DL_MASK)<<8) | (u16_t)frame->data[DATA_PAYLOAD_BYTE1_INDEX];
            
    return LOC_u8bytesCounter;  
}


/*____________________________________________________________________________________________________________________________________*/


 u8_t u8_ConcectiveFrameResponseReception(const strCanDrvFrameInfo* frame, u16_t currentIndex,u16_t expectedNumOfFrames)
{
    u8_t           returnValue=STILL_EXPECTING_CONCECTIVE_FRAME;                                       /*API return Value */

    /*extract data payload (7 bytes)*/
    cpy_array( GLOB_strTpDataUnit.u8TpDataPayload+currentIndex
              ,(frame->data)+DATA_PAYLOAD_BYTE1_INDEX
              ,DATA_PAYLOAD_IN_CONCECTIVE);

    /*increment frame counter*/
    GLOB_ConsecutiveFramesCounter++;
    
    /*if all expected frames have been received*/
    if(GLOB_ConsecutiveFramesCounter==expectedNumOfFrames)
    {
        /*return value indicating concective frames is done*/
        returnValue=ALL_CONCECTIVE_FRAMES_RECEIVED;

        /*reset frame counter*/
        GLOB_ConsecutiveFramesCounter=0;
    }

    else
    {
      /*do nothing*/
    }

    return returnValue;
}


/*____________________________________________________________________________________________________________________________________*/


 void vid_sendFlowControl(u32_t CANID)
{
    strCanDrvFrameInfo LOC_FlowControlFrame = { .FrameID=CANID,           /*configuration for Flow control to be sent */
                                                .RTR=DATA_FRAME,           
                                                .DLC=FLOW_CONTROL_FRAME_DATA_LENGTH,
                                                .data={FLOW_CONTROL_BYTE0_VALUE,FLOW_CONTROL_BLOCK_SIZE,FLOW_CONTROL_DELAY, 0,0,0,0,0}};   
    /*set CanFrame Type*/
    LOC_FlowControlFrame.IDE=GLOB_u8CANFrameType;

    /*send a Flow Control Frame*/
    enum_CanDrvTransmit(&LOC_FlowControlFrame);
    
}

/*____________________________________________________________________________________________________________________________________*/
/// @brief a function for processing obd frame and extracting datapayload and size 
void vid_TpNormalCanProcessingSequence(const strCanDrvFrameInfo* frame)
{
    /*store incoming bytes in the tp data Unit structure*/
    cpy_array(GLOB_strTpDataUnit.u8TpDataPayload
            ,frame->data
            ,frame->DLC);

    /*store the data length in the tp data unit structure*/         
    GLOB_strTpDataUnit.u8DataPayloadSize=frame->DLC;

   /*clear Reception Flag*/
    GLOB_ReceptionFlag=0; 

    /*Set Data unit ready flag*/
    GLOB_DataUnitReadyFlag=DATA_UNIT_READY;

    /*call the recev call back function of upper layer*/
    GLOB_pCallbackfunc1(); 

}


/*____________________________________________________________________________________________________________________________________*/

/// @brief a function for processing UDS frame and OBD requests with more than 8 bytes of data and extracting datapayload and size 
 u8_t u8_TpIsoProcessingSequence(const strCanDrvFrameInfo* frame)
{
    static u16_t LOC_u8bytesCounter=0;                                    /*static variable to store the number of bytes recieved */
    static u16_t LOC_index=0;                                              /*index used to fill the tp data unit*/ 
    static u16_t LOC_numOfExpectedConcectiveFrames=0;
    u8_t  PCINibbleValue=0;                                              /*variable to store the value of the PCI (last nibble of the byte 0 in data field)*/
    u8_t returnValue=0;
    u8_t             LOC_funcReturnValue=0;
                                                    

    /*get UDS Frame type form the last 4 nibbles in byte 0*/
    PCINibbleValue=frame->data[DATA_PAYLOAD_BYTE0_INDEX]>>4;


        /*check the PCI Nibble Value*/
        switch (PCINibbleValue)
        {
            case SINGLE_FRAME:
            /*process the single received Frame*/
            vid_UdsSingleFrameReceptionProcessing(frame);

            /*assign return value to be ok*/
             returnValue=SINGLE_FRAME;

             /*Set Data unit ready flag*/
            GLOB_DataUnitReadyFlag=DATA_UNIT_READY;

            /*call the recev call back function of upper layer*/
             GLOB_pCallbackfunc1();
             break;


             case FIRST_FRAME:
            /*process the first Frame and return the total number of bytes recevied*/
             LOC_u8bytesCounter= u16_UdsFirstFrameReceptionProcessing(frame);

            /*caluclate the expected concective frames, subtract the six bytes of the first frame*/
            LOC_numOfExpectedConcectiveFrames= (u16_t)ceil((LOC_u8bytesCounter-DATA_PAYLOAD_IN_FIRST_FRAME)/(float32_t)DATA_PAYLOAD_IN_CONCECTIVE);

            /*increment the LOC_index used to fill the Tp data unit array*/
            LOC_index=LOC_index+DATA_PAYLOAD_IN_FIRST_FRAME;
            
            /*send flow control*/
             vid_sendFlowControl(GLOB_u8FlowControlID);
            
            /*assign return value to be ok*/
             returnValue=FIRST_FRAME;
             break;
            

            case CONCECTIVE_FRAME:
            /*processing the concective Frame*/
            LOC_funcReturnValue=u8_ConcectiveFrameResponseReception(frame,LOC_index,LOC_numOfExpectedConcectiveFrames);

            /*increment the LOC_index used to fill the Tp data unit array, subtract the PCI byte*/
            LOC_index= LOC_index + (frame->DLC)-1;

            /*check if the concective frame was the last concective frame (all bytes has been sent)*/
            if(LOC_funcReturnValue==ALL_CONCECTIVE_FRAMES_RECEIVED)
            {
                GLOB_strTpDataUnit.u8DataPayloadSize=LOC_index;
                
                /*reset LOC_index and concective frames counter*/
                LOC_index=0;
                LOC_numOfExpectedConcectiveFrames=0;
                /*Set Data unit ready flag*/
                GLOB_DataUnitReadyFlag=DATA_UNIT_READY;

                /*call the recev call back function of upper layer*/
                GLOB_pCallbackfunc1();


            }
            else
            {
               /*do nothing*/

            }
            /*assign return value to be ok*/
             returnValue=CONCECTIVE_FRAME;
            break;


            default:
            returnValue=UNKNOWN_FRAME;
        }

     /*clear Reception Flag*/
    GLOB_ReceptionFlag=NO_RECEPTION; 

    return returnValue;
}


/*_____________________________Public Functions Implementation_______________________________*/
/*____________________________________________________________________________________________________*/

void vid_TpInit(void)
{ 
/*initalize Global Variables*/
GLOB_pCallbackfunc1=CallbackPtrDefaultFunc;                           
GLOB_pCallbackfunc2=CallbackPtrDefaultFunc;                             
GLOB_ReceptionFlag=NO_RECEPTION;                              
GLOB_DataUnitReadyFlag=NO_DATA_UNIT; 

    /*set callback function for reception indication */
    vid_CanDrvSetReceiveCallPack(vid_TpReceptionIndicator);
    vid_CanDrvSetTransmitCallPack(vid_TpTransmissionIndicator);
}

/*____________________________________________________________________________________________________*/

void vid_TpsetCanFrameType(u8_t CANFrameType)
{
     vid_DisableIrq();
    GLOB_u8CANFrameType=CANFrameType;
     vid_EnableIrq();
}


/*____________________________________________________________________________________________________________________________________*/

void vid_IsoTpSet(u32_t u32_FlowControlID){
    GLOB_u8IsoTpOption = ISO_TP_ENABLED;

    /*store the flow control ID in the */
    GLOB_u8FlowControlID=u32_FlowControlID;

}


/*____________________________________________________________________________________________________________________________________*/


/*____________________________________________________________________________________________________________________________________*/

u8_t struct_GetTpReceivedDataUnit(u8_t* outputBuffer,u16_t* size)
{

          if(GLOB_DataUnitReadyFlag==DATA_UNIT_READY)
          {


            /*Reset Flag*/
            GLOB_DataUnitReadyFlag=NO_DATA_UNIT;

            /*reset Iso processing option*/
            GLOB_u8IsoTpOption=ISO_TP_DISABLED;

            cpy_array(outputBuffer,GLOB_strTpDataUnit.u8TpDataPayload,GLOB_strTpDataUnit.u8DataPayloadSize);
            *size= GLOB_strTpDataUnit.u8DataPayloadSize;


            memset(GLOB_strTpDataUnit.u8TpDataPayload,0,GLOB_strTpDataUnit.u8DataPayloadSize);

            /*return address of structure*/
           return DATA_UNIT_READY;
          }

          else
          {
            return NO_DATA_UNIT;
          }
}


/*____________________________________________________________________________________________________________________________________*/

enumTpApiError_e vid_TpTransmitDataUnit (const TpTransmitDataUnitInfo *DataUnitStruct)
{
     /*construct Frame to Transmit*/
    static strCanDrvFrameInfo LOC_CanFrameToSend = {                                                                         
                                              .RTR=DATA_FRAME,
                                              .DLC=8}; 


    enumTpApiError_e ApiReturnValue=CAN_TP_API_NOT_OK;  /*API return value*/
    EnumCanDrvApiError  CanReturnValue=CAN_API_NOT_OK; /*can Driver return value*/

   /*store CAN ID*/
   LOC_CanFrameToSend.FrameID=DataUnitStruct->DiagnosticCANID;

   /*store IDE*/
   LOC_CanFrameToSend.IDE=GLOB_u8CANFrameType;
  
    /*first nibble->DL
    second nibble ->Frame Type (1 for single frame)*/
    LOC_CanFrameToSend.data[0] =  ((u8_t) DataUnitStruct->u8DataPayloadSize & DL_MASK) | (SINGLE_FRAME_VALUE & PCI_MASK);

    /*copy the data bytes we want to send to the CAN Frame structure*/
    cpy_array(LOC_CanFrameToSend.data+1
    ,(DataUnitStruct->u8TpDataPayload)
    ,(DataUnitStruct->u8DataPayloadSize));    

    /*send CAN FRAME*/
    CanReturnValue=enum_CanDrvTransmit(&LOC_CanFrameToSend);

    if(CanReturnValue==CAN_API_OK)
    {
       ApiReturnValue=CAN_TP_API_OK;

       /*store the flow control ID in the */
       GLOB_u8FlowControlID=DataUnitStruct->FlowControlCANID;

       /*Enable ISO TP option in Module for proper proceesing*/
       GLOB_u8IsoTpOption=ISO_TP_ENABLED;
    }

    else
    {
       ApiReturnValue=CAN_TP_API_NOT_OK; 
    }

    return ApiReturnValue;
                                                                                    
}


/*____________________________________________________________________________________________________________________________________*/

void vid_TpSetReceiveCallBack(pFunction ptr_UserCallback)
{
     if((ptr_UserCallback != NULLPTR) && (GLOB_pCallbackfunc1 == CallbackPtrDefaultFunc))
     {
        GLOB_pCallbackfunc1 = ptr_UserCallback;
     }

     else
     {
        /*do nothing*/
     }
}


/*____________________________________________________________________________________________________________________________________*/

void vid_TpSetTransmitCallBack(pFunction ptr_UserCallback)
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_pCallbackfunc2 == CallbackPtrDefaultFunc))
     {
        GLOB_pCallbackfunc2 = ptr_UserCallback;
     }

      else
     {
        /*do nothing*/
     }
}


/*____________________________________________________________________________________________________________________________________*/

void vid_TpReceptionIndicator(void)
{
 /* receive Incoming CAN Frame*/
 vid_CanRecieve(&GLOB_ReceivedCanFrame);

 /*set receiption flag*/
 GLOB_ReceptionFlag=RECEPTION_FOUND;

}


/*____________________________________________________________________________________________________________________________________*/

void vid_TpTransmissionIndicator(void)
{
    /*call the transmission Indicator function of upper layer by callback*/
     GLOB_pCallbackfunc2();
}


/*______________________PUBLIC Periodic Function Implementation____________________________*/

void vid_TpManage(void)
{

    /*if there is a reception occurd*/
    if(RECEPTION_FOUND==GLOB_ReceptionFlag)
    {
       switch(GLOB_u8IsoTpOption)
       {
        /*if Iso processing option is set*/
        case ISO_TP_ENABLED:
        u8_TpIsoProcessingSequence(&GLOB_ReceivedCanFrame);
        break;

        /*if iso processing option is not set*/
        case ISO_TP_DISABLED:
        vid_TpNormalCanProcessingSequence(&GLOB_ReceivedCanFrame);
        break;

       }
    }

    else
    {
       /*do nothing*/
    }
}
