#ifndef LED_DRV_CNFG
#define LED_DRV_CNFG

#include "typedefs.h"


#define POWER_LED_PORT                 GPIOA 
#define POWER_LED_PIN                  GPIO_PIN_8


#define INDICATOR_LED_PORT             GPIOB 
#define INDICATOR_LED_PIN              GPIO_PIN_13

#define LED_MANAGE_PERIODICITY         (u8_t)100  /*time in ms*/

#define LED_MAX_TIME                       UINT16_MAX

#define LED_DRIVER_UT                      UT /*if you are going to unit test the component, set macro to ON */







#endif
