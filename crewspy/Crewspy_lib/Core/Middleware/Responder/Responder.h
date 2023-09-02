#ifndef __RESPONDER_H_
#define __RESPONDER_H_

#include "GlobalCnfg.h"
#include "UartTp.h"

#define MASKING_DEVICDEID_CPUID              0x0F
#define IDS_SIZE                             11

void Responder_PutServiceIDAndParams(uint8_t *buffer,
                   uint8_t service_id,
                   uint8_t *params,
                   size_t sizeOfParams);

void Responder_SendTargetConfigs(void);
#endif
