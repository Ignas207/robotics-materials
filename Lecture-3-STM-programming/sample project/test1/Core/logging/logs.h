#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "usart.h"
#include "stm32f3xx_hal_uart.h"

#define LOGS_MAX_LENGHT 512U

/*
    Gets the path RELATIVE to CMakeLists!
    For this to work need to add the following to CMakeLists.txt!
    -------------------------------------------------------------
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
    add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
    -------------------------------------------------------------
*/
#ifndef SOURCE_PATH_SIZE
    #warning SOURCE_PATH_SIZE is not defined! You have to set it youself, in "logs.h"!
    #define SOURCE_PATH_SIZE 0
#endif



#define __FILENAME__ (__FILE__ + SOURCE_PATH_SIZE)

/**
 * @brief Writes an 'Event' message to the terminal.
 * 
 */
#define LOG_EVENT(fmt, ...)((LogWrite("EVENT", __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))

/**
 * @brief Writes an 'Info' message to the terminal.
 * 
*/
#define LOG_INFO(fmt, ...)((LogWrite("INFO", __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))

/**
 * @brief Writes an 'Error' message to the terminal.
 * 
 */
#define LOG_ERROR(fmt, ...)((LogWrite("ERROR", __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)))

/**
 * @warning Do not use this on its own!
 */
void LogWrite(const char *type,
                    const char *fileName,
                    const uint16_t lineNumber,
                    const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
