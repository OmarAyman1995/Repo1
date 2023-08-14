#include "hardwarePortInit.h"

PUBLIC void portInit(void); // to be ADDED in future by Ahmed 
PUBLIC void timerInit(void); // to be ADDED in future by Ahmed
PUBLIC void rccInit(void); // to be ADDED in future by Ahmed


void initialization(void)
{
    portInit();
    timerInit();
    rccInit();
}