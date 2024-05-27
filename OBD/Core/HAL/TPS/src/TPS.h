#ifndef __TPS_H
#define __TPS_H

/**
 * @file TPS.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of NTC Temperature sensor
 * @version    1.0.0
 * @date       2024-03-07
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "typedefs.h"
#include "ADC.h"
#include "services.h"

/*____________________Macros________________________________________*/
#define TPS_UT  UT
#define ADC_CHANNEL_TPS 4
/*____________________UserDatatypes___________________________________*/

/// @brief this enumeration will be used as a return types to indicate function returns successfully !.
typedef enum
{
    VALID_TPS                   = 0,
    NOT_VALID_TPS               = 1,
    UNKOWN_TPS                  = 2,
    WRITING_IN_PROGRESS_TPS     = 3
}enumRetTps_e;

/// @brief this enumeration defines the states of the NTC temperature sensor.
/// @note High                  (above 70 celsius)
/// @note Low                   (below 10 celsius)
/// @note Normal                (between 5 and 70  celsius)
/// @note Sensor Malfunction    (above 70 or below 0 )
typedef enum
{
    HIGH_TEMPERATURE            = 0,
    LOW_TEMPERATURE             = 1,
    NORMAL_TEMPERATURE          = 2,
    MALFUNCTION_TEMPERATURE     = 3
}  enumTemperatureStates_e;
                    
/// @brief this structure contains updated temperature and state of NTC sensor.
typedef struct
{    
    /*the temperature in celsius*/
    double                  doubleTmp;
    
    /*the temperature state of the sensor*/
    enumTemperatureStates_e enumTmpState;

}strTemperatureNtc_t;

/*_____________________Prototypes______________________________________*/

#if(TPS_UT==ON)
/// @brief this function Claculates resistance of NTC sensor using this equation Rntc=10000.0/((4096.0/adcValue)-1)
/// @param doubleNtcResistanceInOhms the resistance of NTC sensor
/// @param u32AdcValue : the adc value.
/// @return the state of function execution.
///         VALID_TPS (0) - NOT_VALID_TPS (1) - UNKOWN_TPS (2) - WRITING_IN_PROGRESS_TPS(3)

/// @covers Req ID:CCO-CDD-2008
enumRetTps_e enum_TPSClaculateResistance(u32_t u32AdcValue,float32_t *floatNtcResistanceInOhms);
#endif


/// @brief this function initializes ADC channel connected to NTC sensor
/// @param  NAN
/// @return the state of function execution
///         VALID_TPS (0) - NOT_VALID_TPS (1) - UNKOWN_TPS (2) - WRITING_IN_PROGRESS_TPS(3)

/// @note @covers Req_ID: CCO-CDD-2006
enumRetTps_e enum_TPSInit (void);

/// @brief this function Claculates temperature using NTC sensor using the Steinhart-Hart equation : 
/// 1/Tk  = A + B⋅ln(R) + C⋅((ln(R))^2) + D⋅((ln(R))^3)
/// where : 
/// Tk : temperature in kelvin
/// Tc : temperature in cels .
/// (Tc = Tk - 273.15)
/// use https://docs.google.com/spreadsheets/d/1iCVrfVw6mKBvbdQMUZ4F2GkdwTHWHAgpWmi-wSvRxqU/edit#gid=1542034892 
///  to derive the coefficients  A,B,C, and D .
/// R : the resistance of NTC  equation :
///        1/Tk  = A + B⋅ln(R) + C⋅((ln(R))^2) + D⋅((ln(R))^3) and updates PRIVATE strXX structure

/// @return NAN
/// @param NAN
/// @ref https://crew-teq.atlassian.net/wiki/spaces/OBDAddOn/pages/26214427/temperature+sensor+driver
/// @ref https://docs.google.com/spreadsheets/d/1iCVrfVw6mKBvbdQMUZ4F2GkdwTHWHAgpWmi-wSvRxqU/edit#gid=1542034892

/// @note @covers Req_ID: CCO-CDD-2007
void vid_TPSManage(void);

/// @brief this function gets the value of : PRIVATE strXX structure
///        which contains the temperature and state of the NTC sensor.
/// @param  strNTCInfoOut
///         VALID_TPS (0) - NOT_VALID_TPS (1) - UNKOWN_TPS (2) - WRITING_IN_PROGRESS_TPS(3)

/// @note @covers Req_ID: CCO-CDD-2009
enumRetTps_e enum_TPSGetTemperature(strTemperatureNtc_t* strNTCInfoOut);


/// @brief this function calculate Base^Pow (it is just like Pow in standard c )
/// @param Base 
/// @param Pow 
/// @return result 
double double_CustomePow(double Base,char Pow);

/*end __TPS_H*/
#endif
