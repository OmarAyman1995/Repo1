# Read the contents of the header file
file(READ "Core/CommonFiles/ProjectConfigurations.h" HEADER_CONTENTS)

# Use regular expressions to extract the relevant values
string(REGEX MATCH "#define TARGET_ARCH ([A-Za-z_]*)" MATCHED_TARGET_ARCH "${HEADER_CONTENTS}")
string(REGEX MATCH "#define TARGET_MCU ([A-Za-z0-9]*)" MATCHED_TARGET_MCU "${HEADER_CONTENTS}")
string(REGEX MATCH "#define COMMUNICATION_USED ([A-Za-z_]*)" MATCHED_COMMUNICATION_USED "${HEADER_CONTENTS}")
string(REGEX MATCH "#define BUILD_WITH_OUR_DRIVER ([A-Za-z_]*)" MATCHED_BUILD_WITH_OUR_DRIVER "${HEADER_CONTENTS}")
string(REGEX MATCH "#define TARGET_CORTEX ([A-Za-z_0-9]*)" MATCHED_TARGET_CORTEX "${HEADER_CONTENTS}")
string(REGEX MATCH "#define COMPILER_PATH ([^\n]*)" MATCHED_COMPILER_PATH "${HEADER_CONTENTS}")
string(REGEX MATCH "#define TOOLCHAIN ([^\n]*)" MATCHED_TOOLCHAIN "${HEADER_CONTENTS}")

# Extract the values from the regular expression matches
if (MATCHED_TARGET_ARCH)
    string(REGEX REPLACE "#define TARGET_ARCH ([A-Za-z_]*)" "\\1" TARGET_ARCH ${MATCHED_TARGET_ARCH})
endif()

if (MATCHED_TARGET_MCU)
    string(REGEX REPLACE "#define TARGET_MCU ([A-Za-z0-9]*)" "\\1" TARGET_MCU ${MATCHED_TARGET_MCU})
    string(TOUPPER ${TARGET_MCU} TARGET_MCU_CAP)  # Convert to uppercase
    string(REGEX REPLACE "..$" "" TARGET_MCU_XX ${TARGET_MCU_CAP})
endif()

if (MATCHED_COMMUNICATION_USED)
    string(REGEX REPLACE "#define COMMUNICATION_USED ([A-Za-z_]*)" "\\1" COMMUNICATION_USED ${MATCHED_COMMUNICATION_USED})
endif()

if (MATCHED_BUILD_WITH_OUR_DRIVER)
    string(REGEX REPLACE "#define BUILD_WITH_OUR_DRIVER ([A-Za-z_]*)" "\\1" BUILD_WITH_OUR_DRIVER ${MATCHED_BUILD_WITH_OUR_DRIVER})
endif()

if (MATCHED_TARGET_CORTEX)
    string(REGEX REPLACE "#define TARGET_CORTEX " "" TARGET_CORTEX ${MATCHED_TARGET_CORTEX})
endif()

if (MATCHED_COMPILER_PATH)
    string(REGEX REPLACE ".* COMPILER_PATH ([^ ]+).*" "\\1" COMPILER_PATH ${MATCHED_COMPILER_PATH})
endif()

if (MATCHED_TOOLCHAIN)
    string(REGEX REPLACE "#define TOOLCHAIN ([A-Za-z_]*)" "\\1" TOOLCHAIN ${MATCHED_TOOLCHAIN})
endif()

# Print the output values to debug 
message("TARGET_ARCH: ${TARGET_ARCH}")
message("TARGET_MCU: ${TARGET_MCU}")
message("TARGET_MCU_CAP: ${TARGET_MCU_CAP}")
message("TARGET_MCU_XX: ${TARGET_MCU_XX}")
message("COMMUNICATION_USED: ${COMMUNICATION_USED}")
message("BUILD_WITH_OUR_DRIVER: ${BUILD_WITH_OUR_DRIVER}")
message("TARGET_CORTEX: ${TARGET_CORTEX}")
message("COMPILER_PATH: ${COMPILER_PATH}")
message("MATCHED_TOOLCHAIN: ${MATCHED_TOOLCHAIN}")
message("TOOLCHAIN: ${TOOLCHAIN}")


set(TOOLCHAIN_PREFIX ${COMPILER_PATH})
# CMAKE Configuration
set(CMAKE_SYSTEM_NAME Generic)
if(TARGET_ARCH STREQUAL "STM" OR TARGET_ARCH STREQUAL "ARM")
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(FLAGS "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
elseif(TARGET_ARCH STREQUAL "AVR")
    # Do Nothing
else()
    message(FATAL_ERROR "Wrong TARGET_ARCH at CMake Configurations")
endif()

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc.exe ${FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy.exe)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size.exe)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump.exe)
set(CMAKE_LINKER  ${TOOLCHAIN_PREFIX}ld.exe)
message("CMAKE_LINKER: ${CMAKE_LINKER}")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(DUMP_ASM "Create full assembly of final executable" OFF)

