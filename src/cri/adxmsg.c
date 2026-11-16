typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

int adxmsg_level = 0;

int dvCiSetOutputDebugLevel();
int htCiSetOutputDebugLevel();
int vsprintf(char *buffer, const char *format, va_list args);
void scePrintf(const char *format, ...);

int FUN_00265868(void) {
    return adxmsg_level;
}

void FUN_00265878(int level) {
    adxmsg_level = level;
    htCiSetOutputDebugLevel();
    dvCiSetOutputDebugLevel(level);
}

void FUN_002658a8(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (adxmsg_level != 2) {
        vsprintf(buffer, format, args);
        scePrintf(buffer);
    }
    va_end(args);
}

void FUN_00265928(const char *format, ...) {
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
