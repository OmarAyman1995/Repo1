################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Timer.c \
../Core/Src/hardwarePortInit.c \
../Core/Src/keypad.c \
../Core/Src/lcd.c \
../Core/Src/lcdServices.c \
../Core/Src/main.c \
../Core/Src/mcu.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_hal_timebase_tim.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/temperature_control.c \
../Core/Src/temperature_sensor.c 

OBJS += \
./Core/Src/Timer.o \
./Core/Src/hardwarePortInit.o \
./Core/Src/keypad.o \
./Core/Src/lcd.o \
./Core/Src/lcdServices.o \
./Core/Src/main.o \
./Core/Src/mcu.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_hal_timebase_tim.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/temperature_control.o \
./Core/Src/temperature_sensor.o 

C_DEPS += \
./Core/Src/Timer.d \
./Core/Src/hardwarePortInit.d \
./Core/Src/keypad.d \
./Core/Src/lcd.d \
./Core/Src/lcdServices.d \
./Core/Src/main.d \
./Core/Src/mcu.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_hal_timebase_tim.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/temperature_control.d \
./Core/Src/temperature_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Timer.d ./Core/Src/Timer.o ./Core/Src/Timer.su ./Core/Src/hardwarePortInit.d ./Core/Src/hardwarePortInit.o ./Core/Src/hardwarePortInit.su ./Core/Src/keypad.d ./Core/Src/keypad.o ./Core/Src/keypad.su ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/lcdServices.d ./Core/Src/lcdServices.o ./Core/Src/lcdServices.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mcu.d ./Core/Src/mcu.o ./Core/Src/mcu.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_hal_timebase_tim.d ./Core/Src/stm32f1xx_hal_timebase_tim.o ./Core/Src/stm32f1xx_hal_timebase_tim.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/temperature_control.d ./Core/Src/temperature_control.o ./Core/Src/temperature_control.su ./Core/Src/temperature_sensor.d ./Core/Src/temperature_sensor.o ./Core/Src/temperature_sensor.su

.PHONY: clean-Core-2f-Src

