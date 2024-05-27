set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

if(CI_BUILD_FLAG)
set(TOOLCHAIN_PREFIX /CrewDevEnv/Compilers/ARMGCC/v12.2.rel1/bin/arm-none-eabi-)
set(FLAGS
    "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
set(CPP_FLAGS
    "-fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc ${FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER}as)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)

else()
set(TOOLCHAIN_PREFIX C:/CrewDevEnv/Compilers/ARMGCC/v12.2.rel1/bin/arm-none-eabi-)
set(FLAGS
    "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
set(CPP_FLAGS
    "-fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc.exe ${FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER}as.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++.exe ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy.exe)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size.exe)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump.exe)

endif()


set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)



# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.20)
###############################################################################
# Set project name and source code folder location
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(DUMP_ASM "Create full assembly of final executable" OFF)

# Set microcontroller information
set(MCU_FAMILY STM32F1xx)
set(MCU_MODEL STM32F103xB)
set(CPU_PARAMETERS
-mcpu=cortex-m3
-mthumb)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeIDE/Application/User/Startup/startup_stm32f103c8tx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeIDE/STM32F103C8TX_FLASH.ld)
project(OBD_Project)
###############################################################################
set(EXECUTABLE OBD_Project)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###############################################################################
set(PROJECT_INCLUDE_DIRECTORIES

    # MCAL Generated files
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include 
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeIDE/Application/User/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    
    # App
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App
    
      # App
      ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/OBDStaticDataFetcher/src
      ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/LowPowerApp/src
      ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/MonitoringApp/src
      ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/AlarmApp/src

     # FuelSystemMonitor
     ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/FuelSystemMonitor/src
    
    # Battery Monitor Module
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/BatteryMonitor/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/BatteryMonitor/BatteryVoltageConverter/src

    # OBDII 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/OBDII

    # VIN Reader 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/VinNumberReader/src

    # Software Starter Module
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/SWStartInit/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/SWStartActions/src
    
    # Standard Files
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/StandardFiles
    
    # HAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/BLE_Driver
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/SDCard_Driver
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/TPS/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/External_Eeprom/src

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/LED_Driver/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Buzzer_Driver/src


    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/CRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Battery/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/BitsManager/src

    # MCAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Gpio_Integration
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Uart_Integration
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/adcIntegration
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CanDriver
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CanIntegration

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CmsisAbstract/src
    

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/MCU/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/WDT/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/GPIO/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/ADC/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/UART/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/I2C/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/TIMER/src

    # Middleware
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Converter
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/ClientCom
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CommandsHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDCom
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CNTDIS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CAN_ISO_15765/src
    # Middleware - CanComMngr
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComAL/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComStateMachine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ReceiveQueue/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/TransmitQueue/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/SubscribersDatabase/src
       
    
    
    # Middleware - CANTp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CANTp/src

    #Middleware - Sdcard
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/SDcard/src

    #Middleware - FAT32
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/FAT32/src
    
    #Middleware - OBDIIHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDIIHandler/src

    #Middleware - UDSHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/UDSHandler/src

    #StandardFiles - strings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/StandardFiles

    #Middleware - Assertion
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Assertion/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Assertion/src/FailureAction/src

    # Middleware - VecoApp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/VeCoApp/src

    # Middleware - UDSHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/UDSHandler/src

    # HAL - rtcAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/rtcAL/src

    # Middleware - Converter
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDDataConverter/src

    # Middleware - ConverterUnits
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDDataConverter/src/ConversionUnits/src

    # Middleware - Memory Manager
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/MemMangEeprom/src
    
    # Middleware - Pwm_Commander
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/PWM_Commander/src
    
    # FreeRtos
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles/ARM_CM3_MPU
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles/include
    #Middleware - HAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/CRS/src
    #Middleware - CNTDIS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CNTDIS/src
    # Tasks
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/BluetoothCommTask
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/CANScheduledFunction
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/ProcessingTask
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/CommonFilesBetweenTasks
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/MonitorTask
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/MqttCommTask

    # SIM800L
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src


    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/PIDsDatabase/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/VeDi_App/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/HandlingBluetooth/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/HandlingMqtt/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ProcessingRequest/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/ISO_Uart_Protocols/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Bluetooth_Driver/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComAL/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComStateMachine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ReceiveQueue/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/TransmitQueue/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/SubscribersDatabase/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/PIDsDatabase/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ConversionMngr/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ConversionMngr/src/ConversionUnits/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/QueueInterface/
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/StandardFiles/JsonLibrary/src/


    )


file(GLOB STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
# MCAL Generated files
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeIDE/Application/User/Core/*.c
   
# App
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/OBDStaticDataFetcher/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/LowPowerApp/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/MonitoringApp/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/AlarmApp/src/*.c
    
     # App
     ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/BatteryMonitor/src/*.c
     ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/BatteryMonitor/BatteryVoltageConverter/src/*.c

     # FuelSystemMonitor
     ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/FuelSystemMonitor/src/*.c
    
    # OBDII 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/OBDII/*.c

    # VIN Reader 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/VinNumberReader/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/SWStartInit/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/SoftwareStarter/SWStartActions/src/*.c


# HAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/BLE_Driver/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/TPS/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/External_Eeprom/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/LED_Driver/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Buzzer_Driver/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Battery/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/BitsManager/src/*.c

# MCAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CanDriver/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CanIntegration/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Gpio_Integration/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/adcIntegration/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Timer_Integration/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/Uart_Integration/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/CmsisAbstract/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/MCU/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/GPIO/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/WDT/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/ADC/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/UART/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/I2C/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MCAL/TIMER/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Battery/src/*.c

# Middleware

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/CanComMngr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/TransmitQueue/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ReceiveQueue/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/SubscribersDatabase/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComStateMachine/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComAL/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Converter/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/ClientCom/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CommandsHandler/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDCom/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CANTp/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CNTDIS/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/CAN_ISO_15765/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/MemMangEeprom/src/*.c
    
    # Middleware - Pwm_Commander
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/PWM_Commander/src/*.c

    #Middleware - Sdcard
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/SDcard/src/*.c

     #Middleware - FAT32
     ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/FAT32/src/*.c

    #Middleware - OBDIIHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDIIHandler/src/*.c


    #StandardFiles - strings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/StandardFiles/*.c

    #Middleware - Assertion
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Assertion/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/Assertion/src/FailureAction/src/*.c

    # Middleware - VecoApp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/VeCoApp/src/*.c

    # Middleware - UDSHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/UDSHandler/src/*.c

    # HAL - rtcAL
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/rtcAL/src/*.c

    # Middleware - Converter
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDDataConverter/src/*.c

    # Middleware - ConverterUnits
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/OBDDataConverter/src/ConversionUnits/src/*.c

    # FreeRtos
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles/ARM_CM3_MPU/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/FreeRTOSfiles/source/*.c

    #HAL - CRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/CRS/src/*.c

    # Tasks
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/BluetoothCommTask/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/CANScheduledFunction/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/ProcessingTask/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/MonitorTask/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Tasks/MqttCommTask/*.c

    # SIM800L
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Mqtt_Driver/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/PIDsDatabase/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/VeDi_App/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/HandlingBluetooth/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Wireless_App/src/HandlingMqtt/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ProcessingRequest/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Middleware/ISO_Uart_Protocols/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/HAL/Bluetooth_Driver/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComAL/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ComStateMachine/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/ReceiveQueue/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/TransmitQueue/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ComM/src/SubscribersDatabase/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/PIDsDatabase/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ConversionMngr/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/Vehicle_App/src/ConversionMngr/src/ConversionUnits/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/App/QueueInterface/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Core/StandardFiles/JsonLibrary/src/*.c
)


add_executable(${EXECUTABLE} 
               ${STM32CUBEMX_SOURCES} 
               ${STARTUP_SCRIPT})

# target_link_libraries(${EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/libCrewConnect.a )


target_compile_definitions(${EXECUTABLE} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
    USE_HAL_DRIVER 
    STM32F103xB)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})
###############################################################################
target_compile_options(${EXECUTABLE} PRIVATE
${CPU_PARAMETERS}
    -Wextra
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion # STM libraries!
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-O0 -g3 -ggdb>
    $<$<CONFIG:Release>:-O0 -g3>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--no-warn-rwx-segment
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    --specs=nosys.specs
    -Wl,--print-memory-usage
    -Wl,--end-group)

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)


set(BIN_FILE ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin)
set(FLASH C:/CrewDevEnv/Debuggers/Micro/ST/ST_LINK/v.1.7.0/bin/st-flash.exe)
add_custom_target(Flash
    COMMAND ${CMAKE_COMMAND} -E echo "Flashing ${BIN_FILE} with st-flash"
    COMMAND ${FLASH} write ${BIN_FILE} 0x8000000
    COMMAND ${FLASH} reset
)

add_custom_target(Reset
    COMMAND ${FLASH} reset
)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()
###############################################################################
