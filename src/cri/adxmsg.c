#include "dw4/libkernl.h"
#include "dw4/cri/adxmsg.h"
#include "dw4/cri/dvci.h"
#include "dw4/cri/htci.h"
#include "dw4/newlib_stdio.h"


int adxmsg_level = 0;


int ADXPS2_GetOutputDebugLevel(void) {
    return adxmsg_level;
}

void ADXPS2_SetOutputDebugLevel(int level) {
    adxmsg_level = level;
    htCiSetOutputDebugLevel(level);
    dvCiSetOutputDebugLevel(level);
}

void ADXPS2_PrintfErr(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (adxmsg_level != 2) {
        vsprintf(buffer, format, args);
        scePrintf(buffer);
    }
    va_end(args);
}

void ADXPS2_PrintfWarn(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (adxmsg_level == 0) {
        vsprintf(buffer, format, args);
        scePrintf(buffer);
    }
    va_end(args);
}

void ADXMSG_PrintErr(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (adxmsg_level != 2) {
        vsprintf(buffer, format, args);
        scePrintf(buffer);
    }
    va_end(args);
}
