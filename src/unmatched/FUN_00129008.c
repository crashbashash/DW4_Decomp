/* 0x00129008 — FUN_00129008 (96 bytes). Reentrant wrapper: clears the global error word, calls FUN_0010b528 with
 * the remaining three arguments and, when it fails with -1 and set an error, copies that error into the caller's
 * state block. The shape of newlib's _read_r/_write_r family (hypothesis; the 64-bit `long` result is newlib's
 * _ssize_t, which is what moves the result through v1). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct LibState129008 { int error; } LibState129008;

extern int D_0058d244;  /* global error word set by the low-level call */
int FUN_0010b528(int a, int b, int c);

long FUN_00129008(LibState129008 *state, int a, int b, int c) {
    long ret;

    D_0058d244 = 0;
    if ((ret = (long)FUN_0010b528(a, b, c)) == -1 && D_0058d244 != 0) {
        state->error = D_0058d244;
    }
    return ret;
}
