
/**
 * @file WDT.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of Watch-Dog Timer (WDT) Component
 * @version    1.0.0
 * @date       2024-03-05
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __WDTCREWTEQ__H__
#define __WDTCREWTEQ__H__



/*__________________ -Includes- _________________*/
#include "main.h"
#include "typedefs.h"
#include "stm32f1xx_hal.h"






/*__________________ -Macros- _________________*/
#define CPU_SPEED_IN_WWDG_DRIVER 32000

/*__________________ -Public- _________________*/



/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_WDT		= 0,
	NOT_VALID_WDT 		= 1,
	UNKOWN_WDT		= 2
}enumRetWdt_e;


/*__________________ -Prototypes- _________________*/

/// @brief this function is responsible for initializing WDT to make its period time 
///        is configurable with maximum 50 ms
/// please follow this formula : tWWDG  = tPCLK1 * 4096 * (2^ WDGTB[1:0]) * (T[5:0]  + 1 ) = (X ms)
///										tPCLK1 @ref : PCLK1_IN_WWDG_DRIVER
///										(2^ WDGTB[1:0]) : prescaler @ref hwwdg.Init.Prescaler = 8
///                                     (T[5:0]  + 1 )  : Down-Counter @ref hwwdg.Init.Counter 
/*[[  _________ tWWDG  = tPCLK1 X 4096 X (2^ WDGTB[1:0]) X (T[5:0]  + 1 ) = (X ms)
      u8TimeInMilliSec = (1/CPU_SPEED_IN_WWDG_DRIVER) X 4096 X prescaler X LOC_u32DownCounter
      LOC_u32DownCounter = u8TimeInMilliSec/((1/CPU_SPEED_IN_WWDG_DRIVER) X 4096 X prescaler)
  */
/// @param u8TimeInMilliSec: the reset time of WDT in milli-Second.
/// @return the validity of executing the function
///		    VALID_GPIO Or NOT_VALID_GPIO Or UNKOWN_GPIO

/// @covers Req ID: CCO-CDD-2050
enumRetWdt_e enum_WdtSetResetTime(u8_t u8TimeInMilliSec);


/// @brief this function resets the WDT counter to protect resetting.
/// @return NAN
/// @param NAN

/// @covers Req ID: CCO-CDD-2051 
void vid_WdtRefresh(void);

#endif
