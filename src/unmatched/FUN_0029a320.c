/* MWSFD error report: formats the message into a 256-byte buffer with vsprintf (vsprintf-
 * shaped: buffer, format, va_list) and passes it to FUN_0029a3e8. */
typedef __builtin_va_list va_list;

void *memset(void *, int, unsigned int);
int vsprintf();
void FUN_0029a3e8(char *message);

extern char DAT_0057f980[256]; /* formatted message */

void FUN_0029a320(const char *format, ...) {
    va_list args;

    memset(DAT_0057f980, 0, sizeof(DAT_0057f980));
    __builtin_stdarg_start(args, format);
    vsprintf(DAT_0057f980, format, args);
    FUN_0029a3e8(DAT_0057f980);
    __builtin_va_end(args);
}
