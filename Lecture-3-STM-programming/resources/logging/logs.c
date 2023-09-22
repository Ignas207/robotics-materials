#include "logs.h"

static void WriteLogFile(const char* msg, uint32_t len);


void LogWrite(const char *type,
                    const char *fileName,
                    const uint16_t lineNumber,
                    const char *fmt, ...)
{
    uint32_t retSize;
    va_list argp;
    char logStr[LOGS_MAX_LENGHT] = {0};

    // memset(logStr, 0, LOGS_MAX_LENGHT);
    // Writing the starting portion
    retSize = snprintf(logStr, LOGS_MAX_LENGHT, "%s (%s:%d): ", type, fileName, lineNumber);

    // Writing the VA_ARGS
    va_start(argp, fmt);
    vsnprintf(logStr + retSize, LOGS_MAX_LENGHT - retSize, fmt, argp);
    va_end(argp);
    
    WriteLogFile(logStr, LOGS_MAX_LENGHT);
}


static void WriteLogFile(const char* msg, uint32_t len)
{
    // #error Implement this!
    HAL_UART_Transmit(&huart2, (const uint8_t*)msg, len, 1000);
}
