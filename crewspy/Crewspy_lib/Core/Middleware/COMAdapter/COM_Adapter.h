#ifndef __COM_ADAPTER_H
#define __COM_ADAPTER_H

#include "COM_Adapter_Cnfg.h"
#include "GlobalCnfg.h"

void ComAdapterGetBuffer(uint8_t *u8Buffer, uint8_t *frame_size);

uint8_t ComBufferIsReady(void);

void ComAdapterSendBuffer(  uint8_t *u8Buffer,
                            enumRespType_t responseType,
                            uint8_t size);

#endif

