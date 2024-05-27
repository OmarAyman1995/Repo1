
/**
 * @file Mcu.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of Microcontroller Component
 * @version    1.0.0
 * @date       2024-02-22
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __MCU__H__
#define __MCU__H__



/*__________________ -Includes- _________________*/
#include "typedefs.h"
#include "stm32f1xx_hal.h"
#include "main.h"
/*__________________ -Macros- _________________*/

#define MCU_UT	UT

/*__________________ -Public- _________________*/


/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_MCU 			= 0,
	NOT_VALID_MCU 		= 1,
	UNKOWN_MCU 			= 2
}enumRetMcu_e;

///@brief : this enumeration defines the stability of the PLL Unit. 
typedef enum 
{
	PLL_UNSTABLE 		= 0,
	PLL_STABLE 		= 1,
	PLL_UNKNOWN  		= 2
}enumPLLstability_e;



/*__________________ -Prototypes- _________________*/


/// @brief  :this function is responsible for enabling clocks of : 
///          CAN + UART1,2,3 + GPIOA,B,C + ADC + I2C + WDT
/// @param  :NAN
/// @return : the validity of enabling clocks of peripherals
///           VALID_MCU Or NOT_VALID_MCU Or UNKOWN_MCU
/// @covers_Req_ID : CCO-CDD-2030

enumRetMcu_e enum_McuEnablePeripherals(void); 


/// @brief  :this  function is responsible for selecting the clock source
///          of the system to be the external 8MHZ crystal,
///          and use PLL to boost the speed to 64MHZ.         
/// @param  : NAN
/// @return : the validity of executing this function 
///           VALID_MCU Or NOT_VALID_MCU Or UNKOWN_MCU   
/// @covers_Req_ID : CCO-CDD-2031

enumRetMcu_e enum_McuSetClockSource(void);

/// @brief  : this function returns the PLL status, if its activated or Not.      
/// @param  : NAN
/// @return : the stability of the PLL Unit.  
///           PLL_STABLE  or PLL_UNSTABLE  or PLL_UNKNOWN        
/// @covers_Req_ID :CCO-CDD-2032

enumPLLstability_e  enum_McuGetPllStatus(void);

/// @brief  : this function is responsible for Disabling all unused peripherals.      
/// @param  : NAN
/// @return : the validity of Disabling clocks of Unused peripherals
///           VALID_MCU Or NOT_VALID_MCU Or UNKOWN_MCU      
/// @covers_Req_ID :CCO-CDD-2033

enumRetMcu_e  enum_McuDisablePeripherals(void);


#endif
