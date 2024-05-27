#include "CanCnfg.h"

/*Configuring Components */
#define WAKE_UP_FILTER_BANK     FILTER_BANK_2
#define CAN_ID_WAKEUP           0x5CF
#define LOW_POWER_APP_UT        UT           /*Enable to Run Unit test*/  

/*Constant Macros*/
#define LOW_POWER_CONDITION_TRUE  1
#define LOW_POWER_CONDITION_FALSE 0