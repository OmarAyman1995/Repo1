#ifndef __GLOBAL_CNFG_H
#define __GLOBAL_CNFG_H


#include <stdint.h>
#include <stddef.h>
#include "Services.h"
#include "Address.h"

typedef void (*function_ptr)(void);
typedef void (*function_ptr_d)(uint8_t data);

#define VERSION_MAJOR (uint8_t)1

#define VERSION_MINOR (uint8_t)4

#define VERSION_PATCH (uint8_t)0

#define ID (uint8_t)0x67
#define EOF (uint8_t)0x24
#define STARTOFRAM (uint32_t)536870912
#define ENDOFRAM (uint32_t)537001984
#define BUFFER_SIZE (uint8_t)100
#define FRAME_SIZE (uint8_t)16
#define MAX_PARAMETERS (uint8_t)10
#define LAST_SERVICE_NUMBER (uint8_t)20
#define FIRST_SERVICE_NUMBER (uint8_t)1
#define TARGET_ADDRESS (uint8_t)0x78
#define UINT8_T (uint8_t)8
#define UINT16_T (uint8_t)16
#define UINT32_T (uint8_t)32
#define MAX_SERVICES_NUM (uint8_t)20
#define STACK_PATTERN (uint32_t)0xAB
#define STACK_PATTERN_FOURBYTES (uint32_t)0xABABABAB
/*address range for peripheral registers*/
#define STARTOFPERPHERALS          (uint32_t)  1073741824      
#define ENDOFPERIPHERALS           (uint32_t)  2684358655


#define NUM_OF_PARMS (uint8_t)10

#define INVALID 0U
#define VALID   1U

/*Our Custom Services*/
#define ACK_SERVICE         (uint8_t)0xFE
#define STARTCOM_SERVICE    (uint8_t)0xFD
#define ENDCOM_SERVICE      (uint8_t)0xFC
#define READ_SERIVCE        (uint8_t)80
#define READ_REGISTER_SERIVCE     (uint8_t)70
#define WRITE_REGISTER_SERIVCE    (uint8_t)60
#define WRITE_BIT_SERIVCE         (uint8_t)90
#define READ_GENERAL_REGISTER       (uint8_t)150
#define WRITE_SERIVCE       (uint8_t)50
#define GETVERSION_SERIVCE  (uint8_t)20
#define GETSTACKPTR_SERIVCE  (uint8_t)30
#define SOFTWARERESET_SERIVCE  (uint8_t)40
#define UNITTESTING_SERIVCE  (uint8_t)120
#define MAXSTACK_SERIVCE  (uint8_t)130
#define EXECUTIONTIME_SERIVCE  (uint8_t)140
#define DEVICEID_CPUID_SERIVCE  (uint8_t)11
#define BREAKPOINT_INFO_SERIVCE  (uint8_t)2
#define BREAKPOINT_CONT_SERIVCE  (uint8_t)1



#define USER_MAX_PARAMETERS (uint8_t)50
#define FRAME_MAX_SIZE  USER_MAX_PARAMETERS + (uint8_t)1


#define NULLPTR (void*)0

#define PUBLIC extern
#define PRIVATE static


/* Response type table */
typedef enum{
NEGATIVE_RESPONSE,
POSITIVE_RESPONSE
}enumRespType_t;

/*Negative code table*/
typedef enum{
CRC_ERROR = 0x01,
SERVICE_ID_NOT_FOUND,
SERVICE_PARAM_NOT_CORRECT
}enumNegCode_t;

#endif
