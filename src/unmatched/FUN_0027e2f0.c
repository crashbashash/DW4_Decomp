/* SVM error report: formats the message into a 128-byte buffer with vsprintf (vsprintf-shaped:
 * buffer, format, va_list) and hands it to the registered error callback. */
typedef __builtin_va_list va_list;

void *memset(void *, int, unsigned int);
int vsprintf();

struct ErrorCallback0027e2f0 {
    void (*fn)(int arg, char *message); /* +0 */
    int arg;                            /* +4 */
};

extern char DAT_004bb040[128];                     /* formatted message */
extern struct ErrorCallback0027e2f0 DAT_00570bb0;  /* error callback */

void FUN_0027e2f0(const char *format, ...) {
    va_list args;

    memset(DAT_004bb040, 0, sizeof(DAT_004bb040));
    __builtin_stdarg_start(args, format);
    vsprintf(DAT_004bb040, format, args);
    if (DAT_00570bb0.fn != 0) {
        DAT_00570bb0.fn(DAT_00570bb0.arg, DAT_004bb040);
    }
    __builtin_va_end(args);
}
