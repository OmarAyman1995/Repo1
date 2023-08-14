set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX C:/devtools/arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi/bin/arm-none-eabi-)
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

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Core/Startup/startup_stm32f103c8tx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)

project(ACCU3)
###############################################################################
set(EXECUTABLE ACCU3)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# set(CMAKE_BUILD_TYPE REALEASE)
###############################################################################
set(STM32CUBEMX_INCLUDE_DIRECTORIES
${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc
    )


set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/*.c)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)

add_executable(${EXECUTABLE} 
               ${STM32CUBEMX_SOURCES} 
               ${PROJET_SOURCES} 
               ${STARTUP_SCRIPT})

target_compile_definitions(${EXECUTABLE} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
    USE_HAL_DRIVER 
    STM32F103xB)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES})

target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})
###############################################################################
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
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)


set(BIN_FILE ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin)
set(FLASH C:/devtools/stlink-1.7.0-i686-w64-mingw32/bin/st-flash.exe)

add_custom_target(flash
    COMMAND ${CMAKE_COMMAND} -E echo "Flashing ${BIN_FILE} with st-flash"
    COMMAND ${FLASH} write ${BIN_FILE} 0x8000000
)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()
