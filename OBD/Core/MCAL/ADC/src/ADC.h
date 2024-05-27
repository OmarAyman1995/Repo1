
/**
 * @file ADC.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of Analoug / digtal converter (ADC) Component
 * @version    1.0.0
 * @date       2024-03-04
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __ADCCREWTEQ__H__
#define __ADCCREWTEQ__H__



/*__________________ -Includes- _________________*/
#include "main.h"
#include "typedefs.h"
#include "stm32f1xx_hal.h"

/*__________________ -Macros- _________________*/
#define ADC_UT 	UT

/*__________________ -Public- _________________*/



/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_ADC 			= 0,
	NOT_VALID_ADC 		= 1,
	UNKOWN_ADC			= 2
}enumRetAdc_e;


/*__________________ -Prototypes- _________________*/


/// @brief this function is responsible for  initializing the  adc peripheral in discontinuous Mode with Software trigger (without HW trigger) .
/// @param  NAN

/// @covers Req ID : CCO-CDD-2060
enumRetAdc_e enum_AdcInit(void);


/// @brief this function is responsible for reading the digital representation (value from 0 to 4095 )
///        of the analog voltage on a specific analog channel.
/// @param u8Channel ADC channel to read from (for example channel0 @ PA0, so set u8Channel = 0)
/// @param u16ReadValue the digital representation (value from 0 to 4095 )
///                     of the analog voltage on the u8Channel
/// @return VALID_ADC Or NOT_VALID_ADC Or UNKOWN_ADC
///         the validity of executing the function

/// @covers Req ID :CCO-CDD-2061
enumRetAdc_e enum_AdcReadFromChannel(u8_t u8Channel,u32_t *u32ReadValue);


#endif
