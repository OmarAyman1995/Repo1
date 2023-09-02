/*Includes*/
#include "Checkers.h"
#include "Services.h"
#define ZERO_FRAME_SIZE         0

/**
 * @brief we will use this function to check the equality of two Bytes.
 *
 * @param Byte this byte represent the id in the frame
 * @param Data this represent the id from the "GlobalCnfg.h"
 * @return enumFrameValidity, this return type for (Valid or Invalid)
 */
 uint8_t checkEquality(uint8_t byte, uint8_t data)
 {
    uint8_t retval = INVALID;
    if(byte == data)
    {
        retval = VALID;
    }
    else
    {
        retval = INVALID;
    }
    return retval;
 }

 /**
  * @brief we will use this function to check the range of any byte
  *  if it whithin the ranger we will return
  * Valid, if it isn't within the range we will return Invalid
  * @param Byte this Byte represent the service ID from the frame.
  * @param Min this the minimum range we will check with it
  * @param Max this the max range we will check with it
  * @return enumFrameValidity, this return type represent (Valid or Invalid).
  */
  uint8_t checkRange(uint8_t byte,uint8_t min, uint32_t max)
  {
    uint8_t retval = INVALID;

    if((byte >= min) && (byte <= max))
    {
        retval = VALID;
    }
    else
    {
        retval = INVALID;
    }

    return retval;
  }

/**
 * @brief we will use this function to calculate the crc
 * if this function return zero that's mean the frame that
 * we need to calculate crc to it is equal NULL
 * @param frame the frame that we need to calculate crc to it
 * @param sizeOfFrame the size of frame
 * @return uint8_t we will return the CRC value
 */
uint8_t calculateCRC(uint8_t *frame,uint8_t sizeOfFrame)
{
    uint8_t returnValue=0;
    uint8_t  sum = 0;
    uint8_t  tempsizeofframe = sizeOfFrame;
    uint8_t *tmpframe = frame;
    if (frame != NULL)
    {
        /* Calculate CRC */
        while (tempsizeofframe > 0)
        {
            --tempsizeofframe;
            sum += *(tmpframe++);
        }
    returnValue = (~sum);
    }
    else
    {
        /* Misra C*/
    }
    return returnValue;
}
