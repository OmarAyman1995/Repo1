#ifndef _CMSISABSTRACT_H
#define _CMSISABSTRACT_H

/**
 * @brief abstracts upper layer from the Cmsis function called to enable all interrupts
 * 
 */
void vid_EnableIrq(void);

/**
 * @brief abstracts upper layer from the Cmsis function called to Disable all interrupts
 * 
 */
void vid_DisableIrq(void);

/**
 * @brief abstracts upper layer from the Cmsis function called to go to wait for interrupt mode (sleep Mode)
 * 
 */
void vid_GoToWFI(void);

#endif
