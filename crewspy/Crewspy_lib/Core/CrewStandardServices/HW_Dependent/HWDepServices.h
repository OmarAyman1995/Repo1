#ifndef __HWDEPSERVICES_H
#define __HWDEPSERVICES_H

#include "GlobalCnfg.h"
#include "CrewServices_Cnfg.h"


void Service_SoftwareReset(void);

void Service_StackConsumption(void);

void Service_ExecutionTime(void);

void fillStackWithPattern(void);

void Service_ReadGPR(void);

#endif
