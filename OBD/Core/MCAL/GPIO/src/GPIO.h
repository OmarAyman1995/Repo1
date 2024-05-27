
/**
 * @file GPIO.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of General Purpose Input Output (GPIO) Component
 * @version    1.0.0
 * @date       2024-02-27
 *
 * @copyright  Copyright (crewteq.com) 2024
 */


#ifndef __GPIOCREWTEQ__H__
#define __GPIOCREWTEQ__H__



/*__________________ -Includes- _________________*/
#include "main.h"
#include "typedefs.h"
#include "stm32f1xx_hal.h"

/*__________________ -Macros- _________________*/
#define GPIO_UT  UT

/*__________________ -Public- _________________*/



/*__________________ -UserDataTypes- _________________*/
///@brief : 	this enumeration will be used as a return types
        //  to indicate if the function returns successfully
        //  or Not !.
typedef enum 
{
	VALID_GPIO 			= 0,
	NOT_VALID_GPIO 		= 1,
	UNKOWN_GPIO			= 2
}enumRetGpio_e;


/*__________________ -Prototypes- _________________*/

/// @brief this function is responsible for initializing gpio pins as required at high speed 64MHZ.
/// @param  NAN
/// @return the validity of executing the function 
///         VALID_GPIO Or NOT_VALID_GPIO Or UNKOWN_GPIO

/// @covers_Req_ID :CCO-CDD-2040
enumRetGpio_e enum_GpioInit(void);



/// @brief                    this function is responsible for (atomic) Reading a specific Pin in a PORT.
/// @param GPIOx              the PORT a pin connected to      (----Mapped to --- [PORTA,B,C])
/// @param u16Pinx 			  bit from the port                (----Mapped to --- [bit number])
/// @param enumPinState(Out)  the voltage level STATE of pin   (----Mapped to --- [High Voltage state , LOW voltage state])
///								This parameter can be GPIO_PIN_x where x can be (0..15).
/// @return the validity of executing the function 
///         VALID_GPIO Or NOT_VALID_GPIO Or UNKOWN_GPIO 

/// @covers_Req_ID :CCO-CDD-2041
enumRetGpio_e enum_GpioReadPin(GPIO_TypeDef* GPIOx,u16_t u16Pinx,GPIO_PinState* enumPinState);

/// @brief    this function is responsible for (atomic) writing a specific Pin in a PORT.
/// @param GPIOx              the PORT a pin connected to      (----Mapped to --- [PORTA,B,C])
/// @param u16Pinx 			  bit from the port                (----Mapped to --- [bit number])
///                           This parameter can be GPIO_PIN_x where x can be (0..15).
/// @param enumPinState       the voltage level STATE of pin   (----Mapped to --- [High Voltage state , LOW voltage state])

/// @return the validity of executing the function 
///         VALID_GPIO Or NOT_VALID_GPIO Or UNKOWN_GPIO 

/// @covers_Req_ID :CCO-CDD-2042
enumRetGpio_e enum_GpioWritePin(GPIO_TypeDef* GPIOx,u16_t u16Pinx,GPIO_PinState enumPinState);

/// @brief    this function is responsible for Toggeling a specific Pin in a PORT.
/// @param GPIOx              the PORT a pin connected to      (----Mapped to --- [PORTA,B,C])
/// @param u16Pinx 			  bit from the port                (----Mapped to --- [bit number])
///                           This parameter can be GPIO_PIN_x where x can be (0..15).

/// @return the validity of executing the function 
///         VALID_GPIO Or NOT_VALID_GPIO Or UNKOWN_GPIO 

/// @covers_Req_ID :CCO-CDD-2042
enumRetGpio_e enum_GpioTogglePin(GPIO_TypeDef* GPIOx,u16_t u16Pinx);

/// @brief  this function is responsible for initializing all unused pins as pull down inputs. 
/// @param  NAN
/// @return 

/// @covers_Req_ID :CCO-CDD-2043
void vid_GpioInitUnusedPins(void);


/// @brief  this function is responsible for initializing all Used pins. 
/// @param  NAN
/// @return NAN

/// @covers_Req_ID :CCO-CDD-2044
void vid_GpioInitUsedPins(void);

/// @brief  this function is responsible for refreshing used pins and unused pins configurations.
/// @param  NAN
/// @return NAN
/// @covers_Req_ID :CCO-CDD-2044
void vid_GpioManage(void);

#endif
