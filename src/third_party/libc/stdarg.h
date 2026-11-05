#ifndef DW4_LIBC_STDARG_H
#define DW4_LIBC_STDARG_H
#ifdef __cplusplus
extern "C" {
#endif
typedef char *va_list;
/* MWCC spills the named register arguments below the variadic ones: __builtin_args_info(2) counts
 * them and __builtin_next_arg gives the end of the area. */
#define va_start(ap, last) \
    ((ap) = (char *)__builtin_next_arg(last) - \
            (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define va_end(ap) ((void)0)
#ifdef __cplusplus
}
#endif
#endif
