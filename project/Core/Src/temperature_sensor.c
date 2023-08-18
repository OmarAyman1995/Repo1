#include "temperature_sensor.h"

PUBLIC ADC_HandleTypeDef hadc1;

s64_t s64_TemperatureUpdateValue(void)
{
    u32_t LOC_u32adcRead0  = 0x00;
    s64_t LOC_s64sensorTemperature = 0.0 ; 
    
   
    HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
    LOC_u32adcRead0 =  HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
   
    LOC_s64sensorTemperature = (s64_t)LOC_u32adcRead0;
    LOC_s64sensorTemperature = LOC_s64sensorTemperature * 150.0;
    LOC_s64sensorTemperature = LOC_s64sensorTemperature / 4096.0;
    

    if(LOC_s64sensorTemperature>=0.0 && LOC_s64sensorTemperature<150.0)
    {
        return LOC_s64sensorTemperature;
    }
    else 
    {
        return TEMP_SENS_API_RETURN_ERROR;
    }
}
