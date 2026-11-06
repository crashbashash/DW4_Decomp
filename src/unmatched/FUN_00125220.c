/* Variadic front end: forwards (stream, format, ...) to vfprintf as a va_list. */
typedef __builtin_va_list va_list;

int vfprintf(void *stream, const char *format, va_list args);

int FUN_00125220(void *stream, const char *format, ...) {
    va_list args;
    int ret;

    __builtin_stdarg_start(args, format);
    ret = vfprintf(stream, format, args);
    __builtin_va_end(args);
    return ret;
}
