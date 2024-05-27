#include "typedefs.h"

/*Configuring Components */
#define DIAGNOSTIC_CAN_ID_11BIT     0x7DF               /*according to ISO15765-4 standrad page 12*/
#define DIAGNOSTIC_CAN_ID_29BIT     0x18DB33F1         /*according to ISO15765-4 standrad page 13*/
#define TIMEOUT_COUNT               100              /*timeout period for reception and transmission*/
#define MAX_BAUDRATE_RECORD_SIZE    (u8_t)10         /*Baudrate record array max size*/
#define CLOCK                          64000000     /*clock of CAN Driver*/
#define CAN_ISO_UT                     OFF         /*Enable to Run Unit test*/

/*Constant Macros*/
#define FLAG_SET                       (u8_t)1        
#define FLAG_CLEAR                     (u8_t)0
#define OPERATION_SUCCESS              (u8_t)1 
#define OPERATION_FAILED               (u8_t)0     