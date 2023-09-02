#ifndef __SERVICEHANDLER_H
#define __SERVICEHANDLER_H

#include "GlobalCnfg.h"



struct function_mapping {
    uint8_t id;
    uint8_t privilege_flag;
    function_ptr addr;
}__attribute__((packed));

void ServHndl_RegisterService(uint8_t service_id, function_ptr ptr);

void ServHndl_ExecuteService(uint8_t service_id);

uint8_t ServHndl_GetCurrentService(void);

void ServHndl_SetPrivilege(uint8_t id);

uint8_t ServHndl_getPrivilege(uint8_t id);

#endif
