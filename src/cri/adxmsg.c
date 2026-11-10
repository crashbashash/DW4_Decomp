typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

extern int DAT_004a52c0;

int FUN_002743c0();
int FUN_00276e30();
int vsprintf(char *buffer, const char *format, va_list args);
void FUN_0010d108(const char *format, ...);

int FUN_00265868(void) {
    return DAT_004a52c0;
}

void FUN_00265878(int level) {
    DAT_004a52c0 = level;
    FUN_00276e30();
    FUN_002743c0(level);
}

void FUN_002658a8(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (DAT_004a52c0 != 2) {
        vsprintf(buffer, format, args);
        FUN_0010d108(buffer);
    }
    va_end(args);
}

void FUN_00265928(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (DAT_004a52c0 == 0) {
        vsprintf(buffer, format, args);
        FUN_0010d108(buffer);
    }
    va_end(args);
}

void FUN_002659a0(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    if (DAT_004a52c0 != 2) {
        vsprintf(buffer, format, args);
        FUN_0010d108(buffer);
    }
    va_end(args);
}
