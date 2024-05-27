#include "PIDsDatabase.h"
#include "ConvUnits.h"


/**
 * @brief pids database storage
 * 
 */
static PIDsInfo_t GLOB_arrpidsInfoArray[MAX_PIDS] = {
{.returned_length = 4 ,.pid_support_type = 0,  .pid_type = STATIC, .pid_convfunction = ConvPIDS_Supported},                // 0
{.returned_length = 4 ,.pid_support_type =  0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},               // 1
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},      // 2
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelSystemStatus},              // 3
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},             // 4
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},         // 5
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelTrim},                      // 6
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelTrim},                      // 7
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelTrim},                      // 8
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelTrim},                      // 9
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelPressure},                 // 10
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed},                // 11
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvEngine_RPM},                   // 12
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed},                // 13
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvTimingAdvance},                // 14
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},        // 15
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvMassFlowRate},                 // 16
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 17
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCommandedSecondaryAirStatus},  // 18
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvOxygenSensorPresentIn2Banks},  // 19
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 20
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 21
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 22
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 23
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 24
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 25
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 26
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1VoltageFuel},     // 27
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvVehicle_Speed},                // 28
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvVehicle_Speed},                // 29
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvVehicle_Speed},                // 30
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 31
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},               // 32
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 33
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelRailPressure},             // 34
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelRailGaugePressure},        // 35
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 36
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 37
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 38
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 39
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 40
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 41
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 42
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1ABCD},            // 43
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 44
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelTrim},                     // 45
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 46
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 47
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed},                // 48
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 49
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvEvapSystemPressure},           // 50
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed},                // 51
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 52
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 53
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 54
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 55
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 56
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 57
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 58
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOxygenSensor1RatioCurrent},    // 59
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCatalystTemperature},          // 60
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCatalystTemperature},          // 61
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCatalystTemperature},          // 62
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCatalystTemperature},          // 63
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},               // 64
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},              // 65
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvControlModuleVoltage},         // 66
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAbsoluteLoadValue},            // 67
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCommandedAirFuelEqRatio},      // 68
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 69
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},        // 70
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 71
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 72
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 73
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 74
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 75
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 76
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 77
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 78
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvMaxValuesForSensors},          // 79
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvMaxValueForAirFlowRate},       // 80
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvVehicle_Speed},                // 81
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 82
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAbsEvapSystemPressure},       // 83
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvEvapSystemVaporPressure},     // 84
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveShortTermBanks},              // 85
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveShortTermBanks},              // 86
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveShortTermBanks},              // 87
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveShortTermBanks},              // 88
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelRailGaugePressure},        // 89
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 90
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},            // 91
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},        // 92
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveFuelInjectionTiming},         // 93
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveEngineFuelRate},              // 94
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvVehicle_Speed},                // 95
{.returned_length = 4 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},               // 96
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveDriverDemandEngineTorque},    // 97
{.returned_length = 1 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveDriverDemandEngineTorque},    // 98
{.returned_length = 2 ,.pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvRunTimeSinceEngineStarts},     // 99
{.returned_length = 5 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConveDriverDemandEngineTorque},   // 100
{.returned_length = 2 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed},               // 101
{.returned_length = 5 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConveMassAirFlowSensor},          // 102
{.returned_length = 3 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},       // 103
{.returned_length = 3 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},       // 104
{.returned_length = 7 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 105
{.returned_length = 5 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 106
{.returned_length = 5 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 107
{.returned_length = 5 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 108
{.returned_length = 11 ,.pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 109
{.returned_length = 9 , .pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 110
{.returned_length = 3 , .pid_support_type =0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 111
{.returned_length = 10 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 112
{.returned_length = 6 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 113
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 114
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 115
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 116
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 117
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 118
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 119
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 120
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 121
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 122
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 123
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 124
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 125
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 126
{.returned_length = 13 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},    // 127
{.returned_length = 4 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},              // 128
{.returned_length = 41 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 129
{.returned_length = 41 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 130
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 131
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},       // 132
{.returned_length = 10 ,.pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 133
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 134
{.returned_length = 5 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAbsEvapSystemPressure},       // 135
{.returned_length = 13 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 136
{.returned_length = 41 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 137
{.returned_length = 41 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 138
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 139
{.returned_length = 17 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 140
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvThrottle_Position},           // 141
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveDriverDemandEngineTorque},   // 142
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 143
{.returned_length = 3 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvCollect4Numbers},             // 144
{.returned_length = 5 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvCollect4Numbers},             // 145
{.returned_length = 2 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 146
{.returned_length = 3 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvCollect4Numbers},             // 147
{.returned_length = 12 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 148
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                         // 149
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                         // 150
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                         // 151
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},       // 152
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvAir_Intake_Temprature},       // 153
{.returned_length = 6 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 154
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 155
{.returned_length = 17 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 156
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 157
{.returned_length = 2 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 158
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 159
{.returned_length = 4 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},              // 160
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 161
{.returned_length = 2 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveMassAirFlowSensor},          // 162
{.returned_length = 9 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},             // 163
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConveTransmissionActualGear},     // 164
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvDieselExhaustFluid},          // 165
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvOdometer},                    // 166
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},           // 167
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},           // 168
{.returned_length = 4 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvCollect4Numbers},           // 169
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 170
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 171
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 172
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 173
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 174
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 175
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 176
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 177
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 178
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 179
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 180
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 181
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 182
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 183
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 184
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 185
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 186
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 187
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 188
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 189
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 190
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 191
{.returned_length = 4 , .pid_support_type = 0, .pid_type = STATIC,  .pid_convfunction = ConvPIDS_Supported},            // 192
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 193
{.returned_length = 0 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = NULLPTR},                       // 194
{.returned_length = 2 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvFuelLeveInput},             // 195
{.returned_length = 8 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},           // 196
{.returned_length = 4 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},           // 197
{.returned_length = 7 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvCollect4Numbers},           // 198
{.returned_length = 2 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvRunTimeSinceEngineStarts},  // 199
{.returned_length = 1 , .pid_support_type = 0, .pid_type = DYNAMIC, .pid_convfunction = ConvVehicle_Speed}              // 200
};






u8_t u8_getSupportInfo(u8_t pid_number){
    return GLOB_arrpidsInfoArray[pid_number].pid_support_type;
}


u8_t u8_getPidType(u8_t pid_number){
    return GLOB_arrpidsInfoArray[pid_number].pid_type;
}


void    vid_setSupportInfo(u8_t pid_number, u8_t support_info){
    if(pid_number < MAX_PIDS){
        GLOB_arrpidsInfoArray[pid_number].pid_support_type = support_info;
    }
}


ConvUnitType p_getConvFunction(u8_t pid_number){
    return  GLOB_arrpidsInfoArray[pid_number].pid_convfunction;
}


u8_t u8_getReturnedBytes(u8_t pid){
    return GLOB_arrpidsInfoArray[pid].returned_length;
}
