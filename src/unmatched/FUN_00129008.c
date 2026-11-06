/* Reentrant wrapper: clears the global error word, calls FUN_0010b528 with the remaining three
 * arguments and, when it fails with -1 and set an error, copies that error into the caller's state
 * block. The result is a 64-bit `long`, which is what moves it through v1. */
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
