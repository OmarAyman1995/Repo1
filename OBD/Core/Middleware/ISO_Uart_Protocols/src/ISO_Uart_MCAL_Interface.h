#ifndef __ISO_UART_MCAL_INTERFACE_H
#define __ISO_UART_MCAL_INTERFACE_H



#include "typedefs.h"
#include "ISO_Uart_Protocols.h"


void IsoUartInit10400bps(void);
void IsoUartInit5bps(void);

/**
 * @brief handles sending on UART using MCAL Driver
 * 
 * @param LOC_arrData 
 * @param LOC_u32size 
 * @return u8_t 1 sucess, 0 fail
 */
u8_t u8_UartSend(u8_t LOC_arrData[], u32_t LOC_u32size);


/**
 * @brief handles receiving on UART by polling using MCAL Driver
 * 
 * @param LOC_arrData 
 * @param LOC_u32size 
 * @return u8_t 1 sucess, 0 fail
 */
u8_t u8_UartReceive(u8_t LOC_arrData[], u32_t LOC_u32size);


/**
 * @brief handles receiving on UART by interrupt using MCAL Driver
 * 
 * @param LOC_arrData 
 * @param LOC_u32size 
 * @return u8_t 1 sucess, 0 fail
 */
u8_t u8_UartReceiveIT(u8_t LOC_arrData[], u32_t LOC_u32size);


#endif
