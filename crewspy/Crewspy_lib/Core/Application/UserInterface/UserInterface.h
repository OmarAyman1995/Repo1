#ifndef __USERINTERFACE_H
#define __USERINTERFACE_H

#include "GlobalCnfg.h"

typedef struct 
{
    /* data */
    char func_name[30];
    uint16_t func_time;
    void (*funcPtr)(void);
}CrewServices_t;

extern uint8_t numberOfCallbacks;
extern CrewServices_t InventoryOfCallbacks[30];
#define CREWSPY_MEASURE(callback_name)  strcpy((char*)InventoryOfCallbacks[numberOfCallbacks].func_name, (char*)#callback_name);\
                                        InventoryOfCallbacks[numberOfCallbacks].funcPtr = callback_name;\
                                        numberOfCallbacks++



typedef void (*function_ptr)(void);
void CREWSPY_REGISTER_SERVICE(uint8_t service_id, function_ptr addr);

void CREWSPY_SET_PARAM(uint8_t parameter, uint8_t index);

uint8_t CREWSPY_GET_PARAM(uint8_t index_of_param);

void CREWSPY_SET_RESPONSE_TYPE(uint8_t response_type);

void CREWSPY_INIT(void);

uint8_t CREWSPY_RUN(void);

void CREWSPY_SET_PRIVILEGE_SERVICE(uint8_t id);

void BRK(char* breakname);


#endif
