/* printf-style error report: formats the arguments into the message buffer DAT_004abb50 with
 * vsprintf and passes it to the registered error callback DAT_004abb48 (with its object
 * DAT_004abb4c), if any. */
/* ee-gcc ships no stdarg.h here: the compiler builtins stand in for it. */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

extern void (*DAT_004abb48)(int object, const char *message);
extern int DAT_004abb4c;
extern char DAT_004abb50[];
int vsprintf(char *buffer, const char *format, va_list args);

void FUN_002777f8(const char *format, ...) {
    va_list args;

    va_start(args, format);
    vsprintf(DAT_004abb50, format, args);
    va_end(args);
    if (DAT_004abb48 != 0) {
        DAT_004abb48(DAT_004abb4c, DAT_004abb50);
    }
}
