#include "COM_Adapter.h"
#include "GlobalCnfg.h"
#include "UartTp.h"
#include "string.h"


extern uint8_t u8ReadyBufferTp[SIZE_OF_u8READYBUFFERTP];
extern uint8_t u8NumOfFrames;


/**
 * @brief we will use this function to send the ready buffer from
 *  any Com_protocol to the upstairs layers
 * @param u8Buffer this the buffer we will copy the ready buffer
 * from any com_protocol in it
 */
void ComAdapterGetBuffer(uint8_t *u8Buffer, uint8_t *frame_size)
{
    if(u8Buffer == NULL || frame_size == NULL){
        return;
    }
    uint8_t u8counter=0;
    switch (COM_PROTOCOL)
    {
    case UARTTP:
        *frame_size = u8NumOfFrames;
        bufferProcessing();
        for((u8counter=0); u8counter < (((*frame_size)*NUM_OF_PARMS)+1) ; (u8counter++)){
            u8Buffer[u8counter]= u8ReadyBufferTp[u8counter];
        }
        break;
    case CANTP:
    /* Not implemented yet */
        break;
    case I2CTP:
    /* Not Implemented yet */
        break;
    case LINTP:
    /* Not Implemented yet */
        break;
    case SPITP:
    /* Not Implemented yet */
        break;
    default:
    /* Misra C*/
        break;
    }
}


/**
 * @brief we will use this function to know if the buffer from any
 * Com_Protocol is ready or not
 * @return we will return if it is valid or no
 */
uint8_t ComBufferIsReady(void)
{
    uint8_t u8returnValue=0;
    switch (COM_PROTOCOL)
    {
    case UARTTP:
    u8returnValue=bufferIsReadyFromUart();
        break;
    case CANTP:
    /* Not implemented yet */
        break;
    case I2CTP:
    /* Not Implemented yet */
        break;
    case LINTP:
    /* Not Implemented yet */
        break;
    case SPITP:
    /* Not Implemented yet */
        break;
    default:
    /* Misra C*/
        break;
    }
    return u8returnValue;
}


/**
 * @brief we will use this function to recieve the buffer from Mng
 * and send it to any com_protocol
 * @param u8Buffer it is the buffer we will send it to any com_protocol
 * @param responseType the response type(Positive or Negative)
 */
void ComAdapterSendBuffer(  uint8_t *u8Buffer,
                            enumRespType_t responseType,
                            uint8_t size)
{
    switch (COM_PROTOCOL)
    {
    case UARTTP:
    sendFramesToUart(u8Buffer,responseType, size);
        break;
    case CANTP:
    /* Not implemented yet */
        break;
    case I2CTP:
    /* Not Implemented yet */
        break;
    case LINTP:
    /* Not Implemented yet */
        break;
    case SPITP:
    /* Not Implemented yet */
        break;
    default:
    /* Misra C*/
        break;
    }
}
