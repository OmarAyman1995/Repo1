#ifndef __TEMP_CONTROL_H
#define __TEMP_CONTROL_H

#include "standards.h"
#include "commonMacros.h"
#include "keypad.h"
#include "lcd.h"
#include "lcdServices.h"
#include "main.h"

#include "temperature_sensor.h" // just for testing


typedef enum {
		TEMP_CONTROL_API_RETURN_OK=1,
		TEMP_CONTROL_API_RETURN_ERROR=-1
}tempControlApiRet_e;


typedef enum {
		TEMP_INCREASE_WHEN_BUTTON_PRESSED=1,
		TEMP_DECREASE_WHEN_BUTTON_PRESSED=0
       
}setTemperatureAction_e;

typedef enum
{
    TEMP_AUTO_BUTTON_PRESSED=1,
    TEMP_AUTO_BUTTON_UNPRESSED=0
}autoButtonState_e;
 
/// @brief this function handles teperature setting of the vehicle,
//           it handles three actions (temperature increse, decrese, Auto Mode)
/// @param    it takes no arguments
/// @return TEMP_CONTROL_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns TEMP_CONTROL_API_RETURN_ERROR "-1" 
tempControlApiRet_e temperatureHandle(void);
#endif