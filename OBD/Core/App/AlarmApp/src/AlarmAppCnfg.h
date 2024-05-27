#include "typedefs.h"

#ifndef ALARM_APP_CNFG
#define ALARM_APP_CNFG

/*CONSTANT MACROS*/
#define ALARM_ON      (u8_t)1
#define ALARM_OFF     (u8_t)0
#define ALARM_ERROR   (u8_t)2


/*SWC Configurations*/
#define ALARM_MSG                      "DISCONNECTED"
#define BATTERY_ALARM_TOGGLE_PERIOD        500      /*Time in ms*/
#define BATTERY_ALARM_TOGGLE_TIME          5000    /*Time in ms*/
#define WIRELESS_ALARM_TOGGLE_PERIOD       1000   /*Time in ms*/  
#define ALARM_APP_UT                        ON  /*Enable to Run Unit test*/   

#define MAX_TIME        0xffffU


#endif
