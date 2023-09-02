#ifndef __BREAKPOINT_H
#define __BREAKPOINT_H

#include "GlobalCnfg.h"

#define BREAK_SET 1
#define BREAK_NOTSET 0

#define BRKNAME_SIZE 20

void Service_BrkInfo(void);

void Service_BrkContinue(void);

void BrkPointMain(void);

void BrkSetName(uint8_t* name);

void BrkClearName(void);
#endif