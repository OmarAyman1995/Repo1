#ifndef __CONVUNITS_H
#define __CONVUNITS_H


#include "typedefs.h"



/* Conversion Units */

u8_t ConvVehicle_Speed(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvEngine_RPM(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvFuelSystemStatus(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvAir_Intake_Temprature(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvThrottle_Position(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvBarometric_Pressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvPIDS_Supported(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);


u8_t ConvFuelTrim(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvFuelPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvTimingAdvance(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvMassFlowRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvCommandedSecondaryAirStatus(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvOxygenSensorPresentIn2Banks(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvOxygenSensor1VoltageFuel(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvRunTimeSinceEngineStarts(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvFuelRailPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvFuelRailGaugePressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvOxygenSensor1ABCD(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvOxygenSensor1RatioCurrent(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvCatalystTemperature(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvCollect4Numbers(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvControlModuleVoltage(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvAbsoluteLoadValue(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvCommandedAirFuelEqRatio(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvMaxValuesForSensors(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvMaxValueForAirFlowRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvAbsEvapSystemPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveShortTermBanks(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveFuelInjectionTiming(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveEngineFuelRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveDriverDemandEngineTorque(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveMassAirFlowSensor(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConveTransmissionActualGear(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvDieselExhaustFluid(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvOdometer(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvEvapSystemPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvEvapSystemVaporPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u8_t ConvFuelLeveInput(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

u32_t getConvertedSize(void);

#endif
