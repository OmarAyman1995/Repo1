#ifndef __HWINDEPSERVICES_H
#define __HWINDEPSERVICES_H


#include "GlobalCnfg.h"
#include "CrewServices_Cnfg.h"



void Service_GetVersion(void);

void Service_ReadVariable(void);

void Service_WriteVariable(void);

void SaveUnitTestResults(void);

void Unit_Testing_DeInit(void);

void Service_UnitTesting(void);

int putchar(int c);

void __attribute__((weak)) UnitTestingEnvironment(void) ;

void Service_ReadRegister(void);

void Service_WriteRegister(void);

void Service_WriteBit(void);

#endif
