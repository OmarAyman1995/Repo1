/**
 * @file Cancnfg.h
 * @author  Ahmed Bahaa - (https://crewteq.com/)
 
 * @brief This is a header file for a CAN Driver Component for STM32F103C8T6, Target Device has Only One Can Peripheral 
          File Contains Configuration Needed for CAN Driver Component
 * @version 1.6.0
 * @date 2023-10-8
 * 
 * @copyright Copyright (crewteq) 2023 
 */

#ifndef CANCNFG_H
#define CANCNFG_H
/*________________________________includes_______________________________*/

/*________________________________Macros_______________________________*/

/*CAN Configurations*/ 
#define             BAUDRATE_PRESCALER                      4
#define             SAMPLING_POINT                          (float32_t)81.3
#define             SJW                                      1
#define             CAN_MAX_BAUDRATE                        1000000U
#define             CAN_FILTERS_TOTAL_NUM                    14U

/*CAN FILTERS NUMBER*/
#define            FILTER_BANK_0                              0
#define            FILTER_BANK_1                              1
#define            FILTER_BANK_2                              2
#define            FILTER_BANK_3                              3
#define            FILTER_BANK_4                              4
#define            FILTER_BANK_5                              5
#define            FILTER_BANK_6                              6
#define            FILTER_BANK_7                              7
#define            FILTER_BANK_8                              8
#define            FILTER_BANK_9                              9
#define            FILTER_BANK_10                             10
#define            FILTER_BANK_11                             11
#define            FILTER_BANK_12                             12
#define            FILTER_BANK_13                             13


/*CAN receiving mode*/
#define             POLLING                                    0U
#define             INTERRUPT                                  1U
#define             CAN_RX_MODE                               INTERRUPT 

#endif
