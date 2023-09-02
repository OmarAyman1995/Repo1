#ifndef __UARTTP_H
#define __UARTTP_H

#include "UartTp_Cnfg.h"
#include "GlobalCnfg.h"

#define TRANSMIT_TIMEOUT 100



uint8_t sendBufferFromUartTp(uint8_t *buffer);

void sendFramesToUart(uint8_t *buffer,
                      enumRespType_t responseType,
                      uint8_t size);

void makeBufferReady(uint8_t u8NumberOfFrames);

uint8_t sanityChecks(uint8_t u8FrameNumber);

void makeBufferReadyToSend(void);

void bufferProcessing(void);

uint8_t bufferIsReadyFromUart (void);

enumRespWithFrmCon_t fillResponseByte (enumRespType_t response, uint8_t u8numberOfFrames,
                          uint8_t u8CurrentFrame);

void UartInterruptProcessing(uint8_t received_byte);
#endif
