#ifndef __CREWSERVICES_CNFG_H
#define __CREWSERVICES_CNFG_H
#include "SessionManager.h"
#include "MemoryAccess.h"
#include <string.h>
#include <stdlib.h>

/* some configrations to make unity working with any serial communication*/
#define UNITY_OUTPUT_CHAR
#define UNITY_OUTPUT_CHAR(a) putchar(a)
#include "unity.h"



#define TRUE (uint8_t)1
#define FALSE (uint8_t)0

#define STACK_PTR_OFFSET_FOR_SP_CONSUMPTION_SER (uint8_t)40
#define ADDRESS_PARAMS (int8_t)8
#define DATA_SIZE_INDEX (uint8_t)8
#define STACK_PTR_OFFSET_GET_SP_SER (uint8_t)24
#define OFFSET_TO_THE_FIRST_NUM_AFTER_DEC_POINT (uint8_t)10
#define OFFSET_TO_THE_SEC_NUM_AFTER_DEC_POINT (uint8_t)100
#define THE_FIRST_PARM_INDEX (uint8_t)0
#define THE_SEC_PARM_INDEX (uint8_t)1
#define THE_THIRD_PARM_INDEX (uint8_t)2
#define THE_FOURTH_PARM_INDEX (uint8_t)3
#define THE_FIFTH_PARM_INDEX (uint8_t)4
#define THE_SIX_PARM_INDEX (uint8_t)5
#define THE_SEVENTH_PARM_INDEX (uint8_t)6
#define THE_EIGHTH_PARM_INDEX (uint8_t)7
#define THE_NINTH_PARM_INDEX (uint8_t)8
#define THE_TENTH_PARM_INDEX (uint8_t)9

#define VECT_KEY                                  0x5FAUL
#define VECT_KEY_POS                              16UL
#define SOFTWARE_RESET_BIT_POS                    2UL
#define max_count                                 40
#define VALUE_OF_ONE                              (int8_t)1
#define VALUE_OF_ZERO                             0
#define HEX_CONVERT_VALUE                         9
#define percentage_value                          100
#define True                                      1
#define ELEMENT_SIZE                              (uint32_t)4
#define INDEX_ZERO                                0
#define INDEX_ONE                                 1
#define INDEX_TWO                                 2


#define FIRST_BYTE 0
#define SECOND_BYTE 1
#define THIRD_BYTE 2
#define FOURTH_BYTE 3

#endif
