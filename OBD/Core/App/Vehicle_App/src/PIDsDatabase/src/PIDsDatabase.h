#ifndef __PIDSDATABASE_H
#define __PIDSDATABASE_H


#include "typedefs.h"

#define NOT_SUPPORTED 0
#define SUPPORTED     1

#define STATIC        1
#define DYNAMIC       0

#define MAX_PIDS 201

/**
 * @brief pids database information
 * 
 */
typedef struct 
{
    ConvUnitType pid_convfunction;
    u8_t pid_support_type; // supported - not supported
    u8_t pid_type;   // static - dynamic
    u8_t returned_length; // data bytes returned
}PIDsInfo_t;


/**
 * @brief get the information of that pid is supported or not
 * 
 * @param pid_number 
 * @return u8_t 1 if supported, 0 if not
 * @note CCO-CDD-220
 */
u8_t u8_getSupportInfo(u8_t pid_number);


/**
 * @brief get the information of pid is static or dynamic
 * 
 * @param pid_number pid number
 * @return u8_t 1 if static, 0 if dynamic
 * @note CCO-CDD-220
 */
u8_t u8_getPidType(u8_t pid_number);


/**
 * @brief updates the information of pid is supported or not supported with new information
 * 
 * @param pid_number pid number
 * @param support_info STATIC / DYNAMIC
 * @note CCO-CDD-220
 */
void    vid_setSupportInfo(u8_t pid_number, u8_t support_info);


/**
 * @brief gets the information of pid conversion function
 * 
 * @param pid_number pid number
 * @return ConvUnitType address of the conversion function
 * @note CCO-CDD-220
 */
ConvUnitType p_getConvFunction(u8_t pid_number);


/**
 * @brief get returned bytes length in the response of the pid
 * 
 * @param pid returned bytes length
 * @return u8_t 
 */
u8_t u8_getReturnedBytes(u8_t pid);

#endif

