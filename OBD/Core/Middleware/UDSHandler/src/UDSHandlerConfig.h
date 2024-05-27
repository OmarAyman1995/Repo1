
#ifndef UDS_HANDLER_CONFIG
#define UDS_HANDLER_CONFIG

#define UDS_HANDLER_MODULE_ID                    55U

#define NEGATIVE_SID_RESPONSE                         0x7F   
#define POSITIVE_SID_DID_TYPE                          0
#define POSITIVE_SID_SUB_FUNC_TYPE                     1
#define NEGATIVE_SID_TYPE                              2

/*Read By Identifier Service*/
#define READ_BY_IDENTIFIER_RANGE_L_LIMIT        0xF180U          /* lower limit of the range of the service's DIDs*/
#define READ_BY_IDENTIFIER_RANGE_H_LIMIT        0xF19EU          /* higher limit of the range of the service's DIDs*/
#define READ_BY_IDENTIFIER_SID                   0x22U           /* Service SID*/
#define READ_BY_IDENTIFIER_L_BYTE_MASK           0xFF00U         /*left Mask*/
#define READ_BY_IDENTIFIER_R_BYTE_MASK           0x00FFU         /*right Mask*/
#define READ_BY_IDENTIFIER_BYTES_COUNT            3U             /*three bytes in the UDS request*/

/*Test Present Service*/
#define TESTER_PRESENT_SID                       0x3EU
#define TESTER_PRESENT_BYTES_COUNT                 2U
#define TESTER_PRESENT_SUB_VALUE_1                 0x00
#define TESTER_PRESENT_SUB_VALUE_2                 0x80

/*ECU Reset*/
#define ECU_RESET_SID                             0x11U
#define ECU_RESET_RANGE_L_LIMIT                   0U
#define ECU_RESET_RANGE_H_LIMIT                   5U
#define ECU_RESET_BYTES_COUNT                     2U


#define SUBFUNCTION_REQUEST_LENGTH                 2 /*Two Bytes: SID and sub Func*/
#define DID_REQUEST_LENGTH                         3 /*three Bytes: SID and two DID bytes*/
#define DTC_REQUEST_LENGTH                         4 /*Four Bytes : SID two DID and 1 optional Mask status byte*/




#endif