#ifndef __OBDDATACONVERTER_H
#define __OBDDATACONVERTER_H

#include "typedefs.h"
#include "ConvUnits.h"





/**
 * @brief it converts the OBD response to a physical value in a string
 * 
 * @param pid response pid
 * @param A 
 * @param B 
 * @param C 
 * @param D 
 * @param output_string the converted string will be stored in this pointer
 * @return u8_t 0 if sucess, 1 if fail
 * @note CCO-CDD-224 CCO-CDD-226
 */
u8_t u8_ConvertOBDToPhysicalValue(u8_t pid,
                               u8_t A,
                               u8_t B,
                               u8_t C,
                               u8_t D,
                               u8_t* output_string);


/**
 * @brief size of the string that had been convereted
 * 
 * @return u32_t size
 * @note CCO-CDD-224 CCO-CDD-226
 */
u32_t u32_getConvertedSize(void);

#endif
