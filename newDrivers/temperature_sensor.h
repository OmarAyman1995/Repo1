
#ifndef _TEMP_SENS_H
#define _TEMP_SENS_H    


#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "standards.h"
#include "commonMacros.h"

typedef enum {
		TEMP_SENS_API_RETURN_OK=1,
		TEMP_SENS_API_RETURN_ERROR=-1
}tempSensApiRet_e;



/// @brief This function updates value of temperature sensor
/// @param  NONE
/// @return the temperature of the sensor which wull be reurned is between (0.0 ~ 150.0)
s64_t s64_TemperatureUpdateValue(void);

#endif