
#ifndef __COM_SM_H
#define __COM_SM_H

#include "ComMCommonDataTypes.h"
#include "ComM.h"
#include <stdbool.h>




/**
 * @brief tranmist actions state
 * 
 */
void vid_make_transmit_actions(void);

/**
 * @brief receive actions state
 * 
 */
void vid_make_receive_actions(void);

/**
 * @brief idle actions state
 * 
 */
void vid_idle_actions(void);

/**
 * @brief waiting for the receive state
 * 
 */
void vid_waiting_receive_actions(void);

/**
 * @brief receive timeout actions
 * 
 */
void vid_receive_timeout_actions(void);

/**
 * @brief transmit timeout actions
 * 
 */
void vid_transmit_timeout_actions(void);

/**
 * @brief waiting for transmit to success
 * 
 */
void vid_waiting_transmit_actions(void);

/**
 * @brief determine the state based on some information
 * 
 * @param isReceiveQueueEmpty 
 * @param isTransmitQueueEmpty 
 * @param isReceiveTimeout 
 * @param isEventFlagSet 
 * @param isTransmitTimeout 
 * @param isTransmitCplt 
 * @return ComStatus_e the determined state
 */
ComStatus_e enum_determineState( bool isReceiveQueueEmpty,
                            bool isTransmitQueueEmpty,
                            bool isReceiveTimeout,
                            bool isEventFlagSet,
                            bool isTransmitTimeout,
                            bool isTransmitCplt);

/**
 * @brief changes the state of the state machine to new state
 * 
 * @param new_state 
 */
void vid_state_machine_switchto(ComStatus_e new_state);

/**
 * @brief makes the switch to the new state
 * 
 */
void vid_state_machine_run(void);

#endif