# Set microcontroller information
if (TARGET_ARCH STREQUAL "STM")
    set(MCU_FAMILY ${TARGET_MCU_XX})
    set(CPU_PARAMETERS
    -mcpu=cortex-m${TARGET_CORTEX}
    -mthumb)
    set(OPTIMIZE "-O0")

elseif(TARGET_ARCH STREQUAL "AVR")
    set(OPTIMIZE "-O0")
    set(CPU_PARAMETERS "-mmcu=${TARGET_MCU} -Wall")
else()
    message(FATAL_ERROR "Wrong TARGET_ARCH at MCU INFO")
endif()

cmake_minimum_required(VERSION 3.20)
project(crewspy)
set(EXECUTABLE crewspy)


# Adding Startup and Linker Files
if(TARGET_ARCH STREQUAL "STM")
    set(STARTUP_SCRIPT ${PROJECT_DIR}/StartupCodes/STM/startup_stm32f103xb.s)
    set(MCU_LINKER_SCRIPT ${PROJECT_DIR}/LinkerScripts/STM/STM32F103C8Tx_FLASH.ld)
endif()
# Adding Header Files
set(STM32CUBEMX_INCLUDE_DIRECTORIES

    # Application
    ${PROJECT_DIR}/Core/Application/Inc
    ${PROJECT_DIR}/Core/Application/SessionManager
    ${PROJECT_DIR}/Core/Application/UserInterface
    
    # CommonFiles
    ${PROJECT_DIR}/Core/CommonFiles
    ${PROJECT_DIR}/Core/CommonFiles/Services
    
    # CrewStandardServices
    ${PROJECT_DIR}/Core/CrewStandardServices/CommonInc
    ${PROJECT_DIR}/Core/CrewStandardServices/MemoryAccess
    ${PROJECT_DIR}/Core/CrewStandardServices/HW_Dependent
    ${PROJECT_DIR}/Core/CrewStandardServices/HW_Independent
    
    # MCAL
    ${PROJECT_DIR}/Core/MCAL/STMGeneratedDrivers/Drivers/CMSIS/Core/Include
    ${PROJECT_DIR}/Core/MCAL/STMGeneratedDrivers/Drivers/CMSIS/Device/ST/${MCU_FAMILY}xx/Include
    ${PROJECT_DIR}/Core/MCAL/STMGeneratedDrivers/Drivers/${MCU_FAMILY}xx_HAL_Driver/Inc
    ${PROJECT_DIR}/Core/MCAL/STMGeneratedDrivers/Drivers/${MCU_FAMILY}xx_HAL_Driver/Inc/Legacy
    ${PROJECT_DIR}/Core/MCAL/STMGeneratedDrivers/Inc
    ${PROJECT_DIR}/Core/MCAL/UartDriver
    ${PROJECT_DIR}/Core/MCAL/TimerDriver
    ${PROJECT_DIR}/Core/MCAL/UartIntegration
    ${PROJECT_DIR}/Core/MCAL/TimerIntegration
    
    # Middleware
    ${PROJECT_DIR}/Core/Middleware/Checkers
    ${PROJECT_DIR}/Core/Middleware/COMAdapter
    ${PROJECT_DIR}/Core/Middleware/Parser
    ${PROJECT_DIR}/Core/Middleware/Responder
    ${PROJECT_DIR}/Core/Middleware/ServiceHandler
    ${PROJECT_DIR}/Core/Middleware/Breakpoint
    ${PROJECT_DIR}/Core/Middleware/Unity/Inc
    
    # TransportProtocol
    ${PROJECT_DIR}/Core/TransportProtocol/UartTp
    )

