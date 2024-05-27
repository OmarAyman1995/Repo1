/**
 * @file Timer.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of (Timer) Component
 * @version    1.0.0
 * @date       2024-03-06
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __TIMERCREWTEQ__H__
#define __TIMERCREWTEQ__H__
/*__________________ -Includes- _________________*/
#include    "main.h"
#include    "typedefs.h"
#include    "stm32f1xx_hal.h"

/*__________________ -Macros- _________________*/
#define     FREE_RUNNIG_TIMER_MODE        0U 


#define     TIMER_ONE_THIRD               90U //8us High , 16us LOW
#define     TIMER_TWO_THIRD               740U // 16us High , 8us LOW
#define     TIMER_200US_SOF               10500U// ~200us

/*__________________ -UserDataTypes- _________________*/

///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_TIMER 			= 0,
	NOT_VALID_TIMER		= 1,
	UNKOWN_TIMER			= 2
}enumRetTimer_e;

/// @brief this enumeration contains the different options for Ton.
typedef enum
{
  TON_8_US            = TIMER_ONE_THIRD,
  TON_16_US           = TIMER_TWO_THIRD,
  TON_200_US          = TIMER_200US_SOF
}enumTonInUs_e;

/// @brief this enumeration will be used for declaration the HIGH and LOW voltage levels  .
typedef enum
{
  SAE_LOW = 0 ,
  SAE_HIGH = 1,
  SAE_SOF = 2
}enumSAElogic_e;

/*__________________ -Public- _________________*/


/*__________________ -Prototypes- _________________*/

/// @brief this function is responsible for initialization of Timer module to work in (free running Mode).
/// @param NAN
/// @return the validity of executing the function
///         VALID_TIMER Or NOT_VALID_TIMER  Or UNKOWN_TIMER  
/// @covers Req ID:CCO-CDD-2085
enumRetTimer_e enum_TimerInit(void);

/// @brief this function is responsible for initializing timer module to set the Ton time (duty cycle)
///        so the Mcu could generate the HIGH and LOW bits concepts
///        in (SAE J1850 PWM) perspective
/// @param enumHighLow :SAE_LOW or SAE_HIGH
/// @return the validity of executing the function
///         VALID_TIMER Or NOT_VALID_TIMER  Or UNKOWN_TIMER  
/// @covers Req ID:CCO-CDD-2087
enumRetTimer_e enum_TimerSetPeriod(enumSAElogic_e enumHighLow);


/// @brief this function is responsible for getting the counter register of the timer
///        so we can recognize the HIGH and LOW bits concept in (SAE J1850 PWM) perspective.
/// @param NAN
/// @return the validity of executing the function
///         VALID_TIMER Or NOT_VALID_TIMER  Or UNKOWN_TIMER  
/// @covers Req ID:CCO-CDD-2088
enumRetTimer_e enum_TimerWaitToGetPeriod(void);


#endif