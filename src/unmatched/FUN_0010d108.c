typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)__builtin_next_arg(last) - (8 - __builtin_args_info(0)) * 8)
int FUN_0010cad8(const char *, va_list);
int deci2Putchar(int);
extern int (*DAT_00481e64)(int);
int FUN_0010d108(const char *fmt, ...) {
    va_list ap;
    int r;
    int (*old)(int) = DAT_00481e64;
    DAT_00481e64 = deci2Putchar;
    va_start(ap, fmt);
    r = FUN_0010cad8(fmt, ap);
    DAT_00481e64 = old;
    return r;
}
