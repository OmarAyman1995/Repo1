/* Includes */
#include "GlobalCnfg.h"
#include "Checkers.h"
#include "UartTp.h"
#include "Services.h"
#include "string.h"
#include "Uart_Integration.h"
#define VALUE_OF_ONE                  1
#define VALUE_OF_ZERO                 0

uint8_t u8ReceivedByte = 0;

uint8_t u8BufferTp[SIZE_OF_U8BUFFERTP];

uint8_t u8ReadyBufferTp[SIZE_OF_u8READYBUFFERTP];

uint8_t u8RecievedBuffer[FRAME_SIZE];

uint8_t u8FlagBufferIsReady=0;

/* Number of the received frames that will be used in operations of UartTp 
so cannot be changed during receiving at ISR */
uint8_t u8NumOfFrames=0;


/**
 * @brief we will use this function to store the response type and
 * frame control in the response type byte
 *
 * @param Response this the response type if positive or negative
 *
 * @param size this the number of frame
 * @return uint8_t it's the actual byte that has the response type
 * and frame control and you can store it in response type byte in the
 * frame.
 */
enumRespWithFrmCon_t fillResponseByte (enumRespType_t response, uint8_t u8numberOfFrames,
                          uint8_t u8CurrentFrame)
{
    enumRespWithFrmCon_t retval = 0;
    switch (response)
    {
    case NEGATIVE_RESPONSE:
        if(u8CurrentFrame!=(u8numberOfFrames-VALUE_OF_ONE)){
            retval = NEGATIVE_RESPONSE_CONTINUE_FRAME;
        }else{
            retval = NEGATIVE_RESPONSE_LAST_FRAME;
        }
        break;
    case POSITIVE_RESPONSE:
        if(u8CurrentFrame!=(u8numberOfFrames-VALUE_OF_ONE)){
            retval = POSITIVE_RESPONSE_CONTINUE_FRAME;
        }else{
            retval = POSITIVE_RESPONSE_LAST_FRAME;
        }
        break;
    default:
        break;
    }

    return retval;
}


/**
 * @brief we will use this function to create the actual buffer
         (with service ID and Parameters)
          with no ID and Targer Adress and Frame Control.
 */
void makeBufferReadyToSend(void)
{
    uint8_t u8counter=0;
    u8ReadyBufferTp[u8counter]=u8BufferTp[SERVICE_ID_INDEX];
    memcpy((u8ReadyBufferTp+VALUE_OF_ONE),(u8BufferTp+THE_FIRST_FOUR_INDEXES)
    ,NUM_OF_PARMS);
    if(u8NumOfFrames!=VALUE_OF_ZERO)
    {
        for(u8counter=1;u8counter<=u8NumOfFrames;(u8counter++))
        {
            memcpy(u8ReadyBufferTp+(VALUE_OF_ONE+(u8counter*(NUM_OF_PARMS)))
            ,(u8BufferTp+THE_FIRST_FOUR_INDEXES)+(u8counter*(FRAME_SIZE))
            ,NUM_OF_PARMS);
        }
    }
}


/**
 * @brief this function used to fill the buffer to make it ready
 to calculate crc on it.
 *
 * @param u8Frame the buffer will be filled
 * @param u8FrameNumber the number of the frame on the buffer
 * @param u8Buffer the buffer that has the frames
 */
void frameFill(uint8_t *u8Frame, uint8_t u8FrameNumber, uint8_t *u8Buffer)
{
    uint8_t u8counter=0;
    for(u8counter=ID_INDEX;u8counter<=PARM10_INDEX;(u8counter++))
    {
            u8Frame[u8counter]=u8Buffer[u8counter+(u8FrameNumber*(FRAME_SIZE))];
    }
    u8Frame[u8counter]=u8Buffer[EOF_INDEX+(u8FrameNumber*(FRAME_SIZE))];
}


/**
 * @brief we will use this function to make the checks to our frame
 *
 * @param u8FrameNumber the frame that i need to check it in the u8BufferTp
 * @return enumFrameValidity we will return VALID or INVALID
 */
uint8_t sanityChecks(uint8_t u8FrameNumber)
{
    uint8_t u8Validity=VALID;
    uint8_t u8CRCTemp = 0;
    uint8_t u8frameBuffer[FRAME_SIZE-1];
    u8Validity=checkEquality(u8BufferTp[ID_INDEX +
                                         (u8FrameNumber*(FRAME_SIZE))],ID);
    
    u8Validity=checkEquality(u8BufferTp[TARGET_ADDRESS_INDEX
    +(u8FrameNumber*(FRAME_SIZE))],TARGET_ADDRESS);


    u8Validity=checkRange(u8BufferTp[FRAME_CONTROL_INDEX
    +(u8FrameNumber*(FRAME_SIZE))]
    ,FRAME_CONTROL_LAST_FRAME,FRAME_CONTROL_CONTINUE);

    frameFill(u8frameBuffer,u8FrameNumber,u8BufferTp);

    u8CRCTemp=calculateCRC(u8frameBuffer,FRAME_SIZE-1);

    u8Validity=checkEquality(u8BufferTp[CRC_IDEX
    +(u8FrameNumber*(FRAME_SIZE))],u8CRCTemp);

    u8Validity=checkEquality(u8frameBuffer[EOF_INDEX-1],EOF);

    if (VALID == u8Validity)
    {
        u8Validity=VALID;
    }
    else
    {
        u8Validity=INVALID;
    }
    return u8Validity;
}


/**
 * @brief we will use this Proccess function to check the validity of the frames
and if all is valid we will make the buffer ready to
send to the upper layer (com_Adaptert).
 *
 * @param ReadyBuffer this the buffer we will store the actual data in it
 */
