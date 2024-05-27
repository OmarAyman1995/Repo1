#ifndef BUZZER_DRV_CNFG
#define BUZZER_DRV_CNFG

#include "typedefs.h"


#define BUZZER_PORT                 GPIOB 
#define BUZZER_PIN                  GPIO_PIN_3

#define BUZZER_MANAGE_PERIODICITY  (u8_t)100      /*time in ms*/

#define BUZZER_MAX_TIME             0xffff     /*Max wait time for a state*/

#define BUZZER_DRV_UT               UT      /*Enable to run Unit tests*/







#endif
