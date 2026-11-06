/* Reentrant wrapper: clears the global error word, calls FUN_0010b5d8 with the remaining three
 * arguments and, when it fails with -1 and set an error, copies that error into the caller's state
 * block. Unlike FUN_00129008 the result stays an int. */
typedef struct LibState125fc8 { int error; } LibState125fc8;

extern int D_0058d244;  /* global error word set by the low-level call */
int FUN_0010b5d8(int file, int offset, int whence);

int FUN_00125fc8(LibState125fc8 *state, int file, int offset, int whence) {
    int ret;

    D_0058d244 = 0;
    if ((ret = FUN_0010b5d8(file, offset, whence)) == -1 && D_0058d244 != 0) {
        state->error = D_0058d244;
    }
    return ret;
}
