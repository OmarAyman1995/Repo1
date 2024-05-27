#ifndef BLUETOOTHDRV_MCAL_H
#define BLUETOOTHDRV_MCAL_H


#include "typedefs.h"

void BlUartInit38400(void);
void BlUartInit115200(void);
void BlUartSend(u8_t *pData, u32_t size);
void BlUartRecv(u8_t *pData, u32_t size);
void BlUartRecvIT(u8_t *pData, u32_t size);
void BlUartSetCallback(pFunction pISR);
void BlUartAbort(void);

void BlGpioSet(void);
void BlGpioReset(void);
u8_t BlGpioRead(void);

u8_t BLCompareString(u8_t *str1, u8_t *str2);










#endif

