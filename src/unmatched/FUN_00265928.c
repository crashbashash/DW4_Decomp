/* printf-style message: unless DAT_004a52c0 is set, formats the arguments into a 128-byte buffer
 * with vsprintf and prints it with FUN_0010d108. */
/* ee-gcc ships no stdarg.h here: the compiler builtins stand in for it. */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

extern int DAT_004a52c0;
void vsprintf(char *buffer, const char *format, va_list args);
void FUN_0010d108(const char *text);

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
