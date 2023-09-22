cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
# set(FLAGS )
message("Build type: "              ${CMAKE_BUILD_TYPE})

set(TOOLCHAIN_PREFIX arm-none-eabi-)
# Define compiler settings
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

project(stm-test)
enable_language(C CXX ASM)

set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m4
    -mfloat-abi=hard
)

set(HAL_DRIVER_SRC)

# Set linker script
set(linker_script_SRC               ${PROJ_PATH}/STM32F303K8TX_FLASH.ld)
# set(linker_script_SRC               ${PROJ_PATH}/STM32L496ZGTXP_FLASH.ld)
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})


string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

add_compile_definitions(STM32F303x8)

set(sources_SRCS)

set(include_path_DIRS
    ${PROJ_PATH}/Core/Inc
    ${PROJ_PATH}/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy
    ${PROJ_PATH}/Drivers/STM32F3xx_HAL_Driver/Inc
    ${PROJ_PATH}/Drivers/CMSIS/Include
    ${PROJ_PATH}/Drivers/CMSIS/Device/ST/STM32F3xx/Include
    # ${PROJ_PATH}/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy
    ${PROJ_PATH}/Core/vl53l1x-stm32-hal-driver/VL53L1X/Inc
    ${PROJ_PATH}/Core/logging


)

file(GLOB sources_SRCS CONFIGURE_DEPENDS ${PROJ_PATH}/Core/Src/*.c)

file(GLOB HAL_DRIVER_SRC CONFIGURE_DEPENDS ${PROJ_PATH}/Drivers/STM32F3xx_HAL_Driver/Src/*.c)

# Executable files
add_executable(${EXECUTABLE} ${sources_SRCS}
    ${HAL_DRIVER_SRC}
    ${PROJ_PATH}/Core/Startup/startup_stm32f303k8tx.s
    ${PROJ_PATH}/Core/vl53l1x-stm32-hal-driver/VL53L1X/Src/vl53l1_platform.c
    ${PROJ_PATH}/Core/vl53l1x-stm32-hal-driver/VL53L1X/Src/vl53l1X_api.c
    ${PROJ_PATH}/Core/vl53l1x-stm32-hal-driver/VL53L1X/Src/vl53l1X_calibration.c
    ${PROJ_PATH}/Core/vl53l1x-stm32-hal-driver/VL53L1X/Src/vl53l1X.c
    ${PROJ_PATH}/Core/logging/logs.c
)

target_include_directories(${EXECUTABLE} PRIVATE ${include_path_DIRS}

)

set(symbols_SYMB
    "DEBUG"
    "USE_HAL_DRIVER"
    "STM32F303x8"
)

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${symbols_SYMB})


# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -O2
    -g3 -ggdb
    -fdata-sections -ffunction-sections
    # Full debug configuration
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    # $<$<CONFIG:Debug>: -Og -g3 -ggdb>
    # $<$<CONFIG:Release>: -O2 -g0>
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
    -T${linker_script_SRC}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    --specs=nano.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

