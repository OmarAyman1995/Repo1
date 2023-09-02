#ifndef __MEMORYACCESS_H
#define __MEMORYACCESS_H

#include <stdint.h>
#include <stddef.h>
#include "BitMath.h"
#include "Address.h"

uint32_t AccessMemoryRead(uint32_t address);

void AccessMemoryWrite(uint32_t address, uint8_t value, uint32_t byte_number);

void AccessRegisterWrite(uint32_t address, uint32_t value);

void AccessBitWrite(uint32_t address, uint32_t bit_number, uint32_t bit_value);

uint32_t ReadGeneralRegister(const uint8_t* reg_Name);

uint32_t read_GeneralRegister(const uint8_t* reg_Name);

void clock_Peripherals_Init(void);
#endif
