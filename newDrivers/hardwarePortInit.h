#ifndef _HWPORTINIT__H
#define _HWPORTINIT__H

#include "commonMacros.h"
#include "standards.h"

#include "Timer.h"
#include  "mcu.h"



typedef enum {
		Init_API_RETURN_OK=1,
		Init_API_RETURN_ERROR=-1
}InitApiRet_e;


InitApiRet_e enumSystemInit(void);
#endif