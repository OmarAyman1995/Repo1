#ifndef __CRS_H
#define __CRS_H

/**
 * @file CRS.h
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      header file of Current sensor
 * @version    1.0.0
 * @date       2024-03-11
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
 #include "ADC.h"
/*____________________Macros________________________________________*/
#define             CRS_UT                                      UT

#define             CRS_MODULE_OUT_AT_0A                        2.50
#define             CRS_MODULE_SENSITIVITY                      0.185
#define             CRS_MODULE_ERROR_DETECTED                   0.10
#define             CRS_MODULE_ADC_ACCURACY                     (u16_t)4096
#define             ADC_CHANNEL_CURRENT_SENSOR                  1U
#define             VCC_CRS                                     5.0
/*____________________UserDatatypes___________________________________*/

/// @brief this enumeration will be used as a return types to indicate function returns successfully !.
typedef enum
{
    VALID_CRS               = 0,
    NOT_VALID_CRS           = 1,
    UNKOWN_CRS              = 2,
    WRITING_IN_PROGRESS_CRS = 3
}enumRetCrs_e;

/// @brief this enumeration defines the states of the current sensor.
/// @note      HIGH    :  >  2000mA
/// @note      LOW     :  <  10mA
/// @note      NORMAL  :  >= 10 mA   && <= 2000mA
/// @note      MALFUNCTION : anything else
/// @note      DISCONNECTED : 0A
typedef enum 
{
    HIGH_CURRENT              =  0 ,
    LOW_CURRENT               =  1 ,  
    NORMAL_CURRENT            =  2 ,
    MALFUNCTION_CURRENT       =  3 , 
    DISCONNECTED_CURRENT      =  4 
}enumCurrentStates_e;

/// @brief this structure contains updated current and state of  the current sensor.
typedef struct 
{
    /* the state of measured current .*/
    enumCurrentStates_e enumCurrentState;
    
    /*the conduction current the circuit consumes in milli Ampere.  */
    double              doubleMilliAmp;
    
}strCurrent_t;


/*_____________________Prototypes______________________________________*/


/// @brief this function initializes ADC channel connected to ACS sensorS
/// @param NAN
/// @return VALID_CRS (0) - NOT_VALID_CRS (1) - UNKOWN_CRS (2) - WRITING_IN_PROGRESS_CRS(3)
/// @note  covers Req ID : CCO-CDD-2010
enumRetCrs_e enum_CRSInit(void);


/// @brief this function Claculates current this equation : 
///        A = ---> {   [ADCvalue * (Vcc1/4096)] - (Vcc2/2) } * (1/185mv ) } 
///         Vcc1 : Vref of ADC (3.3V as a default value selected by ADC driver)
///         Vcc2 : Vcc of current sensor which is 5V . 
///         and updates a PRIVATE strXX structure
/// @param  NAN
/// @return NAN
/// @note  covers Req ID :CCO-CDD-2011
void  vid_CRSManage(void);


/// @brief this function gets the value of : PRIVATE strCurrent_t structure which contains the circuit current
///        in milli amp and state of the current sensor.
/// @param strCurrent (out) the temperature and state of sensor
/// @return the state of function execution.
///         VALID_CRS (0) - NOT_VALID_CRS (1) - UNKOWN_CRS (2) -WRITING_IN_PROGRESS_CRS(3)
/// @note  covers Req ID :CCO-CDD-2012, CCO-CDD-2013
enumRetCrs_e enum_CRSGetCurrent(strCurrent_t* strCurrent);

/*end __CRS_H*/
#endif
