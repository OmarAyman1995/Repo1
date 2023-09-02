#ifndef __UARTTP_CNFG_H
#define __UARTTP_CNFG_H

#include <stdint.h>

#define ID_INDEX (uint8_t)0
#define TARGET_ADDRESS_INDEX (uint8_t)1
#define SERVICE_ID_INDEX (uint8_t)2
#define FRAME_CONTROL_INDEX (uint8_t)3
#define PARM1_INDEX (uint8_t)4
#define PARM2_INDEX (uint8_t)5
#define PARM3_INDEX (uint8_t)6
#define PARM4_INDEX (uint8_t)7
#define PARM5_INDEX (uint8_t)8
#define PARM6_INDEX (uint8_t)9
#define PARM7_INDEX (uint8_t)10
#define PARM8_INDEX (uint8_t)11
#define PARM9_INDEX (uint8_t)12
#define PARM10_INDEX (uint8_t)13
#define CRC_IDEX (uint8_t)14
#define EOF_INDEX (uint8_t)15
#define THE_FIRST_FOUR_INDEXES (uint8_t)4
#define RESPONSE_TYPE_INDEX (uint8_t)3
#define SIZE_OF_U8BUFFERTP (uint8_t)100
#define SIZE_OF_u8READYBUFFERTP (uint8_t)55
#define SIZE_OF_u8RECIEVEDBUFFER (uint8_t)100
#define FRAME_CONTROL_CONTINUE (uint8_t)1
#define FRAME_CONTROL_LAST_FRAME (uint8_t)0
#define CLEARING_U8BYTESCOUNTER (int8_t)-1
#define ACK_INDEX (uint8_t)2
#define CRC_ACK_FRAME_INDEX (uint8_t)3
#define EOF_ACK_FRAME_INDEX (uint8_t)4
#define ACK_FRAME_SIZE (uint8_t)5

/**
 * we will use this enum in response frame to make the pc
 * tool know if this frame i will send is the last frame or
 * not.
*/
typedef enum{
NEGATIVE_RESPONSE_LAST_FRAME = 0,
NEGATIVE_RESPONSE_CONTINUE_FRAME=  1,
POSITIVE_RESPONSE_LAST_FRAME = 2,
POSITIVE_RESPONSE_CONTINUE_FRAME = 3
}enumRespWithFrmCon_t;

#endif
