/* 0x001251c8 — FUN_001251c8 (84 bytes). Variadic front end: forwards (stream, format, ...) to FUN_0012c858 as a
 * va_list, the shape of newlib's fiprintf over vfiprintf (hypothesis; FUN_00125220 is the same over vfprintf).
 * Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef __builtin_va_list va_list;

int FUN_0012c858(void *stream, const char *format, va_list args);

int FUN_001251c8(void *stream, const char *format, ...) {
    va_list args;
    int ret;

    __builtin_stdarg_start(args, format);
    ret = FUN_0012c858(stream, format, args);
    __builtin_va_end(args);
    return ret;
}