void bufferProcessing(void)
{
    uint8_t u8ValidityFlag=VALID;
    uint8_t u8ValidityTemp=0;
    uint8_t u8CurrentFrame=0;

    for((u8CurrentFrame=0); u8CurrentFrame < u8NumOfFrames; (u8CurrentFrame++))
    {
        u8ValidityTemp=sanityChecks(u8CurrentFrame);
        if (INVALID == u8ValidityTemp)
        {
            u8ValidityFlag = INVALID;
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (VALID == u8ValidityFlag) {
        makeBufferReadyToSend();
        u8NumOfFrames = 0;

    }

    clear_array(u8BufferTp ,SIZE_OF_U8BUFFERTP);
    u8FlagBufferIsReady=0;
}


/**
 * @brief we will use this function to recieve the buffer from the
 com_Adapter layer and send it frame by frame to uart.
 * @param buffer this buffer that has the service ID and parameters.
 * @param ResponseType the response type
 (Positive Response or Negative Response) will be included on the frame
 */
void sendFramesToUart(  uint8_t *buffer,
                        enumRespType_t responseType,
                        uint8_t size)
{
    uint8_t  u8NumOfFramesToSendActaul=0;
    uint8_t u8NumOfFramesToSendTemp=0;
    uint8_t u8SeviceID=buffer[0];
    uint8_t u8CRCTempBuff[FRAME_SIZE-1];
    uint8_t u8CRCValue=0;
    uint8_t u8Response=0;

    u8NumOfFramesToSendActaul = (size-1)/NUM_OF_PARMS;

    for ((u8NumOfFramesToSendTemp = 0); u8NumOfFramesToSendTemp < u8NumOfFramesToSendActaul; (u8NumOfFramesToSendTemp++))
    {
        /*assign the ID*/
        u8RecievedBuffer[ID_INDEX] = ID;

        /*assign the TARGET_ADDRESS_INDEX*/
        u8RecievedBuffer[TARGET_ADDRESS_INDEX] = TARGET_ADDRESS;

        /*assign the RESPONSE_TYPE_INDEX*/
        u8Response=(uint8_t)fillResponseByte(responseType
                               ,u8NumOfFramesToSendActaul
                               ,u8NumOfFramesToSendTemp);
        u8RecievedBuffer[RESPONSE_TYPE_INDEX] = u8Response;

        /*assign the SERVICE_ID_INDEX*/
        u8RecievedBuffer[SERVICE_ID_INDEX]= u8SeviceID;

        /*assign all parametars*/
        memcpy(u8RecievedBuffer+THE_FIRST_FOUR_INDEXES,(buffer+VALUE_OF_ONE)+
        (u8NumOfFramesToSendTemp*NUM_OF_PARMS),NUM_OF_PARMS);

        /*assign the EOF_INDEX*/
        u8RecievedBuffer[EOF_INDEX]=EOF;

        /* caclulate CRC and store it on the frame */
        frameFill(u8CRCTempBuff,u8NumOfFramesToSendTemp,u8RecievedBuffer);
        u8CRCValue=calculateCRC(u8CRCTempBuff,FRAME_SIZE-VALUE_OF_ONE);

        /*assign the CRC_INDEX*/
        u8RecievedBuffer[CRC_IDEX] = u8CRCValue;

        /*Send this frame to usart*/
        enum_Uart_Integration_Send(0, u8RecievedBuffer, FRAME_SIZE);
    }
}


/**
 * @brief Keeps receiving bytes from USART untill a 16 bytes frame is collected
 * then checks framecontrol bit to decide if it last frame or not
 * 
 * @param received_byte uart must send the data in its DR register
 */
void UartInterruptProcessing(uint8_t received_byte){
    
    u8ReceivedByte = received_byte;

    /* Counter of how many bytes */
    static int8_t u8bytesCounter=0;

    /* Number of frames recevied, can be changed during operations of UartTp */
    static uint8_t u8frameCounterTemp=0;

    /* Put this single byte recevied in storage array to collect the frame */
    u8BufferTp[u8bytesCounter + ( u8frameCounterTemp * (FRAME_SIZE) )] = u8ReceivedByte;

    /* Check the counter of how many bytes has been recevied if it reached 16(full frame) */
    if(u8bytesCounter == (FRAME_SIZE-VALUE_OF_ONE))
    {       
            ++u8NumOfFrames;
            /* After Full frame is collected check if is a last frame or not by frame control bit in the frame */
            if(FRAME_CONTROL_LAST_FRAME == u8BufferTp[FRAME_CONTROL_INDEX + ( u8frameCounterTemp * (FRAME_SIZE) )])
            {
                /* Raise the flag that is a full request frames are received */
                u8FlagBufferIsReady = 1;
                u8frameCounterTemp = 0;
            }
            /* Since it is not last frame, Store the number of frames in temporarly */
            else if ( FRAME_CONTROL_CONTINUE == u8BufferTp[FRAME_CONTROL_INDEX + ( u8frameCounterTemp * (FRAME_SIZE-VALUE_OF_ONE) )])
            {
                u8frameCounterTemp = u8NumOfFrames;
            }
            else{/* misra c */}

            u8bytesCounter = 0 ;
    }
    /* Increase counter of bytes untill it reaches 16(full frame)*/
    else{ 
        ++u8bytesCounter;
    }
}


/**
 * @brief we will use this function to know if
 *  the buffer is ready to procces it or not.
 *
 * @return uint8_t this refer to the buffer is ready or no.
 */
uint8_t bufferIsReadyFromUart (void)
{
    return u8FlagBufferIsReady;
}
