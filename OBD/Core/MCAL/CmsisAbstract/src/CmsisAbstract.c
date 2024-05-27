#include "stdint.h"
#include "CmsisAbstract.h"
#include "cmsis_gcc.h"

void vid_EnableIrq(void)
{
   __enable_irq();
}

void vid_DisableIrq(void)
{
   __disable_irq();
}

void vid_GoToWFI(void)
{
    __WFI();
}
