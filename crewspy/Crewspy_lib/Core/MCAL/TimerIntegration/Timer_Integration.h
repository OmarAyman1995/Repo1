#ifndef TIMER_INTEGRATION_H
#define TIMER_INTEGRATION_H

#include "GlobalCnfg.h"

#define TIMER_PRES 8
#define TIMER_TOP 65000
#define TIMER_NUMBER TIM1

/*      APIs    */

void vid_Timer_Init(void);

void vid_Timer_Start(void);

void vid_Timer_Stop(void);

void vid_Timer_DeInit(void);

uint64_t u64_Timer_GetCounts(void);

void u16_Timer_SetCounts(uint16_t counts);

#endif