# Adding Source Files
file(GLOB_RECURSE STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_DIR}/Core/*.c)

# list(REMOVE_ITEM STM32CUBEMX_SOURCES ${PROJECT_DIR}/Core/Middleware/Unity/Src/unity.c)

add_executable(${EXECUTABLE} 
               ${STM32CUBEMX_SOURCES} 
               ${STARTUP_SCRIPT})

if (TARGET_ARCH STREQUAL "STM")
    target_compile_definitions(${EXECUTABLE} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        USE_HAL_DRIVER 
        ${TARGET_MCU_CAP}xB)
endif()

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES})

# Compiler Flags
if (TOOLCHAIN STREQUAL "ARM_GNU")
    target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
        -Wall #warnings
        -Wextra
        -Wshadow
        -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -Wundef
        -fno-common
        -Wno-unused-parameter
        $<$<CONFIG:Debug>:${OPTIMIZE} -g3 -ggdb>
        $<$<CONFIG:Release>:${OPTIMIZE} -g3>
    )
elseif (TOOLCHAIN STREQUAL "AVR_GNU")
    target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
        -Wall #warnings
        -Wextra
        -Wshadow
        -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -Wundef
        -fno-common
        -Wno-unused-parameter
    )
endif()

# Linker Flags
if (TOOLCHAIN STREQUAL "ARM_GNU")
    target_link_options(${EXECUTABLE} PRIVATE
        -T${MCU_LINKER_SCRIPT}
        ${CPU_PARAMETERS}
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map
        -Wl,--start-group
        -lc
        -lm
        -Wl,--end-group
        -Wl,--print-memory-usage
        -Wl,--undefined=VarUint8 -Wl,--undefined=VarUint16 -Wl,--undefined=VarUint32
        -Wl,--undefined=VarInt8 -Wl,--undefined=VarInt16 -Wl,--undefined=VarInt32)
elseif (TOOLCHAIN STREQUAL "AVR_GNU")
    target_link_options(${EXECUTABLE} PRIVATE
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map
        -Wl,--start-group
        -Wl,--end-group
        -Wl,--print-memory-usage
        -Wl,--undefined=VarUint8 -Wl,--undefined=VarUint16 -Wl,--undefined=VarUint32
        -Wl,--undefined=VarInt8 -Wl,--undefined=VarInt16 -Wl,--undefined=VarInt32
)
endif()

# Custom Commands
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)


set(BIN_FILE ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin)
if (TARGET_ARCH STREQUAL "STM")
    set(FLASH D:/progs/Embedded/ARM/stlink-1.7.0-i686-w64-mingw32/bin/st-flash.exe)
    add_custom_target(flash
        COMMAND ${CMAKE_COMMAND} -E echo "Flashing ${BIN_FILE} with st-flash"
        COMMAND ${FLASH} write ${BIN_FILE} 0x8000000
        COMMAND ${FLASH} reset
    )
elseif(TARGET_ARCH STREQUAL "AVR")
    add_custom_target(flash
        COMMAND ${CMAKE_COMMAND} -E echo "Flashing ${PROJECT_NAME}.hex with usbasp"
        avrdude -c usbasp -p ${AVR_MCU} -U flash:w:${PROJECT_NAME}.hex:i
    )
else()
    message(FATAL_ERROR "Wrong TARGET_ARCH at Flashing")
endif()

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()
###############################################################################




###############################################################################
# Add library target
add_library(MY_LIB STATIC 
${PROJECT_DIR}/Core/Middleware/ServiceHandler/ServiceHandler.c
${PROJECT_DIR}/Core/MCAL/UartIntegration/Uart_Integration.c
${PROJECT_DIR}/Core/CommonFiles/Services/Services.c
${PROJECT_DIR}/Core/TransportProtocol/UartTp/UartTp.c
${PROJECT_DIR}/Core/Middleware/Checkers/Checkers.c
${PROJECT_DIR}/Core/Middleware/BreakPoint/BreakPoint.c
${PROJECT_DIR}/Core/Application/UserInterface/UserInterface.c
${PROJECT_DIR}/Core/Application/SessionManager/SessionManager.c
${PROJECT_DIR}/Core/Middleware/COMAdapter/COM_Adapter.c
${PROJECT_DIR}/Core/Middleware/Responder/Responder.c
${PROJECT_DIR}/Core/MCAL/UartDriver/usart.c
${PROJECT_DIR}/Core/Middleware/Parser/Parser.c
${PROJECT_DIR}/Core/CrewStandardServices/HW_Dependent/HWDepServices.c
${PROJECT_DIR}/Core/CrewStandardServices/HW_Independent/HWIndepServices.c
${PROJECT_DIR}/Core/CrewStandardServices/MemoryAccess/MemoryAccess.c
)

# Set Name
set_target_properties(MY_LIB PROPERTIES OUTPUT_NAME CrewConnect)

target_include_directories(MY_LIB SYSTEM PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES})

target_compile_definitions(MY_LIB PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    USE_HAL_DRIVER 
    STM32F103xB)

target_compile_options(MY_LIB PRIVATE
${CPU_PARAMETERS}
    -fvisibility=hidden
    -Wall #warnings
    -Wextra
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter)
