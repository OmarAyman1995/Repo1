#ifndef __PARSER_H
#define __PARSER_H

#include "GlobalCnfg.h"
#include "Responder.h"
#include "Services.h"

#define IDX_SERVICEID       0
#define IDX_PARAMS_START    1
#define IDX_PARAMS_END      11

#define SERVICE_ERR 247

uint8_t Parse_ServiceID(uint8_t const *buffer);

#endif

