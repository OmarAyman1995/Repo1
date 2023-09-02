#include "Services.h"
#include "math.h"
#include <string.h>

#define VALUE_OF_ZERO        0
#define VALUE_OF_ONE         1

/**
 * @brief clears array with zeros (integer 0)
 * 
 * @param array desired array
 * @param size desired size
 * @return a cleared array
 */
uint8_t* clear_array(uint8_t* array, size_t size)
{
    for (size_t i = 0; i < size; (i++)) {
        array[i] = VALUE_OF_ZERO;
    }
    return array;
}


/**
 * @brief check the data if it is a digit ascii or not
 * 
 * @param c data
 * @return 1 if digit / 0 if nondigit
 */
uint8_t Isdigit(uint8_t c) {
    uint8_t retval = 0;
    if ((c >= '0') && (c <= '9')) {
        retval = VALUE_OF_ONE;
    } else {
        retval = VALUE_OF_ZERO;
    }

    return retval;
}


/**
 * @brief this function will be used transfer from hexa to decimal
 *
 * @param str this is the string will be transformed
 * @return uint32_t returtn the hex num
 */

uint32_t hextoi(uint8_t *hex) {
    int8_t len = 8;
    uint32_t base = 1;
    uint32_t decimal = 0;
    int8_t i=0;
    uint32_t returnvalue=0;
    if (hex != NULL)
    {
        for ((i = (len - 1)); (i >= VALUE_OF_ZERO) ; (i--)) {
            if ((hex[i] >= ZERO_CHAR) && (hex[i] <= NINE_CHAR)) {
                decimal += (hex[i] - ASCII_DIGIT_OFFSET) * base;
                base *= HEX_BASE;
            }
            else if ((hex[i] >= 'a') && (hex[i] <= 'f')) {
                decimal += (hex[i] - MAX_VALUE) * base;
                base *= HEX_BASE;
            }
            else if ((hex[i] >= 'A') && (hex[i] <= 'F')) {
                decimal += (hex[i] - ASCII_HEX_OFFSET) * base;
                base *= HEX_BASE;
            }else{
                /* misra C */
            }
        }
        returnvalue = decimal;
    }
    return returnvalue;
}

