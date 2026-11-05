/* 0x001284c8 — FUN_001284c8 (92 bytes). Reentrant variadic print: forwards (state, format, ...) to FUN_0012d640
 * with the state block's output stream (+8) and a va_list. The shape of newlib's _printf_r (hypothesis).
 * Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef __builtin_va_list va_list;

typedef struct LibState1284c8 {
    int error;          /* +0 */
    void *in;           /* +4 */
    void *out;          /* +8 */
} LibState1284c8;

int FUN_0012d640(LibState1284c8 *state, void *stream, const char *format, va_list args);

int FUN_001284c8(LibState1284c8 *state, const char *format, ...) {
    va_list args;
    int ret;

    __builtin_stdarg_start(args, format);
    ret = FUN_0012d640(state, state->out, format, args);
    __builtin_va_end(args);
    return ret;
}
