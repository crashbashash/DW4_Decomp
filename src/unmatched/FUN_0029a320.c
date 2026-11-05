/* 0x0029a320 — FUN_0029a320 (148 bytes). MWSFD error report: formats the message into a 256-byte buffer with FUN_0012fde0 (vsprintf-shaped: buffer, format, va_list) and passes it to FUN_0029a3e8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef __builtin_va_list va_list;

void *memset(void *, int, unsigned int);
int FUN_0012fde0();
void FUN_0029a3e8(char *message);

extern char DAT_0057f980[256]; /* formatted message */

void FUN_0029a320(const char *format, ...) {
    va_list args;

    memset(DAT_0057f980, 0, sizeof(DAT_0057f980));
    __builtin_stdarg_start(args, format);
    FUN_0012fde0(DAT_0057f980, format, args);
    FUN_0029a3e8(DAT_0057f980);
    __builtin_va_end(args);
}
