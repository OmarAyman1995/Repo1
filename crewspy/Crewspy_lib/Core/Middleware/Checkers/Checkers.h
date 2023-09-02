#ifndef __CHECKERS_H
#define __CHECKERS_H

#include "GlobalCnfg.h"

uint8_t checkEquality(uint8_t byte,uint8_t data);
uint8_t checkRange(uint8_t byte,uint8_t min,uint32_t max);
uint8_t calculateCRC(uint8_t *frame,uint8_t sizeOfFrame);

#endif

