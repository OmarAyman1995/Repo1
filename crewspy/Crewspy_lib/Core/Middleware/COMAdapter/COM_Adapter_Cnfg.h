#ifndef __COM_ADAPTER_CNFG_H
#define __COM_ADAPTER_CNFG_H

#include "BuildOptions.h"
typedef enum{
    UARTTP  = 0,
    CANTP   = 1,
    I2CTP   = 2,
    SPITP   = 3,
    LINTP   = 4,
}enumWhichComPotocol;

#if COMMUNICATION_USED == UART
    #define COM_PROTOCOL UARTTP

#elif COMMUNICATION_USED == SPI
    #define COM_PROTOCOL SPITP

#elif COMMUNICATION_USED == I2C
    #define COM_PROTOCOL I2CTP

#elif COMMUNICATION_USED == CAN
    #define COM_PROTOCOL CANTP

#endif

#endif

