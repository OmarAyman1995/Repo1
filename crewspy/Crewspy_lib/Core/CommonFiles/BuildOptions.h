#ifndef __BUILDOPTIONS_H
#define __BUILDOPTIONS_H

/***********************************************************************/
#define STM
#define AVR

#define TARGET_ARCH STM
/***********************************************************************/
#define stm32f103
#define atmega32

#define TARGET_MCU stm32f103
// Only if TARGET_ARCH is STM or ARM
#define TARGET_CORTEX 3 
/***********************************************************************/
#define COMPILER_PATH C:/devtools/arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi/bin/arm-none-eabi-
/***********************************************************************/
#define UART    0
#define SPI     1
#define I2C     2
#define CAN     3

#define COMMUNICATION_USED UART
/***********************************************************************/
#define YES
#define NO

#define BUILD_WITH_OUR_DRIVER YES
/***********************************************************************/
#define AVR_GNU
#define ARM_GNU

#define TOOLCHAIN ARM_GNU
#endif
