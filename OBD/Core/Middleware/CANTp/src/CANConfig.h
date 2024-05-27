
#ifndef CANCONFIG
#define CANCONFIG

#define DATA_PAYLOAD_BYTE0_INDEX     (u8_t)  0U
#define DATA_PAYLOAD_BYTE1_INDEX      (u8_t) 1U
#define DATA_PAYLOAD_BYTE2_INDEX      (u8_t) 2U
#define DATA_PAYLOAD_BYTE3_INDEX      (u8_t) 3U
#define DATA_PAYLOAD_BYTE4_INDEX      (u8_t) 4U
#define DATA_PAYLOAD_BYTE5_INDEX      (u8_t) 5U
#define DATA_PAYLOAD_BYTE6_INDEX      (u8_t) 6U
#define DATA_PAYLOAD_BYTE7_INDEX      (u8_t) 7U

#define OBD_REQUEST_ID                             (u16_t) 0x7DFU
#define OBD_RESPONSE_ID                            (u16_t) 0x7E8U


#define SINGLE_FRAME                                 (u8_t)  0x0U
#define FIRST_FRAME                                  (u8_t)  0x1U
#define CONCECTIVE_FRAME                              (u8_t) 0x2U  
#define UNKNOWN_FRAME                                 (u8_t)  0x4U

#define FLOW_CONTROL_FRAME_DATA_LENGTH                (u8_t)  8U
#define FLOW_CONTROL_BYTE0_VALUE                      (u8_t) 0x30U
#define FLOW_CONTROL_BLOCK_SIZE                       (u8_t)  0U
#define FLOW_CONTROL_DELAY                             (u8_t) 0U

#define DATA_PAYLOAD_IN_FIRST_FRAME                      (u8_t) 6U
#define DATA_PAYLOAD_IN_SINGLE_FRAME                     (u8_t) 7U
#define DATA_PAYLOAD_IN_CONCECTIVE                       (u8_t) 7U
#define TP_RECEIVE_BUFFER_SIZE                             (u16_t)500U
#define CAN_PROTOCOL_DATA_BYTES_PAYLOAD                  (u8_t) 8U


#define PCI_MASK                                       (u8_t) 0xF0U    
#define DL_MASK                                        (u8_t) 0x0FU
#define FIRST_FRAME_DL_MASK                            (u16_t) 0x0FFU   
#define SINGLE_FRAME_VALUE                             (u8_t)0x00 
#define FIRST_FRAME_VALUE                                (u8_t)0x10
#define CONCECTIVE_FRAME_VALUE                            (u8_t)0x20

#define ALL_CONCECTIVE_FRAMES_RECEIVED                   (u8_t) 1
#define STILL_EXPECTING_CONCECTIVE_FRAME                  (u8_t)0

#define NO_RECEPTION                                     (u8_t) 0
#define RECEPTION_FOUND                                  (u8_t) 1

#define DATA_UNIT_READY                                  (u8_t) 1
#define NO_DATA_UNIT                                     (u8_t) 0

#define CAN_TP_UT_ON                                        1
#define CAN_TP_UT_OFF                                       0
#define CAN_TP_UT                                           UT            


#endif