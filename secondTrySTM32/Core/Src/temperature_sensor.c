#include "temperature_sensor.h"

PUBLIC ADC_HandleTypeDef hadc1;

double TemperatureUpdateValue(void)
{
    u16_t u8_adcRead0  = 0x00;
    double sensorTemperature = 0 ; 
    
   
    HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
    u8_adcRead0 =  HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
   

    sensorTemperature = (double) u8_adcRead0;
    sensorTemperature = sensorTemperature * 150.0;
    sensorTemperature = sensorTemperature / 4096.0;
    return sensorTemperature;
}
