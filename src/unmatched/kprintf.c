typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)__builtin_next_arg(last) - (8 - __builtin_args_info(0)) * 8)
int FUN_0010cad8(const char *, va_list);
int kprintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    return FUN_0010cad8(fmt, ap);
}
